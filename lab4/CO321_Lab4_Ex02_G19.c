/*
 * ex2.c
 * desc: Fade an LED using PWM 
 * auth: M.S. Peeris <e19275@eng.pdn.ac.lk>
 *       T. Nithusikan <e19266@eng.pdn.ac.lk>
 *       A.P.T.T Perera <e19278@eng.pdn.ac.lk>
 * date: Dec 6, 2023
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(){
  DDRD |= (1<<PD6);

  TCCR0A |= (1<<WGM01) | (1<<WGM00); // fast PWM mode
  TCCR0A |= (1<<COM0A1); // non-inverting mode
  TCCR0B |= (1<<CS01) | (1<<CS00); // 64 factor prescaler (976.56Hz freq)
  
  while(1) {
    for(int i=0; i<256; i++){
      OCR0A = i;
      _delay_ms(10);
    }
    for(int i=255; i>-1; i--){
      OCR0A = i;
      _delay_ms(10);
    }
  }

  return 0;
}
