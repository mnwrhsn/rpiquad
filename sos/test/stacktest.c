#include <stdio.h>

#include "../rrm_config.h"
#include "../os_config.h"

/*
   for checking task switching functionality
   task 1: blink led from 0 -> 3
   task 2: blink led from 4 -> 7
 */

#define MY_STACK_SIZE	128

typedef struct __task_control {
	volatile uint8_t *stacktop;	//stack top
	uint8_t *stack;		//stack starting
	uint8_t ssize;		//stack size
}task_control_t;

static task_control_t task1;
static task_control_t task2;

static uint8_t t1stack[MY_STACK_SIZE];
static uint8_t t2stack[MY_STACK_SIZE];

task_control_t *current = NULL;	//current runnable task
task_control_t *other = NULL;		//next runnable task (test code, not making use of find runnable function)

typedef void (*taskf)(void *);

//stackb bottom pointer, task function pointer
#define __init_stack(stackb, __task) \
{ \
	uint16_t address = 0; \
	*stackb-- = 0xD8; \
	\
	address = (uint16_t) __task; \
	*stackb-- = lo8(address); \
	*stackb-- = hi8(address); \
	\
	*stackb-- = 0x00;	/*r0 */	\
	*stackb-- = 0x80;	/*SERG : sei*/	\
	*stackb-- = 0x00;	/*r1*/	\
	*stackb-- = 0x00;	/*r2*/	\
	*stackb-- = 0x00;	/*r3*/	\
	*stackb-- = 0x00;	/*r4*/	\
	*stackb-- = 0x00;	/*r5*/	\
	*stackb-- = 0x00;	/*r6*/	\
	*stackb-- = 0x00;	/*r7*/	\
	*stackb-- = 0x00;	/*r8*/	\
	*stackb-- = 0x00;	/*r9*/	\
	*stackb-- = 0x00;	/*r10*/	\
	*stackb-- = 0x00;	/*r11*/	\
	*stackb-- = 0x00;	/*r12*/	\
	*stackb-- = 0x00;	/*r13*/	\
	*stackb-- = 0x00;	/*r14*/	\
	*stackb-- = 0x00;	/*r15*/	\
	*stackb-- = 0x00;	/*r16*/	\
	*stackb-- = 0x00;	/*r17*/	\
	*stackb-- = 0x00;	/*r18*/	\
	*stackb-- = 0x00;	/*r19*/	\
	*stackb-- = 0x00;	/*r20*/	\
	*stackb-- = 0x00;	/*r21*/	\
	*stackb-- = 0x00;	/*r22*/	\
	*stackb-- = 0x00;	/*r23*/	\
	\
	*stackb-- = 0x00;	/*r24*/	\
	*stackb-- = 0x00;	/*r25*/	\
	\
	*stackb-- = 0x00;	/*r26*/	\
	*stackb-- = 0x00;	/*r27*/	\
	*stackb-- = 0x00;	/*r28*/	\
	*stackb-- = 0x00;	/*r29*/	\
	*stackb-- = 0x00;	/*r30*/	\
	*stackb-- = 0x00;	/*r31*/	\
}

#define __save_all_regs() \
{ \
	__asm__ volatile ( \
		"push       r0      \n\t" \
		"in         r0, __SREG__    \n\t" \
		"cli                \n\t" \
		"push       r0      \n\t" \
		"push       r1      \n\t" \
		"clr        r1      \n\t" \
		"push       r2      \n\t" \
		"push       r3      \n\t" \
		"push       r4      \n\t" \
		"push       r5      \n\t" \
		"push       r6      \n\t" \
		"push       r7      \n\t" \
		"push       r8      \n\t" \
		"push       r9      \n\t" \
		"push       r10     \n\t" \
		"push       r11     \n\t" \
		"push       r12     \n\t" \
		"push       r13     \n\t" \
		"push       r14     \n\t" \
		"push       r15     \n\t" \
		"push       r16     \n\t" \
		"push       r17     \n\t" \
		"push       r18     \n\t" \
		"push       r19     \n\t" \
		"push       r20     \n\t" \
		"push       r21     \n\t" \
		"push       r22     \n\t" \
		"push       r23     \n\t" \
		"push       r24     \n\t" \
		"push       r25     \n\t" \
		"push       r26     \n\t" \
		"push       r27     \n\t" \
		"push       r28     \n\t" \
		"push       r29     \n\t" \
		"push       r30     \n\t" \
		"push       r31     \n\t" \
		::); \
}

