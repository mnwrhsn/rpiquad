#ifndef __RRM_SOS_OS_TASK_H_
#define __RRM_SOS_OS_TASK_H_

#include "os_config.h"
#include "os_arch.h"
#include "os_sem.h"


typedef struct __task_control
{
	volatile uint8 *stacktop;	//always the first value
	uint8 *stackbottom;		//bottom of the stack

	uint8 stacksz;			//limiting to 255
	uint8 bprio;			//base priority
	/*in case elevted priority (priority inversion), task can return to runqueue position based on base priority*/
	uint8 state;			//task state

	//struct __task_control *next;	//next tcb (to be used for elev_prio tcbs)
	void *data;
}task_control_t;

//macro for declaring task, tcb and stack
#define DECLARE_TASK(name, ssize) \
    static uint8 name##_stack[ssize]; \
    static task_control_t name##_tcb = {\
	    .stacktop = &(name##_stack[ssize - 1]), \
	    .stackbottom = &(name##_stack[ssize - 1]), \
	    .stacksz = ssize, \
	    .base_prio = OS_CONFIG_TASK_PRIO_LOW2, \
	    .state = OS_CONFIG_TASK_STATE_STOPD, \
    };

//initialization funtion, starts with disabling irq
//setup the timer
extern void os_init(void) __attribute__ ((constructor));	//XXX rechk attribute

//start the timer, load current task
extern void os_start(void) __attribute__ ((naked));

typedef void (*taskfn) (void *);
//task_function, data, priority
extern void os_task_create(task_control_t *, taskfn, void *, uint8);

#define CREATE_TASK(name, taskfn, dp, prio) \
{ \
	name##_tcb.data = dp;	\
	os_task_create(&(name##_tcb), taskfn, data, prio); \
}

#endif //__RRM_SOS_OS_TASK_H_
