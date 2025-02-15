# 递归函数

递归函数是指函数自己调用自己。递归函数的定义一般是：

```c
return_type function_name(parameter_list)
{
    // base case
    if (base_condition)
    {
        // return some value
    }
    // recursive case
    else
    {
        // recursive call
        return function_name(parameter_list);
    }
}
```

递归函数的特点是：

1. 递归函数的定义中包含两个部分：base case 和 recursive case。
2. base case 是指函数在某些特定条件下可以直接返回一个值，而不需要再调用函数自身。
3. recursive case 是指函数在某些特定条件下需要再次调用自身，直到 base case 条件满足。
4. 递归函数的调用方式和其他函数一样，通过参数传递。

递归函数的优点是：

1. 递归函数可以解决一些复杂的问题，比如计算阶乘、计算阶乘的阶乘等。
2. 递归函数的实现方式简洁，容易理解。
3. 递归函数的效率高，可以处理大量的数据。
4. 递归函数可以用迭代函数来实现，迭代函数的效率也高于递归函数。 

递归函数的缺点是：

1. 递归函数的调用栈的深度受限于系统的限制，可能会导致栈溢出。
2. 递归函数的效率低，可能会导致栈溢出。
3. 递归函数的实现方式不容易调试，容易出现错误。
4. 递归函数的实现方式不容易理解，容易出错。 

递归函数的使用场景：

1. 计算阶乘、计算阶乘的阶乘等。
2. 树形结构的遍历。
3. 二叉树的遍历。
4. 图的遍历。   
5. 排序算法（快速排序）。       

## 经典递归函数

### 计算阶乘

```c
int factorial(int n)
{
    if (n <= 1){
        return 1;
    }
    return n * (n - 1);
}
```

### 计算斐波那契数列

```c
int fibonacci(int n)
{
    if (n <= 1){
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

### 汉诺塔问题

```c
int hanoi(int n, char from, char to, char aux)
{
    if (n == 1) {
        printf("%d -> %d\n", from, to);
        return 1;
    }
    int count = hanoi(n - 1, from, aux, to);
    printf("%d -> %d\n", from, to);
    count += hanoi(n - 1, aux, to, from);
    return count;
}

//或者是我写的奇怪实现
int hanoi(int from, int to, int order)
{
    if(order == 1){
        return 1;
    }
    int count = 0;
    unsigned short halls = 0b00000000;
    halls |= (0b00000001 << from);
    halls |= (0b00000001 << to);
    halls ^= 0b00001110;
    for (int i = 1; i <= 3; i++){
        if(halls & 0b00000001 << i){
            count += hanoi(from, i, order - 1);
            count += 1;
            count += hanoi(i, to, order - 1);
            break;
        }
    }
    return count;
}
```


