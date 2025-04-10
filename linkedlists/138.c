/*
 * LeetCode Problem 138: Copy List with Random Pointer
 * Difficulty: Medium
 *
 * Problem Description:
 * A linked list of length 'n' is given where each node contains an additional 
 * 'random' pointer, which could point to any node in the list or be NULL.
 *
 * Construct a deep copy of the list. The deep copy should consist of exactly 'n' 
 * brand new nodes, where each new node has its value set to the value of its 
 * corresponding original node. Both the 'next' and 'random' pointers of the new 
 * nodes should point to new nodes in the copied list, such that the pointers in 
 * the original and copied list represent the same state. None of the pointers in 
 * the new list should reference any node in the original list.
 *
 * Input and Output Representation:
 * The linked list is represented as a list of 'n' nodes. Each node is a pair: 
 * [val, random_index], where:
 * - val: integer representing Node.val
 * - random_index: index of the node that the 'random' pointer refers to, or null
 *
 * Return the head of the deep copied list.
 *
 * Example 1:
 * Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
 * Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
 *
 * Example 2:
 * Input: head = [[1,1],[2,1]]
 * Output: [[1,1],[2,1]]
 *
 * Example 3:
 * Input: head = [[3,null],[3,0],[3,null]]
 * Output: [[3,null],[3,0],[3,null]]
 *
 * Constraints:
 * - 0 <= n <= 1000
 * - -10^4 <= Node.val <= 10^4
 * - Node.random is either NULL or points to another node in the list
 */

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *next;
 *     struct Node *random;
 * };
 */

 struct Node *copyNode(struct Node *node) {

    if (node == NULL) {
        return NULL;
    }

    struct Node *newNode = (struct Node*) malloc (sizeof(struct Node));
    newNode->val = node->val;
    newNode->random = NULL;
    newNode->next = NULL;

    return newNode;
}

void printNode (struct Node *node) {

    if (node == NULL) {
        printf("NULL ");
    }
    else {
        printf("%d ", node->val);
    }

    return;

}

struct Node* copyRandomList(struct Node* head) {

    // at every node we will perform a copy and then traverse to the random ptr from the original LL. we will copy this node if it exists then return it back to the copy to be assigned
    // then we will adjust the copyHead to goto next which will be NULL, then we will also adjust head to goto next and repeat
    // the trick is assigning the random ptr properly. Once we copy all the nodes we cannot create new nodes so we must assign the random pts in the copied list properly
    // to do this we need to reference the original list and the only way to know that the random ptr point to the correct one is by indexes if you put every node in the copied list
    // as an element in an array

    // then in the original list we need to know the proper indices for the random ptrs as if we put them in an array of node ptr

    if (head == NULL) {
        return NULL;
    }

    struct Node *temp = head;
    int count = 0;

    // Find out the how many nodes are in the linked list
    while (temp != NULL) {
        // printf("temp: %d\r\n", (uintptr_t)temp);
        count++;
        temp = temp->next;
    }
    temp = head;

    // copy the root node
    int i = 0;
    struct Node *copyHead = copyNode(head);
    struct Node *copyHeadIter = copyHead;

    struct Node **nodeArr = (struct Node**) malloc (sizeof(struct Node*) * (count + 1)); // + 1 because we need to store extra element for NULL
    nodeArr[i] = copyHeadIter;
    // copy all the nodes but not assigning the random ptr values
    while (temp != NULL) {
        copyHeadIter->next = copyNode(temp->next);

        // printNode(copyHeadIter);
        // printNode(temp);
        // printf("\r\n");

        nodeArr[i] = copyHeadIter;
        i++;
        copyHeadIter = copyHeadIter->next;
        temp = temp->next;
    }
    nodeArr[count] = NULL;

    // make an array containing the random node ptrs as if they were an index value of the original list
    // i.e indexArr[i] = index of the node that random ptr of ith node points if the linked list were in an array
    // indexArr[1] = 0, since the 2nd node points to the first node which is index 0
    // indexArr[0] = count; 

    // we will use these indices to refer to nodeArr[] which cointains the ptrs to the copied nodes, they are in order and the last element in nodeArr is NULL;
    int *indexArr = (int*) malloc (sizeof(int) * count);
    temp = head;
    uintptr_t headInt = (uintptr_t)head;
    for (i = 0; i < count; i++) {
        
        uintptr_t index = ((uintptr_t)temp->random - headInt) / 48; // we got 48 as the offset between nodes from the top print while loop
        indexArr[i] = index;
        if (indexArr[i] < 0) { // random was null
            indexArr[i] = count;
        }
        // printf("arr: %d\r\n", indexArr[i]);
        temp = temp->next;
    }

    // Now let's assign the random ptrs
    copyHeadIter = copyHead;
    i = 0;
    while (copyHeadIter != NULL) {
        copyHeadIter->random = nodeArr[indexArr[i]];
        copyHeadIter = copyHeadIter->next;
        i++;
    }

    return copyHead;
}