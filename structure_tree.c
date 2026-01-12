#include "common.h"

#define MAX_WORD_LENGTH 100

void structure_tree(const char *text) {
    // Slice the text into words
    //unsigned char[][] words = slice_text_into_words(text)

    // Check if number of nodes is odd, if so duplicate last node

    // Create leaf nodes of each word hashing
    

    // Build the tree by hashing pairs of nodes until the root is formed

}

// Helpers function to hash a list of words into nodes
void hash_words(const char *words[], int n_words, unsigned char nodes[][SHA256_DIGEST_LENGTH]) {
    for (int i = 0; i < n_words; i++) {
        SHA256((unsigned char *)words[i], strlen(words[i]), nodes[i]);
    }
}
