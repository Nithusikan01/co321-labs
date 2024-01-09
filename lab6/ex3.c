#include <avr/io.h>
#include <string.h>
#include <ex1.h>


void usart_transmit_sentense(char* sentence){
    for( int i = 0; i < strlen(sentence); i++){
        // Sends the ith character of sentence 
        usart_send((unsigned char)sentence[i]);
    }

    // Send a new line character after the sentence
    usart_send("\n");
}

char caesar_cipher(char character){
    if(character >= 'A' && character <= 'Z'){

        return (character - 'A' + 3) % 26 + 'A';

    } else if (character >= 'a' && character <= 'z'){

        return (character - 'a' + 3) % 26 + 'a';

    }else{

        return character;
    }
}

void encrypt_and_send(){
    char character;
    char* encrypted_sentense; // to buffer the encrypted sentense

    int i = 0;
    while((character = usart_receive()) != '\r' && i < sizeof(encrypted_sentense) - 1){
        encrypted_sentense[i++] = caesar_cipher(character);
    }

    encrypted_sentense[i] = '\0';

    usart_transmit_sentense(encrypted_sentense);
}

int main() {

    //Initialize USART
    usart_init();

    while (1)
    {
        encrypt_and_send();
    }

    return 0;
    
}