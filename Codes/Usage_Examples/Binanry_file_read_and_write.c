#include <stdio.h>
typedef struct 
{
    int age;
    char name[20];
} Student;

int main(){
    Student student1 = {20, "aaa"};
    FILE *fileWrite = fopen("student.bin", "wb");
    //if null
    fwrite(&student1, sizeof(Student), 1, fileWrite);
    fclose(fileWrite);

    Student student2;
    FILE *fileRead = fopen("student.bin", "rb");
    fread(&student2, sizeof(Student), 1, fileRead);
    printf("Age:%d, Name:%s", student2.age, student2.name);
    fclose(fileRead);
}