AVRMCU := atmega32
readpwm_SRC := readpwm.c ../sos/os_lcd.c


all: readpwm.hex

readpwm.hex: readpwm.elf
	avr-objcopy -j .text -j .data -O ihex readpwm.elf readpwm.hex

readpwm.elf: $(readpwm_SRC)
	avr-gcc -Os -mmcu=$(AVRMCU) -o readpwm.elf $(readpwm_SRC)

clean:
	rm *.elf *.hex
