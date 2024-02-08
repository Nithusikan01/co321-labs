/*
 * ex2-1.c
 * desc: Read first 1024 bytes of EEPROM and print to serial
 * auth: M.S. Peeris <e19275@eng.pdn.ac.lk>
 *       T. Nithusikan <e19266@eng.pdn.ac.lk>
 *       A.P.T.T Perera <e19278@eng.pdn.ac.lk>
 * date: Feb 1, 2024
 */

#include <avr/io.h>
#include <stdio.h>
#include "eeprom.c"
#include "serial.c"
#include <util/delay.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VAL F_CPU/16/BAUD-1

#define EEPROM_SIZE 1024

int main(){
  // initialize serial communication
  USARTinit(UBRR_VAL);
  stdout = fdevopen(USARTsend, NULL);
  
  while(1){
    // read EEPROM
    for(int i=0; i<EEPROM_SIZE; i++)
        printf("%d %c\n", i, EEPROMread(i));
  }
}
