#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "../display/screen.h"
extern "C" {
#include "../../node1/include/comm.h"
}
// SubMenu::i = 0;

SubMenu::SubMenu() : SubMenu("", 0) {}

// SubMenu &SubMenu::operator=(SubMenu rhs) {
// 	this->parent = rhs.parent;
// 	this->name = rhs.name;
// 	this->size = rhs.size;
// 	this->currentIndex = rhs.currentIndex;
// 	SubMenu * temp
// }

SubMenu::SubMenu(char *name, uint8_t size) : parent(NULL),
											 children(NULL),
											 name(name),
											 size(size),
											 currentIndex(0)
{
	if (size > 0)
	{
		this->children = (SubMenu *)malloc(size);
	}
}

SubMenu *SubMenu::getChildren() const
{
	return this->children;
}

SubMenu *SubMenu::getParent() const
{
	return this->parent;
}

char *SubMenu::getName() const
{
	return this->name;
}

uint8_t SubMenu::getSize() const
{
	return this->size;
}

SubMenu SubMenu::addSubMenu(char *name, uint8_t size)
{
	this->children[currentIndex++] = SubMenu(name, size);
	this->children[currentIndex].addParent(this);
	// printf("Creating %s, %x\n", this->children[currentIndex].getName(), &this->children[currentIndex]);
	return this->children[currentIndex];
}

void SubMenu::addParent(SubMenu *parent)
{
	this->parent = parent;
}

// SubMenu **getChildrenNames();
// {
// 	// Screen o;
// 	// o.clear(0x00);
// 	// o.goTo(0, 0);
// 	Submenu **test;
// 	for (int i = 0; i < this->size; i++)
// 	{
// 		test[i] = &this->children[i];
// 		// o.writeString(res[i]);
// 	}
// 	return test;
// }

char **SubMenu::getChildrenNames()
{
	char *res[this->size];

	for (int i = 0; i < this->size; i++)
	{
		res[i] = this->children[i].getName();
		// printf("%s: %x\n", res[i], &this->children[i]);
	}
	return res;
}

SubMenu::~SubMenu()
{
	free(children);
}

void SubMenu::debug() const
{
	printf("");
}

// Menu::Menu(SubMenu *head)
// {
// 	this->head = head;
// 	this->current = head;
// }
// char **Menu::getChoices()
// {
// 	uint8_t size = current->getSize();
// 	printf("size: %d\n", size);
// 	char *outp[size];
// 	for (int i = 0; i < size; i++)
// 	{
// 		outp[i] = (current->getchildren() + i)->getName();
// 		// printf("%s \n", outp[i]);
// 		printf("Hello\n");
// 	}
// 	return outp;
// }

// void Menu::select()
// {
// 	current = current->getchildren() + index;
// 	return;
// }

// void Menu::goBack()
// {
// 	if (current != head)
// 	{
// 		current = current->getparent();
// 	}
// 	return;
// }

// void Menu::goUp()
// {
// 	if (index == 0)
// 	{
// 		index = (int)sizeof(current->getchildren());
// 	}
// 	else
// 	{
// 		index = index - 1;
// 	}
// }

// void Menu::goDown()
// {
// 	if (index == (int)sizeof(current->getchildren()))
// 	{
// 		index = 0;
// 	}
// 	else
// 	{
// 		index = index + 1;
// 	}
// }