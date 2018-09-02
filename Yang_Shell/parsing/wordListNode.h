#include <stdlib.h>
#include <stdio.h>

#ifndef WORDLISTNODE_H
#define WORDLISTNODE_H

struct WordNode{
	char* word; 
	struct WordNode * nextWord; 
};

struct WordNodeList{
	struct WordNode * head; 
};

struct WordNodeList * MakeList(){
	struct WordNodeList * newList = (struct WordNodeList *)malloc(sizeof(struct WordNodeList));
	newList->head = NULL;
}

struct WordNode * MakeNode(char* newWord){
	struct WordNode * newNode = (struct WordNode*)malloc(sizeof(struct WordNode));
	newNode->word = newWord;
	newNode->nextWord = NULL;
	return newNode;
}

void Insert(struct WordNodeList * list,struct WordNode * newNode) {
	struct WordNode * curNode;
	struct WordNode * nextNode;
	 
	if(list->head == NULL){
		list->head = newNode; 
	} else {
		curNode = list->head;
		while(curNode->nextWord != NULL){
			curNode = curNode->nextWord;
		}
		curNode->nextWord = newNode;
	}
}

void DispNode(struct WordNode * word_node) {
	printf("%s", word_node->word);
}

void PrintAllNodesSeparatedByDot(struct WordNodeList * list){
	struct WordNode * tempPtr = list->head; 
	while(tempPtr != NULL){
		DispNode(tempPtr); 
		if(tempPtr->nextWord != NULL){
			printf(".");
		}
		tempPtr = tempPtr->nextWord;
	}
	printf("\n");
}

void clearList(struct WordNodeList * list){
	struct WordNode * currentNode; 
	struct WordNode * nextNode; 

	currentNode = list->head; 
	while(currentNode != NULL){
		nextNode = currentNode->nextWord;
		currentNode->nextWord = NULL;
		/*printf("freeing node: %s \n", currentNode->word);*/
		free(currentNode->word);
		free(currentNode);
		currentNode = nextNode;
	}

	list->head = NULL;
}


typedef struct WordNode WordNode;
typedef struct WordNodeList WordNodeList; 
#endif
