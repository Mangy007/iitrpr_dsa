#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define NODE_VALUE_CAPACITY 5
#define NODE_LAST_N_DIGITS 100000

typedef struct Node {
    int value;
    char * valueInString;
    struct Node * prev;
    struct Node * next;
} Node;


int getNumberLength(int number);
void printNumberOfTrailingZeros();
void printNumberOfTimesPatternMatched(char *pattern);
void printList();
Node * createNode(int val);
void performDigitWiseMultiplication(Node * node, int number);
void performPowerOperation(int number);
void performNHashOperation(int number, char *pattern);

Node *head = NULL;
Node *tail = NULL;
char *nHashOutput = NULL;

int main() {

	int testCases;
	scanf("%d", &testCases);
	while(testCases--) {

		int N;
        char pattern[3];
        scanf("%d %s", &N, pattern);
        performNHashOperation(N, pattern);
	}
	printf("\n");
	return 0;
}

Node * createNode(int val) {

    Node *node = (Node *) malloc(sizeof(Node));
    node -> value = val;
    node -> valueInString = NULL;
	node -> prev = NULL;
    node -> next = NULL;
	
    head = node;
    tail = node;
    
   return node;
}

void printNumberOfTrailingZeros() {
    int zeroesCount = 0;
    Node *node = head;
    bool isNonZeroFound = false;
    while(node != NULL) {
        for(int i=strlen(node->valueInString)-1; i >= 0; i--) {
            if(node->valueInString[i] != '0') {
                isNonZeroFound = true;
                break;
            }
            zeroesCount++;
        }
        if(isNonZeroFound) break;
        node = node->next;
    }
    printf("%d ", zeroesCount);
}

void printNumberOfTimesPatternMatched(char *pattern) {

    int patternMatchedCount = 0;
    if(tail==NULL) {
        printf("%d\n", patternMatchedCount);
        return;
    }

    long long int outputLength = 0;
    Node *node = tail;
    bool isLastNode = true;
    while(node!=NULL) {
        if(isLastNode) {
            bool isNonZeroFound = false;
            for(int i=0; i<strlen(node->valueInString); i++) {
                if(node->valueInString[i]!='0') isNonZeroFound = true;
                if(isNonZeroFound) outputLength++;
            }
            isLastNode = false;
        }
        else outputLength += strlen(node->valueInString);

        node = node->prev;
    }

    node = tail;
    isLastNode = true;
    nHashOutput = calloc(outputLength, sizeof(char));

    while(node!=NULL) {
        if(isLastNode) {
            bool isNonZeroFound = false;
            for(int i=0; i<strlen(node->valueInString); i++) {
                if(node->valueInString[i]!='0') isNonZeroFound = true;
                if(isNonZeroFound) {
                    char charToStr[2];
                    charToStr[0] = node->valueInString[i];
                    charToStr[1] = '\0';
                    strcat(nHashOutput, charToStr);
                }
            }
            isLastNode = false;
        }
        else strcat(nHashOutput, node->valueInString);

        node = node->prev;
    }
    int index = 0;// lastMatchedIndex = 0;
    
    for (int i = 0; i < strlen(nHashOutput); i++) {
        if(nHashOutput[i]==pattern[index]) {
            int currentIndex = i;
            while (nHashOutput[currentIndex]==pattern[index])
            {
                currentIndex++;
                index++;
                if(index == strlen(pattern)) {
                    patternMatchedCount++;
                    break;
                }
            }
            index = 0; 
        }     
    }
    
    printf("%d ", patternMatchedCount);
}

void printList() {
    
	if(strlen(nHashOutput) > 0) printf("%s", nHashOutput);
	printf("\n");
}

char * getNumberInString(int number, bool isLastNode) {

    char *str = calloc(NODE_VALUE_CAPACITY, sizeof(char));
    if(isLastNode) {
        sprintf(str, "%d", number);
        return str;
    }
    
    int index = NODE_VALUE_CAPACITY-1;
    while (number>0) {
        int rem = number%10;
        str[index--] = rem+'0';
        number /= 10;
    }
    while (index >= 0) {
        str[index--] = '0';
    }

    return str;
}

void performDigitWiseMultiplication(Node * node, int number) {
    
    int val = node->value * number;
    int carry = val / NODE_LAST_N_DIGITS;
    val = val % NODE_LAST_N_DIGITS;
    node->value = val;
    node->valueInString = getNumberInString(node->value, false);
    while (carry > 0 || node->next) {
        if(node->next) {
            node = node->next;
            val = (node->value * number) + carry;
            carry = val / NODE_LAST_N_DIGITS;
            val = val % NODE_LAST_N_DIGITS;
            node->value = val;
            node->valueInString = getNumberInString(node->value, false);
        }
        else {
            Node *newNode = (Node *) malloc(sizeof(Node));
            newNode->value = carry;
            newNode->valueInString = getNumberInString(newNode->value, true);
            newNode->prev = node;
            newNode->next = NULL;
            node->next = newNode;
            node = node->next;
            carry = 0;
        }
    }
    tail = node;
}

void performPowerOperation(int number) {

	Node * node = head;
	for(int i=0; i<number; i++) {
        node = head;
        performDigitWiseMultiplication(node, number);
	}
}

void performNHashOperation(int n, char *pattern) {


    createNode(1);

    for(int i=2; i<=n; i++) {
		performPowerOperation(i);
    }
    printNumberOfTrailingZeros();
    printNumberOfTimesPatternMatched(pattern);
    printList();
}