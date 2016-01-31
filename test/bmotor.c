/*
 reading from RF receiver and controlling motor
*/

#include "../sos/rrm_config.h"
#include "../sos/os_lib_servo.h"
#include "../sos/os_lib_lcd.h"

int main(void)
{
	int cnt;
	cli();
	servo_setup_timer1_channel1(0);
	lcd_n5110_init();
	sei();

	while (1) {
		lcd_n5110_clear();
		for (cnt = 0; cnt <= 5; cnt++) {
			servo_set_timer1_channel1(cnt * 10);
			lcd_n5110_format_string("\n duty width: %d\n", cnt * 10);
			_delay_ms(1000);
		}
	}

	return 0;
}
