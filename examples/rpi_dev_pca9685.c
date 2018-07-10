#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#define PCA9685_ADDR		0x40

#define PCA9685_MAX_PWM		4096
#define PCA9685_SERVO_FREQ	50

//PCA9685 Registers-----------------------------------------
#define PCA9685_REG_MODE1	0x00
#define PCA9685_REG_MODE2	0x01
#define PCA9685_REG_ALLONL	0xFA
#define PCA9685_REG_ALLONH	0xFB
#define PCA9685_REG_ALLOFFL	0xFC
#define PCA9685_REG_ALLOFFH	0xFD
#define PCA9685_REG_PRESCALE	0xFE
//motor1
#define PCA9685_REG_LEDON0L	0x06
#define PCA9685_REG_LEDON0H	0x07
#define PCA9685_REG_LEDOFF0L	0x08
#define PCA9685_REG_LEDOFF0H	0x09
//motor2
#define PCA9685_REG_LEDON1L	0x0A
#define PCA9685_REG_LEDON1H	0x0B
#define PCA9685_REG_LEDOFF1L	0x0C
#define PCA9685_REG_LEDOFF1H	0x0D
//motor3
#define PCA9685_REG_LEDON2L	0x0E
#define PCA9685_REG_LEDON2H	0x0F
#define PCA9685_REG_LEDOFF2L	0x10
#define PCA9685_REG_LEDOFF2H	0x11
//motor4
#define PCA9685_REG_LEDON3L	0x12
#define PCA9685_REG_LEDON3H	0x13
#define PCA9685_REG_LEDOFF3L	0x14
#define PCA9685_REG_LEDOFF3H	0x15

#define MOTOR1_START		PCA9685_REG_LEDON0L
#define MOTOR2_START		PCA9685_REG_LEDON1L
#define MOTOR3_START		PCA9685_REG_LEDON2L
#define MOTOR4_START		PCA9685_REG_LEDON3L
//---------------------------------------------------------

int devfd = 0;

static void __pca9685_init(void)
{
	int prescale = 0;
	int settings = 0;

	devfd = wiringPiI2CSetup(PCA9685_ADDR);

	//PCA9685 initialization for servo

	// To set pwm frequency we have to set the prescale register. The formula is:
        // prescale = round(osc_clock / (4096 * frequency))) - 1 where osc_clock = 25 MHz
        // Further info here: http://www.nxp.com/documents/data_sheet/PCA9685.pdf Page 24
        prescale = (int) ((25000000.0f / (4096 * PCA9685_SERVO_FREQ)) - 1.0f);

	settings = wiringPiI2CReadReg8(devfd, PCA9685_REG_MODE1) & 0x7f;

	wiringPiI2CWriteReg8(devfd, PCA9685_REG_MODE1, (uint8_t) (settings | 0x10));
	wiringPiI2CWriteReg8(devfd, PCA9685_REG_PRESCALE, (uint8_t) prescale);
	wiringPiI2CWriteReg8(devfd, PCA9685_REG_MODE1, (uint8_t) ((settings | 0x20) & 0xEF));

	sleep(1);

	wiringPiI2CWriteReg8(devfd, PCA9685_REG_MODE1, (uint8_t) ((settings | 0x20 | 0x80) & 0xEF));

	sleep(2);
}

//pulse value needs to be between 0-4095
static void __pca9685_set_pwm(int led, int pulse)
{
	//always start pulse on 0
	wiringPiI2CWriteReg16(devfd, led, 0x0);
	wiringPiI2CWriteReg16(devfd, (led + 2), (pulse & 0x0fff));	//only 12bits are valid (0-4095)
}

static void __pca9685_reset(void)
{
	wiringPiI2CWriteReg16(devfd, PCA9685_REG_ALLONL, 0x0);
	wiringPiI2CWriteReg16(devfd, PCA9685_REG_ALLOFFL, 0x1000);
}

/*
 * Test program to control servo using PCA9685
 * OE - Output enable. Can be used to quickly disable all outputs. When this pin is low all pins are enabled. When the pin is high the outputs are disabled. Pulled low by default (hence optional pin)
 * Vcc: logic power 3-5v
 * V+: power to servo 5-6v
 * Capacitor value: n * 100uF where n is the number of servos
 */

int main(void)
{
	int i = 0;

	wiringPiSetup();
	__pca9685_init();

	__pca9685_reset();

	while(i < 10) {
		__pca9685_set_pwm(MOTOR1_START, 204);
		usleep(500);
		__pca9685_set_pwm(MOTOR1_START, 224);
		usleep(500);
		__pca9685_set_pwm(MOTOR1_START, 306);
		usleep(500);
		__pca9685_set_pwm(MOTOR1_START, 408);
		usleep(1000);
	}
	return 0;
}
