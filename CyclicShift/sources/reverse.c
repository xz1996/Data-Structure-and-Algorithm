#include "reverse.h"

void reverse(int array[], int left, int right)
{
   int l, r;
   for (l = left, r = right; l < r; l++, r--)
   {
        array[l] = array[l] ^ array[r];
        array[r] = array[l] ^ array[r];  // l ^ r ^ r = l ^ 0 = l.
        array[l] = array[l] ^ array[r];  // l ^ r ^ l = r ^ 0 = r;
   }
}