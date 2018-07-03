#ifndef __RRM_PIFLY_PID_H_
#define __RRM_PIFLY_PID_H_

#include "pifly_global.h"

extern int pid_feedback_init(pifly_global *);
extern void pid_feedback_loop(pifly_global_t *);

#endif //__RRM_PIFLY_PID_H_
