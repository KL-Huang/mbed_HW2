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
    int flag2 = 0; // enter the confirm mode
    int value = 300; // frequency after confirm
    float value2 = 0.00;
    float period = 1/300;
    int sample = 128;
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
            flag2 = 1;
            flag = 0;
        }
    //    printf("flag2 = %d\n", flag2);
        uLCD.locate(0,(now % 3) * 2 + 1);
        uLCD.printf("O");
        for (int m = 0; m < 11; m++) 
            if (m != (now % 3) * 2 + 1) {
                uLCD.locate(0, m);
                uLCD.printf(" ");
            }
        if(flag2) {
            period = 1.00/value;
//            for (float j = period; j >= 0.00; j = j - period/1000.00)
            for (float j = 1.0f; j >= 0.0f; j -= 0.01f) {
                Aout = j;
                wait_us(period * 100);
            //    printf("period = %f\n", period);
            //    printf("Aout = %f\n", 3.00 * (j/period));
            //    ThisThread::sleep_for(10ms);
            }
            for (int i = 0; i < sample; i++) {
                ADCdata[i] = Ain;
                ThisThread::sleep_for(1000ms/sample);
            }
            for (int i = 0; i < sample; i++){
                printf("%f\r\n", ADCdata[i]);
                ThisThread::sleep_for(100ms);
            }
            flag2 = 0;
        }
    }
}


