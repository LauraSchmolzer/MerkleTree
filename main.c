#include "common.h"

int main() {
    const char *words[] = {"Hello", "world", "slay"};
    int n_words = sizeof(words) / sizeof(words[0]);

    // 2D array to store hashes
    unsigned char nodes[n_words][SHA256_DIGEST_LENGTH];

    // Hash the words
    hash_words(words, n_words, nodes);

    // Print hashes
    for (int i = 0; i < n_words; i++) {
        printf("Word: %s\nHash: ", words[i]);
        for (int j = 0; j < SHA256_DIGEST_LENGTH; j++) {
            printf("%02x", nodes[i][j]);
        }
        printf("\n\n");
    }

    return 0;
}