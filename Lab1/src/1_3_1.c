/* Name: 1_2_3.c
 * Author: Shibo Wang
 * Date: 17th Sep 2023
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

#define HIGH 1
#define LOW 0
#define CompareValue 6250 //The calculate equation is shown in my report.

void timer_20Hz(void)
{
    _clockdivide(0); //set the clock speed to 16Mhz
    TCCR3B = 0x03;  // set up the timer3 with prescale /64 250kHz
    set(DDRB,1);
    for(;;){
        /*----------1.3.1----------*/
        if (TCNT3 > CompareValue)
        {
        toggle(PORTB,1); //To set the output frequency 20Hz, toggle the port every 1/40s 
        TCNT3 = 0; // Reset the timer to 0
        }

    }
}