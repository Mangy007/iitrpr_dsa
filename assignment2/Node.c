typedef struct Node {
    int value;
    struct Node * next;
} Node;

typedef struct DoubleLinkedNode {
    int value;
    struct DoubleLinkedNode * next;
    struct DoubleLinkedNode * prev;
} DoubleLinkedNode;