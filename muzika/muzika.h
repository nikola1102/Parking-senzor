#ifndef MBED_MUZIKA_H
#define MBED_MUZIKA_H
#include "mbed.h"
class Muzika
{
public:
    Muzika(PinName pin);
    void sviraj(int n);
private:
    PwmOut _pin;
};
#endif


