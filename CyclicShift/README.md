# Cyclic shift to the array

## Algorithm

### Reverse

code

```C
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
```

As shown above, the ```xor``` method can efficiently implement the exchange of two numbers, please keep some in mind:

* any num xor *0* is itself.

* any num xor *1* is its opposite.

### Left cyclic shift

for example, left cyclic shift n position.

1. reverse the ```first n``` elements.

2. reverse the rest of elements.

3. reverse the entire array.

the order also can be *step2 -> step1 -> step3*.

code

```C
reverse(array, 0, left_shift_num - 1);
reverse(array, left_shift_num, array_size - 1);
reverse(array, 0, array_size - 1);
```

### Right cyclic shift

for instance, right cyclic shift n position.

1. reverse the ```last n``` elements.

2. reverse the remaining elements.

3. reverse the whole array.

apparently, the order can be *step2 -> step1 -> step3* as well.

code

```C
reverse(array, 0, array_size - right_shift_num - 1);
reverse(array, array_size - right_shift_num, array_size - 1);
reverse(array, 0, array_size -1);
```
