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
    Employee emps[N];
    FILE *fp;
    int i;

    // 输入数据
    for (i = 0; i < N; i++) {
        printf("请输入第%d位职工的工号: ", i + 1);
        scanf("%d", &emps[i].no);
        printf("请输入第%d位职工的姓名: ", i + 1);
        scanf("%s", emps[i].name);
        printf("请输入第%d位职工的基本工资: ", i + 1);
        scanf("%d", &emps[i].salary[0]);
        printf("请输入第%d位职工的绩效工资: ", i + 1);
        scanf("%d", &emps[i].salary[1]);
        emps[i].total = emps[i].salary[0] + emps[i].salary[1];
    }

    // 写入二进制文件
    fp = fopen("emp.dat", "wb");
    if (fp == NULL) {
        perror("无法打开文件");
        exit(1);
    }
    fwrite(emps, sizeof(Employee), N, fp);
    fclose(fp);

    printf("数据已保存到emp.dat文件中。\n");
    return 0;
}
