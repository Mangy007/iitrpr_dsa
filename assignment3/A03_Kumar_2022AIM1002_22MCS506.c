#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node * left;
    struct Node * right;
} Node;

Node * root = NULL;

void printPreorder(Node * node);
void printInorder(Node * node);
void printPostorder(Node * node);
void insertIntoBST(int val);
int numberofNodes(Node * node);
int numberofLeaves(Node * node);
void isNodePresent(int val);


int main() {

    insertIntoBST(4);
    insertIntoBST(5);
    insertIntoBST(2);
    insertIntoBST(6);
    insertIntoBST(7);
    insertIntoBST(1);
    insertIntoBST(3);
    Node * node = root;
    printf("\n Preorder: ");
    printf("[");
    printPreorder(node);
    printf("]");
    printf("\n Inorder: ");
    printf("[");
    printInorder(node);
    printf("]");
    printf("\n Postorder: ");
    printf("[");
    printPostorder(node);
    printf("]");
    printf("\n Number of nodes: %d", numberofNodes(node));
    printf("\n Number of leaves: %d", numberofLeaves(node));
    printf("\n");
    isNodePresent(3);
    isNodePresent(10);

    
    return 0;
}

void printPreorder(Node * node) {
    // non recursive approach
    int N = numberofNodes(node);
    Node * stack[N];
    int stackPointer = -1;
    stack[++stackPointer] = node;
    while(stackPointer>=0) {
        Node * tempNode = stack[stackPointer--];
        printf("%d ", tempNode->value);
        if(tempNode->right != NULL) stack[++stackPointer] = tempNode->right;
        if(tempNode->left != NULL) stack[++stackPointer] = tempNode->left;
    }
}

void printInorder(Node * node) {
    if(node==NULL) return;
    printInorder(node->left);
    printf("%d ", node->value);
    printInorder(node->right);
}

void printPostorder(Node * node) {
    if(node==NULL) return;
    printPostorder(node->left);
    printPostorder(node->right);
    printf("%d ", node->value);
}

void insertIntoBST(int val) {
    if(root==NULL) {
        root = (Node *) malloc(sizeof(Node));
        root->value = val;
        root->left = NULL;
        root->right = NULL;
    }
    else {
        Node * node = root;
        while(node != NULL) {
            if(node->value == val) return;
            else if(node->value > val) {
                if(node->left == NULL) {
                    Node * newNode = (Node *) malloc(sizeof(Node));
                    newNode->value = val;
                    newNode->left = NULL;
                    newNode->right = NULL;
                    node->left = newNode;
                }
                node = node->left;
            }
            else {
                if(node->right == NULL) {
                    Node * newNode = (Node *) malloc(sizeof(Node));
                    newNode->value = val;
                    newNode->left = NULL;
                    newNode->right = NULL;
                    node->right = newNode;
                }
                node = node->right;
            }
        }
    }
}

int numberofNodes(Node * node) {
    if(node==NULL) return 0;
    if(node->left == NULL && node->right == NULL) return 1;
    return 1 + numberofLeaves(node->left) + numberofLeaves(node->right);
}

int numberofLeaves(Node * node) {
    if(node==NULL) return 0;
    if(node->left == NULL && node->right == NULL) return 1;
    return numberofLeaves(node->left) + numberofLeaves(node->right);
}

void isNodePresent(int val) {
    Node * node = root;
    if(node == NULL || val <= 0) {
        printf("NO\n");
        return;
    }
    while(node != NULL) {
        if(node->value==val) {
            printf("YES\n");
            return;
        }
        else if(node->value>val) node = node->left;
        else node = node->right;
    }
    printf("NO\n");
}