#ifndef __RTUNIT_PRU_I2C_MASTER_H_
#define __RTUNIT_PRU_I2C_MASTER_H_

#include "pru_global.h"

// i2c registers refer section 26.6

struct i2c_data_t {
	uint32_t i2c;
	uint8_t  slave;
	uint8_t  raddr;
	uint8_t  len;
	uint8_t  *data;
};

#define I2C1_MASTER_START_WAIT(x) \
	{ \
		while (!((I2C_SR1((x)) & I2C_SR1_SB) \
                & (I2C_SR2((x)) & (I2C_SR2_MSL | I2C_SR2_BUSY)))); \
	}

//refer note in 26.6.7 (required to clear ADDR bit in SR1)
#define I2C1_MASTER_ADDR_WAIT(x) \
	{ \
		uint32_t reg32 __attribute__((unused)); \
		while (!(I2C_SR1((x)) & I2C_SR1_ADDR)); \
		reg32 = I2C_SR2((x)); \
	}

#define I2C1_MASTER_WAIT(x) \
	{ \
		while (!(I2C_SR1((x)) & I2C_SR1_BTF)); \
	}

#define I2C1_MASTER_SEND_LAST_WAIT(x) \
	{ \
		while (!(I2C_SR1((x)) & (I2C_SR1_BTF | I2C_SR1_TxE))); \
	}

extern void i2c1_master_setup(void);
extern int i2c_master_read_bytes(struct i2c_data_t *);
extern int i2c_master_write_bytes(struct i2c_data_t *);

#endif //__RTUNIT_PRU_I2C_MASTER_H_
