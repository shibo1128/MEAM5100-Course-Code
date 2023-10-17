#include "m_usb.h"
#include "MEAM_general.h"

void set_channel(int channel)
{
    if (channel==7)
    {
        set(DIDR0,ADC7D);//disable the digital input
        clear(ADCSRB,MUX5); //set Single-Ended Channel Selection
        set(ADMUX,MUX2);
        set(ADMUX,MUX1);
        set(ADMUX,MUX0);
    }
    if (channel==6)
    {
        set(DIDR0,ADC6D);
        clear(ADCSRB,MUX5);
        set(ADMUX,MUX2);
        set(ADMUX,MUX1);
        clear(ADMUX,MUX0);
    }
    if (channel==5)
    {
        set(DIDR0,ADC5D);
        clear(ADCSRB,MUX5);
        set(ADMUX,MUX2);
        clear(ADMUX,MUX1);
        set(ADMUX,MUX0);
    }
    set(ADCSRA,ADEN); //enable ADC
    set(ADCSRA,ADSC); //Start conversion
}

void input_test()
{   //initialize the usb output
    m_usb_init();
    while(!m_usb_isconnected()); // wait for a connection
    _disableJTAG();
    //set Vcc as the reference voltage
    set(ADMUX,REFS0);
    clear(ADMUX,REFS1);
    //set ADC frequency 125kHz
    set(ADCSRA,ADPS0);
    set(ADCSRA,ADPS1);
    set(ADCSRA,ADPS2);
    int channel=7; // initialize the first read channel
    long angle=0;

    for(;;)
    {
        set_channel(channel);
        while(!bit_is_set(ADCSRA,ADIF));//Wait for conversion to finish
        if (channel == 7)
        { _delay_ms(1000); // Convinent to observe the usb output
            channel=6; //transfer to next channel
            m_usb_tx_string("\nBase Joint: "); //print
            angle = 180.0*(ADC-0.0)/700.0; // convert ADC to angle
            m_usb_tx_long(angle);
        }
        else if (channel == 6)
        {   channel=5;
            m_usb_tx_string("\nElbow Joint: ");
            angle = 180*(ADC-175.0)/715.0;
            m_usb_tx_long(angle);
        }
        else
        {   channel=7;
            m_usb_tx_string("\nWrist Joint: ");
            angle = 75*(ADC-0)/500;
            m_usb_tx_long(angle);
        }


        set(ADCSRA,ADIF); //Clear the conversion complete flag
    }
}