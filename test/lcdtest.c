#include "../sos/rrm_config.h"
#include "../sos/os_lib_lcd.h"

int main (void)
{
	cli();
	lcd_n5110_init();


	while (1) {
		lcd_n5110_clear();

		lcd_n5110_format_string("\n Ratnaraj \n");
		_delay_ms(1000);
		lcd_n5110_clear();
		lcd_n5110_format_string("\n Mirgal \n"); 
		_delay_ms(1000);
	}

	return 0;
}
