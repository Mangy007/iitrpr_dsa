#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node * left;
    struct Node * right;
} Node;

Node * root = NULL;

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

int main() {

    insertIntoBST(4);
    insertIntoBST(5);
    insertIntoBST(3);
    insertIntoBST(6);
    insertIntoBST(7);
    insertIntoBST(1);
    Node * node = root;
    printInorder(node);
    printf("\n");
    printPostorder(node);
    
    return 0;
}