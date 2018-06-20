/*
COPIED from pwm-servo example found in,
https://github.com/wendlers/stm32-pwm-servo-sample.git
*/
#ifndef __RTUNIT_PRU_SERVO_H_
#define __RTUNIT_PRU_SERVO_H_

/**
 * Prescale 72000000 Hz system clock by 72 = 1000000 Hz.
 */
#define PWM_PRESCALE	(72)

/**
 * We need a 50 Hz period (1000 / 20ms = 50), thus devide 100000 by 50 = 20000 (us).
 */
#define PWM_PERIOD		(20000)

/**
 * Max. pos. at 2050 us (2.00ms).
 */
#define SERVO_MAX		(2050)

/**
 * Min. pos. at 950  us (0.95ms).
 */
#define SERVO_MIN		(950)

/**
 * Middle pos. at 1580 us (1.58ms).
 */
#define SERVO_NULL		(1580)

/**
 * TIM2 channel for servo 1.
 *
 * Changing this also requires to change settings in {@link servo_init}!
 */
#define SERVO_CH1		TIM_OC2

/**
 * TIM2 channel for servo 2.
 *
 * Changing this also requires to change settings in {@link servo_init}!
 */
#define SERVO_CH2		TIM_OC3

/**
 * Initialize and start the PWM used for the servos, drive servos to middle position.
 */
void servo_init(void);

/**
 * Drive the servo connected to the given channel to the given position in us.
 *
 * @param[in]	ch		The channel of the servo. E.g. SERVO_CH1, SERVO_CH2.
 * @param[in]	pos_us	The position in us to which to drive the servo to.
 */
void servo_set_position(enum tim_oc_id ch, uint32_t pos_us);

#endif //__RTUNIT_PRU_SERVO_H_
