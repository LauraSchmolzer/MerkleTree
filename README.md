# Merkle Tree Maker
Create a Merkle Tree structure from a small text, using words as leaf nodes. The tree can later be used for selective disclosure, allowing verification of individual words without revealing the entire text.

## Features
- Build a Merkle Tree from a string of text of a maximum of 100 words.
- Use *SHA-256* hashes for secure leaf and node hashing.
- Full tree structure is kept in memory for generating *athentication paths*.
- Supports oddn number of words by duplicating last leaf automatically.

## Libraries used
- OpenSSL for SHA-256 hashing

## Compilation
``` bash
    make clean
    make
    ./merkle_tree
```
