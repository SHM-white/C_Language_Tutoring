#include <stdio.h>
#include <stdlib.h>

#define N 5

typedef struct {
    int no;
    char name[20];
    int salary[2];
    int total;
} Employee;

int main() {
    // Employee emps[N];
    // // 输入数据
    // for (int i = 0; i < N; i++) {
    //     printf("请输入第%d位职工的工号: ", i + 1);
    //     scanf("%d", &emps[i].no);
    //     printf("请输入第%d位职工的姓名: ", i + 1);
    //     scanf("%s", emps[i].name);
    //     printf("请输入第%d位职工的基本工资: ", i + 1);
    //     scanf("%d", &emps[i].salary[0]);
    //     printf("请输入第%d位职工的绩效工资: ", i + 1);
    //     scanf("%d", &emps[i].salary[1]);
    //     emps[i].total = emps[i].salary[0] + emps[i].salary[1];
    // }

    // // 写入二进制文件
    // FILE *fp = fopen("emp.dat", "wb");
    // if (fp == NULL) {
    //     perror("无法打开文件");
    //     exit(1);
    // }
    // fwrite(emps, sizeof(Employee), N, fp);
    // fclose(fp);
    // printf("数据已保存到emp.dat文件中。\n");

    Employee emp2[N];

    FILE *fr = fopen("emp.dat", "rb");
    if(fr == NULL){
        perror("error");
        exit(1);
    }
    fread(&emp2, sizeof(Employee), N, fr);

    for (size_t i = 0; i < N; i++)
    {
        printf("id:%d\nname:%s\nsa0:%d\nsa1:%d\ntotal:%d\n", emp2[i].no, emp2[i].name, emp2[i].salary[0], emp2[i].salary[1], emp2[i].total);
    }
    

    return 0;
}
