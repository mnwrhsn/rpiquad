#ifndef __RRM_SOS_SPI_H_
#define __RRM_SOS_SPI_H_

#include "rrm_config.h"
#include "os_config.h"

#ifdef __AVR_ATmega32__

#define SPI_PORT	PORTB
#define SPI_DDR		DDRB
#define SPI_SS_PIN	PB4
#define SPI_MOSI_PIN	PB5
#define SPI_MISO_PIN	PB6
#define SPI_SCK_PIN	PB7
#endif //__AVR_ATmega32__

#endif //__RRM_SOS_SPI_H_
