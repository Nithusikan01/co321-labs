# Get the current directory
$currentDirectory = Get-Location

# Change to the current directory
Set-Location $currentDirectory

# Check if the number of arguments is 0
if ($args.Length -eq 0) {
    Write-Host "Usage: $MyInvocation.MyCommand <filename>"
    exit 1
}

# Get the filename from the command line arguments
$filename = $args[0]

# Compile the C code using avr-gcc
& avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -o $filename $filename.c

# Create hex file using avr-objcopy
& avr-objcopy -O ihex -R .eeprom $filename "$filename.hex"

# Flash the hex file to the ATmega328P using avrdude
& avrdude -F -V -c arduino -p ATMEGA328P -P COM7 -b 115200 -U flash:w:"$filename.hex"

