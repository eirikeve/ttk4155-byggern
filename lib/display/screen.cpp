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
    // sz is number of pages (if o is UPPER or LOWER), else number of columns, for the subscreen
    if  (
         subscreen            && // subcreen argument is not NULL
        (subScreen ==  NULL)  && // This Screen does not have subScreen
        (
            // Check that we have enough space
            ( sz < (colsize)  && (o == LEFT  || o == RIGHT) )  ||
            ( sz < (pagesize) && (o == UPPER || o == LOWER) )
        )
        )
    {

        subScreen = subscreen;
        subScreen->superScreen = this;

        // Update variables - depending on the Orientation o
        subScreen->page0 = page0;
        subScreen->page1 = page1;
        subScreen->col0 = col0;
        subScreen->col1 = col1;

        if (o == LEFT)
        {
            col0 =  col0 + sz;
            subScreen->col1 = col0 + sz;
        }
        else if (o == RIGHT)
        {
            col1 = col1 - sz;
            subScreen->col0 = col1 - sz;
        }
        else if (o == LOWER)
        {
            page1 = page1 - sz;
            subScreen->page0 = page1 - sz;
        }
        else // (o == UPPER)
        {
            page0 = page0 + sz;
            subScreen->page1 = page0 + sz;
        }

        
        subScreen->pagesize = subScreen->page1 - subScreen->page0;
        pagesize = page1 - page0;
        subScreen->colsize = subScreen->col1 - subscreen->col0;
        colsize = col1 - col0;

        // Clear both screens so that we don't have remains of old text
        subScreen->clear();
        clear();
    }
}

void Screen::removeSubScreen()
{
    if (subScreen)
    {
        // subScreen.~Screen(); // Also sets page0, page1 etc.
        // Done by the destructor I thiink?

        subScreen = NULL; 
    }
}

void Screen::addBorderLines()
{
    has_border_lines = true;
    updateBorderLines();
}

void Screen::updateBorderLines()
{
    // @todo horizontal border lines. Must know what is written to the screen...

    uint8_t old_loc_col = loc_col;
    uint8_t old_loc_page = loc_page;

    // Only draw if we currently have border lines for this screen.
    if (has_border_lines)
    {
        for (uint8_t p = 0; p < pagesize; ++p)
        {
            goTo(p, 0);
            Screen::write(0b01010101);
            goTo(p, colsize - 1);
            Screen::write(0b10101010);
        }
    }
    else
    {
        for (uint8_t p = 0; p < pagesize; ++p)
        {
            goTo(p, 0);
            Screen::write(0x00);
            goTo(p, colsize - 1);
            Screen::write(0x00);
        }
    }
    goTo(old_loc_page, old_loc_col);
}

void Screen::removeBorderLines()
{
    has_border_lines = false;
    updateBorderLines();
}

void Screen::goToPage(uint8_t page)
{
    if (page < pagesize)
    {
        loc_page = page;
        oled.goToPage(loc_page + page0);
    }
}

void Screen::goToColumn(uint8_t col)
{
    if (col < colsize)
    {
        loc_col = col;
        oled.goToColumn(loc_col + col0);
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
        if (c == '\n')
        {
            while (loc_col < colsize)
            {
                write(0x00);
                loc_col+= 1;
            }
            loc_col = 1;
            loc_page += 1;
        }
        else
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

    }
    else if (loc_page >= pagesize)
    {
        // pass, there is no more space to write.
    }
    else // loc_col + character_size > colsize
    {
        if (c == '\n')
        {
            loc_col = 1;
            loc_page += 1;
        }
        // Check that we can at least write at least 1 character on a line!
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

void Screen::fill(uint8_t v)
{
    for (int j = page0; j < page1; j++)
    {
        oled.goTo(j, col0);

        for (int i = col0; i < col1; i++)
        {
            oled.write(v);
        }
    }
    updateBorderLines();
}
void Screen::clear()
{
    fill(0x00);
    goTo(0, 1);
}

void Screen::selfTest()
{
    clear();
    goTo(0, 0);
    // addBorderLines();
    writeString("Screen Test. supSc:");
    char buffer[5];
    itoa((int)(superScreen != nullptr), buffer, 10);
    writeString(buffer);
    writeString(" subScr:");
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