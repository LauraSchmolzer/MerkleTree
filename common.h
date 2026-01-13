/* common.h */
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h> 
#include <openssl/sha.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


#define MAX_WORD_LENGTH 100 // Maximum number of words in the text
#define MAX_WORD_LEN 100 // Maximum length of a single word
#define MAX_PATH_LENGTH 20

typedef struct MerkleNode {
    unsigned char hash[SHA256_DIGEST_LENGTH]; // SHA256 hash
    struct MerkleNode *left;                  // left child
    struct MerkleNode *right;                 // right child
    struct MerkleNode *parent;                // parent node
} MerkleNode;

typedef struct MerkleTree {
    MerkleNode *root;  // pointer to the root node
    int n_leaves;      // number of leaves
    MerkleNode **leaves; // array of pointers to leaf nodes
} MerkleTree;

typedef struct Proof {
    unsigned char root_hash[SHA256_DIGEST_LENGTH];  // root node
    char word[MAX_WORD_LEN];    // string of the word being proved
    int word_index; // index of the word in the original text
    int path_length; // length of the authentication path
    unsigned char authentication_path[MAX_PATH_LENGTH][SHA256_DIGEST_LENGTH]; // authentication path
} Proof;

void build_merkle_tree(const char *text, unsigned char root_hash[SHA256_DIGEST_LENGTH], MerkleTree *tree);
MerkleNode** build_leafs(const char *text, int *n_leaves);
int slice_text_into_words(const char *text, char *words[], int n_words);
MerkleNode* build_nodes(MerkleNode *left, MerkleNode *right);
void free_merkle_tree(MerkleNode *node);
MerkleNode* create_leaf(const char *word);
void authentication_path(int word_index, MerkleTree* tree, unsigned char path[MAX_PATH_LENGTH][SHA256_DIGEST_LENGTH], int n_levels);
void create_proof(int word_index, char *word, MerkleTree* tree, Proof* proof);
bool verify_proof(char *text, Proof *proof);


#endif /* COMMON_H */