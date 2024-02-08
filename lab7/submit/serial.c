/*
 * serial.c
 * desc: Simple USART library
 * auth: M.S. Peeris <e19275@eng.pdn.ac.lk>
 *       T. Nithusikan <e19266@eng.pdn.ac.lk>
 *       A.P.T.T Perera <e19278@eng.pdn.ac.lk>
 * date: Feb 1, 2024
 */

#include <avr/io.h>

void  USARTinit(unsigned int ubrr){
    // set baud rate
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    // enable receiver transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    // set frame format: 8 data, 2 stop bit
    UCSR0C = (1 << UCSZ01) | (3 << UCSZ00);
}

void USARTsend(unsigned char data){
    // wait for empty transmit buffer
    while(!(UCSR0A & (1 << UDRE0) ));

    // put the data into buffer, sends the  data
    UDR0 = data;
}

unsigned char USARTreceive(){
    // wait for the data to be received
    while(!(UCSR0A & (1 << RXC0)));

    // get and return received data from buffer
    return UDR0;
}


