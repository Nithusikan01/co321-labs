/*
 * blink.c
 * desc: Blink an array of LEDS
 * auth: M.S. Peeris <e19275@eng.pdn.ac.lk>
 *       T. Nithusikan <e19266@eng.pdn.ac.lk>
 *       A.P.T.T Perera <e19278@eng.pdn.ac.lk>
 * date: 25 Oct, 2023
 */

#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 2000
#define LED_COUNT 4
const int led[LED_COUNT] = {2, 3, 4, 5};

int main(void){
  // setup led pins for output
  for(int i=0; i<LED_COUNT; i++)
    DDRB=DDRB|(1<<led[i]);
  while(1){
    // turn the LEDs on
    for(int i=0; i<LED_COUNT; i++)
      PORTB = PORTB | (1<<led[i]);
    _delay_ms(BLINK_DELAY_MS);
    // turn off the LEDs
    for(int i=0; i<LED_COUNT; i++)
      PORTB = PORTB & ~(1<<led[i]);
    _delay_ms(BLINK_DELAY_MS);
  }
}
