#ifndef STR_UTIL
#define STR_UTIL

/* ------------- header reference --------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* ---------------- macro define ---------------- */


/* ------------- method declaration -------------- */

int* getNextArray(const char* pattern);

int kmp(char* text, char* pattern);

int manacher(const char* rawStr);

int lcs(const char* str1, const char* str2);

#endif
