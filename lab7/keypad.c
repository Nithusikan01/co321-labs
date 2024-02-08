#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

// char keypad[4][4] = {{'*', '0', '#', 'D'},
// 					{'7', '8', '9', 'C'},
// 					{'4', '5', '6', 'B'},
// 					{'1', '2', '3', 'A'}};

char keypad[4][4] = {{'D', '#', '0', '*'},
                    {'C', '9', '8', '7'},
					{'B', '6', '5', '4'},
                    {'A', '3', '2', '1'}
                    };

char readThePressedKey(){

    char pressedLetter ;
    unsigned int colVal , rowVal ;
    
	//columns are input and rows are output
    DDRD &= ~(1 << PD6) ;
    DDRD &= ~(1 << PD7) ;
    DDRB &= ~(1 << PB0) ;
    DDRB &= ~(1 << PB1) ;    

    //PC0-PC3
    
    DDRB |= (1 << PB5) ;
    DDRB |= (1 << PB4) ;
    DDRB |= (1 << PB3) ;
    DDRB |= (1 << PB2) ;


    //in idle state rows are LOW and columns are HIGH

    //PORTD = 0b11111111;
    PORTD |= (1 << PD6) ;
    PORTD |= (1 << PD7) ;
    PORTB |= (1 << PB0) ;
    PORTB |= (1 << PB1) ;



    //PORTC = 0b000000;
    PORTB &= ~(1 << PB5) ;
    PORTB &= ~(1 << PB4) ;
    PORTB &= ~(1 << PB3) ;
    PORTB &= ~(1 << PB2) ;

    while((PIND & (1<<PD7))&&(PIND & (1<<PD6))&&(PINB & (1<<PB1))&&(PINB & (1<<PB0)));

    if(!(PIND & (1<<PD6))){
        colVal = 0 ;
    }
    if(!(PIND & (1<<PD7))){
        colVal = 1 ;
    }
    if(!(PINB & (1<<PB0))){
        colVal = 2 ;
    }
    if(!(PINB & (1<<PB1))){
        colVal = 3 ;
    }

	for(int i = 2 ; i < 6 ; i++){
        PORTB = PORTB | (1 << i) ;
        _delay_ms(20);
        if((PIND & (1<<PD7))&&(PIND & (1<<PD6))&&(PINB & (1<<PB1))&&(PINB & (1<<PB0))){
            rowVal = i- 2 ;
            break;
        }
    }  

	pressedLetter = keypad[rowVal][colVal];

    char* data = "0123456789*#ABCD";
    if(strchr(data , pressedLetter) != NULL){
        return pressedLetter;
    }
    else{
        return '\0';
    }

}