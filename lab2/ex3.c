/*
 * ex3.c
 * desc: Display the number of times a push button 
 *       was pushed in binary using LEDs 
 * auth: M.S. Peeris <e19275@eng.pdn.ac.lk>
 *       T. Nithusikan <e19266@eng.pdn.ac.lk>
 *       A.P.T.T Perera <e19278@eng.pdn.ac.lk>
 * date: 8 Nov, 2023
 */
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define uc unsigned char
#define DEBOUNCE_DELAY_MS 400

uc counter = 0;

int main() {
    // Set PB as output
    DDRB |= 0b00111111;

    // Set PD2 as input with pull-up resistor
    DDRD &= ~(1 << PD2);
  
    // Set up external interrupt for falling edge trigger on PD2 (INT0)
    EICRA |= (1 << ISC01);  // Set to trigger on falling edge
    EICRA &= ~(1 << ISC00);
   
    sei(); //Global interrupts enable
  
    EIMSK |= (1 << INT0);   // Enable INT0
       

    while (1) {
        // Your application code can run here
        // This is just an example; you can add your specific functionality.
    }

    return 0;
}

// External interrupt service routine for INT0
ISR(INT0_vect) {
    // Check if the button is released
    if (!(PIND & (1 << PD2))) {
      /*Incremet the count*/
      if(PORTB == 0b00111111){
        PORTB = 0b00000000;
      }
      PORTB++;
      /*Add a delay to debounce the button*/
      _delay_ms(DEBOUNCE_DELAY_MS);
    }
}

