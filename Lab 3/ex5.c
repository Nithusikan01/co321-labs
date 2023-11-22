/*
 * Group 19
 * desc: blink a LED using TIMER0
 * auth: M.S. Peeris <e19275@eng.pdn.ac.lk>
 *       T. Nithusikan <e19266@eng.pdn.ac.lk>
 *       A.P.T.T Perera <e19278@eng.pdn.ac.lk>
 * date: 22 Nov, 2023
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define TIMER_LOOP 25


int count  = 0;

int main(void){
    DDRB = DDRB | (1<<5);   //Set output pin 5

    TCNT0 = 6;    //Initial counter value

    TCCR0A = 0x00;  //Normal Mode
    TCCR0B = 0x04;  //Prescalar 256

    TIMSK0 |= (1<<TOIE0);   //Enable Time Interrupt Mask Register

    sei();  //Enable global interrupts

    PORTB = PORTB | (1<<5);
    count = 0;

    while(1){
    }

}

ISR(TIMER0_OVF_vect){

    if (count == TIMER_LOOP){
        PORTB = PORTB ^ (1<<5);
        count = 0;
    }else
        count++;

    TCNT0 = 6;    //Initial timer0 value
}