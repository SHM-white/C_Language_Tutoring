#include <stdio.h>
int func(int return_value, int id){
    printf("id = %d, return_value = %d\n", id, return_value);
    return return_value;
}
int main(){
    int a = func(1, 1) || func(1, 2);
    // 输出结果：id = 1, return_value = 1
    // 由于第一个函数的返回值是1，因此整个表达式的结果为1，因此第二个函数就不必计算了。
    int b = func(0, 3) && func(1, 4);
    // 输出结果：id = 3, return_value = 0
    // 由于第一个函数的返回值是0，因此整个表达式的结果为0，因此第二个函数就不必计算了。
    int c = func(1, 5) && func(0, 6);
    // 输出结果：id = 5, return_value = 1
    //          id = 6, return_value = 0
    // 由于第一个函数的返回值是1，整个表达式的结果仍可能为0，因此第二个函数的返回值也会被计算。
    return 0;
}
char toUpper(char in){
    if(in >= 'a' && in <= 'z'){
        return in - 33;
    }
    return in;
}