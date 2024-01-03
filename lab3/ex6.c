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

#define TIMER_LOOP 25
 
int count  = 0;

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

    while(1){
    }
    
}

ISR(TIMER0_OVF_vect){

    if (count == TIMER_LOOP){
        PORTB = PORTB ^ (1<<LED1_PIN);
        count = 0;
    }else
        count++;

    TCNT0 = 0;    //Initial timer0 value
}

ISR(TIMER1_OVF_vect){
    PORTB = PORTB ^ (1<<LED2_PIN);
    TCNT1 = 34286;    //Initial counter value
}
