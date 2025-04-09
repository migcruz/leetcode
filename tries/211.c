/*
 * LeetCode Problem 211: Design Add and Search Words Data Structure
 * Difficulty: Medium
 *
 * Problem Description:
 * A data structure that allows efficient storage and searching of words, 
 * including support for wildcard character '.' (which can match any letter).
 *
 * WordDictionary Operations:
 * - WordDictionary() -> Initializes a WordDictionary object.
 * - void addWord(word) -> Adds 'word' to the data structure.
 * - bool search(word) -> Returns true if 'word' exists, allowing '.' wildcard matching.
 *
 * Example:
 * Input:
 *   ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
 *   [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
 *
 * Output:
 *   [null, null, null, null, false, true, true, true]
 *
 * Explanation:
 *   WordDictionary wordDictionary = new WordDictionary();
 *   wordDictionary.addWord("bad");
 *   wordDictionary.addWord("dad");
 *   wordDictionary.addWord("mad");
 *   wordDictionary.search("pad"); // returns False
 *   wordDictionary.search("bad"); // returns True
 *   wordDictionary.search(".ad"); // returns True
 *   wordDictionary.search("b.."); // returns True
 *
 * Constraints:
 * - 1 <= word.length <= 25
 * - word in addWord consists of lowercase English letters.
 * - word in search consists of '.' or lowercase English letters.
 * - There will be at most 2 dots '.' in search queries.
 * - At most 10^4 calls will be made to addWord and search.
 */

// Forward declare Trie need to do this for typedef struct declarations
typedef struct WordDictionary WordDictionary;  

typedef struct WordDictionary{

    WordDictionary **children;
    bool endOfWord;
    
} WordDictionary;

WordDictionary* wordDictionaryCreate() {

    WordDictionary *newTrie = (WordDictionary*) malloc (sizeof(WordDictionary));
    newTrie->children = (WordDictionary**) calloc (26, sizeof(WordDictionary*)); // 26 chars in alphabet and only using lowercase ASCII
    newTrie->endOfWord = false;

    return newTrie;
    
}

void wordDictionaryAddWord(WordDictionary* obj, char* word) {

   WordDictionary *temp = obj;

    if (word == NULL || temp == NULL) {
        return;
    }

    int len = strlen(word);

    // Insert each letter of  the word into the trie 
    for (int i = 0; i < len; i++) {

        if ( (temp->children)[word[i] - 'a'] == NULL ) {
            (temp->children)[word[i] - 'a'] = wordDictionaryCreate();
        }
        temp = (temp->children)[word[i] - 'a']; // update temp like in linked list so we can add the next char to it as a child
    }
    temp->endOfWord = true;
}

bool wordDictionarySearchHelper(WordDictionary* obj, char* word, int index) { // need to recursively search all nodes when wildcard is encountered instead of using a for loop
    if (obj == NULL || word == NULL) {
        return false;
    }

    // If we've reached the end of the word, check if it's a valid word
    if (index == strlen(word)) {
        return obj->endOfWord;
    }

    char c = word[index];

    if (c == '.') {
        // Check ALL possible children for a match
        for (int i = 0; i < 26; i++) {
            if (obj->children[i] != NULL) {
                int ret = wordDictionarySearchHelper(obj->children[i], word, index + 1); 
                if (ret) {
                    return true; // If ANY path succeeds, return true
                }
            }
        }
        return false;  // No valid path found
    } else {
        // Normal character lookup
        int charIndex = c - 'a';
        return wordDictionarySearchHelper(obj->children[charIndex], word, index + 1);
    }
}

bool wordDictionarySearch(WordDictionary* obj, char* word) {

    return wordDictionarySearchHelper(obj, word, 0);
    
}

void wordDictionaryFree(WordDictionary* obj) {

    if (obj == NULL) {
        return;
    }

    // Free all children
    for (int i = 0; i < 26; i++) {
        if (obj->children[i] != NULL) {
            wordDictionaryFree(obj->children[i]); // Recursively free child nodes
        }
    }

    free(obj->children); // Free the children array
    free(obj); // Free the Trie node itself
    
}

/**
 * Your WordDictionary struct will be instantiated and called as such:
 * WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);
 
 * bool param_2 = wordDictionarySearch(obj, word);
 
 * wordDictionaryFree(obj);
*/