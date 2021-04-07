#include "mbed.h"
#include "uLCD_4DGL.h"

using namespace std::chrono;

AnalogOut  aout(PA_4);
AnalogIn Ain(PB_1);
uLCD_4DGL uLCD(D1, D0, D2);
InterruptIn upbtn(PA_7);
InterruptIn downbtn(PA_6);
InterruptIn confirmbtn(PA_2);
EventQueue queue1(32 * EVENTS_EVENT_SIZE);
EventQueue queue2(32 * EVENTS_EVENT_SIZE);
EventQueue queue3(32 * EVENTS_EVENT_SIZE);
float ADCdata[128]={0};
int j = 0;

bool selected = 0;
float rate = 1;

void menu()
{
    uLCD.cls();
    uLCD.printf("\nrate menu:1/8 1/4 1/2 1\n");

    if (rate == 0.125) uLCD.printf("\nrate:1/8\n");
    else if (rate == 0.25) uLCD.printf("\nrate:1/4\n");
    else if (rate == 0.5) uLCD.printf("\nrate:1/2\n");
    else if (rate == 1) uLCD.printf("\nrate:1\n");
}

void uprate()
{
    if (selected) return;
    if (rate == 0.125) rate = 0.25;
    else if (rate == 0.25) rate = 0.5;
    else if (rate == 0.5) rate = 1;

    queue1.call(&menu);
}

void downrate()
{
    if (selected) return;
    if (rate == 0.25) rate = 0.125;
    else if (rate == 0.5) rate = 0.25;
    else if (rate == 1) rate = 0.5;
    queue2.call(&menu);
}
void select_display()
{
    uLCD.cls();
    if (rate == 1) uLCD.printf("\nselected rate: 1\n");
    else if (rate == 0.5) uLCD.printf("\nselected rate: 1/2\n");
    else if (rate == 0.25) uLCD.printf("\nselected rate: 1/4\n");
    else if (rate == 0.125) uLCD.printf("\nselected rate: 1/8\n");
}
void selection()
{
    selected = 1;
    queue3.call(&select_display);

}


int main(void)
{   
    Thread upThread;
    upThread.start(callback(&queue1, &EventQueue::dispatch_forever));
    Thread downThread;
    downThread.start(callback(&queue2, &EventQueue::dispatch_forever));
    Thread conThread;
    conThread.start(callback(&queue3, &EventQueue::dispatch_forever));
    menu();
    upbtn.fall(queue1.event(&uprate));
    downbtn.fall(queue2.event(&downrate));

    confirmbtn.fall(queue3.event(&selection));
    
    while (1) {ThisThread::sleep_for(1s);}
    
    
    
    /*
    while (1) {
        if(preup != upbtn) {
            if(freq_s < 2) {
                freq_s++;
                f_change();
                preup = upbtn;
            }
        }
        if(predown != downbtn) {
            if(freq_s > 0) { 
                freq_s--;
                f_change();
                predown = downbtn;
            }
        }
        if(precon != confirmbtn) {
            freq = freq_s;
            f_change();
            precon = confirmbtn;
        }
        if (j == 128) led = 1;
        if (pretrans != transmit) {
            for (int i = 0; i < 128; i++){
                printf("%f\r\n", ADCdata[i]);
            }
            pretrans = transmit;
        }
        switch(freq)
        {
            case 2: // 240Hz
                for (float i = 0.0f; i < 0.90f; i += 0.225f) {
                    aout = i;
                    if (j < 128 && s) {
                        ADCdata[j] = Ain;
                        j++;
                    }
                    s = !s;
                    wait_us(420);
                }
                for (float i = 0.90f; i > 0.0f; i -= 0.15f) {
                    aout = i;
                    if (j < 128 && s) {
                        ADCdata[j] = Ain;
                        j++;
                    }
                    s = !s;
                    wait_us(420);
                }
                break;

            case 1: // 120Hz
                for (float i = 0.0f; i < 0.90f; i += 0.1125f) {
                    aout = i;
                    if (j < 128 && s) {
                        ADCdata[j] = Ain;
                        j++;
                    }
                    s = !s;
                    wait_us(420);
                }
                for (float i = 0.90f; i > 0.0f; i -= 0.075f) {
                    aout = i;
                    if (j < 128 && s) {
                        ADCdata[j] = Ain;
                        j++;
                    }
                    s = !s;
                    wait_us(420);
                }
                break;
            
            case 0: //60Hz
                for (float i = 0.0f; i < 0.90f; i += 0.05625f) {
                    aout = i;
                    if (j < 128 && s) {

                        ADCdata[j] = Ain;
                        j++;
                    }
                    s = !s;
                    wait_us(420);
                }
                for (float i = 0.90f; i > 0.0f; i -= 0.0375f) {
                    aout = i;
                    if (j < 128 && s) {
                        ADCdata[j] = Ain;
                        j++;
                    }
                    s = !s;
                    wait_us(420);
                }
                break;
        }
        

    }
    */

}