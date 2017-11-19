#pragma once
extern "C" {
#include <stdint.h>
}

class OLED
{


private:
    const uint8_t* dataAddr = (uint8_t *)0x1200;
    const uint8_t* commandAddr = (uint8_t *)0x1000;
    OLED();

  public:
        static OLED& getInstance()
    {
        static OLED instance;
        return instance;
    }
    // Deleted due to singleton design pattern
    OLED(OLED const&) = delete;
    // Deleted due to singleton design pattern
    void operator=(OLED const&) = delete;

    void write_c(uint8_t command);
    void write(uint8_t c);

    void clear();
    void goToPage(uint8_t page);
    void goToColumn(uint8_t col);
    void goTo(uint8_t page, uint8_t col);
    void writeChar(unsigned char c);
    void writeString(char *string);

};