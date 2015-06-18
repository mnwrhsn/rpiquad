#include "os_i2c_master.h"
#include <util/twi.h>

#define F_SCL           400000UL        //400KHz
#define SCL_PRESCALAR   1
#define TWBR_VAL        (((F_CPU / F_SCL) - 16) / 2)

#define TW_BUSY_WAIT    { while (! (TWCR & (1 << TWINT))); }

void os_mi2c_init(void)
{
	TWBR = TWBR_VAL;
	TWSR = ((0 << TWPS1) | (0 << TWPS0));
	TWCR = (1 << TWEN);
}

uint8_t os_mi2c_start(uint8_t addr)
{
}

void os_mi2c_stop(void)
{
}

uint8_t os_mi2c_write(uint8_t data)
{
}

uint8_t os_mi2c_read(void)
{
}
