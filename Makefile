AVRMCU := atmega2560
RADIO  := R6XS
#RADIO  := NRF24L

sos_SRC := sos/os_arch.c sos/os_task.c sos/os_i2c_master.c sos/os_lib_lcd.c sos/os_lib_mpu6050.c 
sos_SRC += sos/os_lib_servo.c sos/os_sem.c sos/os_spi.c
ifeq ($(RADIO), R6XS)
	sos_SRC += sos/os_lib_radio.c
else
	sos_SRC += sos/os_lib_nrf24l01.c
endif

quad_SRC := quad_main.c


all: rtquad.hex

rtquad.hex: rtquad.elf
	avr-objcopy -j .text -j .data -O ihex rtquad.elf rtquad.hex

rtquad.elf: $(sos_SRC) $(quad_SRC)
	avr-gcc -Os -mmcu=$(AVRMCU) -o rtquad.elf $(sos_SRC) $(quad_SRC)
