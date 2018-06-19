#ifndef __RTUNIT_PRU_USART_PRINT_H_
#define __RTUNIT_PRU_USART_PRINT_H_

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

//USART1 default for logging
#define DEBUG_PRINTF_ON

#ifdef DEBUG_PRINTF_ON
extern void usart_printf_setup(void);
extern int usart_printf(const char *format, ...) __attribute__ ((format (printf, 1, 2)));
#else
void usart_printf_setup(void)
{
}

int usart_printf(const char *format, ...)
{
	return 0;
}
#endif

#endif //__RTUNIT_PRU_USART_PRINT_H_
