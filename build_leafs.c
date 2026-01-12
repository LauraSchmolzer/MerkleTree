#include "common.h"

void build_leafs(const char *text, unsigned char leafs[][SHA256_DIGEST_LENGTH], int *n_leafs) {
    // Slice the text into words
    int max_words = MAX_WORD_LENGTH; // max words to split
    char *words[max_words]; // array to store pointers to words

    // Slice text into words
    int n_words = slice_text_into_words(text, words, max_words);

    // Hash the words
    hash_words(words, leafs, n_words);

    *n_leafs = n_words;

    // free all memory allocated for words
    for (int i = 0; i < n_words; i++) {
    free(words[i]);
    }
}

// Helpers function to hash a list of words into nodes
void hash_words(char *words[], unsigned char nodes[][SHA256_DIGEST_LENGTH], int n_words) {
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

