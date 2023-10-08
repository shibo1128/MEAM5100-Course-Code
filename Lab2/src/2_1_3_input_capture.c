//
// Created by Shibo Wang on 2023/10/1.
//
#include "../inc/MEAM_general.h"
#include "m_usb.h"


void measure_press_time_gap_using_input_capture() {
    _clockdivide(0); //set the clock speed to 16Mhz
    set(DDRD, 1); //set PD1 port as output
    clear(DDRC, 7);//set PC7 port as input(timer 3 input capture)
    set(TCCR3B,ICES3); //store timer value at rising edge
    m_usb_init(); //initialize the usb communication
    while (!m_usb_isconnected()); // wait for a connection
    TCCR3B = 0x05; //set timer3
    //float ms;
    long previous_press_time_stamp = 0;  //unit: ms
    long now_press_time_stamp = 0;
    long time_stamp_gap;
    long time_gap;//unit:ms


    for (;;) {
        if (TCNT3 == 15625) {TCNT3 = 0;}
        // Control the LED on/off
        if (bit_is_set(PINC, 7)) {clear(PORTD, 1);}//on LED and set state
        else {set(PORTD, 1);}//off led and set state
 //at the rising edge (press down the switch)
        now_press_time_stamp = ICR3; //record time stamp
        time_stamp_gap = now_press_time_stamp - previous_press_time_stamp; //calculate the time stamp gap between 2 rising edge
        time_gap = time_stamp_gap * 1000 / 15162;//using time stamp gap to calculate the time gap
        if (time_gap > 0 )//Remove disturbing values
            {
                m_usb_tx_string("\n Press gap(ms):");
                m_usb_tx_long(now_press_time_stamp); //print the calculated time
            }
        previous_press_time_stamp = now_press_time_stamp;//Passing time stamp to the next loop

    }
}