#AVRMCU := atmega32
AVRMCU := atmega2560
readpwm_SRC := readpwm.c ../sos/os_lib_lcd.c
adxl345_SRC := adxl345.c ../sos/os_i2c_master.c ../sos/os_lib_lcd.c
mpu6050_SRC := mpu6050.c ../sos/os_i2c_master.c ../sos/os_lib_lcd.c
servotest_SRC := servotest.c ../sos/os_lib_servo.c
ds1307_SRC := ds1307.c ../sos/os_i2c_master.c ../sos/os_lib_lcd.c
lcdtest_SRC := lcdtest.c ../sos/os_lib_lcd.c
bmotor_SRC := bmotor.c ../sos/os_lib_lcd.c ../sos/os_lib_servo.c


all: readpwm.hex adxl345.hex servotest.hex ds1307.hex bmotor.hex lcdtest.hex mpu6050.hex

readpwm.hex: readpwm.elf
	avr-objcopy -j .text -j .data -O ihex readpwm.elf readpwm.hex

bmotor.hex: bmotor.elf
	avr-objcopy -j .text -j .data -O ihex bmotor.elf bmotor.hex

adxl345.hex: adxl345.elf
	avr-objcopy -j .text -j .data -O ihex adxl345.elf adxl345.hex

mpu6050.hex: mpu6050.elf
	avr-objcopy -j .text -j .data -O ihex mpu6050.elf mpu6050.hex

ds1307.hex: ds1307.elf
	avr-objcopy -j .text -j .data -O ihex ds1307.elf ds1307.hex

servotest.hex: servotest.elf
	avr-objcopy -j .text -j .data -O ihex servotest.elf servotest.hex

lcdtest.hex: lcdtest.elf
	avr-objcopy -j .text -j .data -O ihex lcdtest.elf lcdtest.hex

readpwm.elf: $(readpwm_SRC)
	avr-gcc -Os -mmcu=$(AVRMCU) -o readpwm.elf $(readpwm_SRC)

bmotor.elf: $(bmotor_SRC)
	avr-gcc -Os -mmcu=$(AVRMCU) -o bmotor.elf $(bmotor_SRC)

adxl345.elf: $(adxl345_SRC)
	avr-gcc -Os -mmcu=$(AVRMCU) -o adxl345.elf $(adxl345_SRC)

mpu6050.elf: $(mpu6050_SRC)
	avr-gcc -Os -mmcu=$(AVRMCU) -o mpu6050.elf $(mpu6050_SRC)

ds1307.elf: $(ds1307_SRC)
	avr-gcc -Os -mmcu=$(AVRMCU) -o ds1307.elf $(ds1307_SRC)

servotest.elf: $(servotest_SRC)
	avr-gcc -Os -mmcu=$(AVRMCU) -o servotest.elf $(servotest_SRC)

lcdtest.elf: $(lcdtest_SRC)
	avr-gcc -Os -mmcu=$(AVRMCU) -o lcdtest.elf $(lcdtest_SRC)

clean:
	rm *.elf *.hex
