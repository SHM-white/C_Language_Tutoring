# Class 1

```c
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{

}
```
```c
scanf("%d %d",&a,&b);
```
`%f`
```c
printf("%d %d\n",a,b);
```
`%.2f`

`int float double`

`i++`先利用再改变
`++i`先改变再利用
`=  ==  *  /  %  !=`
及`&&`  `||`或
多用括号表示先后性
用同一形式的数据类型运算，避免强制转换
```c
if()
{

}
else if()
{

}
else
{

}
```
```c
switch(a)
{
    case 1:
        ...;
        
    case 2:
        ...;
        break;
}
```
```c
while(/*condition*/)
{
    //Do something
    break;
}

do
{

} 
while(/*condition*/);
```
```c
for(i=0;i<n;i++)
{

}
```
`break`和`continue`

`int void float`
```c
int add(int a,int b)
{
    int c;
    c=a+b;
    return c;
}
```
a,b,c函数结束就被释放
```c
int main()
{
    int sum;
    sum=add(3,9);
}
```
尽量不使用同名变量，避免搞混
```c
#include <stdio.h>
int f(int n) 
{
    int fib = 0;
    if ((n == 1)||(n == 2)) 
    {
        fib = 1;
    } 
    else 
    {
        fib = f(n - 1) + f(n - 2);
    }
    return fib;
}
int main() {
    int n, fiber;
    scanf("%d",&n);
    fiber= f(n);
    printf("f(%d)=%d\n", n, fiber);
    return 0;
}
```
```c
int *p;
p=&i;
*p=i;
```
```c
#include <stdio.h>
void swap(int *p1, int *p2)    //p1=pointer_1  p2=pointer_2
{   
    int p;
    p = *p1;
    *p1 = *p2;
    *p2 = p;
}
int main() 
{
    int a, b;
    int *pointer_1, *pointer_2;
    scanf("%d %d", &a, &b);
    pointer_1 = &a;
    pointer_2 = &b;
    swap(pointer_1, pointer_2);
    printf("%d,%d", a, b);
    return 0;
}
```
```c
for (i = 0; i < 10; i++) 
{
    scanf("%d", &a[i]);
}
for (i = 0; i < 10; i++) 
{
    printf("%d", a[i]);
}
```
```c
#include <stdio.h>
//返回多个值        //意思应该是传递整个数组的值
double average(int *stu, int n) 
{
    float total = 0,ave;
    for (int i = 0; i < n; i++) 
    {
        total += stu[i]; total=total+stu[i];
    }
    ave=total/n;
    return ave;
}
int main() 
{
    int score[10], i;
    float ave;
    for (i = 0; i < 10; i++) {
        scanf("%d", &score[i]);
    }
    ave = average(score, 10);
    printf("Average is %.2f", ave);
    return 0;
}
```