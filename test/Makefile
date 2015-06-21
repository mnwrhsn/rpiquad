AVRMCU := atmega32
readpwm_SRC := readpwm.c ../sos/os_lcd.c
adxl345_SRC := adxl345.c ../sos/os_i2c_master.c ../sos/os_lcd.c
servotest_SRC := servotest.c ../sos/os_servo.c
ds1307_SRC := ds1307.c ../sos/os_i2c_master.c ../sos/os_lcd.c


all: readpwm.hex adxl345.hex servotest.hex ds1307.hex

readpwm.hex: readpwm.elf
	avr-objcopy -j .text -j .data -O ihex readpwm.elf readpwm.hex

adxl345.hex: adxl345.elf
	avr-objcopy -j .text -j .data -O ihex adxl345.elf adxl345.hex

ds1307.hex: ds1307.elf
	avr-objcopy -j .text -j .data -O ihex ds1307.elf ds1307.hex

servotest.hex: servotest.elf
	avr-objcopy -j .text -j .data -O ihex servotest.elf servotest.hex

readpwm.elf: $(readpwm_SRC)
	avr-gcc -Os -mmcu=$(AVRMCU) -o readpwm.elf $(readpwm_SRC)

adxl345.elf: $(adxl345_SRC)
	avr-gcc -Os -mmcu=$(AVRMCU) -o adxl345.elf $(adxl345_SRC)

ds1307.elf: $(ds1307_SRC)
	avr-gcc -Os -mmcu=$(AVRMCU) -o ds1307.elf $(ds1307_SRC)

servotest.elf: $(servotest_SRC)
	avr-gcc -Os -mmcu=$(AVRMCU) -o servotest.elf $(servotest_SRC)

clean:
	rm *.elf *.hex