#define __load_all_regs() \
{ \
	__asm__ volatile ( \
		"pop        r31     \n\t" \
		"pop        r30     \n\t" \
		"pop        r29     \n\t" \
		"pop        r28     \n\t" \
		"pop        r27     \n\t" \
		"pop        r26     \n\t" \
		"pop        r25     \n\t" \
		"pop        r24     \n\t" \
		"pop        r23     \n\t" \
		"pop        r22     \n\t" \
		"pop        r21     \n\t" \
		"pop        r20     \n\t" \
		"pop        r19     \n\t" \
		"pop        r18     \n\t" \
		"pop        r17     \n\t" \
		"pop        r16     \n\t" \
		"pop        r15     \n\t" \
		"pop        r14     \n\t" \
		"pop        r13     \n\t" \
		"pop        r12     \n\t" \
		"pop        r11     \n\t" \
		"pop        r10     \n\t" \
		"pop        r9      \n\t" \
		"pop        r8      \n\t" \
		"pop        r7      \n\t" \
		"pop        r6      \n\t" \
		"pop        r5      \n\t" \
		"pop        r4      \n\t" \
		"pop        r3      \n\t" \
		"pop        r2      \n\t" \
		"pop        r1      \n\t" \
		"pop        r0      \n\t" \
		"out        __SREG__, r0      \n\t" \
		"pop        r0      \n\t" \
		::); \
}

#define __save_sp() \
{ \
	__asm__ volatile ( \
		"lds	r26, current		\n\t" \
		"lds	r27, current + 1	\n\t" \
		"in	r0, __SP_L__		\n\t" \
		"out	x+, r0			\n\t" \
		"in	r0, __SP_H__		\n\t" \
		"out	x+, r0			\n\t" \
		::	); \
}

#define __load_sp() \
{ \
	__asm__ volatile ( \
		"lds	r26, current		\n\t" \
		"lds	r27, current + 1	\n\t" \
		"ld	r0, x+			\n\t" \
		"out	__SP_L__, r0		\n\t" \
		"ld	r0, x+			\n\t" \
		"out	__SP_H__, r0		\n\t" \
		::	); \
}

#define __save_ctx() \
{ \
	__save_all_regs(); \
	__save_sp(); \
}

#define __load_ctx() \
{ \
	__load_sp(); \
	__load_all_regs(); \
}

static __start(void) __attribute__((naked));
static __start(void)
{
	__load_ctx();
	__asm__ volatile ("ret	\n\t" ::);	//should pop function address
}

#if 0
static inline void __ctx_switch(void)
{
}
#endif

void __local_delay(void)
{
	uint16_t counter;
	for(counter = 0; counter <= 0xfffe; counter++) {
		__asm__ volatile(
			"nop	\n\t"
			"nop	\n\t"
			"nop	\n\t"
			"nop	\n\t"
			::);
	}
}

void blinker1(void *data)
{
	uint8_t cnt = 0;
	while (1) {
		cnt++;
		PORTC = cnt;
		__local_delay();
	}
}

void blinker2(void *data)
{
	uint8_t cnt = 0;
	while (1) {
		cnt++;
		PORTC = cnt;
		__local_delay();
	}
}

ISR(TIMER0_OVF_vect) //timer0 overflow
{
	task_control_t *tmp = current;
	
	__save_ctx();
	current = other;
	other = tmp;
	__load_ctx();
}

int main(void)
{
	cli();
	task1.stack = t1stack;
	task1.stacktop = t1stack + (MY_STACK_SIZE - 1);

	task2.stack = t2stack;
	task2.stacktop = t2stack + (MY_STACK_SIZE - 1);

	__init_stack((task1.stacktop), blinker1);
	__init_stack((task2.stacktop), blinker2);

	current = &task1;
	other = &task2;

	//init resources
	PORTC = 0x00;
	DDRC = 0xff;

	//setup timer
	AT_T0_OI_ENABLE;
	AT_T0_PRESCALE64;
	AT_T0_CNT_RESET;
	
	//sei(); //no need, load context will automatically set sei
	__start();

	//won't come here
	return 0;
}
