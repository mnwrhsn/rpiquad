#include <stdio.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include <string.h>

#define SPI_CHANNEL 0
#define SPI_MESSAGE "Hello STM32 from Raspberry Pi Zero"

// channel is the wiringPi name for the chip select (or chip enable) pin.
// Set this to 0 or 1, depending on how it's connected.

int main(void)
{
	int fd, result;
	int blen = 0;
	int cnt = 0;

	unsigned char buffer[] = "Hello STM32 from RPi Zero";

	wiringPiSetup();

	//strcpy(buffer, SPI_MESSAGE);
	blen = strlen(buffer);

	printf("Buffer length: %d\n", blen);

	fd = wiringPiSPISetup(SPI_CHANNEL, 500000);

	for (cnt = 0; cnt < blen; cnt++) {
		wiringPiSPIDataRW(SPI_CHANNEL, &buffer[cnt], 1);
		sleep(1);
	}

	printf("Buffer value: %s %d\n", buffer, strlen(buffer));

	close(fd);
	return 0;
}

