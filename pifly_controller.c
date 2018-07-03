#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#include "pifly_global.h"
#include "pifly_controller.h"
#include "pifly_pid.h"

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
	pid_feedback_loop(gl);
	printf("pifly_controller: __pid_loop_alarm_handler() end\n");
}

int pifly_controller_init(pifly_global_t *gl)
{
	int rv = 0;
	struct sigevent seve;		//TODO
	struct sigaction sact;

	//TODO set sigevent
	seve.sigev_value.sival_ptr = (void *) gl

	sigemptyset(&(sact.sa_mask));
	sigaddset(&(sact.sa_mask), SIGALRM);

	sact.sa_flags = SA_SIGINFO;
	sact.sa_sigaction = __pid_loop_alarm_handler;

	sigaction(SIGALRM, &sact, NULL);

	if (timer_create(CLOCK_REALTIME, NULL, &(gl->loop_tid))) {
		printf("pifly_controller: pifly_controller_init(), timer_create() failed\n");
		rv = -EINVAL;
	}

	return rv;
}

int pifly_controller_start(pifly_global_t *gl)
{
	int rv = 0;
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
		rv = -EINVAL;
	}

	return rv;
}
