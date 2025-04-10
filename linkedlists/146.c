
/*
 * LeetCode Problem 146: LRU Cache
 * Difficulty: Medium
 *
 * Problem Description:
 * Design a data structure that implements a Least Recently Used (LRU) cache.
 * The cache supports O(1) average time complexity for the following operations:
 *
 *  - LRUCache(int capacity): Initializes the cache with a positive size.
 *  - int get(int key): Returns the value of the key if it exists, otherwise -1.
 *  - void put(int key, int value): Updates the value if the key exists;
 *    otherwise, adds the key-value pair. If the number of keys exceeds the
 *    capacity, evicts the least recently used key.
 *
 * The get and put operations must both run in O(1) average time.
 *
 * Example:
 *
 * Input:
 * ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
 * [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
 *
 * Output:
 * [null, null, null, 1, null, -1, null, -1, 3, 4]
 *
 * Explanation:
 * LRUCache lRUCache = new LRUCache(2);
 * lRUCache.put(1, 1); // cache is {1=1}
 * lRUCache.put(2, 2); // cache is {1=1, 2=2}
 * lRUCache.get(1);    // returns 1
 * lRUCache.put(3, 3); // evicts key 2, cache is {1=1, 3=3}
 * lRUCache.get(2);    // returns -1 (not found)
 * lRUCache.put(4, 4); // evicts key 1, cache is {4=4, 3=3}
 * lRUCache.get(1);    // returns -1
 * lRUCache.get(3);    // returns 3
 * lRUCache.get(4);    // returns 4
 *
 * Constraints:
 *  - 1 <= capacity <= 3000
 *  - 0 <= key <= 10^4
 *  - 0 <= value <= 10^5
 *  - At most 2 * 10^5 calls will be made to get and put.
 *
 * Design Hint:
 * Use a combination of:
 *  - Hash map: key -> node pointer (for O(1) access)
 *  - Doubly linked list: maintains usage order (head = MRU, tail = LRU)
 *
 * Eviction = remove node at tail.
 * Access/update = move node to head.
 */

struct number { // need a doubly linked list for LRUCache so we can rearrange the linked list quickly

    struct number *next;
    struct number *prev;
    int key; //id for uthash
    int val; 
    UT_hash_handle hh; // makes this struct hashable via uthash https://troydhanson.github.io/uthash/. This is already part of leetcode. It's just a header so there's library to link against for builds.
    
};

// hash map implementation
struct number *numberDict = NULL;

struct number *add_number(int key, int val) {

    struct number *newNumber = NULL;
    HASH_FIND_INT(numberDict, &key, newNumber);

    if (newNumber == NULL) {
        newNumber = (struct number*) malloc (sizeof(struct number));
        newNumber->key = key;
        newNumber->val = val;
        newNumber->next = NULL;
        newNumber->prev = NULL;
        HASH_ADD_INT(numberDict, key, newNumber);
    }

    return newNumber;
}

struct number *get_number(int num) {

    struct number *temp = NULL;
    HASH_FIND_INT(numberDict, &num, temp);
    
    return temp;
}

void delete_number(int num) {
    struct number *temp = get_number(num);

    if (temp != NULL) {
        HASH_DEL(numberDict, temp);  /* user: pointer to deletee */
        free(temp);             /* optional; it's up to you! */
    }
}

// LRU Cache implementation

typedef struct LRUCache LRUCache;  

typedef struct LRUCache{

    int capacity;
    struct number *left;
    struct number *right;
} LRUCache;

// insert node back to be most recent
void lRUCacheInsert(LRUCache *obj, struct number *node) {

    if (obj == NULL) {
        return;
    }

    struct number *prev = (obj->right)->prev;
    struct number *next = obj->right;

    prev->next = node;
    next->prev = node;

    node->next = next;
    node->prev = prev;

}

// remove LRU node from LL
void lRUCacheRemove(LRUCache *obj, struct number *node) {

    if (obj == NULL) {
        return;
    }

    struct number *prev = node->prev;
    struct number *next = node->next;
    prev->next = next;
    next->prev = prev;

}

LRUCache* lRUCacheCreate(int capacity) {

    LRUCache *newCache = (LRUCache*) malloc (sizeof(LRUCache));
    newCache->capacity = capacity;
    // we need to create empty nodes for right and left. Right is going to be most recent and left will point to least recent.
    // the actual nodes of the LRUCache will be inbetween left and right
    newCache->right = (struct number*) malloc (sizeof(struct number));
    newCache->left = (struct number*) malloc (sizeof(struct number));

    (newCache->right)->prev = newCache->left;
    (newCache->left)->next = newCache->right;

    return newCache;
    
}

int lRUCacheGet(LRUCache* obj, int key) {

    if (obj == NULL) {
        return -1;
    }
    // we need retrieve the value and also update the cache's most recently used
    struct number *node = get_number(key);
    if (node == NULL) {
        return -1;
    }

    // update the LRU cache
    // need to delete number and readd it
    lRUCacheRemove(obj, node);
    lRUCacheInsert(obj, node);
    return node->val;
    
}

void lRUCachePut(LRUCache* obj, int key, int val) {

    if (obj == NULL) {
        return;
    }

    struct number *newNode = get_number(key);
    if (newNode == NULL) { //does not exist
        newNode = add_number(key, val);
    }
    else {
        lRUCacheRemove(obj, newNode); // remove so we can add it back in and it will be at the top of the list
        newNode->val = val;
    }
    lRUCacheInsert(obj, newNode);

    if (HASH_COUNT(numberDict) > obj->capacity) {
        // remove LRU from list and hashmap
        struct number *temp = (obj->left)->next;
        lRUCacheRemove(obj, temp);
        delete_number(temp->key);
    }

    // printf("CurrentCapacity: %d\r\n", HASH_COUNT(numberDict));
}

void lRUCacheFree(LRUCache* obj) {

    free(obj->right);
    free(obj->left);
    free(obj);

    struct number *currNumber;
    struct number *temp;

    HASH_ITER(hh, numberDict, currNumber, temp) {
        HASH_DEL(numberDict, currNumber);  /* delete; users advances to next */
        free(currNumber);             /* optional- if you want to free  */
    }

}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/

// Resources:
// Neetcode on LRUCache: https://www.youtube.com/watch?v=7ABFKPK2hD4&t=843s