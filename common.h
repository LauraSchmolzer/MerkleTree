/* common.h */
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h> 
#include <openssl/sha.h>
#include <string.h>


void hash_words(const char *words[], unsigned char nodes[][SHA256_DIGEST_LENGTH], int n_words);
int slice_text_into_words(const char *text, char *words[], int n_words);

#endif /* COMMON_H */