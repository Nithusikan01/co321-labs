/*
 * ex3.c
 * desc: Simple Ceasar Cipher Encryption System using a 4x4 Keypad and 16x2 LCD Display
 * auth: M.S. Peeris <e19275@eng.pdn.ac.lk>
 *       T. Nithusikan <e19266@eng.pdn.ac.lk>
 *       A.P.T.T Perera <e19278@eng.pdn.ac.lk>
 * date: Feb 1, 2024
 */

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "eeprom.h"

#define PHRASE_SIZE 10
char phrase[PHRASE_SIZE];
#define NO_KEY '\0'

void encrypt(){
    for(int i=0; i<PHRASE_SIZE; i++){
        phrase[i] = 'A' + (phrase[i] - 'A' + ((char)EEPROMread(0) - '0')) % 4;
    }
}

char keys[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

char get_key()
{
    // set rows as output
    DDRD |= ((1 << PD6) | (1 << PD7));
    DDRB |= ((1 << PB0) | (1 << PB1));
    // set columns as input
    DDRB &= ~((1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5)); 
    // set internal pullups on inputs
    PORTB |= ((1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5));

    for (int row = 0; row < 4; row++){
        if (row < 2)
            PORTD = ~(0x40 << row);
        else
            PORTB = ~(0x01 << (row - 2));

        for (int col = 0; col < 4; col++)
        {
            if (!(PINB & (0x04 << col)))
            {
                _delay_ms(200);
                if (!(PINB & (0x04 << col)))
                    return keys[row][col];
            }
        }
    }
    return NO_KEY; // no key pressed
}


int main(void)
{
    
    // initialize display, cursor off
    lcd_init(LCD_DISP_ON);

    char c; // user input from key pad

    while (1){
        // prompt user for input
        lcd_clrscr();
        lcd_gotoxy(0, 0);
        lcd_puts("1 - Encrypt");
        lcd_gotoxy(0, 1);
        lcd_puts("2 - Change Key");

        do {
            c = get_key();
        } while ((c != '1') && (c != '2'));
        
        if (c == '1'){
            c = NO_KEY;
            lcd_clrscr();
            lcd_puts("Enter Phrase: ");
            lcd_gotoxy(0,1);
            for(int i=0; i<PHRASE_SIZE; i++){
                do {
                    c = get_key();
                } while (c == NO_KEY);
                lcd_putc(c);
                phrase[i] = c;
            }
            encrypt();
            lcd_clrscr();
            lcd_gotoxy(0,0);
            lcd_puts("Encrypted: ");
            lcd_gotoxy(0,1);
            for(int i=0; i<PHRASE_SIZE; i++){
                lcd_putc(phrase[i]);
            }
            _delay_ms(5000);
        }
        
        if (c == '2'){
            lcd_clrscr();
            lcd_gotoxy(0,0);
            lcd_puts("Curr:");
            lcd_putc((char)EEPROMread(0));
            lcd_puts("Enter Key:");
            do {
                c = get_key();
            } while (c == NO_KEY);
            lcd_gotoxy(0,1);
            lcd_putc(c);
            EEPROMwrite(0, c);
            _delay_ms(1000);
            lcd_clrscr();
            lcd_gotoxy(0,0);
            lcd_puts("Saved");
            _delay_ms(2000);
        }
    }

}
