//
// Created by Shibo Wang on 2023/10/1.
//
#include "../inc/MEAM_general.h"
#include "m_usb.h"

#define comparevalue 15625



void switch_control_LED()
{
    _clockdivide(0); //set the clock speed to 16Mhz
    set(DDRD,1);  //set PD1 port as output
    clear(DDRB,1);  //set PB! port as input
    m_usb_init(); //initialize the usb communication
    while(!m_usb_isconnected()); // wait for a connection
    TCCR3B = 0x05; //enable the timer3 with prescaler 1/1024
    //float ms;
    int previous_state=0;
    int now_state=0;     //record

    for(;;){
        // Control the LED on/off
        if (bit_is_set(PINB,1)){clear(PORTD,1);now_state=1;}//on LED and set state
        else{set(PORTD,1); now_state=0;}//off led and set state
        if (previous_state-now_state!=0){m_usb_tx_string("\n state changed Time Stamp:");m_usb_tx_uint(TCNT3);}
        //when the state changes (depress or release the switch), print time stamp via usb.
        previous_state=now_state;
    }
}
