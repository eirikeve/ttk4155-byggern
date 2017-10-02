#include "subdisplay.h"
SubDisplay::SubDisplay() : Display()
{
    x0 = 0;
    y0 = 0;
    x1 = 0;
    y1 = 0;
    parent = NULL;
    child = NULL;
}
SubDisplay::SubDisplay(uint8_t bytes_x, uint8_t bytes_y) : Display(bytes_x, bytes_y)
{
    parent = NULL;
    child = NULL;
    x0 = 0;
    y0 = 0;
    x1 = bytes_x;
    y1 = bytes_y;
}

SubDisplay::SubDisplay(uint8_t bytes, SubDisplay * parent, Orientation o) : Display()
{
    if (parent != NULL &&
        ((bytes < parent->bytes_x && o <= Orientation::HORIZONTAL_RIGHT) ||
         (bytes < parent->bytes_y && o >= Orientation::VERTICAL_UPPER)))
    {
        // screen is already initialized in parent.
        // We need to set the indexes for our screen, and change the parent's indexes so that it
        // Only can modify its own space, and not that of the subdisplay.
        switch(o)
        {
            case HORIZONTAL_LEFT:
            case HORIZONTAL_RIGHT:
            {
                bytes_x = bytes;
                bytes_y = parent->bytes_y;
                break;
            }
            case VERTICAL_LOWER:
            case VERTICAL_UPPER:
            {
                bytes_x = parent->bytes_x;
                bytes_y = bytes;
                break;
            }
            default:
            // Can not be reached
                break;
        }
        parent->AddChild(this, o);
        screen = parent->screen;
    }
}

SubDisplay::~SubDisplay()
{
    if (child !=  NULL)
    {

        child->~SubDisplay();
    }
    if (parent != NULL)
    {
        
        if (parent->bytes_x != bytes_x)
        {
            parent->bytes_x += bytes_x;
            if (x0 < parent->x0)
            {
                parent->x0 = x0;
            }
            if (parent->x1 < x1)
            {
                parent->x1 = x1;
            }
        }
        else if (parent->bytes_y != bytes_y)
        {
            parent->bytes_y += bytes_y;
            if (y0 < parent->y0)
            {
                parent->y0 = y0;
            }
            if (parent->y1 < y1)
            {
                parent->y1 = y1;
            }
        }
        if (parent->child != NULL)
        {
            parent->child = NULL;
        }
    }
    else // parent was NULL, so this is the top parent. So, need to delete the screen.
    {
        
        if (screen != NULL)
        {
            for (uint8_t y = 0; y < bytes_y; ++y)
            {
                free(screen[y]);
                screen[y] = NULL;
            }
            free(screen);
            screen = NULL;
        }
        
    }

    
}

void SubDisplay::AddChild(SubDisplay * c, Orientation o)
{
    // Absolutely certainly contains bugs
    if (child != NULL)
    {
        child = c;
        switch (o)
        {
            case HORIZONTAL_LEFT:
            {
                child->x0 = x0;
                x0 += child->bytes_x;
                child->x1 = x0;
    
                child->y0 = y0;
                child->y1 = y1;
                child->bytes_y = bytes_y;
                break;
            }
            case HORIZONTAL_RIGHT:
            {
                child->x1 = x1;
                x1 -= child->bytes_x;
                x0 = parent->x1;
    
                y0 = parent->y0;
                y1 = parent->y1;
                child->bytes_y = bytes_y;
                break;
            }
            case VERTICAL_LOWER:
            {
                child->x0 = x0;
                child->x1 = x1;
    
                child->y1 = y1;
                y1 -= child->bytes_y;
                child->y0 = y1;
                child->bytes_x = bytes_x;
                break;
            }
            case VERTICAL_UPPER:
            {
                child->x0 = x0;
                child->x1 = x1;
    
                child->y0 = y0;
                y0 += child->bytes_y;
                child->y1 = y0;
                child->bytes_x = bytes_x;
                break;
            }
            default:
            {
                // Should NOT ever reach this, since the enum only has 4 values
            }
        }
    }
    
}
void SubDisplay::DeleteChild()
{
    if (child != NULL)
    {
        // Deletes the child, and also sets this->child to NULL.
        child->~SubDisplay();
    }
}
