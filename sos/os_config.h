#ifndef __RRM_SOS_OS_CONFIG_H_
#define __RRM_SOS_OS_CONFIG_H_

#include <avr/io.h>
#include <avr/signal.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <avr/iom128.h>         //TODO whts this for??

//http://www.nongnu.org/avr-libc/user-manual/FAQ.html

#define int8 	char
#define uint8 	unsigned char
#define int16 	int               //confirmd in avr gcc manual
#define uint16 	unsigned int
#define int32 	long
#define uint32 	unsigned long
#define int64 	long long
#define uint64 	unsigned long long

//float/double 32 bits, pointer 16 bits

#define OS_CONFIG_STACK_DEFAULT_SIZE 	128
#define OS_CONFIG_STACK_IDLE_SIZE 	64
#define OS_CONFIG_STACK_KERN_SIZE 	64

#define OS_CONFIG_TASK_PRIO_HIGH1 	0
#define OS_CONFIG_TASK_PRIO_HIGH2 	1
#define OS_CONFIG_TASK_PRIO_MEDI1 	2
#define OS_CONFIG_TASK_PRIO_MEDI2 	3
#define OS_CONFIG_TASK_PRIO_MEDI3 	4
#define OS_CONFIG_TASK_PRIO_LOW1 	5
#define OS_CONFIG_TASK_PRIO_LOW2 	6
#define OS_CONFIG_TASK_PRIO_IDLE 	7

#define OS_CONFIG_MAX_TASKS 		0x07   //not more than 7 (as of now)
#define OS_CONFIG_MAX_PRIOS 		0x08

#define OS_CONFIG_TASK_STATE_STOPD 	0x00	//default state while creating n initing a task
#define OS_CONFIG_TASK_STATE_READY 	0x01	//after task creation it's marked "ready" for running
#define OS_CONFIG_TASK_STATE_RUNIG 	0x02	//currently getting executed
#define OS_CONFIG_TASK_STATE_WAITG 	0x03	//waiting for event (sema or else)

#endif //__RRM_SOS_OS_CONFIG_H_
