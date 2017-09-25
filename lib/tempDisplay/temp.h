#pragma once
extern "C" {
#include <stdint.h>
}

class OLED
{
  private:
    volatile uint8_t *dataAddr;
    volatile uint8_t *commandAddr;

  public:
    OLED();
    void write_c(uint8_t command);
    void write(uint8_t c);

    void clear();
    void goToPage(uint8_t page);
    void goTo(uint8_t page, uint8_t col);
    void writeChar(unsigned char c);
    void writeString(char *string);

};