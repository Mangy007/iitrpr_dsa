#include<stdio.h>
#include<stdlib.h>
#include "Node.c"

void insertAtBeginning(int val);
void insertAtEnd(int val);
void deleteFirstNode();
void deleteLastNode();
void deleteSpecificNode(int val);
void findNode(int val);
void printList();
void size();
void performOperationsBasedOnInput(int choice);

Node *head = NULL;

int main() {

	int testCases;
	scanf("%d", &testCases);
	int currentTestcase = 1;
	while(testCases--) {

		int entries;
		scanf("%d", &entries);
		head = NULL;//(Node*) malloc(sizeof(Node));
		printf("\n#%d", currentTestcase++);
		while (entries--)
		{
			int choice;
			scanf("%d",&choice);
			performOperationsBasedOnInput(choice);
		}
	}
	printf("\n");
	return 0;
}

void insertAtBeginning(int val) {

    Node *node = (Node *) malloc(sizeof(Node));
    node -> value = val;
    node -> next = head;

	head = node;
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

void deleteFirstNode() {
	
	if (head==NULL) {
		printf(" E");
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

void deleteLastNode() {

	if (head==NULL) {
		printf(" E");
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

void deleteSpecificNode(int val) {

	if (head==NULL) {
		printf(" E");
		return;
	}
	// when only one node is present
	if (head->next==NULL) {
		if(head->value==val) {
			free(head);
			head = NULL;
			return;
		}
		printf(" N");
		return;
	}
	Node *node = head;
	// when the node to be find is the first node
	if(node->value==val) {
		head = head->next;
		free(node);
		return;
	}

	// finding and deleting the node in intermediate
	while (node->next->next) {
		if(node->next->value==val) break;
		node = node->next;
	}
	if(node->next->value==val) {
		Node *temp = node->next;
		node->next = node->next->next;
		free(temp);
		return;
	}
	printf(" N");
}

void findNode(int val) {

	if (head==NULL) {
		printf(" E");
		return;
	}
	int i=1;
	Node *headAddress = head;
	Node *node = head;
	while (node->next) {
		if (node->value==val) break;
		node = node->next;
		i++;
	}

	if (node->value==val) {
		Node *nodeAddress = node;
//		printf("\nnode  size: %ld", sizeof(Node));
//		printf("\nhead: %ld node: %ld", headAddress, nodeAddress);
		int diff = headAddress-nodeAddress;
		printf(" %d(%d)", i, diff);
	}
	else {
		printf(" N");
	}
}

void size() {
    
	Node *node = head;
	int counter = 0;
    while(node!=NULL) {
        counter++;
        node = node->next;
    }
	printf(" %d", counter);
}

void printList() {
    
	if(head==NULL) {
		printf(" E");
		return;
	}
	printf(" [");
	Node *node = head;
    while(node!=NULL) {
        if(node->next)
            printf("%d-",node->value);
        else
            printf("%d",node->value);
        node = node->next;
    }
	printf("]");
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
				insertAtBeginning(val);
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
			// delete specific node
			int val;
			scanf("%d", &val);
			deleteSpecificNode(val);
			break;
		}
		case 6: {
			// find node position and address difference from head in units
			int val;
			scanf("%d", &val);
			findNode(val);
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
			printf(" W");
			break;
		}
	}
}