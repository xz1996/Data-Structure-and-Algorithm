# String Utility

## KMP Algorithm

- intro

    In computer science, the Knuth–Morris–Pratt string-searching algorithm (or KMP algorithm) searches for occurrences of a "word" W within a main "text string" S by employing the observation that when a mismatch occurs, the word itself embodies sufficient information to determine where the next match could begin, thus bypassing re-examination of previously matched characters.

- algorithm

  - How to calculate the next array value? The **pattern string** will stagger one position and compare itself.
    ![nextArray1](./doc/pictures/nextArray1.jpg)
    ![nextArray2](./doc/pictures/nextArray2.jpg)
    ![nextArray3](./doc/pictures/nextArray3.jpg)
    ![nextArray4](./doc/pictures/nextArray4.jpg)
    ![nextArray5](./doc/pictures/nextArray5.jpg)

- core code

    ```C
    int* getNextArray(const char* pattern)
    {
        int len = strlen(pattern);

        // Next array records the new beginning index of pattern string if the character is a mismatch between main string and pattern string.
        int* next = (int*)calloc(len, sizeof(int));
        next[0] = -1;

        int i = 0;
        int newStart = -1;       // This variable not only means the new beginning index of pattern string, but also is to traverse the other pattern string.

        // Note that at first, the pattern string will stagger one position and compare itself,
        // then it will get the result which is the intersection of longest prefix substring and longest suffix substring.
        while (i < len - 1)
        {
            if (newStart == -1 || pattern[i] == pattern[newStart])
            {
                next[++i] = ++newStart;
            }
            else
            {
                // If mismatch, then move to proper position according to the next array.
                newStart = next[newStart];
            }
        }
        return next;
    }

    int kmp(char* text, char* pattern)
    {
        int textLen = strlen(text);
        int patternLen = strlen(pattern);
        int textIndex = 0, patternIndex = 0;
        int* next = getNextArray(pattern);

        while (textIndex < textLen && patternIndex < patternLen)
        {
            // Note that "patternIndex = -1" means there is no any matching substring, so both index are all right shift and compare.
            if (patternIndex == -1 || text[textIndex] == pattern[patternIndex])
            {
                ++textIndex;
                ++patternIndex;
            }
            else
                patternIndex = next[patternIndex];
        }

        if (patternIndex == patternLen)
            return textIndex - patternIndex;
        else
            return -1;
    }
    ```

Time complexity: *O(m + n)*, m means raw text length, n means pattern text length.

More information, please refer to <https://www.zhihu.com/question/21923021/answer/281346746>

## Manacher Algorithm

core code

```C
int manacher(const char* rawStr)
{
    char* newStr = (char*)calloc(strlen(rawStr) * 2 + 3, sizeof(char));
    int* p = (int*)calloc(strlen(rawStr) * 2 + 3, sizeof(int)); // p[i]的值表示以i为中心的最长回文半径
    int len = initManacher(rawStr, newStr);  // 将字符串的长度转为奇数并以"$"开始，"\0"结尾
    int max_len = -1;  // 最长回文长度

    int center = 0;     // center的主要作用是作为回文的中心，这个轴中心是从左往右跳跃着变化的
    int radius = 0;     // 以center为中心的最大回文半径

    for (int i = 1; i < len; i++)
    {
        if (i < radius)     // 如果i在以center为中心，回文半径为radius的范围内，则可以利用回文的特性，快速求取p[i]的值。 p[2 * center - i]是i以center为中心的对称点的值
            p[i] = min(p[2 * center - i], radius - i);  // 计算出p[i]的最小可能值
        else                // 如果不在该半径内，则无法利用回文的特性，只能按普通的方法来一步一步求取p[i]的准确值，最开始的默认值为1
            p[i] = 1;

        // 因为上面计算所得的p[i]值为最小可能值，p[i]的准确值还需通过不断扩展来判断，这个while循环判断以i为中心的回文半径（i的回文半径外的第一个位置的值如果两边都相等，说明回文半径还可以加1）。注意，这里不需边界判断，因为左有'$',右有'\0'
        while (newStr[i - p[i]] == newStr[i + p[i]])
            p[i]++;

        // 我们每走一步 i，都要和 radius 比较，我们希望 radius 尽可能的远，这样才能更有机会执行 if (i < radius)这句代码，从而提高效率
        if (radius < i + p[i])
        {
            center = i;     // 更新center的位置
            radius = i + p[i];  // 更新为以新center为中心的最大回文半径
        }

        max_len = max(max_len, p[i] - 1);
    }

    free(newStr);
    free(p);
    return max_len;
}

```

Time complexity: *O(n)*

Refer to <https://ethsonliu.com/2018/04/manacher.html>

## Longest Common Substring

core code

```C

int lcs(const char* str1, const char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char dp[1000][1000];    // dp array for recording the all comparative information of these two strings.
    int rowIndex;
    int columnIndex;
    int maxLen = 0;         // record the maximum length of substring.
    int maxRow = 0;         // record the row num of the maxLen in dp array.

    // Init the first column with 0
    for (rowIndex = 0; rowIndex < len1 + 1; rowIndex++)
    {
        dp[rowIndex][0] = 0;
    }

    // Init the first row with 0
    for (columnIndex = 0; columnIndex < len2 + 1; columnIndex++)
    {
        dp[0][columnIndex] = 0;
    }

    for (rowIndex = 1; rowIndex < len1 + 1; rowIndex++)
    {
        for (columnIndex = 1; columnIndex < len2 + 1; columnIndex++)
        {
            if (str1[rowIndex - 1] == str2[columnIndex - 1])        // because the begin of rowIndex and columnIndex are 1, so they both need to minus 1.
            {
                dp[rowIndex][columnIndex] = dp[rowIndex - 1][columnIndex - 1] + 1;  // Its value depends on diagonal.
            }
            else
            {
                dp[rowIndex][columnIndex] = 0;
            }

            if (maxLen < dp[rowIndex][columnIndex])
            {
                maxLen = dp[rowIndex][columnIndex];
                maxRow = rowIndex;
            }
        }
    }

    // Print the Longest Common Substring
    // char s[100];
    // int i = 0;
    // for (int j = maxRow - maxLen; i < maxLen; i++, j++)
    // {
    //     s[i] = str1[j];
    // }
    // s[i] = '\0';
    // printf("The Longest Common Substring is %s\n", s);

    return maxLen;

}

```

Time complexity: *O(n²))*

Refer to <https://zhuanlan.zhihu.com/p/47597440>
