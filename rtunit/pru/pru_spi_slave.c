#include <stdio.h>
#include <errno.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/spi.h>

#include "pru_spi_slave.h"

#define __PRU_NO_DMA_

#ifdef __PRU_NO_DMA_
void spi_slave_setup(void)
{
	//enable clock
	rcc_periph_clock_enable(RCC_SPI1);

	//pin setup and config
	/* Configure GPIOs: SS=PA4, SCK=PA5, MISO=PA6 and MOSI=PA7 */
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO4 | GPIO5 | GPIO7);
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO6);

	spi_disable(SPI1);
	spi_reset(SPI1);

	spi_init_master(SPI1,
			SPI_CR1_BAUDRATE_FPCLK_DIV_2,
			SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
			SPI_CR1_CPHA_CLK_TRANSITION_1,
			SPI_CR1_DFF_8BIT,
			SPI_CR1_MSBFIRST);
			
	spi_set_slave_mode(SPI1);
	spi_enable(SPI1);
}

/* use following,

	char rx = spi_xfer(ch);
	or 
	spi_send(SPI1, ch);
	char rx = spi_read(SPI1);

*/

#else // with DMA

/* SPI receive completed with DMA */
void dma1_channel2_isr(void)
{
}

/* SPI transmit completed with DMA */
void dma1_channel3_isr(void)
{
}

static void __spi_dma_enable(void)
{
	/* SPI1 RX on DMA1 Channel 2 */
	nvic_set_priority(NVIC_DMA1_CHANNEL2_IRQ, 0);
	nvic_enable_irq(NVIC_DMA1_CHANNEL2_IRQ);
	/* SPI1 TX on DMA1 Channel 3 */
	nvic_set_priority(NVIC_DMA1_CHANNEL3_IRQ, 0);
	nvic_enable_irq(NVIC_DMA1_CHANNEL3_IRQ);
}

void spi_slave_setup(void)
{
	//enable clock
	rcc_periph_clock_enable(RCC_SPI1);

	//pin setup and config
	/* Configure GPIOs: SS=PA4, SCK=PA5, MISO=PA6 and MOSI=PA7 */
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO4 | GPIO5 | GPIO7);
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO6);

	spi_disable(SPI1);
	spi_reset(SPI1);

	spi_init_master(SPI1,
			SPI_CR1_BAUDRATE_FPCLK_DIV_2,
			SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
			SPI_CR1_CPHA_CLK_TRANSITION_1,
			SPI_CR1_DFF_8BIT,
			SPI_CR1_MSBFIRST);
			
	spi_set_slave_mode(SPI1);
	spi_enable(SPI1);

	__spi_dma_enable();
}
#endif
