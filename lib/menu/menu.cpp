#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

SubMenu *SubMenu::getNext()
{
	return this->next;
}

SubMenu *SubMenu::getPrev()
{
	return this->prev;
}

char *SubMenu::getName()
{
	return this->name;
}

uint8_t SubMenu::getSize()
{
	return this->size;
}

~SubMenu()
{
	free(next);
}

char **Menu::getChoices()
{
	uint8_t size = current->getSize();
	char **outp = (char **)malloc(size);
	for (int i = 0; i < size; i++)
	{
		outp[i] = (current->getNext() + i)->getName();
	}
	return outp;
}

void Menu::select()
{
	current = current->getNext() + index;
	return;
}

void Menu::goBack()
{
	if (current != head)
	{
		current = current->getPrev();
	}
	return;
}

void Menu::goUp()
{
	if (index == 0)
	{
		index = (int)sizeof(current->getNext());
	}
	else
	{
		index = index - 1;
	}
}

void Menu::goDown()
{
	if (index == (int)sizeof(current->getNext()))
	{
		index = 0;
	}
	else
	{
		index = index + 1;
	}
}