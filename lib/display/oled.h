#pragma once
extern "C" {
#include <stdint.h>
}


/**
 * Low level class for writing to the OLED screen on the supplied I/O board.
 * This class is used by Screen objects for rendering to the screen.
 * The OLED is 128 pxl wide and 64 pxl high, where the 64 pixels are split into
 * 8 pages of 8 pixels. So, there are 128x8 = 1024 pages = 1024 bytes.
 **/
class OLED
{
private:
    // Address used for writing pixels to the oled.
    volatile uint8_t *dataAddr;
    // Address used for writing commands to the OLED.
    volatile uint8_t *commandAddr;

  public:
    // Public constructor
    OLED();
    /**
     * Writes a command to the OLED.
     * Used when initializing the screen, and changing page/column
     * @param command: A command to the OLED
     **/
    void write_c(uint8_t command);

    /**
     * Writes the 8 bit value c to the current page/column in the OLED.
     * @param c: 8 bit variable where 1 represents a pixel turned on.
     **/
    void write(uint8_t c);

    /**
     * Changes the current page to the specified page.
     * The OLED auto-increments page/column as we write.
     * @param page: New page, between 0 and 7. (0-indexed)
     **/
    void goToPage(uint8_t page);
    /**
     * Changes the current column to the specified col.
     * @param col: New column, between 0 and 127. (0-indexed)
     **/
    void goToColumn(uint8_t col);


    /**
     * Calls goToPage(page) and goToColumn(col)
     * @param page: New page, between 0 and 7. (0-indexed)
     * @param col: New column, between 0 and 127. (0-indexed)
     **/
    void goTo(uint8_t page, uint8_t col);
};