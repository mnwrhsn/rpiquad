//SOS: scheduler related file
#include "os_task.h"
#include "os_config.h"

static task_control_t *__run_queue[SOS_CONFIG_MAX_PRIOS];

#define KERNEL_STACK_SIZE	64

static uint8 __kstack[KERNEL_STACK_SIZE];
void *kstack = &(__kstack[KERNEL_STACK_SIZE - 1]);

#if 0
void __os_add_tcb_node(task_control_t *tcb)
{
    if (!__run_queue[tcb->elev_prio])
        __run_queue[tcb->elev_prio] = tcb;
    else {
        task_control_t *curr = __run_queue[tcb->elev_prio];
        while (curr->next)
            curr = curr->next;
        curr->next = tcb;
        tcb->next = NULL;
    }
}
#endif
void __os_add_tcb_node(task_control_t *tcb)		//ver1.0
{
	__run_queue[tcb->base_prio] = tcb;
}

#if 0	//for ver1.0 i don't need this
void __os_del_tcb_node(task_control_t *tcb)
{
    if (__run_queue[tcb->elev_prio] == tcb)
        __run_queue[tcb->elev_prio] = __run_queue[tcb->elev_prio]->next;
    else {
        task_control_t *curr = __run_queue[tcb->elev_prio];
        while (curr->next) {
            if (curr->next == tcb)
                break;
            curr = curr->next;
        }

        curr->next = tcb->next;
        tcb->next = NULL;
    }
}
#endif

//now need to add init_node
#define __OS_INIT_TCB(tcb) memset((void *) tcb, 0, sizeof(task_control_t))

static void __idle_task(void *data)
{
	while(1) {
		//sleep for a while
		//chk for runnable process
		__os_schedule();
		//introduce routines
	}
}

//to be invoked in os_init, before os_start
static void __os_idle_task(void)
{
	DECLARE_TASK(idle, OS_CONFIG_IDLE_STACK);

	CREATE_TASK(idle, __idle_task, NULL, OS_CONFIG_IDLE_STACK, 
			OS_CONFIG_TASK_PRIO_IDLE);

	//current = (void *) &idle_tcb;     //why this is here???
}

//to be called in timer isr and also in case of blocking calls
//not exposed to apps
void __os_schedule(void)
{
	OS_SAVE_CTX();
	uint8 prio;
	for (prio = OS_CONFIG_TASK_PRIO_HIGH1; prio <= OS_CONFIG_TASK_PRIO_IDLE; prio++)
		if ( __run_queue[prio] && __run_queue[prio]->state == OS_CONFIG_TASK_STATE_READY) {
			current = __run_queue[prio];  //no chk for current->prio < task->prio.. its obv
			break;
		}
	OS_LOAD_CTX();
}

//os_init declared as __attribute__ ((constructor))
//void os_init(void) __attribute__ ((constructor));
void os_init(void)
{
	uint8 cnt;
	OS_IRQ_DISABLE();            //__asm__("cli")
	__os_init_timer0();

	memset((void *) __run_queue, 0, 
			(sizeof(task_control_t *) * SOS_CONFIG_MAX_PRIOS));

	*kstack-- = 0xD0;	//poison

	__os_idle_task();
}

//TODO declare as __attribute__(naked)
//obviously by this time current pointer is set!!!
void os_start(void) __attribute__ ((naked));
void os_start(void)
{
	OS_LOAD_CONTEXT();		//expects current to be set
	__asm__ volatile ("ret"); 	//TODO verify
}

//to be called under __irq_disable
//want to avoid boundry chks...seems very unnecessary at this moment
void os_task_create(task_control_t *tcb, taskfn thrd, void *data, uint8 *stack, 
		uint8 stacksz, uint8 prio)
{
	tcb->base_prio = prio;

	tcb->stacktop = __os_init_stack(stack, thrd, data);

	//__os_add_tcb_node(&__run_queue[prio], tcb);

	//assumption: this function never be called dynamically
	tcb->state = OS_CONFIG_TASK_STATE_READY;
	//otherwise we'll hv to create barriers, sync points

	//chk prio and reset current if necessary
	if (((task_control_t *)current)->base_prio > prio)
		current = (void *) tcb;
}

