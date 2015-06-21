#include "../sos/rrm_config.h"
#include "../sos/os_i2c_master.h"
#include "../sos/os_lcd.h"

struct ds1307_time {
	uint8_t sec;
	uint8_t min;
	uint8_t hr;
};

struct ds1307_date {
	uint8_t date;
	uint8_t month;
	uint8_t year;
};

#define DS1307_DEC2BCD(value) (value + 6 * (value / 10))
#define DS1307_BCD2DEC(value) (value - 6 * (value >> 4))

void ds1307_init(void)
{
	os_mi2c_start(0xD0);
	os_mi2c_write(0x07);	//control
	os_mi2c_write(0x00);
	os_mi2c_stop();
}

void ds1307_read_time(struct ds1307_time *t)
{
	os_mi2c_start(0xD0);
	os_mi2c_write(0x00);

	os_mi2c_start(0xD1);
	t->sec = os_mi2c_read_ack();
	t->min = os_mi2c_read_ack();
	t->hr = os_mi2c_read_nack();

	os_mi2c_stop();
}

void ds1307_read_date(struct ds1307_date *t)
{
	os_mi2c_start(0xD0);
	os_mi2c_write(0x04);

	os_mi2c_start(0xD1);
	t->date = os_mi2c_read_ack() & 0x7f;
	t->month = os_mi2c_read_ack();
	t->year = os_mi2c_read_nack();

	os_mi2c_stop();
}

int main (void)
{
	struct ds1307_time mytime;
	struct ds1307_date mydate;
	lcd_n5110_init();
	os_mi2c_init();

	ds1307_init();

	while (1) {
		lcd_n5110_clear();

		ds1307_read_time(&mytime);
		ds1307_read_date(&mydate);

		lcd_n5110_format_string("time : \n%d:%d:%d\n", 
				DS1307_BCD2DEC(mytime.sec), 
				DS1307_BCD2DEC(mytime.min), 
				DS1307_BCD2DEC(mytime.hr));
		_delay_ms(1000);
		lcd_n5110_clear();
		lcd_n5110_format_string("date : \n%d:%d:%d\n", 
				DS1307_BCD2DEC(mydate.date), 
				DS1307_BCD2DEC(mydate.month), 
				DS1307_BCD2DEC(mydate.year));
		_delay_ms(1000);
	}

	return 0;
}
