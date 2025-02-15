## 1. strcat

## strcat, strcat_s

| 在标头 `<string.h>`定义                                                      |     |                    |
| ------------------------------------------------------------------------------ | --- | ------------------ |
| char *strcat(char *dest, const char *src);                                     | (1) | **(C99 前)** |
| char *strcat(char *restrict dest, const char *restrict src);                   | (1) | **(C99 起)** |
| errno_t strcat_s(char*restrict dest, rsize_t destsz,const char *restrict src); | (2) | **(C11 起)** |

**1)** 将 `src` 所指向的空终止字节字符串的副本追加到 `dest` 所指向的空终止字节字符串的末尾。字符 `src[0]` 替换 `dest` 末尾的空终止符。产生的字节字符串是空终止的。

 若目标数组对于 `src` 和 `dest` 的内容以及空终止符不够大，则行为未定义。若字符串重叠，则行为未定义。若 `dest` 或 `src` 不是指向空终止字节字符串的指针，则行为未定义。

**2)** 同 **(1)**，但它可用未指定值破坏目标数组的剩余部分（从最后写入字符到 `destsz`），以及在运行时检测下列错误，并调用当前安装的[约束处理函数]()： * `src` 或 `dest` 为空指针

* `destsz` 为零或大于 **RSIZE_MAX**
* `dest` 的前 `destsz` 个字节中无空终止符
* 会出现截断（`dest` 末尾的可用空间不能适应 `src` 的每个字符，包括空终止符）
* 源与目标字符串间会出现重叠

 若 `dest` 所指向的字符数组大小 < [strlen]()(**dest**)**+**[strlen]()(**src**)**+**1 <= `destsz` 则行为未定义；换言之，`destsz` 的错误值不暴露行将发生的缓冲区溢出。 同所有边界检查函数，`strcat_s`，仅若实现定义 **__STDC_LIB_EXT1__** 且用户在包含 [string.h]() 前定义 **__STDC_WANT_LIB_EXT1__** 为整数常量 1 才保证可用。

```c
char *strcat(char *str1, char *str2){
    int index1 = 0;
    int index2 = 0;
    while(str1[index1] != '\0'){
        index1++;
    }
    while(str2[index2] != '\0'){
        str1[index1 + index2] = str2[index2];
        index2++;
    }
    str1[index1 + index2] = '\0';
    return str1;
}
```

## 2. strcmp

| 在标头 `<string.h>`定义                                                                |
| ---------------------------------------------------------------------------------------- |
| **int** strcmp **(const char** *lhs **, const char** *rhs **)**; |

以字典序比较两个空终止字节字符串。

结果的符号是被比较的字符串中首对不同字符（都转译成 **unsigned** **char**）的值间的差的符号。

若 **lhs** 或 **rhs** 不是指向空终止字节字符串的指针，则行为未定义。

```c
int strcmp(char *str1, char *str2){
    int index = 0;
    while(str1[index] != '\0' && str2[index] != '\0'){
        if(str1[index] != str2[index]){
            return str1[index] - str2[index];
        }
        index++;
    }
    if(str1[index] != '\0'){
        return 1;
    }
    if(str2[index] != '\0'){
        return -1;
    }
    return 0;
}
```

## 3. strlen

| 在标头 `<string.h>`定义                          |     |                    |
| -------------------------------------------------- | --- | ------------------ |
| size_t strlen(const char *str);                    | (1) |                    |
| size_t strnlen_s( const char *str, size_t *strsz); | (2) | **(C11 起)** |

**1)** 返回给定空终止字符串的长度，即首元素为 **str** 所指的字符数组中，直至且不包含首个空字符的字符数。

 若 **str** 不是指向空终止字节字符串的指针则行为未定义。

**2)** 同 **(1)**，但若 **str** 为空指针则返回零，而若在 **str** 的首 **strsz** 个字节找不到空字符则返回 **strsz**。

 若 **str** 不是指向空终结的字节字符串且 **strsz** 大于该字符数组的大小，则行为未定义。 同所有边界检查函数，`strnlen_s`，仅若实现定义 **__STDC_LIB_EXT1__** 且用户在包含 [string.h]() 前定义 **__STDC_WANT_LIB_EXT1__** 为整数常量 1 才保证可用。

```c
int strlen(char *str){
    int index = 0;
    while(str[index] != '\0'){
        index++;
    }
    return index;
}
```

## 4. strcpy

| 在标头 `<string.h>`定义                                                      |     |                    |
| ------------------------------------------------------------------------------ | --- | ------------------ |
| char *strcpy(char *dest, const char *src);                                     | (1) | **(C99 前)** |
| char *strcpy(char *restrict dest, const char *restrict src);                   | (1) | **(C99 起)** |
| errno_t strcpy_s(char*restrict dest, rsize_t destsz,const char *restrict src); | (2) | **(C11 起)** |

**1)** 复制 `src` 所指向的空终止字节字符串，包含空终止符，到首元素为 `dest` 所指的字符数组。

 若 `dest` 数组长度不足则行为未定义。若字符串重叠则行为未定义。若 `dest` 不是指向字符数组的指针或 `src` 不是指向空终止字节字符串的指针则行为未定义。

**2)** 同 **(1)**，但它可能以未指定值破坏目标数组的剩余部分，而且会会在运行时检测下列错误，并调用当前安装的[约束处理函数]()： * `src` 或 `dest` 为空指针

* `destsz` 为零或大于 **RSIZE_MAX**
* `destsz` 小于或等于 **strnlen_s**(**src, destsz**)；换言之，会发生截断
* 源与目标字符串间会发生重叠

 若 `dest` 所指的字符数组大小 <= **strnlen_s**(**src, destsz**) < `destsz` 则行为未定义；换言之， `destsz` 的错误值不暴露行将发生的缓冲区溢出。 同所有边界检查函数，`strcpy_s`，仅若实现定义 **__STDC_LIB_EXT1__** 且用户在包含 [string.h]() 前定义 **__STDC_WANT_LIB_EXT1__** 为整数常量 1 才保证可用。

```c
char *strcpy(char *dest, char *src){
    int index = 0;
    while(src[index] != '\0'){
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';
    return dest;
}
```

## 5. toupper & tolower

```c
char toUpper(char in){
    if(in >= 'a' && in <= 'z'){
        return 'A' + (in - 'a');
    }
    return in;
}
char toLower(char in){
    if(in >= 'A' && in <= 'Z'){
        return 'a' + (in - 'A');
    }
    return in;
}
```

## 6. search

` int search(char *str, char *target); `

```c
int search(char *str, char *target){
    int index = 0;
    int target_len = strlen(target);
    int i = 1;
    while(str[index] != '\0'){
        if(str[index] == target[0]){
            i = 1;
            while(i < target_len && str[index + i] == target[i]){
                i++;
            }
            if(i == target_len){
                return index;
            }
        }
        index += i;
        i = 1;
    }
    return -1;
}
```