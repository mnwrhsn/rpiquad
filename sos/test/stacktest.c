#include "../rrm_config.h"
#include "../os_config.h"
//#include "../os_task.h"

/*
   for checking task switching functionality
   task 1: blink led from 0 -> 3
   task 2: blink led from 4 -> 7
   load stack
   ldi r16, lo8(function)
   out spl, r16
   ldi r16, hi8(function)
   out sph, r16
 */

#define MY_STACK_SIZE	128

static uint8_t t1stack[MY_STACK_SIZE];
static uint8_t t2stack[MY_STACK_SIZE];

typedef void (*taskf)(void *);

//stackb bottom pointer, task function pointer
static inline void __init_stack(uint8_t *stackb, taskf __task)
{
	uint16_t address = 0;

	*stackb-- = 0xD8;

	address = (uint16_t) __task;
	*stackb-- = lo8(address);
	*stackb-- = hi8(address);

	*stackb-- = 0x00;	/*r0 */	
	*stackb-- = 0x80;	/*SERG : sei*/	
	*stackb-- = 0x00;	/*r1*/	
	*stackb-- = 0x00;	/*r2*/	
	*stackb-- = 0x00;	/*r3*/	
	*stackb-- = 0x00;	/*r4*/	
	*stackb-- = 0x00;	/*r5*/	
	*stackb-- = 0x00;	/*r6*/	
	*stackb-- = 0x00;	/*r7*/	
	*stackb-- = 0x00;	/*r8*/	
	*stackb-- = 0x00;	/*r9*/	
	*stackb-- = 0x00;	/*r10*/	
	*stackb-- = 0x00;	/*r11*/	
	*stackb-- = 0x00;	/*r12*/	
	*stackb-- = 0x00;	/*r13*/	
	*stackb-- = 0x00;	/*r14*/	
	*stackb-- = 0x00;	/*r15*/	
	*stackb-- = 0x00;	/*r16*/	
	*stackb-- = 0x00;	/*r17*/	
	*stackb-- = 0x00;	/*r18*/	
	*stackb-- = 0x00;	/*r19*/	
	*stackb-- = 0x00;	/*r20*/	
	*stackb-- = 0x00;	/*r21*/	
	*stackb-- = 0x00;	/*r22*/	
	*stackb-- = 0x00;	/*r23*/	

	*stackb-- = 0x00;	/*r24*/	
	*stackb-- = 0x00;	/*r25*/	

	*stackb-- = 0x00;	/*r26*/	
	*stackb-- = 0x00;	/*r27*/	
	*stackb-- = 0x00;	/*r28*/	
	*stackb-- = 0x00;	/*r29*/	
	*stackb-- = 0x00;	/*r30*/	
	*stackb-- = 0x00;	/*r31*/	
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
}

#define __load_sp() \
{ \
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

static inline void __ctx_switch(void)
{
}

void blinker1(void *data)
{
	PORTC |= 0x00;
	DDRC |= 0x0f;
	while (1) {

		//switch context
	}
}

void blinker2(void *data)
{
	PORTC |= 0x00;
	DDRC |= 0xf0;
	while (1) {

		//switch context
	}
}

int main(void)
{
	cli();

	sei();
	return 0;
}
