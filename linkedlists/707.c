/*
 * LeetCode Problem 707: Design Linked List
 * Difficulty: Medium
 *
 * Problem Description:
 * Design a linked list implementation.
 * You may choose a singly or doubly linked list structure.
 * Each node should have attributes like 'val' (value of the node) and 'next' (pointer to the next node).
 * A doubly linked list may also have 'prev' to indicate the previous node.
 * All indices in the list are 0-based.
 *
 * Implement the following operations in the MyLinkedList class:
 *
 * - MyLinkedList(): Initializes the linked list object.
 * - int get(int index): Returns the value of the node at the given index, or -1 if the index is invalid.
 * - void addAtHead(int val): Inserts a node with value val at the beginning of the list.
 * - void addAtTail(int val): Appends a node with value val to the end of the list.
 * - void addAtIndex(int index, int val): Inserts a node with value val before the given index.
 *      If index equals the length of the list, the node is appended.
 *      If index is greater than the length, no insertion occurs.
 * - void deleteAtIndex(int index): Deletes the node at the given index if it exists.
 *
 * Example:
 * Input:
 * ["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
 * [[], [1], [3], [1, 2], [1], [1], [1]]
 * Output:
 * [null, null, null, null, 2, null, 3]
 * Explanation:
 * MyLinkedList myLinkedList = new MyLinkedList();
 * myLinkedList.addAtHead(1);              // list: 1
 * myLinkedList.addAtTail(3);              // list: 1 -> 3
 * myLinkedList.addAtIndex(1, 2);          // list: 1 -> 2 -> 3
 * myLinkedList.get(1);                    // returns 2
 * myLinkedList.deleteAtIndex(1);          // list: 1 -> 3
 * myLinkedList.get(1);                    // returns 3
 *
 * Constraints:
 * - 0 <= index, val <= 1000
 * - Do not use the built-in LinkedList library.
 * - At most 2000 method calls will be made to get, addAtHead, addAtTail, addAtIndex, and deleteAtIndex.
 */

typedef struct MyLinkedList MyLinkedList; 

typedef struct Node Node;  

typedef struct Node{
    Node *next;
    int val;
    
} Node;

typedef struct MyLinkedList{
    Node *head;
    
} MyLinkedList;


MyLinkedList* myLinkedListCreate() {

    MyLinkedList *newList = (MyLinkedList*) malloc (sizeof(MyLinkedList));
    newList->head = NULL;

    return newList;
    
}

int myLinkedListGet(MyLinkedList* obj, int index) {

    int count = 0;
    int ret = -1;

    Node *temp = obj->head;

    while (temp != NULL) {
        if (count == index) {
            ret = temp->val;
            break;
        }
        temp = temp->next;
        count++;
    }

    return ret;
    
}

void myLinkedListAddAtHead(MyLinkedList* obj, int val) {

    Node *newNode = (Node*) malloc (sizeof(Node));

    newNode->next = obj->head;
    newNode->val = val;

    obj->head = newNode;
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val) {

    Node *temp = obj->head;

    if (temp == NULL) {
        myLinkedListAddAtHead(obj, val);
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }

    //now we're at last node
    Node *newNode = (Node*) malloc (sizeof(Node));
    newNode->next = NULL;
    newNode->val = val;
    temp->next = newNode;
    
}

void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {

    int count = 0;

    Node *temp = obj->head;
    Node *prev = temp;

    if (index == 0) { // empty list
        myLinkedListAddAtHead(obj, val);
        return;
    } 

    while (temp != NULL) {

        if (count == index) {
            Node *newNode = (Node*) malloc (sizeof(Node));
            newNode->val = val;
            newNode->next = temp;

            prev->next = newNode;

            return;
            
        }
        prev = temp;
        temp = temp->next;
        count++;
    }

    if (count == index) { // we need to add to the tail
        Node *newNode = (Node*) malloc (sizeof(Node));
        newNode->val = val;
        newNode->next = NULL;

        prev->next = newNode;
        return;
    }

    return;
    
}

void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {

    int count = 0;
    Node *temp = obj->head;
    Node *prev = temp;

    if (temp == NULL) {
        return;
    }

    if (index == 0 && temp != NULL) {
        obj->head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL) {

        if (count == index) {
            prev->next = temp->next;
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
        count++;
    }
    
}

void myLinkedListFree(MyLinkedList* obj) {

    Node *temp = obj->head;

    while (temp != NULL) {
        Node *del = temp;
        temp = temp->next;

        free(del);
    }

    free(obj);
    
}

/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);
 
 * myLinkedListAddAtHead(obj, val);
 
 * myLinkedListAddAtTail(obj, val);
 
 * myLinkedListAddAtIndex(obj, index, val);
 
 * myLinkedListDeleteAtIndex(obj, index);
 
 * myLinkedListFree(obj);
*/