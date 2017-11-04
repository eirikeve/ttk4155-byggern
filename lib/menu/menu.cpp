extern "C" {
#include <stdlib.h>
#include <stdio.h>
}
#include "menu.h"

Menu::Menu(MenuNode *head) : head(head),
                             current(head),
                             selectIndex(0)
{
}
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
    if (this->current->getChild(0) != NULL)
    {
        // printf("%s\n", this->current->getName());
        printf("%s\n", this->current->getChild(this->selectIndex)->getName());
        this->current = this->current->getChild(this->selectIndex);
        this->selectIndex = 0;
    }
}

void *Menu::back()
{
    if (this->current == this->head)
    {
        // Root level in menu
        // this->selectIndex = 0;
        return this->head;
    }
    this->current = this->current->getParent();
    this->selectIndex = 0;
}

void *Menu::up()
{
    if (this->selectIndex > 0)
    {
        this->selectIndex--;
    }
}

void *Menu::down()
{
    if (this->selectIndex < this->current->getTotNrOfChildren() - 1)
    {
        this->selectIndex++;
    }
}
