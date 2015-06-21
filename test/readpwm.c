/*
reading pwm values from turnigy 6XS receiver.
TODO: duty period is some times more than 2000us
need to consider timer overflow
*/

#include "../sos/rrm_config.h"
#include "../sos/os_lcd.h"

volatile int32_t duty = 0;
volatile int32_t spulse = 0;
volatile int32_t epulse = 0;

ISR(INT0_vect)
{
	if (PORTD & PD2) {
		spulse = TCNT1;
	} else {
		epulse = TCNT1;
		duty = epulse - spulse;
		TCNT1 = 0;
	}
}

int main(void)
{
	asm volatile ("cli	");
	AT_SET_ENABLE_INT0;
	AT_INT0_SENSE_ANY;

	AT_T1_PRESCALE8;
	TCNT1 = 0;

	lcd_n5110_init();
	asm volatile ("sei	");

	while (1) {
		lcd_n5110_clear();

		lcd_n5110_format_string("\n duty width: \n %d %d\n", duty, epulse);
		_delay_ms(1000);
	}

	return 0;
}
