#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "rpi_dev_mpu6050.h"

//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------

static void __all_init(void)
{
	//imu_device_init();
}

void __pid_loop(void)
{
	//imu_read_motion();
	//flight instructions
	//pid compute
	//motor control
}

int main(void)
{
	__all_init();
	printf("");

	while(1) {
		__pid_loop();
		usleep(10000);		//100Hz (10ms sleep)
	}

	return 0;
}
