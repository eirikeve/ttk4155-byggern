#include "screen.h"
extern "C" {
#include <stdlib.h>
}

Screen::Screen()
{
    oled = OLED();
    superScreen = NULL;
    subScreen = NULL;
    page0 = 0;
    page1 = 8;
    col0 = 0;
    col1 = 128;
    pagesize = page1 - page0;
    colsize = col1 - col0;
    loc_page = 0;
    loc_col = 0;
    has_border_lines = false;
}

Screen::Screen(Screen *superscreen, uint8_t sz, Orientation o) : Screen()
{
    if (superscreen)
    {
        superscreen->addSubScreen(this, sz, o);
    }
}

Screen::~Screen()
{
    if (subScreen)
    {
        subScreen->~Screen();
        subScreen = NULL;
    }
    if (superScreen)
    {
        if (superScreen->page0 != page0)
        {
            page0 = superScreen->page0;
        }
        if (superScreen->page1 != page1)
        {
            page1 = superScreen->page1;
        }
        if (superScreen->col0 != col0)
        {
            col0 = superScreen->col0;
        }
        if (superScreen->col1 != col1)
        {
            col1 = superScreen->col1;
        }
        superScreen->subScreen = NULL;
    }
}

void Screen::addSubScreen(Screen *subscreen, uint8_t sz, Orientation o)
{
    if (subscreen &&
        (((o == HORIZONTAL_LEFT || o == HORIZONTAL_RIGHT) &&
          (sz < (col1 - col0))) ||
         ((o == VERTICAL_LOWER || o == VERTICAL_LOWER) &&
          (sz < (page1 - page0)))))
    {

        subScreen = subscreen;
        subScreen->superScreen = this;
        subScreen->page0 = page0;
        subScreen->page1 = page1;
        subScreen->col0 = col0;
        subScreen->col1 = col1;

        if (o == HORIZONTAL_LEFT)
        {
            col0 = sz;
            subScreen->col1 = sz;
        }
        else if (o == HORIZONTAL_RIGHT)
        {
            col1 = sz;
            subScreen->col0 = sz;
        }
        else if (o == VERTICAL_LOWER)
        {
            page1 = sz;
            subScreen->page0 = sz;
        }
        else // o == VERTICAL_UPPER
        {
            page0 = sz;
            subScreen->page1 = sz;
        }

        subScreen->pagesize = subScreen->page1 - subScreen->page0;
        pagesize = page1 - page0;
        subScreen->colsize = subScreen->col1 - subscreen->col0;
        colsize = col1 - col0;
        subScreen->clear(0x00);
    }
}

void Screen::removeSubScreen()
{
    if (subScreen)
    {
        // subScreen.~Screen(); // Also sets page0, page1 etc.
        subScreen = NULL; // Done by the destructor I thiink
    }
}

void Screen::updateBorderLines()
{
    uint8_t old_loc_col = loc_col;
    uint8_t old_loc_page = loc_page;

    for (uint8_t p = 0; p < pagesize; ++p)
    {
        goTo(p, 0);
        Screen::write(0xFF);
        goTo(p, colsize);
        Screen::write(0xFF);
    }
}

void Screen::goToPage(uint8_t page)
{
    if (page < pagesize)
    {
        loc_page = page;
    }
}

void Screen::goToColumn(uint8_t col)
{
    if (col < colsize)
    {
        loc_col = col;
    }
}

void Screen::goTo(uint8_t page, uint8_t col)
{
    goToColumn(col);
    goToPage(page);
}

void Screen::writeChar(unsigned char c)
{
    if (loc_col + character_size <= colsize && loc_page < pagesize)
    {
        // Enough space to write one more char
        oled.goTo(loc_page + page0, loc_col + col0);
        oled.writeChar(c);
        loc_col += (character_size + 1);
        if (loc_col >= colsize)
        {
            loc_col = 1;
            loc_page += 1;
        }
    }
    else if (loc_page >= pagesize)
    {
        // pass, there is no more space to write.
    }
    else
    {
        if (colsize - 1 > character_size)
        {
            loc_col = 1;
            loc_page += 1;
            writeChar(c);
        }
    }
}

void Screen::writeString(char *string)
{
    int i = 0;
    while (string[i] != '\0')
    {
        writeChar(string[i++]);
    }
}

void Screen::write(uint8_t c)
{
    oled.write(c);
}

void Screen::clear(uint8_t v)
{
    for (int j = page0; j < page1; j++)
    {
        oled.goTo(j, 0);

        for (int i = col0; i < col1; i++)
        {
            oled.write(v);
        }
    }
}

void Screen::selfTest()
{
    clear(0x00);
    goTo(0, 0);
    // addBorderLines();
    writeString("Screen Test. superScreen:");
    char buffer[5];
    itoa((int)(superScreen != nullptr), buffer, 10);
    writeString(buffer);
    writeString(" Has subScreen:");
    itoa((int)(subScreen != nullptr), buffer, 10);
    writeString(buffer);
    writeString(" page0:");
    itoa(page0, buffer, 10);
    writeString(buffer);
    writeString(" page1:");
    itoa(page1, buffer, 10);
    writeString(buffer);
    writeString(" col0:");
    itoa(col0, buffer, 10);
    writeString(buffer);
    writeString(" col1:");
    itoa(col1, buffer, 10);
    writeString(buffer);
    char dots[160];
    for (int i = 0; i < 160; i++)
    {
        dots[i] = '.';
    }
    writeString(dots);
}