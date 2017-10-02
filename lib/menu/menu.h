#pragma once
extern "C" {
#include <stdlib.h>
}

class SubMenu
{
private:
	char *name;
	SubMenu **children;
	SubMenu **parent;
	uint8_t size;
	uint8_t currentIndex;

	// SubMenu &operator=(SubMenu rhs) = delete;
	// SubMenu(const SubMenu &rhs) = delete;

public:
	static int i;
	SubMenu();
	SubMenu(char *name, uint8_t size);

	SubMenu *getChildren() const;
	SubMenu *getParent() const;
	char *getName() const;
	uint8_t getSize() const;

	SubMenu addSubMenu(char *name, uint8_t size);
	void addParent(SubMenu *parent);

	char **getChildrenNames();

	~SubMenu();
	void debug() const;
};

class Menu
{
private:
	SubMenu *head;
	SubMenu *current;
	int index;

public:
	Menu(SubMenu *head);
	char **getChoices(); // returner en liste med alle valg i en undermeny
	void select();			 // velger et alternativ
	void goBack();			 // går til prev
	void goUp();				 //index -1
	void goDown();			 // index +1
};