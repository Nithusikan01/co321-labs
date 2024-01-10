#include <avr/io.h>
#include <string.h>

#define MAX_BUFF_LEN 100

void  usart_init(){

    /* set UBRR value = 16000000/(16 * 9600) - 1*/
    unsigned char ubrr = 103;

    /*set baud rate*/
    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char) (ubrr);

    /*Enable receiver and transmitter*/
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    /*Set frame format: 8 data, 1 stop bit*/
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
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




// A function to send a sentense
void usart_transmit_sentense(char sentence[MAX_BUFF_LEN]){
    for( int i = 0; i < MAX_BUFF_LEN; i++){
        // Sends the ith character of sentence 
        usart_send((unsigned char)sentence[i]);
    }

    // Send a new line character after the sentence
    usart_send('\n');
}

//caesar_ciper
char caesar_cipher(char character){
    if(character >= 'A' && character <= 'Z'){

        return (character - 'A' + 3) % 26 + 'A';

    } else if (character >= 'a' && character <= 'z'){

        return (character - 'a' + 3) % 26 + 'a';

    }else{

        return character;
    }
}

void encrypt_and_send(){
    char character;
    char encrypted_sentense[MAX_BUFF_LEN]; // to buffer the encrypted sentense

    int i = 0;
    while((character = usart_receive()) != '\r' && i < MAX_BUFF_LEN - 1){
        encrypted_sentense[i++] = caesar_cipher(character); 
    }

    encrypted_sentense[i] = '\0'; //To indicate the end of sentense

    usart_transmit_sentense(encrypted_sentense);
}

int main() {

    //Initialize USART
    usart_init();

    while (1)
    {
        encrypt_and_send();
    }

    return 0;
    
}