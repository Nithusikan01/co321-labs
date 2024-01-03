
/*
 * ex1.c
 * desc: Display the number of times a push button 
 *       was pushed in binary using LEDs 
 * auth: M.S. Peeris <e19275@eng.pdn.ac.lk>
 *       T. Nithusikan <e19266@eng.pdn.ac.lk>
 *       A.P.T.T Perera <e19278@eng.pdn.ac.lk>
 * date: 1 Nov, 2023
 */

#include <avr/io.h>
#include <util/delay.h>

#define uc unsigned char
#define DEBOUNCE_DELAY_MS 300

int main() {
  // Set the first 6 pins in PORTB for output (6 LSBs for LEDs)
  DDRB = 0b00111111;
  // Set pin 7 in PORTD for input (push button)
  DDRD &= ~(1 << 7);

  uc counter = 0;
  uc btn_state = 0;

  while (1) {
    uc current_btn_state = (PIND >> 7) & 1;

    if (!btn_state && current_btn_state) {
      // Implement debounce: Wait for a short delay before counting another press
      _delay_ms(DEBOUNCE_DELAY_MS);

      // Increment counter accounting for overflow
      if (counter == 0b00111111) {
        counter = 0;
      } else {
        counter++;
      }

      // Update LEDs
      PORTB = counter;
    }

    btn_state = current_btn_state;
  }
}


