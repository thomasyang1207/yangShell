#include "wordListNode.h"

//Global List:
static WordNodeList * globalList;

int main(){
	WordNodeList * list; 
	WordNode * head;
	WordNode * testNode1;
	WordNode * testNode2; 

	globalList = MakeList();

	//test 1 -> Can add a node with new node; 
	list = MakeList();
	head = (WordNode *)malloc(sizeof(WordNode));
	Insert(list, head);
	printf("test1: Add one node passed \n");
	clearList(list);
	if(list->head == NULL){
		printf("test1: successfully freed all blocks \n");
	}
	free(list);
	printf("test1: Clear one node passed \n");


	//test 2 -> can add more than one node
	list = MakeList(); 
	head = MakeNode("Head");
	testNode1 = MakeNode("testNode1");
	
	Insert(list,head);
	Insert(list,testNode1);

	PrintAllNodesSeparatedByDot(list);
	clearList(list);
	if(list->head == NULL){
		printf("test2: successfully freed all blocks \n");
	}
	free(list);



	//test 3 -> can print one node
	list = MakeList(); 
	head = MakeNode("head"); 
	testNode1 = MakeNode("testNode1");
	testNode2 = MakeNode("testNode2");
	
	Insert(globalList,head);
	Insert(list,testNode1);
	Insert(list,testNode2);
	
	PrintAllNodesSeparatedByDot(list);
	clearList(list);
	free(list);
	
	//test 4 -> can print more than one node
	head = MakeNode("head"); 
	testNode1 = MakeNode("testNode1");
	testNode2 = MakeNode("testNode2");
	
	Insert(globalList,head);
	Insert(globalList,testNode1);
	Insert(globalList,testNode2);
	
	PrintAllNodesSeparatedByDot(globalList);
	clearList(globalList); 

	free(globalList);
	return 0;

}
