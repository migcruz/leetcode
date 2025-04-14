# Helper functions for Linked Lists

## Linked List reversal
```C
// Function to reverse the linked list
Node* reverseList(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;  // Store next node
        current->next = prev;  // Reverse pointer
        prev = current;        // Move prev forward
        current = next;        // Move current forward
    }
    return prev;  // New head of reversed list
}
```

## Linked lists as queues
### Enqueue
```C
// We need to make a queue which is FIFO.
void insertNode(struct queueNode **node, int val) {
    if (node == NULL) {
        return;
    }
    
    struct queueNode *temp = *node;
    struct queueNode *newNode = (struct queueNode*) malloc (sizeof(struct queueNode));
    newNode->val = val;
    newNode->next = NULL;

    if (temp == NULL) { // list is empty
        *node = newNode;
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // we are at the end of the queue
        temp->next = newNode;
    }
    return;
}
```
### Dequeue
```C
// here we need to pop the top of the queue  and then update the root ptr
int popFront(struct queueNode **node) {

    if (node == NULL) {
        return NULL;
    }

    struct queueNode *temp = *node;
    int val;

    *node = temp->next;
    val = temp->val;
    
    free(temp);
    return val;
}
```
## Linked lists as stacks
### Push Stack
```C
void pushStack(struct Node **root, int val) {

    if (root == NULL) {
        return;
    }

    struct Node *temp = *root;
    struct Node *newNode = (struct Node*) malloc (sizeof(struct Node));
    newNode->next = NULL;
    newNode->val = val;

    if (temp == NULL) {
        *root = newNode;
    }
    else {
        newNode->next = *root;
        *root = newNode;
    }

}
```
### Pop stack
```C
int popStack(struct Node **root) {

    if (root == NULL) {
        return;
    }
    int val;
    struct Node *temp = *root;
    *root = temp->next;
    val = temp->val;

    free(temp);
    return val;

}
```