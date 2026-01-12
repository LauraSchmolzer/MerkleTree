#include "common.h"

int main() {
    const char *text = "Hello world this is a beautiful string";

    unsigned char root_hash[SHA256_DIGEST_LENGTH];
    // Build the Merkle tree and get the root node
    MerkleNode *root = build_merkle_tree(text, root_hash);

    // Print the root hash in hex
    printf("Merkle root: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", root_hash[i]);
    }
    printf("\n");

    free_merkle_tree(root);



    return 0;
}