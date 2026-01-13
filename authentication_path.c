#include "common.h"

void authentication_path(int word_index, MerkleTree* tree, unsigned char path[MAX_PATH_LENGTH][SHA256_DIGEST_LENGTH], int n_levels) {

    // Find the leaf of the word at gives index
    MerkleNode* current = tree->leaves[word_index];

    for (int i = 0; i < n_levels; i++) {

        MerkleNode* parent = current->parent;
        if (!parent) break; // reached root

        MerkleNode* sibling = (parent->left == current) ? parent->right : parent->left; // find the sibling

        memcpy(path[i], sibling->hash, SHA256_DIGEST_LENGTH); // store sibling hash
        current = parent; // move up to parent
    }
}

void create_proof(int word_index, char *word, MerkleTree* tree, Proof* proof) {
    int n_levels = (int)ceil(log2(tree->n_leaves)); // total levels in the tree

   if (word_index < 0 || word_index >= tree->n_leaves) {
        fprintf(stderr, "Error: word index out of range\n");
        exit(EXIT_FAILURE);
    }   

    strncpy(proof->word, word, MAX_WORD_LEN); // copy the word
    proof->word[MAX_WORD_LEN - 1] = '\0';
    proof->word_index = word_index;
    memcpy(proof->root_hash, tree->root->hash, SHA256_DIGEST_LENGTH); // copy root hash
    if (n_levels > MAX_PATH_LENGTH) {
    fprintf(stderr, "Error: tree too deep for authentication path!\n");
    exit(EXIT_FAILURE);
    }
    proof->path_length = n_levels;
    authentication_path(word_index, tree, proof->authentication_path, n_levels); // get authentication path
}
