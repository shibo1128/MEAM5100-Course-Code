//
// Created by HP on 2023/9/30.
//

#include "m_usb.h"
#include "MEAM_general.h"

void usb_communication_test()
{
    m_usb_init();
    while(!m_usb_isconnected()); // wait for a connection
    while(1)
    {
        m_usb_tx_uint(16);
        _delay_ms(1000);
    }
}
