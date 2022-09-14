#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max(a,b) ((a>=b)?a:b)
#define BST 0
#define AVL 1

typedef struct Node {
    int value;
    struct Node * left;
    struct Node * right;
    // int height;
} Node;

Node * root = NULL;
int currentTree = -1;

void insertIntoBST(int val);
Node * deleteFromBST(Node * node, int val);
void insertIntoAVL(int val);
Node * deleteFromAVL(Node * node, int val);
void findNode(int val);
int numberofNodes(Node * node);
int numberofLeaves(Node * node);
void preorder(Node * node);
void inorder(Node * node);
void postorder(Node * node);
void levelOrder(Node * node);
int width(Node * node);
int height(Node * node);
int lowestCommonAncestor(int val1, int val2);
void route(int val1, int val2);
int diameter(Node * node);
void perimeter(Node * node);
void performOperationsBasedOnInput(char choice);


int main() {

    int testCases;
    
    scanf("%d", &testCases);
    
    while(testCases--) {
        char choice;
        scanf(" %c",&choice);
        performOperationsBasedOnInput(choice);
    }
	printf("\n");
    
    return 0;
}

void findNode(int val) {
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

int numberofNodes(Node * node) {
    if(node==NULL) return 0;
    if(node->left == NULL && node->right == NULL) return 1;
    return 1 + numberofNodes(node->left) + numberofNodes(node->right);
}

int numberofLeaves(Node * node) {
    if(node==NULL) return 0;
    if(node->left == NULL && node->right == NULL) return 1;
    return numberofLeaves(node->left) + numberofLeaves(node->right);
}

void preorder(Node * node) {
    // non recursive approach
    if(node==NULL) return;
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

void inorder(Node * node) {
    if(node==NULL) return;
    inorder(node->left);
    printf("%d ", node->value);
    inorder(node->right);
}

void postorder(Node * node) {
    if(node==NULL) return;
    postorder(node->left);
    postorder(node->right);
    printf("%d ", node->value);
}

void levelOrder(Node * node) {
    if(node==NULL) return;
    int N = numberofNodes(node);
    Node * queue[N];
    int front = -1;
    int rear = -1;
    queue[++front] = node;
    rear = front;
    while (front <= rear) {
        Node * tempNode = queue[front++];
        if(tempNode == NULL) continue;
        printf("%d ", tempNode->value);
        if(tempNode->left != NULL) queue[++rear] = tempNode->left;
        if(tempNode->right != NULL) queue[++rear] = tempNode->right;
    }
}

Node * createNode(int val) {
    Node * node = (Node *) malloc(sizeof(Node));
    node->value = val;
    // node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insertIntoBST(int val) {
    if(val <= 0) return;
    if(root==NULL) {
        root = createNode(val);
    }
    else {
        Node * node = root;
        while(node != NULL) {
            if(node->value == val) return;
            else if(node->value > val) {
                if(node->left == NULL) {
                    Node * newNode = createNode(val);
                    node->left = newNode;
                }
                node = node->left;
            }
            else {
                if(node->right == NULL) {
                    Node * newNode = createNode(val);
                    node->right = newNode;
                }
                node = node->right;
            }
        }
    }
}

Node * deleteFromBST(Node * node, int val) {
    if(node==NULL) return node;
    else if(node->value == val) {
        if(node->left==NULL && node->right==NULL) return NULL;
        else if(node->left==NULL) node = node->right;
        else if (node->right==NULL) node = node->left;
        else {
            Node * currNode = node->left;
            while (currNode->right!=NULL) currNode = currNode->right;
            node->value = currNode->value;
            node->left = deleteFromBST(node->left, currNode->value);
        }   
    }
    else if(val<node->value) node->left = deleteFromBST(node->left, val);
    else node->right = deleteFromBST(node->right, val);
   
    return node;
}

Node * performLLrotation(Node * node) {
    Node * currPointer = node;
    Node * leftPointer = node->left;

    currPointer->left = leftPointer->right;
    leftPointer->right = currPointer;

    return leftPointer;
}

Node * performLRrotation(Node * node) {
    Node * currPointer = node;
    Node * leftPointer = node->left;
    Node * leftRightPointer = node->left->right;

    leftPointer->right = leftRightPointer->left;
    leftRightPointer->left = leftPointer;
    leftRightPointer->right = currPointer;

    return leftRightPointer;
}

Node * performRRrotation(Node * node) {
    Node * currPointer = node;
    Node * rightPointer = node->right;

    currPointer->right = rightPointer->left;
    rightPointer->right = currPointer;

    return rightPointer;
}

Node * performRLrotation(Node * node) {
    Node * currPointer = node;
    Node * rightPointer = node->right;
    Node * rightLeftPointer = node->right->left;

    rightPointer->left = rightLeftPointer->right;
    rightLeftPointer->right = rightPointer;
    rightLeftPointer->left = currPointer;

    return rightLeftPointer;
}

void insertIntoAVL(int val) {
    // if(val <= 0) return;
    Node * node = root;
    
    if(root==NULL) {
        root = createNode(val);
    }
    else {
        while(node != NULL) {
            if(node->value == val) break;
            else if(node->value > val) {
                if(node->left == NULL) {
                    Node * newNode = createNode(val);
                    node->left = newNode;
                }
                node = node->left;
            }
            else {
                if(node->right == NULL) {
                    Node * newNode = createNode(val);
                    node->right = newNode;
                }
                node = node->right;
            }
        }
    }
    node = root;
    int N = numberofNodes(node);
    Node * stack[N];
    for(int i=0; i<N; i++) stack[i] = NULL;
    int stackPointer = -1;
    while(node != NULL) {
        stack[++stackPointer] = node;
        if(node->value==val) break;
        else if(node->value>val) node = node->left;
        else node = node->right;
    }

    for (int i = stackPointer-1; i > 0; i--) {
        Node * tempNode = stack[i];
        int balanceFactor = height(tempNode->left)-height(tempNode->right);
        if(balanceFactor>1) {
            // LL or LR rotation
            if(tempNode->left->left!=NULL) tempNode =  performLLrotation(tempNode);
            else tempNode = performLRrotation(tempNode);
        } 
        else if(balanceFactor<-1) {
            // RR or RL rotation
            if(tempNode->right->right!=NULL) tempNode = performRRrotation(tempNode);
            else tempNode = performRLrotation(tempNode);
        }
    }
}

Node * deleteNode(Node * node, int val) {
    if(node==NULL) return node;
    else if(node->value == val) {
        if(node->left==NULL && node->right==NULL) return NULL;
        else if(node->left==NULL) node = node->right;
        else if (node->right==NULL) node = node->left;
        else {
            Node * currNode = node->left;
            while (currNode->right!=NULL) currNode = currNode->right;
            node->value = currNode->value;
            node->left = deleteNode(node->left, currNode->value);
        }   
    }
    else if(val<node->value) node->left = deleteNode(node->left, val);
    else node->right = deleteNode(node->right, val);
   
    return node;
}

Node * deleteFromAVL(Node * node, int val) {
    node = deleteNode(node, val);

    int N = numberofNodes(node);
    Node * stack[N];
    Node * currNode = node;
    for(int i=0; i<N; i++) stack[i] = NULL;
    int stackPointer = -1;
    while(currNode != NULL) {
        stack[++stackPointer] = currNode;
        if(currNode->value==val) break;
        else if(currNode->value>val) currNode = currNode->left;
        else currNode = currNode->right;
    }

    for (int i = stackPointer-1; i > 0; i--) {
        Node * tempNode = stack[i];
        int balanceFactor = height(tempNode->left)-height(tempNode->right);
        if(balanceFactor>1) {
            // LL or LR rotation
            if(tempNode->left->left!=NULL) tempNode = performLLrotation(tempNode);
            else tempNode = performLRrotation(tempNode);
        } 
        else if(balanceFactor<-1) {
            // RR or RL rotation
            if(tempNode->right->right!=NULL) tempNode = performRRrotation(tempNode);
            else tempNode = performRLrotation(tempNode);
        }
    }

    return node;
}

int height(Node * node) {
    if(node==NULL) return 0;
    if(node->left == NULL && node->right == NULL) return 0;
    return 1 + max(height(node->left),height(node->right));
}

int width(Node * node) {
    if(node==NULL) return 0;
    int N = numberofNodes(node);
    Node * queue[N];
    int front = -1;
    int rear = -1;
    int width = 1;
    queue[++front] = node;
    rear = front;
    int lastRear = rear;
    while (front <= rear) {
        if(front-1==lastRear) {
            if(width<(rear-front+1)) width = rear-front+1;
            lastRear = rear;
        }
        Node * tempNode = queue[front++];
        if(tempNode->left != NULL) queue[++rear] = tempNode->left;
        if(tempNode->right != NULL) queue[++rear] = tempNode->right;
    }
    return width;
}

void getPathOfNodeFromRoot(Node * node, int * arr, int N, int val) {
    for(int i=0; i<N; i++) {
        arr[i] = -1;
    }
    int i=0;
    bool isFound = false;
    while(node != NULL) {
        arr[i++] = node->value;
        if(node->value==val) {
            // arr1[i++] = val1;
            isFound = true;
            break;
        }
        else if(node->value>val) node = node->left;
        else node = node->right;
    }
    if (!isFound) {
        for(int i=0; i<N; i++) arr[i] = -1;
    }
    
}

int lowestCommonAncestor(int val1, int val2) {

    Node * node = root;
    if(node == NULL || val1 <= 0 || val2 <= 0) {
        return -1;
    }
    int N = numberofNodes(node);
    int arr1[N], arr2[N], i=0;
    getPathOfNodeFromRoot(node, arr1, N, val1);
    getPathOfNodeFromRoot(node, arr2, N, val2);
    int lastMatched = -1;
    for(i=0; i<N; i++) {
        if(arr1[i]<=0 || arr2[i]<=0) break;
        else if(arr1[i]==arr2[i]) lastMatched = arr1[i];
    }
    return lastMatched;
}

void route(int val1, int val2) {
    Node * node = root;
    int N = numberofNodes(node);
    int arr1[N], arr2[N];//, i=0;
    getPathOfNodeFromRoot(node, arr1, N, val1);
    getPathOfNodeFromRoot(node, arr2, N, val2);

    if(arr1[0]==-1) {
        printf("Source does not exist\n");
        return;
    }
    if(arr2[0]==-1) {
        printf("Destination does not exist\n");
        return;
    }
    bool isAncestorFoundInPath = false, isReachable = false;

    for(int i=0; i<N; i++) {
        if(arr2[i]==val1) isAncestorFoundInPath = true;
        if(isAncestorFoundInPath && arr2[i]==val2) {
            isReachable = true;
            break;
        }
    }
    if(!isReachable) {
        printf("Unreachable\n");
        return;
    }
    Node * ancestorNode = NULL;
    while(node != NULL) {
        if(node->value==val1) {
            // arr1[i++] = val1;
            ancestorNode = node;
            break;
        }
        else if(node->value>val1) node = node->left;
        else node = node->right;
    }

    printf("%d", ancestorNode->value);
    while (ancestorNode != NULL) {
        if(ancestorNode->value==val2) {
            // printf(" %d", ancestorNode->value);
            break;
        }
        else if(ancestorNode->value > val2) {
            ancestorNode = ancestorNode->left;
            printf(" L %d", ancestorNode->value);
        }
        else {
            ancestorNode = ancestorNode->right;
            printf(" R %d", ancestorNode->value);
        }
    }
    printf("\n");
}

int diameter(Node * node) {
    if(node==NULL) return 0;

    int lstHeight = 0, rstHeight = 0;
    if(node->left!=NULL) lstHeight = 1+height(node->left);
    if(node->right!=NULL) rstHeight = 1+height(node->right);
    
    return max(1+lstHeight+rstHeight, max(diameter(node->left), diameter(node->right)));
}

int traverseRightSideNodes(Node * node, int arr[], int index) {
    while (node!=NULL) {
        if(node->left==NULL && node->right==NULL) break;
        arr[index++] = node->value;
        if(node->right==NULL) node = node->left;
        else node = node->right;
    }
    return index;
}

int traverseLeafNodes(Node * node, int arr[], int index) {
    if(node==NULL) return index;
    if(node->left==NULL && node->right==NULL){
        arr[index++] = node->value;
        return index;
    }
    index = traverseLeafNodes(node->right, arr, index);
    index = traverseLeafNodes(node->left, arr, index);
}

void traverseLeftSideNodes(Node * node, int arr[], int N) {
    while (node!=NULL) {
        if(node->left==NULL && node->right==NULL) break;
        arr[N--] = node->value;
        if(node->left==NULL) node = node->right;
        else node = node->left;
    }
}

void perimeter(Node * node) {
    if(node==NULL) return;
    int perimeter  = 0;
    int N = numberofNodes(node);
    int arr[N];
    for (int i = 0; i < N; i++) arr[i] = -1;
    int index = 0;
    arr[index++] = node->value;
    index = traverseRightSideNodes(node->right, arr, index);
    index = traverseLeafNodes(node, arr, index);
    traverseLeftSideNodes(node->left, arr, N-1);

    for (int i = 0; i < N; i++)
    {
        if(arr[i]>-1) perimeter += arr[i];
    }
    printf("%d ", perimeter);
    for (int i = 0; i < N; i++)
    {
        if(arr[i]>-1) printf("%d ", arr[i]);
    }
    printf("\n");
}

void freeTreeIfFilled(Node * node) {
    if(node==NULL) return;
    freeTreeIfFilled(node->left);
    freeTreeIfFilled(node->right);
    free(node);
}

void performOperationsBasedOnInput(char choice) {
    switch(choice) {
		case 'T': {
            // BST insertion and deletion
            freeTreeIfFilled(root);
            root = NULL;
            currentTree = BST;
            while(getchar()!=10) {
                int val;
                scanf("%d", &val);
                if(val>0) insertIntoBST(val);
                else if(val<0) root = deleteFromBST(root, abs(val));
                // printf(" %d",val);
            }
            break;
		}
		case 'H': {
            // AVL insertion and deletion
            freeTreeIfFilled(root);
            root = NULL;
            currentTree = AVL;
            while(getchar()!=10) {
                int val;
                scanf("%d", &val);
                if(val>0) insertIntoAVL(val);
                else if(val<0) root = deleteFromAVL(root, abs(val));
            }
			break;
		}
		case 'A': {
            // insert node into existing tree
            while(getchar()!=10) {
                int val;
                scanf("%d", &val);
                if(val>0) {
                    if(currentTree==BST) insertIntoBST(val);
                    else insertIntoAVL(val);
                }
                // printf(" %d",val);
            }
			break;
		}
		case 'U': {
            // delete node from existing tree
            while(getchar()!=10) {
                int val;
                scanf("%d", &val);
                if(val>0) {
                    if(currentTree==BST) root = deleteFromBST(root, val);
                    else root = deleteFromAVL(root, val);
                }
                // printf(" %d",val);
            }
			break;
		}
		case 'F': {
            // find node
            int val;
            scanf("%d", &val);
            findNode(val);
			break;
		}
		case 'Q': {
            // output number of leaves
            printf("%d\n",numberofLeaves(root));
			break;
		}
		case 'N': {
            // output number of nodes
            printf("%d\n",numberofNodes(root));
			break;
		}
		case 'P': {
            // preorder traversal
            preorder(root);
            printf("\n");
			break;
		}
		case 'I':{
            // inorder traversal
            inorder(root);
            printf("\n");
			break;
		}
        case 'S':{
            // postorder traversal
            postorder(root);
            printf("\n");
			break;
		}
        case 'L':{
            // levelorder traversal
            levelOrder(root);
            printf("\n");
			break;
		}
        case 'D':{
            // depth/height
            printf("%d\n",height(root));
			break;
		}
        case 'W':{
            // width
            printf("%d\n",width(root));
			break;
		}
        case 'C':{
            // lowest common ancestor
            while(getchar()!=10) {
                int val1, val2;
                scanf("%d%d", &val1, &val2);
                printf("%d\n",lowestCommonAncestor(val1, val2));
            }
			break;
		}
        case 'R':{
            // route
            while(getchar()!=10) {
                int val1, val2;
                scanf("%d%d", &val1, &val2);
                route(val1, val2);
            }
			break;
		}
        case 'X':{
            // diameter
            printf("%d\n",diameter(root));
			break;
		}
        case 'Y':{
            // perimeter
            perimeter(root);
			break;
		}
		default: break;
    }
}