#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//读取file1.txt中的内容，并将其内容写入file2.txt中
int main() {
    //打开需要读取的文件
    FILE *file1 = fopen("file1.txt", "r");
    if (file1 == NULL) {
        printf("Error: Could not open file1.txt for reading\n");
        return 1;
    }

    //读取文件内容
    char buffer[100];
    fgets(buffer, 100, file1);
    // fgets(buffer, 100, stdin); 可以从终端读取输入
    printf("Contents of file1.txt: %s", buffer);

    //关闭文件
    fclose(file1);

    //打开需要写入的文件
    FILE *file2 = fopen("file2.txt", "w");
    if (file2 == NULL) {
        printf("Error: Could not open file2.txt for writing\n");
        return 1;
    }

    //写入文件内容
    fwrite(buffer, strlen(buffer), 1, file2);

    //关闭文件
    fclose(file2);

    return 0;
}
//详见https://zh.cppreference.com/w/c/io/fopen
