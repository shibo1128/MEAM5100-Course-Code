/* Name: 1_2_3.c
 * Author: Shibo Wang
 * Date: 17th Sep 2023
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#include "math.h" // process the float type variable 

#define HIGH 1
#define LOW 0

void timer_pwm(void)
{
    _clockdivide(0); //set the clock speed to 16Mhz
    float duty_cycle = 0; // inrange of 0-1
    //float frequency;
    
    if(fabsf(duty_cycle)>=0.01) // Avoid the unexpective pulse
    {
        set(DDRC,6);
        TCCR3A = 0x81;   // Set mode5 and clear at counter = OCR3A
        TCCR3B = 0x0B;  // set up the timer3 with prescale /64 250kHz
        int CompareValue = duty_cycle*255;
        OCR3A = CompareValue;
    }
    else
    {
        clear(PORTC,6);
    }
}