#include <xc.h>
#include "lcd.h"
#include "mcc.h"

//--------------------------------------------------------------Global Variables
char stack[100];

//---------------------------------------------------------------------Prototype
void delay(unsigned long int t);
double calc(int a, int b, char op);
void error();
int charToInt(char c);
char readKey();

//--------------------------------------------------------------------------Main
int main(){
    char ctmp;
    // int itmp[10];
   
    
    
    SYSTEM_Initialize();
    LCD_Initialize();
    LCDClear();
    ANSELA = 0x0000;
    ANSELB = 0x0000;
    CNPDA = 0x001F;
    TRISA |= 0x001f; // i
    TRISB &= 0x0fff; // o
    int a = 0;
    int i = 0;
    while(1){
        if(a == 0){
            LCDPutCmd(LCD_HOME);

            LCDGoto(0, 0);
            LCDPutStr("Hello!");
            a = 1;
        }
        ctmp = readKey();
        if(ctmp != '!'){
            delay(50);
            if(ctmp == readKey()){
                LCDGoto(i, 1);
                i++;
                LCDPutChar(ctmp);
                delay(200);
            }
        }else if(ctmp == '!'){
            LCDGoto(i, 1);
            i++;
            LCDPutChar('$');
            delay(1000);
        }
    }
    
    
    
    return 0;
}

//------------------------------------------------------------------------------
void delay(unsigned long int t){
    unsigned long i = 0; 
    for(i = 0; i < (unsigned long)(t*(_XTAL_FREQ/150000.0)); i++);
}

//------------------------------------------------------------------------------
double calc(int a, int b, char op){
    switch(op){
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if(b != 0)
                return a / b;
            if(b == 0)
                error();
    }
}

//------------------------------------------------------------------------------
void error(){
    LCDClear();
    //LCD
}
int charToInt(char c){
    int i = 0;
    if(((int)c < 58 && (int)c > 47)){
        i = (int)c - 48;
        return i;
    }
}

//------------------------------------------------------------------------------
char readKey(){ // technical debt
    char c;
   
    LATBbits.LATB12 = 1;
    LATBbits.LATB13 = 0;
    LATBbits.LATB14 = 0;
    LATBbits.LATB15 = 0;

    if(PORTAbits.RA0)
            return '1';
    else if(PORTAbits.RA1)
            return '2';
    else if(PORTAbits.RA2)
            return '3';
    else if(PORTAbits.RA3)
            return '+';
    else if(PORTAbits.RA4)
            return '-';
    else
         c = '!';
    
    LATBbits.LATB12 = 0;
    LATBbits.LATB13 = 1;
    LATBbits.LATB14 = 0;
    LATBbits.LATB15 = 0;
    
    if(PORTAbits.RA0)
            return '4';
    else if(PORTAbits.RA1)
            return '5';
    else if(PORTAbits.RA2)
            return '6';
    else if(PORTAbits.RA3)
            return '*';
    else if(PORTAbits.RA4)
            return '/';
    else
         c = '!';
    
    LATBbits.LATB12 = 0;
    LATBbits.LATB13 = 0;
    LATBbits.LATB14 = 1;
    LATBbits.LATB15 = 0;
    
    if(PORTAbits.RA0)
            return '7';
    else if(PORTAbits.RA1)
            return '8';
    else if(PORTAbits.RA2)
            return '9';
    else if(PORTAbits.RA3)
            return '.';
    else if(PORTAbits.RA4)
            return 'd';
    else
         c = '!';
    
    LATBbits.LATB12 = 0;
    LATBbits.LATB13 = 0;
    LATBbits.LATB14 = 0;
    LATBbits.LATB15 = 1;
    
    if(PORTAbits.RA0)
            return '(';
    else if(PORTAbits.RA1)
            return '0';
    else if(PORTAbits.RA2)
            return ')';
    else if(PORTAbits.RA3)
            return 'a';
    else if(PORTAbits.RA4)
            return '=';
    else
         c = '!';

    return c;
}
