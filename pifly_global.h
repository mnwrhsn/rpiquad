#ifndef __RRM_PIFLY_GLOBAL_H_
#define __RRM_PIFLY_GLOBAL_H_

/*
 * Enable to compile with PRU
 * TODO: move it to Makefile
 */
//#define CONFIG_FLY_WITH_PRU

#ifdef CONFIG_FLY_WITH_PRU	//STM32 PRU based controller
//TODO
#else //--------------- RPI flight controller ------------------------

#include <stdint.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#define CONFIG_IMU_MPU6050

#define IMU_BUFFER_MAX	16

//---------------- IMU Data ------------------------------------
typedef struct motion_data_s {
	union {
		uint8_t buffer[IMU_BUFFER_MAX];
	};
} motion_data_t;

typedef struct motion_dev_s {
	int devfd;
	//IMU configuration
	motion_data_t	motion_data;		//motion data ready for pid calculation
} motion_dev_t;

//------------------ Flight Directions ------------------------------

enum flight_control {
	FLIGHT_X_ROLL = 0,
	FLIGHT_Y_PITCH,
	FLIGHT_Z_YAW,
	FLIGHT_THROTTLE,
	FLIGHT_CTRL_MAX,
};

typedef __flight_data_s {
} flight_data_t;

//------------------------ Motor Control ----------------------------

enum motor_num {
	PIFLY_MOTOR1 = 0,
	PIFLY_MOTOR2 = 1,
	PIFLY_MOTOR3 = 2,
	PIFLY_MOTOR4 = 3,

	PIFLY_MOTOR_MAX = 4,
};

typedef struct motor_data_s {
	int	motor_speed[PIFLY_MOTOR_MAX];
} motor_data_t;

typedef struct motor_dev_s {
	int devfd;
	motor_data_t motor_data;
}motor_dev_t;

typedef struct pifly_global_s {
	timer_t		loop_tid;	//pid feedback loop alarm event
	motion_dev_t	motion_dev;
	flight_data_t	flight_data;	//X, Y, Z and throttle info
	motor_dev_t	motor_dev;
} pifly_global_t;

#endif	//RPI flight controller
#endif //__RRM_PIFLY_GLOBAL_H_
