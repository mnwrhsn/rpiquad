#ifndef __RRM_PWM_SERVO_H_
#define __RRM_PWM_SERVO_H_

#include "rrm_config.h"

//TODO: 4/12MHz clock support
//for 50Hz PWM servo signal
//for better results use 8 or 16MHz clock
//compatibility with prescalar 8
#define AT_IS_P8_COMPATIBLE	(!((F_CPU / 1000000UL) % 8))
#define AT_MULTIPLIER_CONST	(F_CPU / 8000000UL)


#define MIN_PULSE_WIDTH		(1000 * AT_MULTIPLIER_CONST)	//1ms
#define DEF_PULSE_WIDTH		(1500 * AT_MULTIPLIER_CONST)	//1.5ms 90deg
#define MAX_PULSE_WIDTH		(2000 * AT_MULTIPLIER_CONST)	//2ms

#define BASE_PULSE_WIDTH	MIN_PULSE_WIDTH
#define ONE_PULSE_GAIN		(10 * AT_MULTIPLIER_CONST)	//1%gain

#ifdef __AVR_ATmega32__
#define SERVO_T1CH1_PORT	DDRD
#define SERVO_T1CH1_PIN		PD5	//o/p

#define SERVO_T1CH2_PORT	DDRD
#define SERVO_T1CH2_PIN		PD4
#endif

//o/p @ oc1a (pin pd5)
extern void servo_setup_timer1_channel1(uint8_t);

//o/p @ oc1b (pin pd4)
extern void servo_setup_timer1_channel2(uint8_t);

//expected value is 0 - 100
extern void servo_set_timer1_channel1(uint8_t);
extern void servo_set_timer1_channel2(uint8_t);

#endif //__RRM_PWM_SERVO_H_
