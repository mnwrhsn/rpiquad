#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/i2c.h>
#include <stdio.h>
#include <errno.h>

#include "pru_global.h"
#include "pru_usart_print.h"
#include "pru_i2c_master.h"

void i2c1_master_setup(void)
{
	rcc_periph_clock_enable(RCC_I2C1);
	i2c_reset(I2C1);

	//SCL1 = PB6 SDA1 = PB7
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN, 
			GPIO_I2C1_SCL | GPIO_I2C1_SDA);

	i2c_peripheral_disable(I2C1);
	i2c_set_speed(I2C1, i2c_speed_sm_100k, 8);
	I2C_CR1(I2C1) |= I2C_CR1_ACK;

	i2c_peripheral_enable(I2C1);
}

int i2c_master_read_bytes(struct i2c_data_t *pd)
{
	int count = 0;
	if (pd && pd->len) {
		i2c_send_start(pd->i2c);
		I2C1_MASTER_START_WAIT(pd->i2c);

		usart_printf("i2c start sent\n");

		i2c_send_7bit_address(pd->i2c, pd->slave, I2C_WRITE);
		I2C1_MASTER_ADDR_WAIT(pd->i2c);

		usart_printf("slave address sent: %x\n", pd->slave);

		usart_printf("reg address: %x\n", pd->raddr);

		i2c_send_data(pd->i2c, pd->raddr);
		I2C1_MASTER_SEND_LAST_WAIT(pd->i2c);

		usart_printf("slave reg address sent\n");

		i2c_send_start(pd->i2c);
		I2C1_MASTER_START_WAIT(pd->i2c);

		usart_printf("i2c start sent\n");
		
		I2C_CR1(pd->i2c) |= I2C_CR1_ACK;
		
		i2c_send_7bit_address(pd->i2c, pd->slave, I2C_READ);
		I2C1_MASTER_ADDR_WAIT(pd->i2c);

		usart_printf("slave address sent\n");

		for(count = 0; count < (pd->len - 1); count++) {
			I2C1_MASTER_WAIT(pd->i2c);
			pd->data[count] = I2C_DR(pd->i2c);
		}

		I2C_CR1(pd->i2c) &= ~I2C_CR1_ACK;
		I2C1_MASTER_WAIT(pd->i2c);
		
		i2c_send_stop(pd->i2c);
		
		pd->data[count] = I2C_DR(pd->i2c);
		count++;

		usart_printf("Total reg read: %d\n", count);
	}
	return count;
}

int i2c_master_write_bytes(struct i2c_data_t *pd)
{
	int count = 0;
	if (pd && pd->len) {
		i2c_send_start(pd->i2c);
		I2C1_MASTER_START_WAIT(pd->i2c);

		usart_printf("i2c start sent\n");
		
		i2c_send_7bit_address(pd->i2c, pd->slave, I2C_WRITE);
		I2C1_MASTER_ADDR_WAIT(pd->i2c);
		usart_printf("slave address sent: %x\n", pd->slave);
		
		i2c_send_data(pd->i2c, pd->raddr);

		for (count = 0; count < pd->len; count++) {
			I2C1_MASTER_WAIT(pd->i2c);
			i2c_send_data(pd->i2c, pd->data[count]);
		}
		I2C1_MASTER_SEND_LAST_WAIT(pd->i2c);
		i2c_send_stop(pd->i2c);
	}
	return count;
}

