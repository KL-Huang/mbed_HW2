#include "mbed.h"
#include "uLCD_4DGL.h"

DigitalIn up(D3);
DigitalIn down(D4);
DigitalIn confirm(D5);

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

int main()
{
    up.mode(PullNone);
    down.mode(PullNone);
    confirm.mode(PullNone);
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.color(WHITE);
    uLCD.printf("\n=> number1\n");
    uLCD.printf("\n   number2\n");
    uLCD.printf("\n   number3");
    
    for (int i=10; i>=0; --i) {
        uLCD.locate(1,2);
        uLCD.printf("%2d",i);
        ThisThread::sleep_for(500ms);
    }
    
    while(1)
    {
        
    }
}