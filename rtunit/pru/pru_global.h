#ifndef __RTUNIT_PRU_GLOBAL_H_
#define __RTUNIT_PRU_GLOBAL_H_

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
} pru_global_t;

extern pru_global_t cur_global;

#define __add_delay() { \
	do { \
		int delay_counter; \
		for (delay_counter = 0; delay_counter < 100000; delay_counter++) { \
			__asm__("nop"); \
		} \
	} while(0); \
}

#endif //__RTUNIT_PRU_GLOBAL_H_
