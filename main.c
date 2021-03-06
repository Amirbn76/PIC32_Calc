#include <xc.h>
#include "mcc_generated_files/lcd.h"
#include "mcc_generated_files/mcc.h"

//--------------------------------------------------------------Global Variables
int error = 0;

//---------------------------------------------------------------------Prototype
void delay(unsigned long int t);
double calc(int a, int b, char op);
void showError();
int charToInt(char c);
char readKey();
void intToChar();

//--------------------------------------------------------------------------Main
int main(){
    char ctmp[100];
    double calc_result;
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
        ctmp[i] = readKey();
        if(ctmp[i] != '!'){
            delay(10);
            if(ctmp[i] == readKey() && ctmp[i] != '='){
                LCDGoto(i, 1);
                LCDPutChar(ctmp[i]);
                i++;
            }else if(ctmp[i] == readKey() && ctmp[i] == '='){
                LCDGoto(i, 1);
                LCDPutChar(ctmp[i]);
                calc_result = calc( charToInt(ctmp[i - 3]) , charToInt(ctmp[i - 1]) , ctmp[i - 2] );
                i++;
                // double to char
                i++;
            }
        }else if(ctmp[i] == '!'){
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
    if(op == '+'){
        return a + b;
    }else if(op == '-'){
        return a - b;
    }else if(op == '*'){
        return a * b;
    }else if(op == '/'){
        if(!b){
            showError();
            return 0;
        }else if(b)
            return a / b;
    }
}

//------------------------------------------------------------------------------
void showError(){ // technical debt
    LCDClear();
    LCDPutStr("error");
    error++;
}
int charToInt(char c){
    int i = 0;
    if(((int)c < 58 && (int)c > 47)){
        i = (int)c - 48;
        return i;
    }
}
void intToChar(char mem[],int n){
    int A,B,C;
    int frac;
    char chA,chB,chC,chfrac;
    C = n % 10;
    B = (n-C) % 100;
    A = (n-C-B) / 100;
    frac = n % 1;
    chA = '0'+A;
    chB = '0'+B;
    chC = '0'+C;
    chfrac = '0'+frac;
    
            mem[0] = chA;
            mem[1] = chB;
            mem[2] = chC;
            mem[3] = chfrac;
    
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
