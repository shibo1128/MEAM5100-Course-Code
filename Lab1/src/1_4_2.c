/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

#define HIGH 1
#define LOW 0

void breath_led_routine(float increase_time, float decrease_time, float peak_brightness)
{
    _clockdivide(0); //set the clock speed to 16Mhz
    float increase_cycles = increase_time*1000/(1+(256/16000000));  
    // calculate how many times the timer count to 255 from 0
    float decrease_cycles = decrease_time*1000/(1+(256/16000000));  
    float increase_gap = 256/increase_cycles;
    //calculate how the step between each loop.
    float decrease_gap = 256/decrease_cycles;
    set(DDRC,6);
    TCCR3A = 0x81;
    TCCR3B = 0x09;  // set up the timer3 with prescale /1 16MHz
    float CompareValue=0;
    for(;;){
        for (; CompareValue<=255; CompareValue += increase_gap)
        //accumulate the duty cycle step
        {
            OCR3A = CompareValue*peak_brightness;// Change the peak brightness
            _delay_ms(1);
        }
        CompareValue=255;
        for (; CompareValue>=0; CompareValue -= decrease_gap)
        {
            OCR3A = CompareValue*peak_brightness;
            _delay_ms(1);
        }
        break;
    }
}

void heart_beat()
{
    for(;;)
    {//call the routine and set the increasing time to 0.1, decreasing time to 0.4 and peak value to 1 or 0.5 as the time in the questio
        breath_led_routine(0.1,0.4,1);
        breath_led_routine(0.1,0.4,0.5);
        breath_led_routine(0.1,0.4,1);
        breath_led_routine(0.1,0.4,0.5);
        _delay_ms(2000);
        }
    
}


