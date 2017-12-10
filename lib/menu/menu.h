
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
  uint8_t selectIndex;


public:
  Menu(MenuNode *head);

  uint8_t getSelectIndex();

  MenuNode *getCurrent();
  void select();
  void *back();
  void *up();
  void *down();
};
