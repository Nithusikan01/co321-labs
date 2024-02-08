avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -o ex3.out ex3.c lcd.c
avr-objcopy -O ihex -R .eeprom ex3.out ex3.hex
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM1 -b 115200 -U flash:w:ex3.hex

