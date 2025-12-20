#include <stdio.h>
#include <stdlib.h>
int main() {
    int *arr = (int *)malloc(5 * sizeof(int)); // 动态分配5个整数的内存
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1; // 分配失败，退出程序
    }
    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1; // 初始化数组
    }
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]); // 输出数组元素
    }
    printf("\n");
    arr = (int *)realloc(arr, 10 * sizeof(int)); // 扩展数组大小到10个整数
    if (arr == NULL) {
        printf("Memory reallocation failed\n");
        return 1; // 扩展失败，退出程序
    }
    for (int i = 5; i < 10; i++) {
        arr[i] = i + 1; // 初始化新元素
    }
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]); // 输出扩展后的数组元素
    }
    printf("\n");
    free(arr); // 释放动态分配的内存
    return 0;
}