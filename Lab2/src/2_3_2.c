//
// Created by Shibo Wang on 2023/10/1.
//
#include "../inc/MEAM_general.h"
#include "m_usb.h"
#include<math.h>

void frequency_detector() {
    _clockdivide(0); //set the clock speed to 16Mhz
    set(DDRD, 1); //red LED (on for 662Hz)
    set(DDRD,2);//green LED (on for 25Hz)
    set(DDRD,0);//extra yellow
    clear(DDRB, 1);
    TCCR3B = 0x05; // pre scaler 1/1024 , count to 15625, 1 sec
    m_usb_init(); //initialize the usb communication
    while (!m_usb_isconnected()); // wait for a connection
    int frequency;
    int previous_time_stamp=0;
    int now_time_stamp=0;
    int time_stamp_gap; //unit: ms
    int previous_state=0;
    int now_state=0;

    for (;;) {
        if (TCNT3==15625){
            TCNT3=0;
            clear(PORTD,1);clear(PORTD,2);
        }// calculated by the prescaler
        // Control the LED on/off
        if (bit_is_set(PINB, 1)){now_state=1;}//donot need to set LED, just change the state
        else{now_state=0;}
        if (now_state-previous_state==1)
        {
            now_time_stamp=TCNT3; // read the time stamp
            time_stamp_gap=now_time_stamp-previous_time_stamp; //calculate time gap of one cycle
            if (time_stamp_gap>0)
            {
                frequency=15625/(time_stamp_gap);
            } //calculate the frequency
            else
            {
                frequency=15625/(time_stamp_gap+15625);
            }
            if(abs(frequency-25)<3){set(PORTD,1);clear(PORTD,2);clear(PORTD,0);}// if the detected frequency is around 25Hz, turn on the red LED
            else if(abs(frequency-662)<50){set(PORTD,2);clear(PORTD,1);clear(PORTD,0);}// if the detected frequency is around 662Hz, turn on the red LED
            else if(abs(frequency-200)<10){clear(PORTD,2);clear(PORTD,1);set(PORTD,0);}// for extra credit
            else{clear(PORTD,1);clear(PORTD,2);clear(PORTD,0);}
            previous_time_stamp=now_time_stamp;
            m_usb_tx_string("\n Frequency:");m_usb_tx_uint(frequency);
        }//down edge
        previous_state=now_state;
        frequency=0;

    }
}

