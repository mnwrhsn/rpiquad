#ifndef __RRM_SOS_OS_ARCH_H_
#define __RRM_SOS_OS_ARCH_H_

#define __OS_INIT_STACK(stack, taskf, data) \
{ \
	uint16 address;		\
	*stack-- = 0xD8;	\
				\
	/*pushing address, poped by ret/reti call in PC */	\
	address = (uint16) taskf;	\
	*stack-- = lo8(address);	\
	*stack-- = hi8(address);	\
					\
	*stack-- = 0x00;	/*r0 */	\
	*stack-- = 0x80;	/*SERG : sei*/	\
	*stack-- = 0x00;	/*r1*/	\
	*stack-- = 0x00;	/*r2*/	\
	*stack-- = 0x00;	/*r3*/	\
	*stack-- = 0x00;	/*r4*/	\
	*stack-- = 0x00;	/*r5*/	\
	*stack-- = 0x00;	/*r6*/	\
	*stack-- = 0x00;	/*r7*/	\
	*stack-- = 0x00;	/*r8*/	\
	*stack-- = 0x00;	/*r9*/	\
	*stack-- = 0x00;	/*r10*/	\
	*stack-- = 0x00;	/*r11*/	\
	*stack-- = 0x00;	/*r12*/	\
	*stack-- = 0x00;	/*r13*/	\
	*stack-- = 0x00;	/*r14*/	\
	*stack-- = 0x00;	/*r15*/	\
	*stack-- = 0x00;	/*r16*/	\
	*stack-- = 0x00;	/*r17*/	\
	*stack-- = 0x00;	/*r18*/	\
	*stack-- = 0x00;	/*r19*/	\
	*stack-- = 0x00;	/*r20*/	\
	*stack-- = 0x00;	/*r21*/	\
	*stack-- = 0x00;	/*r22*/	\
	*stack-- = 0x00;	/*r23*/	\
					\
	address = (uint16) data;	/*as per avr-libc*/	\
	*stack-- = lo8(address);	/*r24*/	\
	*stack-- = hi8(address);	/*r25*/	\
						\
	*stack-- = 0x00;	/*r26*/	\
	*stack-- = 0x00;	/*r27*/	\
	*stack-- = 0x00;	/*r28*/	\
	*stack-- = 0x00;	/*r29*/	\
	*stack-- = 0x00;	/*r30*/	\
	*stack-- = 0x00;	/*r31*/	\
}

//store register context
#define __OS_SAVE_ALL_REGS() \
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
            ::)

//restore register context
#define __OS_RESTORE_ALL_REGS() \
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
            ::)

#define OS_ENTER_CRITICAL() \
    __asm__ volatile ( \
            "in         __tmp_reg__, __SREG__   \n\t" \
            "cli        \n\t" \
            "push       __tmp_reg__     \n\t" \
            ::)

#define OS_EXIT_CRITICAL() \
    __asm__ volatile ( \
            "pop        __tmp_reg__     \n\t" \
            "out        __SREG__, __tmp_reg__   \n\t" \
            ::)

#define OS_IRQ_DISABLE() \
    __asm__ volatile ( \
            "cli        \n\t" \
            ::)

#define OS_IRQ_ENABLE() \
    __asm__ volatile ( \
            "sei        \n\t" \
            ::)

//definition currently in os_task.c.. move it to os_arch.c
extern volatile void *current;
extern void *kstack;	//constant anyway!!

//TODO this shud really go in <arch>/ __SP_H__ n __SP_L__ is not directly copied
//TODO verify current->stacktop is updating by following steps
#define __OS_SAVE_SP() \
    __asm__ volatile ( \
	    "lds        r26, current		\n\t" \
	    "lds        r27, current + 1	\n\t" \
	    "in		r0, __SP_L__		\n\t" \
	    "st		x+, r0			\n\t" \
	    "in 	r0, __SP_H__		\n\t" \
	    "st		x+, r0			\n\t" \
	    ::)

//all kernel functions (ISR's) need to be atomic
#define __OS_SAVE_KERN()	{}	//no need to store current stack!!!

#define __OS_LOAD_SP() \
    __asm__ volatile ( \
            "lds        r26, current		\n\t" \
            "lds        r27, current + 1	\n\t" \
            "ld	        r0, x+			\n\t" \
            "out        __SP_L__, r0		\n\t" \
            "ld		r0, x+			\n\t" \
            "out        __SP_H__, r0		\n\t" \		verify TODO
            ::)

//TODO verify __restore_current "st" statement seems to wrong

#define OS_SAVE_CONTEXT() \
{ \
    __OS_SAVE_ALL_REGS(); \
    __OS_SAVE_SP(); \
}

#define OS_LOAD_CONTEXT() \
{ \
    __OS_LOAD_SP(); \
    __OS_RESTORE_ALL_REGS(); \
}

extern void __os_init_peri(void);
extern void __os_init_timer0(void);
extern void __os_init_ports(void);

//stack_top, task_function, data
extern uint8 *__os_init_stack(uint8 *, void *, void *);

#endif //__RRM_SOS_OS_ARCH_H_
