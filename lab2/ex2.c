/*
 * ex2.c
 * desc: Toggle LED using push button 
 * auth: M.S. Peeris <e19275@eng.pdn.ac.lk>
 *       T. Nithusikan <e19266@eng.pdn.ac.lk>
 *       A.P.T.T Perera <e19278@eng.pdn.ac.lk>
 * date: 8 Nov, 2023
 */
 
 #include <avr/io.h>
#include <avr/interrupt.h>

//#define F_CPU 16000000UL  // CPU frequency (16 MHz)
#include <util/delay.h>

#define BLINK_DELAY_MS 100
int main() {
    // Set PB0 as output
    DDRB |= (1 << PB0);

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
  // toggle PB0
  if((PORTB>>0)&1)
    PORTB &= ~(1<<0);
  else
    PORTB |= (1<<0);

  // delay for switch debounce
  _delay_ms(BLINK_DELAY_MS);
}


