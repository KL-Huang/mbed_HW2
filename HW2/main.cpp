#include "mbed.h"
#include "uLCD_4DGL.h"

DigitalIn up(D3);
DigitalIn down(D4);
DigitalIn confirm(D5);
AnalogOut Aout(PA_4);
AnalogIn Ain(A0);

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
void out(int i);

int main()
{
    int freq[2] = {300, 500, 720};
    int now = 0; // current frequency index
    int flag = 0; // enter the selection mode
    int output = 0; // output the FFT
    int value = 300; // frequency after confirm
    float period = 1/300;
    int sample = 128;
    int nsample = 0;
    float ADCdata[128];

    up.mode(PullNone);
    down.mode(PullNone);
    confirm.mode(PullNone);
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.color(WHITE);
    uLCD.printf("\n   300\n");
    uLCD.printf("\n   500\n");
    uLCD.printf("\n   720");
    
    while(1){    
        out(now % 3);
        if(up) {
            now++; flag = 1;
        }
        else if(down) {
            now--; flag = 1;
        }
        else if (flag & confirm) {
            value = freq[now % 3];
            flag = 0;
            output = 1;
        }
        period = 1/value;
        for (float j = 0; j <= period; j = j + 0.01) {
            Aout = 3 * (j/period);
            ThisThread::sleep_for(10ms);
        }
    }
}

void out(int i) {
    uLCD.locate(i * 2,0);
    uLCD.printf("O");
    ThisThread::sleep_for(500ms);
}

