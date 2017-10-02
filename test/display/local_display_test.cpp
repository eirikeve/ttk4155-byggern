#include <stdint.h>
#include <iostream>
#include "display.h"
#include "subdisplay.h"

template<typename T>
void print(T t)
{
    std::cout<<t;
}
template<typename T, typename W>
void print(T t, W w)
{
    print(t);
    print(w);
}
template<typename T, typename W, typename Z>
void print(T t, W w, Z z)
{
    print(t);
    print(w);
    print(z);
}
template<typename T, typename W, typename Z, typename K>
void print(T t, W w, Z z, K k)
{
    print(t);
    print(w);
    print(z);
    print(k);
}
void test1()
{
    int x_sz = 10;
    int y_sz = 10;
    print("Initializing Display:\n");
    Display d = Display(x_sz, y_sz);
    d.debugDisplay();
    print("Drawing to display:\n");
    d.Set(0b11111111, 0,0);
    d.debugDisplay();
    print("Masking the drawn area:\n");
    d.Mask(0b01010101, 0,0);
    d.debugDisplay();
    print("Adding to the drawn area:\n");
    d.Add(0b10100000, 0, 0);
    d.debugDisplay();
    print("Drawing the next byte:\n");
    d.Set(0b11111111, 1, 0);
    d.debugDisplay();
    print("Clearing the first byte:\n");
    d.Clr(0,0);
    d.debugDisplay();
    print("Filling the whole display:\n");
    for (int i = 0; i < x_sz; ++i)
    {
        for (int j = 0; j < y_sz; ++j)
        {
            d.Set(0b11111111, i, j);
        }
    }
    d.debugDisplay();
    print("Clearing the whole display:\n");
    d.Clr();
    d.debugDisplay();
    print("Trying to delete screen:\n");
    //d.testDeleteScreen();
    print("Deleted screen\n");
}

void test2()
{
    int x_sz = 12;
    int y_sz = 8;
    int sub_sz = 4;
    Orientation sub_orientation = Orientation::HORIZONTAL_RIGHT;
    for (int i = 0; i < 4; ++i)
    {
        if (i == 0)
        {
            sub_orientation = Orientation::HORIZONTAL_RIGHT;
            print("Test for Horizontal Right:\n");
        }
        else if (i == 1) 
        {
            sub_orientation = Orientation::HORIZONTAL_LEFT;
            print("Test for Horizontal Left:\n");
        }
        else if (i == 2) 
        {
            sub_orientation = Orientation::VERTICAL_LOWER;
            print("Test for Vertical Lower:\n");
        }
        else if (i == 3)
        {
            sub_orientation = Orientation::VERTICAL_UPPER;
            print("Test for Vertical Upper:\n");
        }
        print("Creating parent\n");
        SubDisplay p = SubDisplay(x_sz, y_sz);
        print("Printing parent:\n");
        print("DimX:", p.getMaxX(), " DimY:", p.getMaxY());
        print("\n");
        p.debugDisplay();
        print("Creating child\n");
        SubDisplay c = SubDisplay(sub_sz, &p, sub_orientation);
        print("Printing child:\n");
        print("DimX:", c.getMaxX(), " DimY:", c.getMaxY());
        print("\n");
        c.debugDisplay();
        print("Printing parent after adding child:\n");
        p.debugDisplay();
        print("Adding a 1111 1111 to child[0][0]\n");
        c.Set(0b11111111, 0,0);
        print("Printing resulting child:\n");
        c.debugDisplay();
        print("Printing parent:\n");
        p.debugDisplay();

        print("Trying to remove child:\n");
        p.DeleteChild();
        print("Trying to delete the screen:\n");
        p.testDeleteScreen();
        


        
        
    }
    

    
}

int main()
{
    print("---------\nTest 1:\n");
    test1();
    //print("---------\nTest 2:\n");
    //test2();

    return 0;
}