#include "common.h"

MerkleNode* build_merkle_tree(const char *text, unsigned char root_hash[SHA256_DIGEST_LENGTH]) {
    // Create leaf nodes
    int n_leaves;
    MerkleNode **leaves = build_leafs(text, &n_leaves);

    // Work array for current level
    MerkleNode **current_level = malloc(n_leaves * sizeof(MerkleNode*)); // array of pointers to leaves
    for (int i = 0; i < n_leaves; i++) current_level[i] = leaves[i]; // copy pointers
    free(leaves); // free the initial pointer array, nodes remain

    int level_size = n_leaves;

    while (level_size > 1) { // while more than one node at current level
        int next_level_size = (level_size + 1) / 2; 
        MerkleNode **next_level = malloc(next_level_size * sizeof(MerkleNode*)); // array of pointers for next level

        for (int i = 0, j = 0; i < level_size; i += 2, j++) {
            if (i + 1 < level_size) {
                // Pointer at j in next level is parent of i and i+1 in current level
                next_level[j] = build_nodes(current_level[i], current_level[i+1]); // pair nodes and build parent
            } else {
                // Last node duplicated if odd
                next_level[j] = build_nodes(current_level[i], current_level[i]);
            }
        }

        free(current_level); // free the array of pointers
        current_level = next_level; // move to next level
        level_size = next_level_size;
    }

    memcpy(root_hash, current_level[0]->hash, SHA256_DIGEST_LENGTH); // copy root hash
    MerkleNode *root = current_level[0]; // root node
    free(current_level); // free the final array of pointers

    return root;
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

void free_merkle_tree(MerkleNode *node) {
    if (!node) return;
    free_merkle_tree(node->left);
    free_merkle_tree(node->right);
    free(node);
}