#include "common.h"

void build_merkle_tree(const char *text, unsigned char root_hash[SHA256_DIGEST_LENGTH]) {

    // Create leaf nodes
    unsigned char leafs[MAX_WORD_LENGTH][SHA256_DIGEST_LENGTH];
    int n_leafs;

    build_leafs(text, leafs, &n_leafs);
}

// Helper function to hash two nodes together
MerkleNode* build_nodes(MerkleNode *left, MerkleNode *right) {
    MerkleNode *parent = malloc(sizeof(MerkleNode));
    
    // Concatenate left and right hashes
    unsigned char combined[2 * SHA256_DIGEST_LENGTH];
    memcpy(combined, left->hash, SHA256_DIGEST_LENGTH);
    memcpy(combined + SHA256_DIGEST_LENGTH, right->hash, SHA256_DIGEST_LENGTH);

    // Compute parent hash
    SHA256(combined, 2 * SHA256_DIGEST_LENGTH, parent->hash);

    // Set child pointers
    parent->left = left;
    parent->right = right;

    return parent;
}