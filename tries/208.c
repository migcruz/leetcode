/*
 * LeetCode Problem 208: Implement Trie (Prefix Tree)
 * Difficulty: Medium
 *
 * Problem Description:
 * A Trie (pronounced "try") or Prefix Tree is a tree-like data structure used for
 * efficiently storing and retrieving keys in a dataset of strings. It has applications
 * in autocomplete, spell-checking, and text search.
 *
 * Trie Operations:
 * - Trie() -> Initializes a Trie object.
 * - void insert(String word) -> Inserts 'word' into the Trie.
 * - boolean search(String word) -> Returns true if 'word' is in the Trie.
 * - boolean startsWith(String prefix) -> Returns true if any stored word has the prefix.
 *
 * Example 1:
 * Input:
 *   ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
 *   [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
 *
 * Output:
 *   [null, null, true, false, true, null, true]
 *
 * Explanation:
 *   Trie trie = new Trie();
 *   trie.insert("apple");
 *   trie.search("apple");   // returns true
 *   trie.search("app");     // returns false
 *   trie.startsWith("app"); // returns true
 *   trie.insert("app");
 *   trie.search("app");     // returns true
 *
 * Constraints:
 * - 1 <= word.length, prefix.length <= 2000
 * - word and prefix consist only of lowercase English letters.
 * - At most 3 * 10^4 calls will be made to insert, search, and startsWith.
 */

// Forward declare Trie need to do this for typedef struct declarations
typedef struct Trie Trie;  

typedef struct Trie{

    Trie **children;
    bool endOfWord;
    
} Trie;


Trie* trieCreate() {

    Trie *newTrie = (Trie*) malloc (sizeof(Trie));
    newTrie->children = (Trie**) calloc (26, sizeof(Trie*)); // 26 chars in alphabet and only using lowercase ASCII
    newTrie->endOfWord = false;

    return newTrie;
    
}

void trieInsert(Trie* obj, char* word) {

    Trie *temp = obj;

    if (word == NULL || temp == NULL) {
        return;
    }

    int len = strlen(word);

    // Insert each letter of  the word into the trie 
    for (int i = 0; i < len; i++) {

        if ( (temp->children)[word[i] - 'a'] == NULL ) {
            (temp->children)[word[i] - 'a'] = trieCreate();
        }
        temp = (temp->children)[word[i] - 'a']; // update temp like in linked list so we can add the next char to it as a child
    }
    temp->endOfWord = true;
}

bool trieSearch(Trie* obj, char* word) {

    Trie *temp = obj;

    if (word == NULL || temp == NULL) {
        return false;
    }

    int len = strlen(word);

    // find each letter of the word in the trie
    for (int i = 0; i < len; i++) {

        if ( (temp->children)[word[i] - 'a'] == NULL ) {
            return false; // the letter was not found
        }
        temp = (temp->children)[word[i] - 'a'];
    }

    // if false that means all the letters of the word are in the trie but the last letter was not marked as endOfWord = true;
    return temp->endOfWord;
}

bool trieStartsWith(Trie* obj, char* prefix) {

    Trie *temp = obj;

    if (prefix == NULL || temp == NULL) {
        return false;
    }

    int len = strlen(prefix);

    // find each letter of the prefix in the trie
    for (int i = 0; i < len; i++) {

        if ( (temp->children)[prefix[i] - 'a'] == NULL ) {
            return false; // the letter was not found
        }
        temp = (temp->children)[prefix[i] - 'a'];
    }

    // we have found all letters in prefix
    return true;
}

void trieFree(Trie* obj) {

    if (obj == NULL) {
        return;
    }

    // Free all children
    for (int i = 0; i < 26; i++) {
        if (obj->children[i] != NULL) {
            trieFree(obj->children[i]); // Recursively free child nodes
        }
    }

    free(obj->children); // Free the children array
    free(obj); // Free the Trie node itself
}

/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);
 
 * bool param_2 = trieSearch(obj, word);
 
 * bool param_3 = trieStartsWith(obj, prefix);
 
 * trieFree(obj);
*/