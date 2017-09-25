#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

struct Node {
	char name;
	struct Node* next;
	struct Node* prev;
};

struct Node* head; // global pointer to head node

struct Node* getNewNode(char n,int size) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->name = n;
	newNode->prev = NULL;
	newNode->next = (struct Node*)malloc(size*sizeof(struct Node));
	return newNode;
}

struct Node* insertNode(Node *node,Node *parent,int index){
	parent->next+index = node;
	node->prev = parent;
	return parent;
}

char getChild(Node *node,int index){
	char child = node->next+index->name;
	return child;
	// int size = sizeof node->next;
	// char children[size];
	// for (int i = 0;i < size;i++){
		// children[i] = node->next[i]->name;
	// }
	// return children;
}