
#pragma once
extern "C" {
#include <stdint.h>
}

#include "menuNode.h"

class Menu
{
  private:
    MenuNode *head;
    MenuNode *current;
    uint16_t selectIndex;

  public:
    Menu(MenuNode *head);

    MenuNode *getCurrent();
    MenuNode *select();
    MenuNode *back();
    MenuNode *up();
    MenuNode *down();
};