#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

/*
 * Purpose : create timer event to fire every 2milliseconds
 * 500Hz = 2ms / 250Hz = 4ms / 100Hz = 10ms
 * 1ms = 1000000nsec
 * gcc -o timer_example rpi_timer_event.c -lrt
 */

struct pifly_global_s {
	uint32_t X;	//0xdeadbeef
	uint32_t Y;	//0xbaaaaaad
	uint32_t Z;	//0xcafed00d

	uint32_t T;	//0xdeadc0de
};

static void __alarm_handler(int signo, siginfo_t *info, void *ctx)
{
	static uint32_t count = 0;
	struct pifly_global_s *gl = (struct pifly_global_s *) info->si_value.sival_ptr;

	count++;
	printf("X: %x Y: %x Z: %x T: %x\n", gl->X, gl->Y, gl->Z, gl->T);
	printf("__alarm_handler: called %u times\n", count);
}

int main(void)
{
	timer_t tid;	//timer ID
	struct itimerspec tspec = {
		.it_interval = {
			.tv_sec = 0,
			.tv_nsec = 100000000,	//250Hz
		},
		.it_value = {
			.tv_sec = 5,		//arms after # sec
			.tv_nsec = 0,
		}
	};

	struct sigevent sevent;
	struct sigaction saction;
	sigset_t sigset;

	struct pifly_global_s gl = {
		.X = 0xdeadbeef,
		.Y = 0xbaaaaaad,
		.Z = 0xcafed00d,
		.T = 0xdeadc0de,
	};

	sevent.sigev_notify = SIGEV_SIGNAL;
	sevent.sigev_signo = SIGALRM;
	sevent.sigev_value.sival_ptr = (void *) &gl;

	sigemptyset(&(saction.sa_mask));
	sigaddset(&(saction.sa_mask), SIGALRM);
	saction.sa_flags = SA_SIGINFO;
	saction.sa_sigaction = __alarm_handler;

	sigaction(SIGALRM, &saction, NULL);

	if (timer_create(CLOCK_REALTIME, &sevent, &tid))
		perror("timer_create");

	if (timer_settime(&tid, 0, &tspec, NULL))
		perror("timer_settime");

	while(1);

	return 0;
}
