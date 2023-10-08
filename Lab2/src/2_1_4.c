//
// Created by Shibo Wang on 2023/10/1.
//

#include "../inc/MEAM_general.h"
#include "m_usb.h"

void test_pinMode()
{
    pinMode(B, 1, INPUT_PULLUP);
    pinMode(D, 1, OUTPUT);
    for(;;)
    {
        if (bit_is_set(PINB,1)){clear(PORTD,1);}//on LED
        else{set(PORTD,1);}
    }
}