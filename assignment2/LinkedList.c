#include<stdio.h>
#include<stdlib.h>
#include "Node.c"

void insertAtEnd(int val);
Node * insertAtBeginning(int val);
void deleteLastNode();
void deleteFirstNode();
void deleteSpecifiNode(int val);
void findNode(int val);
void printList();
void size();
void performOperationsBasedOnInput(int choice);

Node *head = NULL;

int main() {

	int testCases;
	scanf("%d", &testCases);
	while(testCases--) {

		int entries;
		scanf("%d", &entries);
		head = NULL;//(Node*) malloc(sizeof(Node));
		while (entries--)
		{
			int choice;
			scanf("%d",&choice);
			performOperationsBasedOnInput(choice);
		}
	}
	return 0;
}


void insertAtEnd(int val) {

    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode -> value = val;
    newNode -> next = NULL;
	Node *node = head;

    if(node == NULL) node = newNode;
    else {
		while(node->next!=NULL) node = node->next;
		node->next = newNode;
	}
}

Node * insertAtBeginning(int val) {

    Node *node = (Node *) malloc(sizeof(Node));
    node -> value = val;
    node -> next = head;

    return node;
}

void deleteLastNode() {

	if (head==NULL) {
		printf("\nNo node to delete");
		return;
	}
	if (head->next==NULL) {
		free(head);
		head = NULL;
		return;
	}
	Node *node = head;
	while (node->next->next) {
		node = node->next;
	}
	free(node->next);
	node->next = NULL;
}

void deleteFirstNode() {
	
	if (head==NULL) {
		printf("\nNo node to delete");
		return;
	}
	if (head->next==NULL) {
		free(head);
		head = NULL;
		return;
	}
	Node *node = head;
	head = head->next;
	free(node);
}

void deleteSpecifiNode(int val) {

	if (head==NULL) {
		printf("\nNo node to delete");
		return;
	}

}

void findNode(int val) {

	if (head==NULL) {
		printf("\nList is empty");
		return;
	}
	
}

void size() {
    
	Node *node = head;
	int counter = 0;
    while(node!=NULL) {
        counter++;
        node = node->next;
    }
	printf("\n%d", counter);
}

void printList() {
    
	printf("\n");
	Node *node = head;
    while(node!=NULL) {
        if(node->next)
            printf("%d-->",node->value);
        else
            printf("%d",node->value);
        node = node->next;
    }
	printf("\n");
}

void performOperationsBasedOnInput(int choice) {

	switch(choice) {
		case 1: {
			// insert at beginning
			int val;
			scanf("%d", &val);
			if(head==NULL) {
				head = (Node*) malloc(sizeof(Node));
				head->value = val;
				head->next = NULL;
			}
			else {
				head = insertAtBeginning(val);
			}
			break;
		}
		case 2: {
			// insert at end
			int val;
			scanf("%d", &val);
			if(head==NULL) {
				head = (Node*) malloc(sizeof(Node));
				head->value = val;
				head->next = NULL;
			}
			else {
				insertAtEnd(val);
			}
			break;
		}
		case 3: {
			// delete first node
			deleteFirstNode();
			break;
		}
		case 4: {
			// delete last node
			deleteLastNode();
			break;
		}
		case 5: {
			// ask for input
			// delete specific node
			int val;
			scanf("%d", &val);
			deleteSpecifiNode(val);
			break;
		}
		case 6: {
			// ask for input
			// find node
			break;
		}
		case 7: {
			// print size
			size();
			break;
		}
		case 8:{
			// print list
			printList();
			break;
		}
		default: { 
			printf("“Wrong Input. \nEnter your choice again: ");
			break;
		}
	}
}
