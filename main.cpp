#include "mbed.h"
#include "ultrasonic.h"
#include "muzika.h"

Muzika buzzer1(PA_1);

AnalogIn Ain(PC_4);
DigitalOut trig(PB_13);
DigitalIn echo(PB_14);

Ticker flip;
int udaljenost;
int t;

DigitalOut t1(PA_4);
DigitalOut t2(PB_0);
InterruptIn tipk(PA_0);

Timer debounce;
bool stanje;

BusOut Seg1(PA_5,PA_6,PA_7,PB_6,PC_7,PA_9,PA_8);
BusOut Seg2(PB_10,PB_4,PB_5,PB_3,PA_10,PC_0,PC_1);
char SegConvert(char SegValue);

char SegConvert(char SegValue)
{
    char SegByte=0x00;
    switch (SegValue) { //DPGFEDCBA
        case 0 :
            SegByte = 0x3F;
            break; // 00111111 binary
        case 1 :
            SegByte = 0x06;
            break; // 00000110 binary
        case 2 :
            SegByte = 0x5B;
            break; // 01011011 binary
        case 3 :
            SegByte = 0x4F;
            break; // 01001111 binary
        case 4 :
            SegByte = 0x66;
            break; // 01100110 binary
        case 5 :
            SegByte = 0x6D;
            break; // 01101101 binary
        case 6 :
            SegByte = 0x7D;
            break; // 01111101 binary
        case 7 :
            SegByte = 0x07;
            break; // 00000111 binary
        case 8 :
            SegByte = 0x7F;
            break; // 01111111 binary
        case 9 :
            SegByte = 0x6F;
            break; // 01101111 binary
        case 10 :
            SegByte = 0x00;
            break;
    }
    return SegByte;
}

void flip1()
{
    if (stanje == 0) {
        t1 = !t1;
        t2 = !t2;
    }
}

void uklj()
{
    if (debounce.read_ms()>200)
        stanje =! stanje;
    debounce.reset();
}

void dist(int distance)
{
    if (stanje == 0) {
        udaljenost = distance/10;
        if(udaljenost<100) {
            Seg2 = SegConvert(udaljenost/10);
            Seg1 = SegConvert(udaljenost%10);

            if(udaljenost<5) {
                buzzer1.sviraj(1);
            }
        }

        if(udaljenost>=100) {
            Seg2 = SegConvert(10);
            Seg1 = SegConvert(10);
        }


    } else {
        Seg2 = SegConvert(10);
        Seg1 = SegConvert(10);
    }
}
ultrasonic mu(PB_13, PB_14, .1, 1, &dist);

int main()
{
    stanje = 1;
    t1=0;
    debounce.start();
    tipk.mode(PullUp);
    tipk.rise(&uklj);

    flip.attach(&flip1, 0.2);
    mu.startUpdates();
    while (1) {
        mu.checkDistance();
        wait(0.05);

    }

}