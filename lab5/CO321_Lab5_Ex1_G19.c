#include <avr/io.h>
#include <util/delay.h>

// Define the pin and delay
#define ADC_IN 1
#define DELAY 500

int main(void)
{
    // Set data direction for the analog input pin
    DDRC &= ~(1 << ADC_IN);
    // Set data direction for the output port
    DDRD = 0xFF;
    
    // Configure ADC settings
    ADCSRA = 0x00;
    // Enable ADC, set prescaler to 128
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    // ADCSRA |= (1 << ADPS0);
    
    // Configure ADC multiplexer
    ADMUX = 0x00;
    // Set reference voltage to AVCC, select ADC channel 1, left-align result
    ADMUX |= (1 << REFS0) | (1 << MUX0) | (1 << ADLAR);

    while (1)
    {
        // Introduce a delay
        _delay_ms(DELAY);

        // Start ADC conversion
        ADCSRA |= (1 << ADSC);

        // Wait for ADC conversion to complete
         while ((ADCSRA & (1 << ADIF)))
        // while (ADCSRA & (1 << ADIF))
        {
            ;// Waiting for conversion to finish
        }

        // Store ADC result in PORTD
        PORTD = ADCH;
    
    }
}
