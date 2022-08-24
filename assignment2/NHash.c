#include<stdio.h>
#include<stdlib.h>
#include "Node.c"

DoubleLinkedNode createNode(int val);
DoubleLinkedNode getPowerOfNumber(DoubleLinkedNode node);
void performNHashOperation(int number);

Node *head = NULL;

int main() {

	int testCases;
	scanf("%d", &testCases);
	while(testCases--) {

		int N;
        scanf("%d", &N);
        performNHashOperation(N);
	}
	printf("\n");
	return 0;
}

DoubleLinkedNode createNode(int val) {

    DoubleLinkedNode *node = (DoubleLinkedNode *) malloc(sizeof(DoubleLinkedNode));
    node -> value = val;
	node -> prev = NULL;
    node -> next = NULL;
	// Node *node = head;

   return node;
}

DoubleLinkedNode getPowerOfNumber(DoubleLinkedNode node) {

	int number = node->value;
	for(int i=0; i<number; i++) {
		node -> value *= number;
	}
	return node;
}

void performNHashOperation(int n) {

    for(int i=1; i<=n; i++) {
        DoubleLinkedNode node = createNode(i);
		getPowerOfNumber(node)
    }
}