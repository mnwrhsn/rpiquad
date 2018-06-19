#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/cm3/nvic.h>
#include <stdio.h>
#include <errno.h>

#include "pru_global.h"

#include "pru_i2c_master.h"
#include "pru_dev_mpu6050.h"
#include "pru_spi_slave.h"
#include "pru_usart_print.h"

//global state machine
pru_global_t cur_global;

/*
 * Based on stm32f103c8t6 (Blue Pill) board
 */

static void __clock_setup(void)
{
	//external 8MHz
	rcc_clock_setup_in_hse_8mhz_out_72mhz();

	//enable Ports
	rcc_periph_clock_enable(RCC_GPIOA);
        rcc_periph_clock_enable(RCC_GPIOB);
        rcc_periph_clock_enable(RCC_GPIOC);
}

static void __blink_setup(void)	//for onboard led GPIO13
{
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
}

int main(void) 
{
	//char buffer[128] =  { 0 };
	//int i = 0;

	__clock_setup();
	__blink_setup();
	usart_printf_setup();
	//spi_slave_setup();		//TODO spi DMA asap
	i2c1_master_setup();

	mpu6050_init();

	usart_printf("Starting Blue pill\n");
	gpio_toggle(GPIOC, GPIO13);	// Toggle LED
	__add_delay();

	gpio_toggle(GPIOC, GPIO13);	// Toggle LED
	__add_delay();

	for (;;) {
		gpio_toggle(GPIOC, GPIO13);	// Toggle LED

		__add_delay();
		__mpu6050_dump_raw();
		__add_delay();

		usart_send_blocking(USART1, '0');
	}

	return 0;
}
