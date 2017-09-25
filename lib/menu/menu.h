#pragma once

class SubMenu {
private:	
	char* name;
	SubMenu* next;
	SubMenu* prev;
public:
	SubMenu() {
		this->prev = NULL;
		this->next = NULL;
		this->name = "";
	}
	SubMenu(SubMenu *parent, const uint8_t size, char*name)
	{
		this->prev = parent;
		this->next = (SubMenu*) malloc(size);
		this->name = name;
	}
	
	
};

class Menu 
{
private:
	SubMenu * head;
	SubMenu * current;
	int index;
	
public:
	char * getChoices(SubMenu * menu); // returner en liste med alle valg i en undermeny
	void select(); // velger et alternativ
	void goBack();
	void goUp();
	void goDown();
	
};