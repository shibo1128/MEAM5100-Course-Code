//
// Created by Shibo Wang on 2023/10/1.
//
#include "../inc/MEAM_general.h"
#include "m_usb.h"





void light_contol_LED() {
    _clockdivide(0); //set the clock speed to 16Mhz
    set(DDRD, 1);
    clear(DDRB, 1);//set the input port, which connected with the phototransistor
    //m_usb_init(); //initialize the usb communication
    //while (!m_usb_isconnected()); // wait for a connection


    for (;;) {

        // Control the LED on/off
        if (bit_is_set(PINB, 1)) {set(PORTD,1);}//on LED
        else {clear(PORTD, 1); }//off led

    }
}
