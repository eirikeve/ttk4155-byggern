#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

char ** Menu::getChoices(SubMenu * menu){
	/* size = (uint8_t)sizeof(menu);
	char**outp = (char**) malloc(size);
	for (int i = 0;i < size;i++){
		*outp+i = menu->name;
	}
	return outp; */
	return;
} 

void Menu::select(){
	current = current.next[index];
	return;
}

void Menu::goBack(){
	if (current != head){
		current = current.prev;
	}
	return;
}

void Menu::goUp(){
	if (index == 0){
		index = (int)sizeof(current->next);
	}
	else {
		index = index -1;
	}
}

void Menu::goDown(){
	if (index == (int)sizeof(current->next)){
		index = 0;
	}
	else {
		index = index + 1;
	}
}