/*
 * ex3.c
 * desc: Use PWM to control a buzzer 
 * auth: M.S. Peeris <e19275@eng.pdn.ac.lk>
 *       T. Nithusikan <e19266@eng.pdn.ac.lk>
 *       A.P.T.T Perera <e19278@eng.pdn.ac.lk>
 * date: Jan 3, 2024
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Frequency of musical notes
#define C4_S 277
#define D4 294
#define E4 330
#define F4_S 370
#define G4 392
#define A4 440
#define B4 494
#define C5_S 554
#define D5 587
#define E5 659
#define F5_S 740
#define G5 784
#define A5 880
#define B5 988
#define C6_S 1109
#define D6 1175
#define E6 1319
#define F6_S 1480
#define G6 1568
#define A6 1760
#define B6 1976

// Time to play a quarter note
#define UNIT_TIME 380

#define TIM1_PRESCALER 8
#define DUTY_CYCLE 10

typedef struct {
  uint16_t freq; // frequency of the note
  float time; // how long the note should sustain
} note;

// Intro of Final Fantasy XII-2 Run 
const note score[] =
{
  {B4, 2}, {F5_S, 2}, 
  {F5_S, 1}, {A5, 1}, {E5, 1}, {D5, 1}, 
  {C5_S, 0.66}, {D5, 0.66}, {E5, 0.66}, {A4, 2},
  {A4, 2}, {D5, 1}, {C5_S, 1},
  {B4, 2}, {F5_S, 2},
  {F5_S, 1}, {A5, 1}, {E5, 1}, {D5, 1}, 
  {C5_S, 0.66}, {D5, 0.66}, {E5, 0.66}, {C6_S, 2},
  {C6_S, 2}, {C6_S, 2},
  {D6, 2}, {F5_S, 2},
  {F5_S, 1}, {F5_S, 1}, {E6, 1}, {D6, 1},
  {C6_S, 2}, {E5, 2},
  {E5, 1}, {D6, 1}, {C6_S, 1}, {A5, 1},
  {B5, 2}, {E5, 2},
  {E5, 1}, {E5, 1}, {D5, 1}, {C5_S, 1},
  {F5_S, 4}
};

// Use timer0 to create a 1ms delay
void delay_1ms(){
  TCNT0 = 6; // 250 * (64 / 16Mhz) = 1ms
  TCCR0A = 0;
  TCCR0B |= (1<<CS01) | (1<<CS00); // 64 prescaler

  while(!(TIFR0 & (1<<TOV0))); // Wait until TOV0 flag is set

  TCCR0B = 0; // Turn off timer

  TIFR0 |= (1<<TOV0); // Clear TOV0 flag
}

// Create a delay of any amount(val) of miliseconds
void delay(int val){
  for(int i=0; i<val; i++)
    delay_1ms();
}


void tone(uint16_t freq, int dur) {
  // Set PB1 to be an output (Pin 9 Arduino UNO)
  DDRB |= (1 << PB1);

  // Set non-inverting mode
  TCCR1A |= (1 << COM1A1);

  // Set fast PWM Mode with
  //    TOP value in ICR1
  //    OCR1A updated at bottom
  //    TOV1 set on TOP
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << WGM13);

  // Set prescaler to 8 and starts PWM
  TCCR1B |= (1 << CS11);

  // Set PWM frequency/top value
  ICR1 = (F_CPU / (TIM1_PRESCALER*freq)) - 1;
  // Set duty cycle
  OCR1A = ICR1 / (100 / DUTY_CYCLE);

  delay(dur);

  // Turn off PWM Signal
  TCCR1A = 0x00;
  TCCR1B = 0x00;

}

// Play all notes for debugging
void tone_test(){
  const uint16_t tones[] = {
    C4_S, D4, E4, F4_S, G4, A4, B4,
    C5_S, D5, E5, F5_S, G5, A5, B5, 
    C6_S, D6, E6, F6_S, G6, A6, B6
  };

  for(int i=0; i<sizeof(tones)/sizeof(uint16_t); i++)
    tone(tones[i], 200);
}

int main() {
  while(1){
    for(int i=0; i<sizeof(score)/sizeof(note); i++)
      tone(score[i].freq, UNIT_TIME*score[i].time);
  }
  return 0;
}

