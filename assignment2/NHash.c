#include<stdio.h>
#include<stdlib.h>
#include "Node.c"

void createLinkedList(int number);
void getPowerOfNumber(DoubleLinkedNode node, int n);
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

void createLinkedList(int number) {

    
}

void performNHashOperation(int n) {

    for(int i=1; i<=n; i++) {
        createLinkedList(i);
    }
}