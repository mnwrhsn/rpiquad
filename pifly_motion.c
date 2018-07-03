#include <stdio.h>
#include <stdlib.h>
#include <unisdt.h>

#include "pifly_global.h"
#include "pifly_i2c_bus.h"
#include "pifly_motion.h"

#ifdef CONFIG_IMU_MPU6050

static int __mpu6050_device_init(motion_dev_t *md)
{
	return 0;
}

int imu_device_init(motion_dev_t *md)
{
	return __mpu6050_device_init(md);
}

static int __mpu6050_get_raw_motion(motion_dev_t *md)
{
	return 0;
}

int imu_get_raw_motion(motion_dev_t *md)
{
	return __mpu6050_get_raw_motion(md);
}

static int __mpu6050_get_motion(motion_dev_t *md)
{
	return 0;
}

int imu_get_motion(motion_dev_t *md)
{
	return __mpu6050_get_motion(md);
}

#endif
