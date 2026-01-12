#include "common.h"

int main() {
    const char *text = "Hello words slay";

    int max_words = 10;                     // max words to split
    char *words[max_words];                 // array to store pointers to words

    // Slice text into words
    int n_filled = slice_text_into_words(text, words, max_words);

    // Print the words
    for (int i = 0; i < n_filled; i++) {
        printf("Word %d: %s\n", i, words[i]);
    }

    return 0;
}