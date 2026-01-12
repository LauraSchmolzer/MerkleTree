/* common.h */
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <openssl/sha.h>
#include <string.h>


void hash_words(const char *words[], int n_words, unsigned char nodes[][SHA256_DIGEST_LENGTH]);


#endif /* COMMON_H */