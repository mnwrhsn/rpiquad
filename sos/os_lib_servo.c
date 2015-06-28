#include "rrm_config.h"
#include "os_lib_servo.h"

//inverted pwm, 50 Hz, fast pwm option 14,

#ifdef __AVR_ATmega32__

void servo_setup_timer1_channel1(uint8_t ch2)
{
	if (AT_IS_P8_COMPATIBLE) {
		SERVO_T1CH1_PORT |= (1 << SERVO_T1CH1_PIN);
		if (!ch2) {
			TCCR1A |= (1 << WGM11) | (1 << COM1A1) | (1 << COM1A0);
			TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);

			ICR1 = 19999 * AT_MULTIPLIER_CONST;
		}
		OCR1A = ICR1 - MIN_PULSE_WIDTH;
	}
}

void servo_setup_timer1_channel2(uint8_t ch1)
{
	if (AT_IS_P8_COMPATIBLE) {
		SERVO_T1CH2_PORT |= (1 << SERVO_T1CH2_PIN);
		if (!ch1) {
			TCCR1A |= (1 << WGM11) | (1 << COM1B1) | (1 << COM1B0);
			TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);

			ICR1 = 19999 * AT_MULTIPLIER_CONST;
		}
		OCR1B = ICR1 - MIN_PULSE_WIDTH;
	}
}

void servo_set_timer1_channel1(uint8_t g)
{
	OCR1A = ICR1 - (BASE_PULSE_WIDTH + (ONE_PULSE_GAIN * g));
}

void servo_set_timer1_channel2(uint8_t g)
{
	OCR1B = ICR1 - (BASE_PULSE_WIDTH + (ONE_PULSE_GAIN * g));
}
#endif //__AVR_ATmega32__
