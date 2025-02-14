1. strcat
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