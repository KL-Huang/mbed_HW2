#include "mbed.h"
#include "uLCD_4DGL.h"

DigitalIn up(D3);
DigitalIn down(D6);
DigitalIn confirm(D5);
AnalogOut Aout(PA_4);
AnalogIn Ain(A0);

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

int main()
{
    int freq[3] = {300, 500, 720};
    int now = 3; // current frequency index
    int flag = 0; // enter the selection mode
//    int flag2 = 0; // enter the confirm mode
    int value = 300; // frequency after confirm
    float value2 = 0.00;
    float period = 1/300;
    int sample = 100;
    float ADCdata[100];
    int x = 0; // index of sample points

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
        if(up) {
            now++; flag = 1;
        }
        else if(down) {
            now--; 
            if(now <= 0) now += 3;
            flag = 1;
        }
        else if (flag & confirm) {
            value = freq[now % 3];
            value2 = float(value);
            printf("value = %f\n", value2);
 //           flag2 = 1;
            flag = 0;
            x = 0;
        }
        uLCD.locate(0,(now % 3) * 2 + 1);
        uLCD.printf("->");
        for (int m = 0; m < 11; m++) {
            for (int n = 0; n < 2; n++) 
                if (m != (now % 3) * 2 + 1) {
                    uLCD.locate(n, m);
                    uLCD.printf(" ");
                }
        }
        period = 1.00/value;
        for (float j = 1.0f; j >= 0.0f; j -= 0.01f) {
            Aout = j;
            wait_us(period * 100);
            if(x < sample) {
                ADCdata[x] = Ain;
                x++;
            }
//            ThisThread::sleep_for(1000ms/sample);
//        }
//        for (int i = 0; i < sample; i++){
//            ThisThread::sleep_for(100ms);
        }
        for (int y = 0; y < sample; y++)
            printf("%f\r\n", ADCdata[y]);
        ThisThread::sleep_for(10s);
    }
}


