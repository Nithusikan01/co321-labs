/*
 * ex1.c
 * desc: Use PWM to control the brightness of an LED 
 * auth: M.S. Peeris <e19275@eng.pdn.ac.lk>
 *       T. Nithusikan <e19266@eng.pdn.ac.lk>
 *       A.P.T.T Perera <e19278@eng.pdn.ac.lk>
 * date: Dec 6, 2023
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define uc unsigned char

int main(){
  DDRD |= (1<<PD6);
  PORTD |= (1<<PD6);

  // OCR0 = 127 for 50% duty cycle
  OCR0A = 127;

  // WGM02:0 to 111 for FAST PWM with TOP in OCR0A  
  // COM0A1:0 to 01 to toggle OC0A on compare match
  // CS02:0 to 011 for 64 factor prescaler (976.56Hz frequency)
  TCCR0A = (1<<COM0A0) | (1<<WGM01) | (1<<WGM00);
  TCCR0B = (1<<WGM02) | (1<<CS01) | (1<<CS00);
  
  while(1) ;

  return 0;
}
