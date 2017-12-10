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

void Menu::select()
{
    MenuNode *child = this->current->getChild(this->selectIndex);
    if (child != NULL)
    {
        // Check that child to be selected has another child again.
        // (That the child has at least one more choise for user).
        // If not, check if child has a callback function that should be called
        if (child->getChild(0) != NULL){
            this->current = child;
            this->selectIndex = 0;
        }
        else if (child->callback_function != NULL){
            child->callback_function(child->callback_function_arg);
        }
    }
}

void Menu::back()
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

void Menu::up()
{
    if (this->selectIndex > 0)
    {
        this->selectIndex--;
    }
}

void Menu::down()
{
    if (this->selectIndex < this->current->getTotNrOfChildren() - 1)
    {
        this->selectIndex++;
    }
}
