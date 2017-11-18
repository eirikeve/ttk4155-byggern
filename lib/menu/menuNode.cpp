#include <stdlib.h>
#include <stdio.h>


#include "menuNode.h"

MenuNode::MenuNode(PROGMEM char * name, void (*callback_function)(uint8_t), uint8_t cb_fun_arg) : parent(NULL),
                                                                                                child(NULL),
                                                                                                nextSibling(NULL),
                                                                                                prevSibling(NULL),
                                                                                                name(name),
                                                                                                totNrOfChildren(0),
                                                                                                indexOfSiblings(0),
                                                                                                callback_function(callback_function),
                                                                                                callback_function_arg(cb_fun_arg) {}


MenuNode::MenuNode(PROGMEM char * name) : parent(NULL),
                                        child(NULL),
                                        nextSibling(NULL),
                                        prevSibling(NULL),
                                        name(name),
                                        totNrOfChildren(0),
                                        indexOfSiblings(0),
                                        callback_function(NULL),
                                        callback_function_arg(NULL) {}

void MenuNode::setParent(MenuNode &menu)
{
    this->parent = &menu;
}

void MenuNode::setIndexOfSiblings(uint16_t index)
{
    this->indexOfSiblings = index;
}

void MenuNode::addSibling(MenuNode &menu)
{
    if (this->nextSibling)
    {
        this->nextSibling->addSibling(menu);
    }
    else
    {
        this->nextSibling = &menu;
        menu.prevSibling = this;
        menu.setParent(*this->parent);
        menu.setIndexOfSiblings(this->getTotNrOfSiblings());
        menu.parent->totNrOfChildren++;
    }
}
void MenuNode::addChild(MenuNode &menu)
{
    if (this->child)
    {
        this->child->addSibling(menu);
    }
    else
    {
        this->child = &menu;
        menu.setParent(*this);
        this->totNrOfChildren++;
        menu.setIndexOfSiblings(1);
    }
}

MenuNode *MenuNode::getParent()
{
    return this->parent;
}

char *MenuNode::getName()
{
    return this->name;
}

uint16_t MenuNode::getTotNrOfChildren()
{
    return this->totNrOfChildren;
}

uint16_t MenuNode::getTotNrOfSiblings()
{
    if (this->parent)
    {
        return this->parent->getTotNrOfChildren();
    }
    else
    {
        return 0;
    }
}

MenuNode *MenuNode::getSibling(int8_t offset)
{
    if (offset == 0)
    {
        return this;
    }
    else if (this->nextSibling && offset > 0)
    {
        return this->nextSibling->getSibling(offset - 1);
    }
    else if (this->prevSibling && offset < 0)
    {
        return this->prevSibling->getSibling(offset + 1);
    }
    else
    {
        return NULL;
    }
}

MenuNode *MenuNode::getChild(uint8_t nr)
{
    if (this->child)
    {
        return this->child->getSibling(nr);
    }
    else
    {
        return NULL;
    }
}

MenuNode **MenuNode::getChildren()
{
    MenuNode **menus = (MenuNode **)malloc(this->getTotNrOfChildren());
    for (uint16_t i = 0; i < this->getTotNrOfChildren(); i++)
    {
        menus[i] = this->getChild(i);
    }
    return menus;
}

MenuNode **MenuNode::getSiblings()
{
    MenuNode **menus = (MenuNode **)malloc(this->getTotNrOfSiblings());

    // Get siblings before current
    for (uint16_t i = 0; i < this->indexOfSiblings; i++)
    {
        menus[i] = this->parent->getChild(i);
    }

    // Get siblings after current
    for (uint16_t i = this->indexOfSiblings + 1; i <= this->getTotNrOfSiblings(); i++)
    {
        menus[i - 1] = this->parent->getChild(i);
    }
    return menus;
}
char **MenuNode::getChildrenNames()
{
    char **names = (char **) malloc(sizeof(char*) * this->getTotNrOfChildren());
    for (uint16_t i = 0; i < this->getTotNrOfChildren(); i++)
    {
        names[i] = this->getChild(i)->getName();
    }
    return names;
}

char **MenuNode::getSiblingNames()
{
    char **menus = (char **)malloc(this->getTotNrOfSiblings());
    // Get siblings before current
    for (uint16_t i = 0; i < this->indexOfSiblings; i++)
    {
        menus[i] = this->getSibling(-this->indexOfSiblings + i)->getName();
    }

    // Get siblings after current
    for (uint16_t i = this->indexOfSiblings + 1; i <= this->getTotNrOfSiblings(); i++)
    {
        menus[i - 1] = this->parent->getChild(i)->getName();
    }
    return menus;
}