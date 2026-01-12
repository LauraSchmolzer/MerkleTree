#include "common.h"

MerkleNode* create_leaf(const char *word) {
    MerkleNode *leaf = malloc(sizeof(MerkleNode));
    SHA256((unsigned char*)word, strlen(word), leaf->hash);
    leaf->left = NULL;
    leaf->right = NULL;
    return leaf;
}

// Returns an array of MerkleNode* representing the leaf nodes
MerkleNode** build_leafs(const char *text, int *n_leaves) {
    // Slice the text into words
    char *words[MAX_WORD_LENGTH]; // array to store pointers to words

    // Slice text into words
    int n_words = slice_text_into_words(text, words, MAX_WORD_LENGTH);

    // If odd number of words, duplicate the last word
    if (n_words % 2 != 0) {
        words[n_words] = malloc(strlen(words[n_words - 1]) + 1);
        strcpy(words[n_words], words[n_words - 1]);
        n_words++;
    }

    // Create leaf nodes
    MerkleNode **leaves = malloc(n_words * sizeof(MerkleNode*));
    for (int i = 0; i < n_words; i++) {
        leaves[i] = create_leaf(words[i]);
    }

    *n_leaves = n_words;

    // free all memory allocated for words
    for (int i = 0; i < n_words; i++) free(words[i]);
    
    return leaves;
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

