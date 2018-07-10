#include <stdio.h>
#include <stdlib.h>

#include "pifly_global.h"
#include "pifly_pid.h"

//keep only PID algorithm specific data

int pid_feedback_init(pifly_global *gl)
{
}

int pid_feedback_loop(pifly_global_t *gl)
{
	//1. read IMU data, get converted data
	//imu_get_motion();
	//2. read flight data	(throttle, roll, pitch and yaw information)
	//3. calculate pid
	//4. set values to ESCs
	//control_motors()
}
