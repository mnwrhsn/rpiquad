#ifndef __RTUNIT_PRU_GLOBAL_H_
#define __RTUNIT_PRU_GLOBAL_H_

enum flight_axis {
	FLIGHT_X_ROLL = 0,
	FLIGHT_Y_PITCH,
	FLIGHT_Z_YAW,
	FLIGHT_AXIS_MAX,
};

typedef __flight_data_s {
} flight_data_t;

//TODO: need to develop state machine
enum state {
	PRU_ST_STOPPED = 0,
	PRU_ST_RUNNING = 1,
	PRU_ST_DATA_READY = 2,
	PRU_ST_DATA_READ = 4,
	PRU_ST_DATA_DONE = 8,

	PRU_ST_MAX = 0x80,
};

typedef struct __pru_global_s {
	uint8_t pru_state;
	flight_data_t fdata;
} pru_global_t;

extern pru_global_t cur_global;

#define __add_delay() \
	do { \
		int __delay_counter; \
		for (__delay_counter = 0; __delay_counter < 1000000; __delay_counter++) { \
			__asm__("nop"); \
		} \
	} while(0)

#endif //__RTUNIT_PRU_GLOBAL_H_
