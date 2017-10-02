#pragma once
extern "C" {
#include <stdint.h>
}

class MenuNode
{
  private:
    MenuNode *parent;
    MenuNode *child;
    MenuNode *sibling;
    char *name;
    uint16_t totNrOfChildren;
    // uint16_t totNrOfSiblings;
    uint16_t indexOfSiblings;

    void setParent(MenuNode &menu);
    void setIndexOfSiblings(uint16_t index);
    void addSibling(MenuNode &menu);

  public:
    MenuNode(char *name);

    void addChild(MenuNode &menu);

    MenuNode *getSibling(uint8_t offset);
    MenuNode *getChild(uint8_t nr);
    MenuNode *getParent();
    char *getName();
    uint16_t getTotNrOfChildren();
    uint16_t getTotNrOfSiblings();

    MenuNode **getChildren();
    MenuNode **getSiblings();

    char **getChildrenNames();
    char **getSiblingNames();
};