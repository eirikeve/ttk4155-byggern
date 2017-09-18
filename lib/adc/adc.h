// ADC class for use in TTK4155
// Written by Håvard Borge, Eirik Vesterkjær
// 18/09/2017

enum Channel
{ 
    X, Y;
}

class ADC
{
public:
    Channel c;

public:
    ADC();
    void read();
    void selectChannel();

}