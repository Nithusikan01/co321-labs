#include <avr/io.h>
#include <string.h>

void  usart_init(){

    /* set UBRR value = 16000000/(16 * 9600) - 1*/
    unsigned char ubrr = 103;

    /*set baud rate*/
    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char) (ubrr);

    /*Enable receiver and transmitter*/
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    /*Set frame format: 8 data, 1 stop bit*/
    UCSR0C = (1 << UCSZ01) | (3 << UCSZ00);
}

void usart_send(unsigned char data){

    /* Wait for empty transmit buffer */
    while(!(UCSR0A & (1 << UDRE0) ));

    /* Put the data into buffer, sends the  data */
    UDR0 = data;
}

unsigned char usart_receive(){
    /* Wait for the data to be received */
    while(!(UCSR0A & (1 << RXC0)));

    /* Get and return received data from buffer */
    return UDR0;
}


