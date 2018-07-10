#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "pifly_global.h"
#include "pifly_i2c_bus.h"
#include "pifly_motor.h"

/******************************** PCA9685 *********************************************/

#define PCA9685_I2C_ADDR	0x40

static int __pca9685_init(void)
{
	int fd = 0;
	
	fd = wiringPiI2CSetup(PCA9685_I2C_ADDR);
	if (fd > 0) {
		//initialise PCA9685 for servo control
		//TODO
	}

	return fd;
}

static void __pca9685_set_pwm(int fd, uint8_t l, float pulse)
{
	//TODO
}

/**************************************************************************************/

int pifly_motor_init(motor_dev_t *md)
{
	md->devfd = __pca9685_init();
	if (md->devfd < 0)
		return -EINVAL;

	return 0;
}

int pifly_motor_set(motor_dev_t *md)
{
	//md->motor_data.motor_speed[PIFLY_MOTOR1]
	//md->motor_data.motor_speed[PIFLY_MOTOR2]
	//md->motor_data.motor_speed[PIFLY_MOTOR3]
	//md->motor_data.motor_speed[PIFLY_MOTOR4]
}
