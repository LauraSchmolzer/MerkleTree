#include "common.h"

#define MAX_WORD_LENGTH 100

void structure_tree(const char *text) {
    // Slice the text into words

    //const char *words[]


    //unsigned char[][] words = slice_text_into_words(text)

    // Check if number of nodes is odd, if so duplicate last node

    // Create leaf nodes of each word hashing

    //int n_words = sizeof(words) / sizeof(words[0]);

    // 2D array to store hashes
    //unsigned char nodes[n_words][SHA256_DIGEST_LENGTH];

    // Hash the words
    //hash_words(words, nodes, n_words);

    

    // Build the tree by hashing pairs of nodes until the root is formed

}

// Helpers function to hash a list of words into nodes
void hash_words(const char *words[], unsigned char nodes[][SHA256_DIGEST_LENGTH], int n_words) {
    for (int i = 0; i < n_words; i++) {
        SHA256((unsigned char *)words[i], strlen(words[i]), nodes[i]);
    }
}

int slice_text_into_words(const char *text, char *words[], int n_words) {
    // Make mutable copy of the text
    char *text_copy = malloc(strlen(text) + 1);
    strcpy(text_copy, text);

    char *word = strtok(text_copy, " "); // Points to first character of first word

    int index = 0;
    while (word!= NULL && index <n_words) {
        if (strlen(word) > 0) { // skip empty tokens
            // Allocate memory on the heap for the word 
            words[index] = malloc(strlen(word)+1);
            strcpy(words[index], word); // copy word into words array
            index++;
        }
        word = strtok(NULL, " "); // Points to first character of next word
    }

    free(text_copy); // free the temporary copy, done with the memory
    return index; // number of words filled
}
