#include "strUtil.h"

int main()
{
    char* text = "hello word, world";
    char* pattern = "worl";
    printf("The index is %d.\n", kmp(text, pattern));
}