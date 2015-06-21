#ifndef __RRM_SOS_I2C_H_
#define __RRM_SOS_I2C_H_

#include "rrm_config.h"
#include "os_config.h"
#include <util/twi.h>

#define I2C_READ	0x01
#define I2C_WRITE	0x00

extern void os_mi2c_init(void);
extern uint8_t os_mi2c_start(uint8_t);
extern void os_mi2c_stop(void);

extern uint8_t os_mi2c_write(uint8_t);
extern uint8_t os_mi2c_read(void);

/*usage to read from some register,

os_mi2c_init();
os_mi2c_start(0xE5 | I2C_WRITE);
os_mi2c_write(0x03); <-setting pointer
os_mi2c_start(0xE5 | I2C_READ);
loop {
	data = os_mi2c_read()
}
*/

#endif //__RRM_SOS_I2C_H_
