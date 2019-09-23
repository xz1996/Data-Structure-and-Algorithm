#include "strUtil.h"

int main()
{
    char* text = "hello word, world";
    char* pattern = "worl";
    printf("KMP algorithm, The matching index is %d.\n", kmp(text, pattern));

    char* palindrome = "asd543456";
    printf("The Longest Palindrome Substring length is %d\n\n", Manacher(palindrome));
}
