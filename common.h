/* common.h */
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h> 
#include <openssl/sha.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

typedef struct MerkleNode {
    unsigned char hash[SHA256_DIGEST_LENGTH]; // SHA256 hash
    struct MerkleNode *left;                  // left child
    struct MerkleNode *right;                 // right child
} MerkleNode;

typedef struct MerkleTree {
    MerkleNode *root;  // pointer to the root node
    int n_leaves;      // number of leaves
    MerkleNode **leaves; // array of pointers to leaf nodes
} MerkleTree;

MerkleNode* build_merkle_tree(const char *text, unsigned char root_hash[SHA256_DIGEST_LENGTH])
void build_leafs(const char *text, unsigned char leafs[][SHA256_DIGEST_LENGTH], int *n_leafs);

#endif /* COMMON_H */