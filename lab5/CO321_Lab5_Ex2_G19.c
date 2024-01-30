#include <avr/io.h>
#include <util/delay.h>

// Define the analog input pin, delay, and threshold
#define ADC_IN 2
#define DELAY 500
#define THRESHOLD_LIMIT 100

int main(void)
{
    // Set data direction for the analog input pin
    DDRC &= ~(1 << ADC_IN);
    // Set data direction for the output port
    DDRD = 0xFF;

    // Configure ADC settings
    ADCSRA = 0x00;
    // Enable ADC, set prescaler to 128
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    
    // Configure ADC multiplexer
    ADMUX = 0x00;
    // Select ADC channel 2, left-align result
    ADMUX |= (1 << MUX1) | (1 << ADLAR);

    while (1)
    {
        // Introduce a delay
        _delay_ms(DELAY);

        // Start ADC conversion
        ADCSRA |= (1 << ADSC);

        // Wait for ADC conversion to complete
        while ((ADCSRA & (1 << ADIF)))
        {
            // Waiting for conversion to finish
        }

        // Check if the ADC result is above the threshold limit
        if (ADCH > THRESHOLD_LIMIT)
        {
            // If above the limit, set all bits in PORTD to 1
            PORTD = 0xFF;
        }
        else
        {
            // If below or equal to the limit, set all bits in PORTD to 0
            PORTD = 0x00;
        }
        // PORTD = ADCH;
    }
}
