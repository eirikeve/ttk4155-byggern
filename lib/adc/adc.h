// ADC class for use in TTK4155
// Written by Håvard Borge, Eirik Vesterkjær
// 18/09/2017

#pragma once

enum Channel
{ 
    X=1, 
    Y=2
};

class ADC
{
public:
    Channel c;

public:
    ADC();
    void read();
    void selectChannel();
    uint8_t testAdc();

}