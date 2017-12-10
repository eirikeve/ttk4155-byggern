
#pragma once
extern "C" {
#include <stdint.h>
}

#include "menuNode.h"

/**
 * Class for managing a dynamic menu structured as a tree. 
 * Menu options is created by adding menuNodes.
 * */
class Menu
{
private:

  // Head of menu structure
  MenuNode *head;

  // Current submenu
  MenuNode *current;

  // Index of next menuNode to be selected
  uint8_t selectIndex;


public:

  /**
   * Initialize a menu structure.
   * @param head root choice of the menu structure.
   * */
  Menu(MenuNode *head);

  /**
   * Get current value of which menuNode to be selected next.
   * @return value of selectIndex
   * */
  uint8_t getSelectIndex();

  /**
   * Get current menuNode.
   * @return pointer to current menuNode.
   * */
  MenuNode *getCurrent();

  /**
   * Select chosen menuNode.
   * */
  void select();


  /**
   * Go back to previous menuNode.
   * */
  void back();

  /**
   * Go one step up in current menu choices.
   * Reduces selectIndex by one.
   * */ 
  void up();

  /**
   * Go one step down in current menu choices.
   * Increases selectIndex by one.
   * */ 
  void down();
};
