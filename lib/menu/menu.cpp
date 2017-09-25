#pragma once
#include <stdio.h>
#include <stdlib.h>
#include menu.h

struct Node {
	char name;
	struct Node* next;
	struct Node* prev;
};

struct Node* head; // global pointer to head node

struct Node* getNewNode(char n) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->name = n;
	newNode->prev = NULL;
	newNode->next = [(struct Node*)malloc(1)];
	return newNode;
}

struct Node* insertNewNode(struct node, struct parent){
	parent->next = realloc(parent->next,sizeof(struct Node*)*(parent->next+1));
	parent->next[sizeof(struct Node*)*(parent->next)] = node;
	node->prev = parent;
	return parent;
}