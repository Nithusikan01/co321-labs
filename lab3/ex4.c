/*
 * Group 19
 * desc: At the same time toggles an LED and operating a Knight Rider style circuit of 4 LEDs
 * auth: M.S. Peeris <e19275@eng.pdn.ac.lk>
 *       T. Nithusikan <e19266@eng.pdn.ac.lk>
 *       A.P.T.T Perera <e19278@eng.pdn.ac.lk>
 * date: 22 Nov, 2023
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 500

#define LED_COUNT 6
const int led[LED_COUNT] = {1, 2, 3, 4, 3, 2};

int main(void){
   
    TCNT1 = 34286;    //Initial counter value bit 16

    TCCR1A = 0x00;  //Normal Mode
    TCCR1B = 0x05;  //Prescalar 1024

    TIMSK1|= (1<<TOIE1);   //Enable Time Interrupt Mask Register

    sei();  //Enable global interrupts

    DDRB = DDRB | (1<<5);
    PORTB = PORTB | (1<<5);

    // setup led pins for output
    for(int i=0; i<LED_COUNT; i++)
    DDRB=DDRB|(1<<led[i]);
    while(1){
    // light the LEDs
    for(int i=0; i<LED_COUNT; i++){
      PORTB = PORTB | (1<<led[i]);
      _delay_ms(BLINK_DELAY_MS);
      PORTB = PORTB & ~(1<<led[i]);
    }
  }
}

ISR(TIMER1_OVF_vect){

    PORTB = PORTB ^ (1<<5);
    TCNT1 = 34286;    //Initial counter value

}
