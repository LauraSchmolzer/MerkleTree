#include "common.h"

int main() {
    const char *text = "Hello world this is a beautiful string";

    unsigned char root_hash[SHA256_DIGEST_LENGTH];
    MerkleTree tree;
    // Build the Merkle tree and get the root node
    build_merkle_tree(text, root_hash, &tree);


    // Print the root hash in hex
    printf("Merkle root: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", root_hash[i]);
    }
    printf("\n");

    Proof proof;
    create_proof(2, "this", &tree, &proof);
    printf("Proof successfully created.\n");

    // Print the proof's word and index
    printf("Proof word: %s\n", proof.word);
    printf("Proof index: %d\n", proof.word_index);
    printf("\n");

    bool verified = verify_proof("Hello", &proof);
    printf("Verification process done.\n");

    if (verified) {
        printf("Verification successful.\n");
    } else {
        printf("Verification failed.\n");
    }

    free_merkle_tree(tree.root);
    return 0;
}