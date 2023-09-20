/* Name: 1_2_3.c
 * Author: Shibo Wang
 * Date: 17th Sep 2023
 */
#include "MEAM_general.h"

/*
This function is used to control the PB1 port output a square wave every 2s.
*/
void portb_out(void)
{
    _clockdivide(0); //set the clock speed to 16Mhz
    
    set(DDRB,1); // set the register DDRB to make the port state to output.
    
    for(;;){
        toggle(PORTB,1);	// switch PB1 output state
        _delay_ms(1000);		// wait 1000ms = 1s
    } 
}