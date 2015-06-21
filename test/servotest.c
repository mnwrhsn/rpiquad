#include "../sos/rrm_config.h"
#include "../sos/os_servo.h"

int main(void)
{
	uint8_t cnt;
	cli();
	servo_setup_timer1_channel1(0);
	sei();
	while (1) {
		servo_set_timer1_channel1(50);
		for (cnt = 0; cnt <= 10; cnt++) {
			servo_set_timer1_channel1(cnt);
			_delay_ms(1000);
		}
	}
	return 0;
}
