/*
 * Group 19
 * desc: blink 2 LEDs 
 * auth: M.S. Peeris <e19275@eng.pdn.ac.lk>
 *       T. Nithusikan <e19266@eng.pdn.ac.lk>
 *       A.P.T.T Perera <e19278@eng.pdn.ac.lk>
 * date: 22 Nov, 2023
 */


#include <avr/io.h>
#include <avr/interrupt.h>

#define LED1_PIN 0
#define LED2_PIN 1

#define LED1_COUNT_LIMIT 12
#define LED1_SUB_START 203

int led1Count  = 0;
unsigned char led1Flag = 0; 

int main(void){
    DDRB |= (1<<LED1_PIN) | (1<<LED2_PIN);   //Set output pins 5

    // TIMER0 config
    TCNT0 = 0;    //Initial counter value
    TCCR0A = 0x00;  //Normal Mode
    TCCR0B = 0x04;  //Prescalar 256

    // TIMER1 config
    TCNT1 = 34286;    //Initial counter value
    TCCR1A = 0x00;  //Normal Mode
    TCCR1B = 0x04;  //Prescalar 256

    TIMSK0 |= (1<<TOIE0);   //Enable Time Interrupt Mask Register
    TIMSK1 |= (1<<TOIE1);   //Enable Time Interrupt Mask Register

    sei();  //Enable global interrupts

    PORTB = PORTB | (1<<LED1_PIN);
    PORTB = PORTB | (1<<LED2_PIN);

    led1Count = 0;

    while(1){
    }
    
}

ISR(TIMER0_OVF_vect){

    if (led1Flag == 1){
        led1Flag = 0;
        PORTB = PORTB ^ (1<<LED1_PIN);
        TCNT0 = 0;    //Initial timer0 value
    }
    else if (led1Count == LED1_COUNT_LIMIT){
        led1Flag = 1;
        led1Count = 0;
        TCNT0 = LED1_SUB_START;
    } else{
        led1Count++;
        TCNT0 = 0;    //Initial timer0 value
    }
}

ISR(TIMER1_OVF_vect){
    PORTB = PORTB ^ (1<<LED2_PIN);
    TCNT1 = 34286;    //Initial counter value
}