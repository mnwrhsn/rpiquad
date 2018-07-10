#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#include "pifly_global.h"
#include "pifly_comm.h"
#include "pifly_motion.h"
#include "pifly_pid.h"
#include "pifly_controller.h"

/*
 * Timer to handle PID loop, current frequency 250Hz
 * 500Hz = 2ms / 250Hz = 4ms / 100Hz = 10ms
 * 1ms = 1000000nsec
 * IMPORTANT: as IMU (mpu-6050) refresh rate is 1kHz, PID loop should have lesser frequency
 */

static void __pid_loop_alarm_handler(int signo, siginfo_t *info, void *ctx)
{
	pifly_global_t *gl = info->si_value.sival_ptr;
	printf("pifly_controller: __pid_loop_alarm_handler() start\n");
	//1. read IMU motion data
	//2. read flight control data (Yaw, Pitch, Roll & Throttle)
	//3. Compute PID
	//4. motor control
	pifly_motor_set(&(gl->motor_dev));

	printf("pifly_controller: __pid_loop_alarm_handler() end\n");
}

static int __pifly_timer_event_init(pifly_global_t *gl)
{
	int rv = 0;
	struct sigevent sevent;
	struct sigaction sact;

	sevent.sigev_notify = SIGEV_SIGNAL;
	sevent.sigev_signo = SIGALRM;
	sevent.sigev_value.sival_ptr = (void *) gl;

	sigemptyset(&(sact.sa_mask));
	sigaddset(&(sact.sa_mask), SIGALRM);

	sact.sa_flags = SA_SIGINFO;
	sact.sa_sigaction = __pid_loop_alarm_handler;

	sigaction(SIGALRM, &sact, NULL);

	if (timer_create(CLOCK_REALTIME, &sevent, &(gl->loop_tid))) {
		printf("pifly_controller: pifly_controller_init(), timer_create() failed\n");
		rv = -EINVAL;
	}

	return rv;
}

static void __pifly_timer_event_exit(pifly_global_t *gl)
{
	timer_delete(gl->loop_tid);
}

int pifly_controller_init(pifly_global_t *gl)
{
	int rv = 0;

	if ((rv = __pifly_timer_event_init(gl)) < 0)
		return rv;

	if ((rv = imu_device_init(gl)) < 0)
		goto imu_error;

	if ((rv = pifly_pid_init(gl)) < 0)
		goto pid_error;

	if ((rv = pifly_motor_init(&(gl->motor_dev))) < 0)
		goto motor_error;

	return rv;

motor_error:
	pifly_pid_exit(gl);
pid_error:
	imu_device_exit(gl);
imu_error:
	__pifly_timer_event_exit(gl);

	return rv;
}

void pifly_controller_exit(pifly_global_t *gl)
{
	pifly_motor_ctrl_exit(gl);
	pifly_pid_exit(gl);
	imu_device_exit(gl);
	__pifly_timer_event_exit(gl);
}

void pifly_controller_start(pifly_global_t *gl)
{
	struct itimerspec tspec = {
		.it_interval = {
			.tv_sec = 0,
			.tv_nsec = 10000000,	//100Hz TODO: 250Hz and 500Hz
		},
		.it_value = {
			.tv_sec = 5,		//arms after 5 sec
			.tv_nsec = 0,
		}
	};

	if (timer_settime(&(gl->loop_tid), 0, &tspec, NULL)) {
		printf("pifly_controller: pifly_controller_start(), timer_settime() failed\n");
		exit(-EINVAL);
	}

	while(1);	//point of no return
}
