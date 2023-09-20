
/* Name: 1_2_3.c
 * Author: Shibo Wang
 * Date: 17th Sep 2023
 */
#include "MEAM_general.h"
// This function is used to generate a PWM singnal with a set duty cycle
void set_duty_cycle()
{
    _clockdivide(0); //set the clock speed to 16Mhz
    
    set(DDRB,1); //set the register to make PB1 output
    float duty_cycle=0.2;       //in range of 0~1
    float frequency=200;         // Unit: Hz
    int on_off_state=ON;  // Initialize the two states ON and OFF of a square wave 
    for(;;){
        if (on_off_state == ON)
        {
            if (duty_cycle==0){clear(PORTB,1);} //Get rid of the unexpected pulse
            else
            {
                set(PORTB,1); //Set ON state
                _delay_ms(1000*(duty_cycle/frequency));
                on_off_state = OFF; //define the next state
            }
        }
        else
        {
            clear(PORTB,1);  //Set OFF state
            _delay_ms(1000*(1-duty_cycle)/frequency);
            on_off_state = ON;
        }
    }
}