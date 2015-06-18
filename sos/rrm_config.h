#ifndef __RRM_CONFIG_H_
#define __RRM_CONFIG_H_

#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz clock speed
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#ifdef __AVR_ATmega32__

#define AT_SET_ENABLE_INT0		{ GICR |= (1 << INT0); DDRD |= (0 << PD2); }
#define AT_SET_ENABLE_INT1 		{ GICR |= (1 << INT1); DDRD |= (0 << PD3); }
#define AT_SET_ENABLE_INT2		{ GICR |= (1 << INT2); DDRB |= (0 << PB2); }

//int0 sense control
#define AT_INT0_SENSE_LOW		(MCUCR |= ((0 << ISC01) | (0 << ISC00)))
#define AT_INT0_SENSE_ANY		(MCUCR |= ((0 << ISC01) | (1 << ISC00)))
#define AT_INT0_SENSE_FALL		(MCUCR |= ((1 << ISC01) | (0 << ISC00)))
#define AT_INT0_SENSE_RISE		(MCUCR |= ((1 << ISC01) | (1 << ISC01)))

//int1 sense control
#define AT_INT1_SENSE_LOW		(MCUCR |= ((0 << ISC11) | (0 << ISC10)))
#define AT_INT1_SENSE_ANY		(MCUCR |= ((0 << ISC11) | (1 << ISC10)))
#define AT_INT1_SENSE_FALL		(MCUCR |= ((1 << ISC11) | (0 << ISC10)))
#define AT_INT1_SENSE_RISE		(MCUCR |= ((1 << ISC11) | (1 << ISC11)))

//INT2
#define AT_INT2_SENSE_FALL		(MCUCSR |= (0 << ISC2))
#define AT_INT2_SENSE_RISE		(MCUCSR |= (1 << ISC2))

///timer0
#define AT_T0_OI_ENABLE			(TIMSK |= (1 << TOIE0))		//overflow int
#define AT_T0_CM_ENABLE			(TIMSK |= (1 << OCIE0))		//output compare match

#define AT_T0_PRESCALE0			(TCCR0 |= ((0 << CS02) | (0 << CS01) | (1 << CS00)))
#define AT_T0_PRESCALE8			(TCCR0 |= ((0 << CS02) | (1 << CS01) | (0 << CS00)))
#define AT_T0_PRESCALE64		(TCCR0 |= ((0 << CS02) | (1 << CS01) | (1 << CS00)))
#define AT_T0_PRESCALE256		(TCCR0 |= ((1 << CS02) | (0 << CS01) | (0 << CS00)))
#define AT_T0_PRESCALE1024		(TCCR0 |= ((1 << CS02) | (1 << CS01) | (1 << CS00)))

#define AT_T0_CNT_RESET			(TCNT0 = 0)

//timer1
#define AT_T1_OI_ENABLE			(TIMSK |= (1 << TOIE1))
#define AT_T1_IC_ENABLE			(TIMSK |= (1 << TICIE1))
#define AT_T1_CMA_ENABLE		(TIMSK |= (1 << OCIE1A))
#define AT_T1_CMB_ENABLE		(TIMSK |= (1 << OCIE1B))

#define AT_T1_PRESCALE0			(TCCR1B |= ((0 << CS12) | (0 << CS11) | (1 << CS10)))
#define AT_T1_PRESCALE8			(TCCR1B |= ((0 << CS12) | (1 << CS11) | (0 << CS10)))
#define AT_T1_PRESCALE64		(TCCR1B |= ((0 << CS12) | (1 << CS11) | (1 << CS10)))
#define AT_T1_PRESCALE256		(TCCR1B |= ((1 << CS12) | (0 << CS11) | (0 << CS10)))
#define AT_T1_PRESCALE1024		(TCCR1B |= ((1 << CS12) | (0 << CS11) | (1 << CS10)))

#endif //__AVR_ATmega32__

#endif //__RRM_CONFIG_H_
