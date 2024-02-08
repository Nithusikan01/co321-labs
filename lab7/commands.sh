avr-gcc -Os -D F_CPU=16000000UL -mmcu=atmega328p -o serial.o -c serial.c
avr-gcc -Os -D F_CPU=16000000UL -mmcu=atmega328p -o eeprom.o -c eeprom.c
avr-gcc -Os -D F_CPU=16000000UL -mmcu=atmega328p -o ex2-1.o -c ex2-1.c
avr-gcc -mmcu=atmega328p serial.o eeprom.o ex2-1.o -o ex2-1.elf
