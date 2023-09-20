#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

#define HIGH 1
#define LOW 0

void broken_heart()
{
    float peak_brightness;
    set(DDRC,6);
    for(peak_brightness =1 ;peak_brightness>=0;peak_brightness-=0.05)
    {
        breath_led_routine(0.1,0.4,peak_brightness);
        breath_led_routine(0.1,0.4,peak_brightness/2);
        TCCR3A = 0x00;
        TCCR3B = 0x00;
        _delay_ms(1000);
    }
    
}
