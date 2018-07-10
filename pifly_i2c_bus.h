#ifndef __RRM_PIFLY_I2C_BUS_H_
#define __RRM_PIFLY_I2C_BUS_H_

//return fd
//argument i2c address
int i2c_dev_init(int);

uint8_t i2c_read8(int, int);
int i2c_write8(int, int, int);

#endif //__RRM_PIFLY_I2C_BUS_H_
