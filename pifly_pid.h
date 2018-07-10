#ifndef __RRM_PIFLY_PID_H_
#define __RRM_PIFLY_PID_H_

#include "pifly_global.h"

extern int pifly_pid_init(pifly_global_t *);
extern void pifly_pid_compute(pifly_global_t *);
extern void pifly_pid_exit(pifly_global_t *);

#endif //__RRM_PIFLY_PID_H_
