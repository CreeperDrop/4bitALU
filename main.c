/*
 * File:   main.c
 * Author: Ahmed Elsousy
 *
 * Created on November 18, 2021, 4:58 PM
 */

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 8000000
#include <xc.h>

unsigned char printDigit(unsigned char);
unsigned char sum(unsigned char, unsigned char);
unsigned char subt(unsigned char, unsigned char);
unsigned char bWiseAnd(unsigned char, unsigned char);
unsigned char bWiseOr(unsigned char, unsigned char);

void main(void) {
    
    ADCON1 = 0x07;      //disable analog functionality
    
    while(1){
    
    TRISA = 1;         //A and C input
    TRISC = 1;
    TRISB = 0;         //B and D output
    TRISD = 0;
    
    unsigned char A, B, inputs, result, left, right;
    
    PORTC = 0x00;     //Clear Port C just to make sure
    inputs = PORTC;
    
    A = inputs & 0xF0;      //Get the left 4 digits with the rest being 0s
    A = A >> 4;             //Shift to get rid of 0s
    B = inputs & 0x0F;      //Get the right 4 digits
    
    switch(PORTA){
            case 0x00:
                
                result = sum(A, B);
                right = result % 10;
                left = result / 10;
                
                PORTB = printDigit(left);
                PORTD = printDigit(right);
                
                break;
            
            case 0x01:
                
                result = subt(A, B);
                right = result % 10;
                left = result / 10;
                
                PORTB = printDigit(left);
                PORTD = printDigit(right);
                break;
            
            case 0x02:
                
                result = bWiseOr(A, B);
                right = result % 10;
                left = result / 10;
                
                PORTB = printDigit(left);
                PORTD = printDigit(right);
                break;
                
            case 0x03:
                
                result = bWiseAnd(A, B);
                right = result % 10;
                left = result / 10;
                
                PORTB = printDigit(left);
                PORTD = printDigit(right);
                
                break;
        }            
    }
    return;
}

unsigned char printDigit(unsigned char n){
    
    char digits[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
    
    return digits[n];
    
}

unsigned char sum(unsigned char x, unsigned char y){
    
    unsigned char result; 
    
    result = x + y;
    
    return result;
}

unsigned char subt(unsigned char x, unsigned char y){
    
    unsigned char result;
    
    if(x > y)
        result = x - y;
    else
        result = y - x;
    
    return result;
}

unsigned char bWiseAnd(unsigned char x, unsigned char y){
    unsigned char result;
    
    result = x & y;
    
    return result;
}

unsigned char bWiseOr(unsigned char x, unsigned char y){
    unsigned char result;
    
    result = x | y;
    
    return result;
}