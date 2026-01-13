#include "common.h"
// Here we will implement the function to verify that a given word at a given index corresponds to a given root hash using the authentication path
bool verify_proof(char *text, Proof *proof) {
    // Start with the hash of the word
    unsigned char current_hash[SHA256_DIGEST_LENGTH];

    SHA256((unsigned char *)proof->word, strlen(proof->word), current_hash);

    int index = proof->word_index;

    for (int i = 0; i < proof->path_length; i++) {
        unsigned char combined[2 * SHA256_DIGEST_LENGTH];
        if (index % 2 == 0) { // current node is left child
            memcpy(combined, current_hash, SHA256_DIGEST_LENGTH);
            memcpy(combined + SHA256_DIGEST_LENGTH, proof->authentication_path[i], SHA256_DIGEST_LENGTH);
        } else { // current node is right child
            memcpy(combined, proof->authentication_path[i], SHA256_DIGEST_LENGTH);
            memcpy(combined + SHA256_DIGEST_LENGTH, current_hash, SHA256_DIGEST_LENGTH);
        }

        SHA256(combined, 2 * SHA256_DIGEST_LENGTH, current_hash); // recompute hash
        index /= 2;
    }

    printf("Computed root hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", current_hash[i]);
    }
    printf("\n");


    return memcmp(current_hash, proof->root_hash, SHA256_DIGEST_LENGTH) == 0;
}