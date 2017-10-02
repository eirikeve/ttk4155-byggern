#include "menuNode.h"
extern "C" {
#include <stdlib.h>
#include "../../node1/include/comm.h"
#include <stdio.h>
}

MenuNode::MenuNode(char *name) : parent(NULL),
                                 child(NULL),
                                 sibling(NULL),
                                 name(name),
                                 totNrOfChildren(0),
                                 indexOfSiblings(0) {}

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
    if (this->sibling)
    {
        this->sibling->addSibling(menu);
    }
    else
    {
        this->sibling = &menu;
        menu.setParent(*this->parent);
        menu.setIndexOfSiblings(this->getTotNrOfSiblings());
        menu.parent->totNrOfChildren++;
        // printf("nr of sib: %d, index of sib: %d\n", menu.getTotNrOfSiblings(), menu.indexOfSiblings);
        // printf("------------------------\n");
        // printf("name: %s, sibling: %s, par: %s, par ch: %d\n", menu.getName(), menu.getSibling(0)->getName(), menu.getParent()->getName(), menu.getParent()->getTotNrOfChildren());
        // printf("------------------------\n");
        
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
        // printf("nr of sib: %d, index of sib: %d\n", menu.getTotNrOfSiblings(), menu.indexOfSiblings);        
        // printf("------------------------\n");
        // printf("name: %s, sibling: %s, par: %s, par ch: %d\n", menu.getName(), menu.getSibling(0)->getName(), menu.getParent()->getName(), menu.getParent()->getTotNrOfChildren());
        // printf("------------------------\n");    
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

MenuNode *MenuNode::getSibling(uint8_t offset)
{
    if (offset == 0)
    {
        return this;
    }
    else if (this->sibling)
    {
        this->sibling->getSibling(offset - 1);
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
    // menus[1] = this->getChild(1);

    // for (int i = 0; i < this->getTotNrOfChildren(); i++)
    // {
    //     printf("%s\n", menus[i]->getName());
    // }
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

    char **names = (char **)malloc(this->getTotNrOfChildren());
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
        menus[i] = this->parent->getChild(i)->getName();
    }

    // Get siblings after current
    for (uint16_t i = this->indexOfSiblings + 1; i <= this->getTotNrOfSiblings(); i++)
    {
        menus[i - 1] = this->parent->getChild(i)->getName();
    }
    return menus;
}