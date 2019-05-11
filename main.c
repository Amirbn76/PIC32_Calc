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
    ANSELA = 0x0000;
    ANSELB = 0x0000;
    CNPDA = 0x001F;
    
    SYSTEM_Initialize();
    LCD_Initialize();
    LCDClear();
   
    while(1){
        LCDPutCmd(LCD_HOME);
        LCDGoto(0, 0);
        LCDPutStr("Hello!");
        LCDGoto(6, 0);
        ctmp = readKey();
        if(ctmp != '\0'){
            LCDPutStr("test");
            LCDGoto(0, 1);
            LCDPutChar(ctmp);
            delay(200);
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
    LCDPutStr("Error!");
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
    TRISA = 0x001F; // i
    TRISB = 0x0000; // o
    
    LATBbits.LATB12 = 1;
    LATBbits.LATB13 = 0;
    LATBbits.LATB14 = 0;
    LATBbits.LATB15 = 0;
    switch(PORTA){
        case 0x01:
            return '1';
        case 0x02:
            return '2';
        case 0x04:
            return '3';
        case 0x08:
            return '+';
        case 0x10:
            return '-';
        default:
            c = '\0';
    }
    
    LATBbits.LATB12 = 0;
    LATBbits.LATB13 = 1;
    LATBbits.LATB14 = 0;
    LATBbits.LATB15 = 0;
    switch(PORTA){
        case 0x01:
            return '4';
        case 0x02:
            return '5';
        case 0x04:
            return '6';
        case 0x08:
            return '*';
        case 0x10:
            return '/';
        default:
            c = '\0';
    }
    
    LATBbits.LATB12 = 0;
    LATBbits.LATB13 = 0;
    LATBbits.LATB14 = 1;
    LATBbits.LATB15 = 0;
    switch(PORTA){
        case 0x01:
            return '7';
        case 0x02:
            return '8';
        case 0x04:
            return '9';
        case 0x08:
            return '.';
        case 0x10:
            return 'd';
        default:
            c = '\0';
    }
    
    LATBbits.LATB12 = 0;
    LATBbits.LATB13 = 0;
    LATBbits.LATB14 = 0;
    LATBbits.LATB15 = 1;
    switch(PORTA){
        case 0x01:
            return '(';
        case 0x02:
            return '0';
        case 0x04:
            return ')';
        case 0x08:
            return 'a';
        case 0x10:
            return '=';
        default:
            c = '\0';
    }

    
    return c;
}
