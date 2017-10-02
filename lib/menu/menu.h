#pragma once

class SubMenu
{
  private:
	char *name;
	SubMenu *next;
	SubMenu *prev;
	uint8_t size;

  public:
	SubMenu()
	{
		this->prev = NULL;
		this->next = NULL;
		this->name = '\0';
		this->size = 0;
	}
	SubMenu(SubMenu *parent, const uint8_t size, char *name)
	{
		this->prev = parent;
		this->size = size;
		this->next = (SubMenu *)malloc(size);
		this->name = name;
	}
	SubMenu *getNext();
	SubMenu *getPrev();
	char *getName();
	uint8_t getSize() const;

	~SubMenu();
};

class Menu
{
  private:
	SubMenu *head;
	SubMenu *current;
	int index;

  public:
	char **getChoices(); // returner en liste med alle valg i en undermeny
	void select();		 // velger et alternativ
	void goBack();		 // går til prev
	void goUp();		 //index -1
	void goDown();		 // index +1
};