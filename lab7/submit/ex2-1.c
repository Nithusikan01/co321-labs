/*
 * ex2-1.c
 * desc: Read user input and write to EEPROM
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

#define MAX_BUFFER_LEN 1024
char buffer[MAX_BUFFER_LEN];
int buffer_index = 0;

int main(){
  // initialize serial communication
  USARTinit(UBRR_VAL);
  stdout = fdevopen(USARTsend, NULL);
	stdin = fdevopen(NULL, USARTreceive);

  // read user input
  char ch;
  while(buffer_index != MAX_BUFFER_LEN && (ch = getchar()) != '\r')
     buffer[buffer_index++] = ch;
  
  // write to EEPROM
  for(int i=0; i<buffer_index; i++)
    EEPROMwrite(i, buffer[i]);

}
