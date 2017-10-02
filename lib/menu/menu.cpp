#include "menu.h"

Menu::Menu(MenuNode *head) : head(head),
                             current(head),
                             selectIndex(0) {}

MenuNode *Menu::getCurrent()
{
    return this->current;
}
