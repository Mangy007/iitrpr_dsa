typedef struct Node {
    int value;
    struct Node * next;
} Node;

typedef struct DoubleLinkedNode {
    int value;
    struct DoubleLinkedNode * prev;
    struct DoubleLinkedNode * next;
} DoubleLinkedNode;