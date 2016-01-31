AVRMCU := atmega32
stacktest_SRC := stacktest.c


all: stacktest.hex

stacktest.hex: stacktest.elf
	avr-objcopy -j .text -j .data -O ihex stacktest.elf stacktest.hex

stacktest.elf: $(stacktest_SRC)
	avr-gcc -Os -mmcu=$(AVRMCU) -o stacktest.elf $(stacktest_SRC)

clean:
	rm *.elf *.hex
