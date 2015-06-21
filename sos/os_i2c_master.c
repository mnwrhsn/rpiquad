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
	TWCR = ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));
	TW_BUSY_WAIT;

	if ((TWSR != TW_START) && (TWSR != TW_REP_START))
		return 1;

	TWDR = addr;
	TWCR = ((1 << TWINT) | (1 << TWEN));
	TW_BUSY_WAIT;

	if ((TWSR != TW_MT_SLA_ACK) && (TWSR != TW_MR_SLA_ACK))
		return 1;
	return 0;
}

void os_mi2c_stop(void)
{
	TWCR = ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN));
}

uint8_t os_mi2c_write(uint8_t data)
{
	TWDR = data;
	TWCR = ((1 << TWINT) | (1 << TWEN));

	TW_BUSY_WAIT;

	if (TWSR != TW_MT_DATA_ACK)
		return 1;
	return 0;
}

uint8_t os_mi2c_read(void)
{
	TWCR = ((1 << TWINT) | (1 << TWEN) | (1 << TWEA));
	TW_BUSY_WAIT;

	return TWDR;
}
