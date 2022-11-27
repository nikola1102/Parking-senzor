#include "muzika.h"
#include "mbed.h"

#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_A55  932
#define NOTE_B5  988

#define NOTE_C6  1046
#define NOTE_C66  1109
#define NOTE_D6  1175
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_F66  1480
#define NOTE_G6  1568
#define NOTE_G66  1661
#define NOTE_A6  1760
#define NOTE_A66  1865
#define NOTE_B6  1975
float note_k[] = {       //Note of the song, 0 is a rest/pulse
    NOTE_G6,NOTE_A6,0,NOTE_A6,NOTE_A66,NOTE_A6,NOTE_G6,NOTE_F6,NOTE_G6,0,NOTE_G6,NOTE_G66,NOTE_G6,NOTE_F6,NOTE_E6,
    NOTE_F6,NOTE_G6,NOTE_F6,NOTE_E6,NOTE_F6,NOTE_D6,NOTE_E6,NOTE_F6,NOTE_E6,NOTE_F6,NOTE_E6,NOTE_D6,NOTE_E6,NOTE_F6,0,
    NOTE_G6,NOTE_F6,NOTE_E6,NOTE_D6,NOTE_E6,0,NOTE_E6,NOTE_F6,NOTE_E6,NOTE_D6,0,NOTE_D6,NOTE_C66,NOTE_A55,NOTE_C66,
    NOTE_D6,NOTE_E6,NOTE_F6,NOTE_E6,NOTE_F6,NOTE_G6,NOTE_G66,NOTE_G6,NOTE_D6,NOTE_G6,NOTE_A6,0,NOTE_A6,NOTE_A66,NOTE_A6,
    NOTE_G6,NOTE_F6,NOTE_G6,NOTE_D6,NOTE_G6,NOTE_G66,NOTE_G6,NOTE_F6,NOTE_E6,NOTE_F6,NOTE_G6,NOTE_F6,NOTE_E6,NOTE_F6,NOTE_D6,
    NOTE_E6,NOTE_F6,NOTE_E6,NOTE_F6,NOTE_E6,0,NOTE_D6,NOTE_F6,NOTE_E6,NOTE_F6,0,NOTE_F6,NOTE_G6,NOTE_F6,NOTE_E6,
    NOTE_D6,NOTE_E6,0,NOTE_E6,NOTE_F6,NOTE_E6,NOTE_D6,NOTE_E6,NOTE_F6,NOTE_G6,NOTE_F6,NOTE_E6,NOTE_D6,NOTE_C66,NOTE_D6,
    NOTE_C66,0,NOTE_A6,NOTE_G66,NOTE_A6,0,NOTE_A6,NOTE_G66,NOTE_A6,0,NOTE_A6,NOTE_G66,NOTE_A6,NOTE_A66,NOTE_A6,
    NOTE_G6,0,NOTE_G6,NOTE_F66,NOTE_G6,0,NOTE_G6,NOTE_F66,NOTE_G6,0,NOTE_G6,NOTE_F66,NOTE_G6,NOTE_A6,NOTE_G6,
    NOTE_F6,0,NOTE_F6,NOTE_E6,NOTE_F6,0,NOTE_F6,NOTE_E6,NOTE_F6,0,NOTE_F6,NOTE_E6,NOTE_F6,NOTE_G6,NOTE_F6,
    NOTE_E6,0,NOTE_E6,NOTE_F6,NOTE_G6,NOTE_F6,NOTE_E6,NOTE_D6,NOTE_C66,NOTE_D6,NOTE_C66,NOTE_A5,0

};
int trajanje_k[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
    48,68,137,22,42,68,85,57,57,137,31,37,68,68,45,
    54,111,42,34,65,99,31,68,31,68,179,131,45,65,137,
    37,54,88,51,54,137,34,59,88,88,34,65,65,62,65,
    99,54,42,42,42,42,42,65,79,45,45,131,34,34,65,
    82,48,62,82,34,34,54,68,37,54,108,42,31,62,111,
    51,34,39,25,159,57,119,31,42,54,156,19,39,68,82,
    68,68,156,22,34,59,108,48,54,79,59,68,102,37,45,
    79,439,45,54,59,45,45,54,59,45,59,57,85,48,62,
    68,45,57,57,57,45,57,57,57,45,68,62,62,62,62,
    62,14,62,62,62,14,62,62,62,14,62,62,62,62,62,
    62,14,62,62,62,62,62,102,22,22,82,68,48

};
const int songspeed = 1;
float result;
float bzz = 0.5;


Muzika::Muzika(PinName pin) : _pin(pin)
{
    _pin = 0;
}
void Muzika::sviraj(int n)
{
    if (n=1) {
        for(int i=0; i<163; i++) {

            int w = trajanje_k[i] * songspeed;
            if(note_k[i] == 0) {
                result = 1;
                bzz = 0;
            } else {
                result = 1 / note_k[i];
                bzz = 0.4;
            }

            _pin.period(result);
            _pin.write(bzz);
            wait_ms(w);

        }
    }
}