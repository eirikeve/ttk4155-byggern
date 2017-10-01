#include "temp.h"

enum Orientation
{
    HORIZONTAL_LEFT,
    HORIZONTAL_RIGHT,
    VERTICAL_UPPER,
    VERTICAL_LOWER
};

class Screen
{
  private:
    OLED oled;

    Screen *superScreen;
    Screen *subScreen;

    uint8_t page0;
    uint8_t page1;
    uint8_t col0;
    uint8_t col1;

    uint8_t pagesize;
    uint8_t colsize;

    uint8_t loc_page;
    uint8_t loc_col;

    const uint8_t character_size = 5;

  public:
    Screen();
    Screen(Screen *superscreen, uint8_t sz, Orientation o);
    ~Screen();
    void addSubScreen(Screen *subscreen, uint8_t sz, Orientation o);
    void removeSubScreen();
    void updateScreenLines();

    void goToPage(uint8_t page);
    void goToColumn(uint8_t col);
    void goTo(uint8_t page, uint8_t col);
    void writeChar(unsigned char c);
    void writeString(char *string);
    void write(uint8_t c);
    void clear(uint8_t v);
};