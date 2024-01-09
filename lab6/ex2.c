#include <avr/io.h>
#include <string.h>
#include <ex1.h>


typedef struct {
    char* name;
    char* eNumber;
} Student;


void usart_transmit_data(char* data){
    for( int i = 0; i < strlen(data); i++){
        // Sends the ith character of data 
        usart_send((unsigned char)data[i]);
    }

    // Send a new line character after the data
    usart_send("\n");
}


void transmit_student_data(Student* student){
   
        //Transmit Group members details
        usart_transmit_data(student->name);
        usart_transmit_data(student->eNumber);    
}

int main(){

    //Define Group members
    Student students[] = {
        {"Nithusikan", "E/19/266"},
        {"Sanka", "E/19/275"},
        {"Tharudi", "E/19/278"}
    }

    //Initialize USART
    usart_init();

    //Sends the student data
    for (int i = 0; i< sizeof(students)/sizeof(Student); i++){
        transmit_student_data(&students[i]);
    }


    return 0;
}







