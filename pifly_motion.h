#ifndef __RRM_PIFLY_MOTION_H_
#define __RRM_PIFLY_MOTION_H_

#include "pifly_global.h"
#include "pifly_i2c_bus.h"

#ifdef CONFIG_IMU_MPU6050
//TODO add all mpu6050 specific data
#endif

extern int imu_device_init(motion_dev_t *);
extern int imu_get_raw_motion(motion_dev_t *);
extern int imu_get_motion(motion_dev_t *);

#endif //__RRM_PIFLY_MOTION_H_
