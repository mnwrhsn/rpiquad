#include "os_config.h"
#include "os_arch.h"

volatile void *current;       //current task pointer

extern void __os_schedule(void);

//XXX assumes correct FUSES are set
void __os_init_timer0(void)
{
	//timer0 counter set to 0
	TCNT0 = 0x00;

	//prescale /1024 TODO adjust for clock frequency
	TCCR0 = (1 << CS02) | (1 << CS00);

	TIMSK = (1 << TOIE0);
}

ISR(TIMER0_OVF_vect)            //move this to os_arch.c
{
	//timer0 overflow

	//call schedule
	__os_schedule();
}

void __os_init_ports(void)
{
    //TODO
}
