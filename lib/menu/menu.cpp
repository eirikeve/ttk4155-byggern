#include "menu.h"

Menu::Menu(MenuNode *head) : head(head),
                             current(head),
                             selectIndex(0) {}
uint8_t Menu::getSelectIndex() 
{
    return this->selectIndex;
}
MenuNode *Menu::getCurrent()
{
    return this->current;
}

MenuNode *Menu::select() 
{
    this->current = this->current->getChild(this->selectIndex);
    this->selectIndex = 0;
}

void * Menu::back() 
{
    if (this->current == this->head) {
        // Root level in menu
        this->selectIndex = 0;
        return this->head;
    }
    this->current = this->current->getParent();
    this->selectIndex = 0;
}

void * Menu::up()
{
    if (this->selectIndex > 0)
    {
        this->selectIndex--;
    }
}

void *Menu::down()
{
    if (this->selectIndex < this->current->getTotNrOfChildren())
    {
        this->selectIndex++;
    }
}