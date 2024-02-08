/*
 * eeprom.c
 * desc: Read and write to EEPROM
 * auth: M.S. Peeris <e19275@eng.pdn.ac.lk>
 *       T. Nithusikan <e19266@eng.pdn.ac.lk>
 *       A.P.T.T Perera <e19278@eng.pdn.ac.lk>
 * date: Feb 1, 2024
 */

#include <avr/io.h>

void EEPROMwrite(unsigned int address, unsigned char data){
    // wait until previous write is finished
    while(EECR & (1<<EEPE));
    // set memory address
    EEAR = address;
    // set data to write
    EEDR = data;
    // enable master write
    EECR |= (1<<EEMPE);
    // start write
    EECR |= (1<<EEPE);
}

unsigned char EEPROMread(unsigned int address){
    // wait until previous write is finished
    while(EECR & (1<<EEPE));
    // set memory address
    EEAR = address;
    // start read
    EECR |= (1<<EERE);
    return EEDR;
}
