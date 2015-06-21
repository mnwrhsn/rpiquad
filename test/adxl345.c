#include "../sos/rrm_config.h"
#include "../sos/os_i2c_master.h"
#include "../sos/os_lcd.h"

volatile int16_t xdata = 0;
volatile int16_t ydata = 0;
volatile int16_t zdata = 0;

void adxl345_init(void)
{
	os_mi2c_start(0x3A);
	os_mi2c_write(0x2D);
	os_mi2c_write(1 << 3);
	os_mi2c_stop();
}

void adxl345_read(void)
{
	int16_t reg0;
	int16_t reg1;
	os_mi2c_start(0x3A);
	os_mi2c_write(0x32);
	
	os_mi2c_start(0x3B);

	reg0 = os_mi2c_read_ack();
	reg1 = os_mi2c_read_ack();
	xdata = (reg0 << 8) + reg1;

	reg0 = os_mi2c_read_ack();
	reg1 = os_mi2c_read_ack();
	ydata = (reg0 << 8) + reg1;

	reg0 = os_mi2c_read_ack();
	reg1 = os_mi2c_read_nack();
	zdata = (reg0 << 8) + reg1;
	
	os_mi2c_stop();
}

int main (void)
{
	uint8_t reg;
	cli();
	lcd_n5110_init();
	os_mi2c_init();

	adxl345_init();

	while (1) {
		lcd_n5110_clear();

		lcd_n5110_string("now reading data\n");

		adxl345_read();

		lcd_n5110_clear();

		lcd_n5110_format_string("x: %d\n", xdata);
		lcd_n5110_format_string("y: %d\n", ydata);
		lcd_n5110_format_string("z: %d\n", zdata);

		_delay_ms(1000);
	}

	return 0;
}
