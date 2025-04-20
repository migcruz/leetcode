
/*
 * LeetCode Problem 355: Design Twitter
 * Difficulty: Medium
 *
 * Problem Description:
 * Design a simple version of Twitter with the following features:
 *
 *  - Users can post tweets.
 *  - Users can follow or unfollow other users.
 *  - Users can retrieve the 10 most recent tweets in their news feed.
 *
 * Implement the following methods in the Twitter class:
 *
 *   - Twitter(): Constructor to initialize the Twitter object.
 *   - void postTweet(int userId, int tweetId): 
 *       Posts a new tweet with unique ID `tweetId` by user `userId`.
 *
 *   - List<Integer> getNewsFeed(int userId): 
 *       Returns the 10 most recent tweet IDs posted by the user and the users they follow,
 *       sorted from most recent to least recent.
 *
 *   - void follow(int followerId, int followeeId): 
 *       User `followerId` starts following user `followeeId`.
 *
 *   - void unfollow(int followerId, int followeeId): 
 *       User `followerId` unfollows user `followeeId`.
 *
 * Examples:
 *
 * Input:
 *   ["Twitter", "postTweet", "getNewsFeed", "follow", "postTweet", "getNewsFeed", "unfollow", "getNewsFeed"]
 *   [[], [1, 5], [1], [1, 2], [2, 6], [1], [1, 2], [1]]
 *
 * Output:
 *   [null, null, [5], null, null, [6, 5], null, [5]]
 *
 * Explanation:
 *   Twitter twitter = new Twitter();
 *   twitter.postTweet(1, 5); // User 1 posts tweet 5
 *   twitter.getNewsFeed(1);  // Returns [5]
 *   twitter.follow(1, 2);    // User 1 follows User 2
 *   twitter.postTweet(2, 6); // User 2 posts tweet 6
 *   twitter.getNewsFeed(1);  // Returns [6, 5]
 *   twitter.unfollow(1, 2);  // User 1 unfollows User 2
 *   twitter.getNewsFeed(1);  // Returns [5]
 *
 * Constraints:
 *   - 1 <= userId, followerId, followeeId <= 500
 *   - 0 <= tweetId <= 10^4
 *   - All tweet IDs are unique.
 *   - At most 3 * 10^4 method calls.
 *   - A user cannot follow themself.
 */

// we can make a max heap with all the twitter posts, the most recent tweets will be at the top of the max heap
// we wil extract tweets from the heap and as long as they are being followed by the user or is from the user we add to the return array,
// no matter what, we put the tweet into a queue which will be reinserted into the heap
// once the 10 valid tweets have been retrieved, we reinsert the tweets back into the heap

//OR (above method hits TLE because it uses a global heap for all tweets when its not necessary)

// we will make a list of users each with their own tweet stack and a list of users they follow
// we will make a maxHeap each time we call getNewsFeed using tweets from the user and the users they follow
// we will input the most recent tweet from the user in question and also the most recent tweets of the users they follow into the heap
// when we take from the top of the heap, we will insert the next tweet from that user's tweet stack into the heap
// once we have 10 or the heap is empty we return from getNewsFeed
// the twitter class will have a timestamp counter so we can mark which tweets are the most recent in the heap

struct tweetNode {
    struct tweetNode *next;
    int tweetId;
    int timeStamp; // we can use this as the variable of concern for the maxHeap
};

struct User {
    struct tweetNode *tweetStack; // this users stack of tweets with the most recent being at the top
    bool *following; // boolean array of userIds from 1-500 (0-indexed) showing if this user is following any of them
};

typedef struct {
    struct tweetNode **heapArr;
    int size;
    int maxSize;
} maxHeap;

// Stack functions

void insertStack (struct tweetNode **root, struct tweetNode *newNode) {

    // no need to create a node since it's already created

    if (root == NULL) {
        return;
    }

    struct tweetNode *temp = *root;

    if (temp == NULL) {
        // stack is empty
        *root = newNode;
    }
    else {
        newNode->next = temp;
        *root = newNode;
    }

    return;
}

struct tweetNode *popStack(struct tweetNode **root) {

    if (root == NULL) {
        return NULL;
    }

    struct tweetNode *temp = *root;

    *root = temp->next;

    return temp;
}

