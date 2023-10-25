#!/usr/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: $0 <filename>"
  exit 1
fi

FILENAME=$1

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -o $FILENAME $FILENAME.c
avr-objcopy -O ihex -R .eeprom $FILENAME $FILENAME.hex
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$FILENAME.hex
