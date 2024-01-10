#include <avr/io.h>
#include <string.h>

typedef struct {
    char* name;
    char* eNumber;
} Student;


void  usart_init(){

    /* set UBRR value = 16000000/(16 * 9600) - 1*/
    unsigned char ubrr = 103;

    /*set baud rate*/
    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char) (ubrr);

    /*Enable receiver and transmitter*/
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    /*Set frame format: 8 data, 1 stop bit, no parity*/
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


// A function to transmit the a data word
void usart_transmit_data(char* data){
    for( int i = 0; data[i] != '\0'; i++){
        // Sends the ith character of data 
        usart_send((unsigned char)data[i]);
    }

    // Send a new line character after the data
    usart_send('\n');
}


void transmit_student_data(Student* student){
   
        //Transmit Group members details
        usart_transmit_data(student->name);
        usart_transmit_data(student->eNumber);    
}

int main(){

    //Define Group members
    Student students[] = {
        {"Nithusikan", "E/19/266"},
        {"Sanka", "E/19/275"},
        {"Tharudi", "E/19/278"}
    };

    //Initialize USART
    usart_init();

    //Sends the student data
    for (int i = 0; i< sizeof(students)/sizeof(Student); i++){
        transmit_student_data(&students[i]);

  }
    
    return 0;
}