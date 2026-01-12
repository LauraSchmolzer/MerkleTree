#include "common.h"

MerkleNode* build_merkle_tree(const char *text, unsigned char root_hash[SHA256_DIGEST_LENGTH]) {

    // Create leaf nodes
    unsigned char leafs[MAX_WORD_LENGTH][SHA256_DIGEST_LENGTH];
    int n_nodes;

    // Build the hashed words as leafs from the text
    build_leafs(text, leafs, &n_nodes);

    // Create the MerkleNode struct for the hashed leafs
    MerkleNode **nodes = malloc(n_nodes * sizeof(MerkleNode*));
    for (int i = 0; i < n_nodes; i++) {
        nodes[i] = malloc(sizeof(MerkleNode));
        memcpy(nodes[i]->hash, leafs[i], SHA256_DIGEST_LENGTH);
        nodes[i]->left = NULL;
        nodes[i]->right = NULL;
    }

    // nodes: array of MerkleNode* at current level
    // n_nodes: number of nodes at this level
    while (n_nodes > 1) {
        // Check if odd -> duplicate last node
        if (n_nodes % 2 != 0) {
            nodes = realloc(nodes, (n_nodes + 1) * sizeof(MerkleNode*));
            nodes[n_nodes] = nodes[n_nodes - 1]; // duplicate last node pointer
            n_nodes++;
        }

        // Create a new array for the next level
        int new_level_count = n_nodes / 2;
        MerkleNode **new_level = malloc(new_level_count * sizeof(MerkleNode*));

        // Combine nodes in pairs
        for (int i = 0; i < n_nodes; i += 2) {
            new_level[i / 2] = build_nodes(nodes[i], nodes[i + 1]);
        }

        // Free the old level if you allocated dynamically
        free(nodes);

        // Move to the next level
        nodes = new_level;
        n_nodes = new_level_count;
    }

    // nodes[0] is the root
    memcpy(root_hash, nodes[0]->hash, SHA256_DIGEST_LENGTH);

    MerkleNode *root = nodes[0]; // keep pointer to root for further use
    free(nodes); // free the array of the node pointers, not nodes themselves
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