// Function to swap two elements
void swap(struct tweetNode **a, struct tweetNode **b) {

    if (a == NULL || b == NULL) {
        return;
    }
    struct tweetNode *temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify down (used after deletion)
void maxHeapify(maxHeap *heap, int index) {

    if (heap == NULL) {
        return;
    }

    int left = 2 * index + 1; // left child
    int right = 2 * index + 2; // right child
    int largest = index;
    
    // figure out which child is the largest
    if (left < heap->size && heap->heapArr[left]->timeStamp > heap->heapArr[largest]->timeStamp)
        largest = left;
    if (right < heap->size && heap->heapArr[right]->timeStamp > heap->heapArr[largest]->timeStamp)
        largest = right;
    
    if (largest != index) { // means index was NOT the largest
        swap(&heap->heapArr[index], &heap->heapArr[largest]);
        maxHeapify(heap, largest);
    }
}

// Function to insert an element into the maxHeap
void insertHeap(maxHeap *heap, struct tweetNode *tweetNode) {

    if (heap == NULL) {
        return;
    }

    if (heap->size == heap->maxSize) {
        printf("Heap overflow!\n");
        return;
    }

    // Insert at the end
    (heap->size)++;
    int i = heap->size - 1;
    heap->heapArr[i] = tweetNode;

    // Heapify up to maintain max heap property
    while (i != 0 && heap->heapArr[(i - 1) / 2]->timeStamp < heap->heapArr[i]->timeStamp) { // move element up by swapping with parent if parent is less
        swap(&heap->heapArr[i], &heap->heapArr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to extract the maximum element (root) from maxHeap
struct tweetNode *extractMax(maxHeap *heap) {

    if (heap == NULL) {
        return NULL;
    }

    if (heap->size <= 0) // empty heap
        return NULL;
    if (heap->size == 1) { // only 1 element so no need to bubble up
        heap->size--;
        return heap->heapArr[0];
    }

    struct tweetNode *root = heap->heapArr[0];
    heap->heapArr[0] = heap->heapArr[heap->size - 1]; // bring end of heap to become root
    heap->size--;
    maxHeapify(heap, 0); // now we must rearrange the heap

    return root;
}

// Function to print the heap elements
void printHeap(maxHeap *heap) {
    if (heap == NULL) {
        return;
    }

    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->heapArr[i]->tweetId );
    printf("\n");
}

typedef struct {

    struct User **users; //user list
    int time;

} Twitter;


Twitter* twitterCreate() {

    // Initialize twitter
    Twitter *newTwitter = (Twitter*) malloc (sizeof(Twitter));
    newTwitter->time = 0;

    // Make users list
    newTwitter->users = (struct User**) calloc (501, sizeof(struct User*)); //list of users and each user will have its own array of people they follow
    for (int i = 0; i < 501; i++) {
        struct User *newUser = (struct User*) calloc (1, sizeof(struct User));
        newUser->tweetStack = NULL;
        newUser->following = (bool*) calloc (501, sizeof(bool));
        newTwitter->users[i] = newUser;
    }

    return newTwitter;
    
}

void twitterPostTweet(Twitter* obj, int userId, int tweetId) {

    if (obj == NULL) {
        return;
    }

    // create new tweet
    struct tweetNode *newNode = (struct tweetNode*)malloc(sizeof(struct tweetNode));
    newNode->tweetId = tweetId;
    newNode->next = NULL;
    newNode->timeStamp = obj->time;

    obj->time += 1;

    insertStack(&(obj->users[userId]->tweetStack), newNode);
    
}

int* twitterGetNewsFeed(Twitter* obj, int userId, int* retSize) {

    if (obj == NULL) {
        *retSize = 0;
        return NULL;
    }

    // get the top 10 most recent tweets

    int newsFeedMaxSize = 10;
    int *ret = (int*) calloc (newsFeedMaxSize, sizeof(int));
    int count = 0;

    //make the heap
    // we will push the heads of each users tweetStack onto the max heap
    // when we extract one from the heap, we will push the next tweet from that users tweet stack onto the heap
    maxHeap *newHeap = (maxHeap*) malloc (sizeof(maxHeap));
    newHeap->size = 0;
    newHeap->maxSize = 500; // no need for 501 since indexes in the heap dont match to userId
    newHeap->heapArr = (struct tweetNode**) calloc (500, sizeof(struct tweetNode*));

    //insert nodes into the heap from the user and the users they follow
    if (obj->users[userId]->tweetStack != NULL) {
        insertHeap(newHeap, obj->users[userId]->tweetStack);
    }
    for (int i = 0; i < 501; i++) {

        if (obj->users[userId]->following[i] && obj->users[i]->tweetStack != NULL) {
            insertHeap(newHeap, obj->users[i]->tweetStack);
        }
    }
    // printHeap(newHeap);

    // now we extract from the heap
    while (newHeap->size > 0) {
        struct tweetNode *temp = extractMax(newHeap);
        ret[count] = temp->tweetId;
        count++;

        if (temp->next != NULL) { // insert the next tweet from that user into the heap
            insertHeap(newHeap, temp->next);
        }
        if (count == newsFeedMaxSize) {
            break;
        }
    }

    *retSize = count;
    return ret;
}

void twitterFollow(Twitter* obj, int followerId, int followeeId) {

    if (obj == NULL) {
        return;
    }

    obj->users[followerId]->following[followeeId] = true;
    
}

void twitterUnfollow(Twitter* obj, int followerId, int followeeId) {

    if (obj == NULL) {
        return;
    }

    obj->users[followerId]->following[followeeId] = false;
    
}

void twitterFree(Twitter* obj) {

    if (obj == NULL) {
        return;
    }

    // Empty data from each user
    for (int i = 0; i < 501; i++) {

        struct User *temp = obj->users[i];
        if (temp != NULL) {
            free(temp->following);

            // now free all tweets
            while (temp->tweetStack != NULL) {
                struct tweetNode *freeMe = popStack(&(temp->tweetStack));
                free(freeMe);
            }
            free(temp);
        }
    }
    free(obj->users);

    free(obj);
}

/**
 * Your Twitter struct will be instantiated and called as such:
 * Twitter* obj = twitterCreate();
 * twitterPostTweet(obj, userId, tweetId);
 
 * int* param_2 = twitterGetNewsFeed(obj, userId, retSize);
 
 * twitterFollow(obj, followerId, followeeId);
 
 * twitterUnfollow(obj, followerId, followeeId);
 
 * twitterFree(obj);
*/