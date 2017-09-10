#!bin/bash

avr-gcc -mmcu=atmega162 -Os *.c -o main.o -std=c11
avr-objcopy -j .text -j .data -O ihex main.o main.hex
avrdude -p atmega162 -c atmelice -U flash:w:main.hex:i -U "lfuse:w:0xfd:m hfuse:w:0x91:m efuse:w:0xff:m"