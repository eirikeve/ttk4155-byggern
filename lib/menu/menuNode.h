#pragma once
#include <stdint.h>
#include <avr/pgmspace.h>

class MenuNode
{
private:
  MenuNode *parent;
  MenuNode *child;
  MenuNode *nextSibling;
  MenuNode *prevSibling;
  PROGMEM char * name;
  uint16_t totNrOfChildren;
  // uint16_t totNrOfSiblings;
  uint16_t indexOfSiblings;

  void (*callback_function)(uint8_t); // Used to trigger events in the FSM
  uint8_t callback_function_arg;

  void setParent(MenuNode &menu);
  void setIndexOfSiblings(uint16_t index);
  void addSibling(MenuNode &menu);

public:
  MenuNode(char *name, void (*callback_function)(uint8_t), uint8_t cb_fun_arg);
  MenuNode(char *name);

  void addChild(MenuNode &menu);

  MenuNode *getSibling(int8_t offset);
  MenuNode *getChild(uint8_t nr);
  MenuNode *getParent();
  char *getName();
  uint16_t getTotNrOfChildren();
  uint16_t getTotNrOfSiblings();

  MenuNode **getChildren();
  MenuNode **getSiblings();

  char **getChildrenNames();
  char **getSiblingNames();
  friend class Menu;
};