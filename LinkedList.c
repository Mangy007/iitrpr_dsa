#include<stdio.h>
#include<stdlib.h>
#include "Node.c"


void insertAtEnd(Node *node, int data) {

    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode -> value = data;
    newNode -> next = NULL;

    if(node == NULL) node = newNode;
    else {
		while(node->next!=NULL) node = node->next;
		node->next = newNode;
	}
}

Node * insertAtBeginning(Node *node, int data) {

    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode -> value = data;
    newNode -> next = node;

    return newNode;
}

void printList(Node *node) {
    
    printf("\n");
    while(node!=NULL) {
        if(node->next)
            printf("%d-->",node->value);
        else
            printf("%d",node->value);
        node = node->next;
    }
}

int main() {

    Node *head = NULL;//(Node*) malloc(sizeof(Node));
	int choice;
	printf("Enter the choice: ");
	scanf("%d",&choice);
	while(choice) {
	    switch(choice) {
	        
	        case 1: {
	            printf("Enter the data value: ");
	            insertAtBeginning()
	            break;}
	        case 2: break;
	        case 3: break;
	        case 4: break;
	        case 5: break;
	        case 6: break;
	        case 7: break;
	        case 8: break;
	        default: { 
	            printf("“Wrong Input. \nEnter your choice again:")
	            scanf("%d", &choice);
	            break;
	        }
	    }
	}
	while(N-- > 0) {
		int val;
		scanf("%d", &val);
		if(head==NULL) {
		    head = (Node*) malloc(sizeof(Node));
			head->value = val;
			head->next = NULL;
		}
		else {
			insertAtEnd(head, val);
		}
	}
	
    // Node *temp = head;
    printList(head);
//     while(temp!=NULL) {
//         printf("%d-->",temp->value);
// 		// printf(temp->value);
//         temp = temp->next;
//     }
    head = insertAtBeginning(head, 100);
    head = insertAtBeginning(head, 101);
    printList(head);

    return 0;
}