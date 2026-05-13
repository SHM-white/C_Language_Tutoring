# C++知识汇总

## 一、C++基础

### 1. 输入输出
### 2. 标识符类型
### 3. 引用用作函数参数
### 4. 内存动态的分配与释放

## 二、文件操作

### 1. 文件命名与文件流
### 2. 文件打开读写、关闭文件

## 三、类

### 1. 类的函数成员
### 2. 构造函数，析构函数
### 3. 静态成员（static）
### 4. 友元函数
### 5. 运算符重载
### 6. 继承，多态，虚函数，抽象类

## 四、模板

### 1. 函数模板，类模板

---

### 1. 输入输出
#### 简单的输入输出
```cpp
    cin >> width;
    cout << "矩形宽度为" << width << endl;
```
格式化输出头文件[`#include <iomanip>`](https://cppreference.cn/w/cpp/header/iomanip)  
主要操作符有：[`setw`](https://cppreference.cn/w/cpp/io/manip/setw),[`setprecision`](https://cppreference.cn/w/cpp/io/manip/setprecision)和[`setiosflags`](https://cppreference.cn/w/cpp/io/manip/setiosflags)。

`setw` 操作符为每个输出数据项指定宽度，例如：
```cpp
value = 68;
cout << setw(5) << value;
```
`setw` 括号里的数值指定了将要输出的数据域宽，即输出数据在屏幕上所占的空间。上例指定了 `value` 的域宽是 5，由于它的值是 68，占两个字符的宽度，因此将在 68 前面填充 3 个空格，请看如下语句：
```cpp
value = 68;
cout << "(" << value << ")";    // 通过括号测试输出数据所占的宽度
```
输出如下：
```plaintext
(68)
```
如果在输出中加一个 `setw(5)`：
```cpp
value = 68;
cout << "(" << setw(5) << value << ")";
```
输出如下：
```
(   68)
```
  可以看出，68 占了域宽的最后两个位置，用 3 个空格填充 68 前面的 3 个位置。由于数据在右边，空格在前面，所以称这种对齐方式为右对齐，`setw`仅对与其相邻的一个输出项有效。
  
  在 `cout` 输出中，可以采用 `setprecision` 操作符指定浮点数的输出精度，即输出数的有效位数。
 采用 `setprecision` 指定浮点数的输出精度。
```cpp
#include <iostream>
using namespace std;
#include <iomanip>
int main()
{
    float quotient, number1 = 132.364f, number2 = 26.91f;

    quotient = number1 / number2;
    cout << quotient << endl;
    cout << setprecision(5) << quotient << endl;
    cout << setprecision(4) << quotient << endl;
    cout << setprecision(3) << quotient << endl;
    cout << setprecision(2) << quotient << endl;
    cout << setprecision(1) << quotient << endl;
    return 0;
}
```
【程序运行结果】
```plaintext
4.91877
4.9188
4.919
4.92
4.9
5
```
精度的设置在它被重新设置之前一直有效。

另外一个流操作符是 `setiosflags`，用来控制 `cout` 输出定点形式的浮点数。将上例中的格式控制修改如下：
```cpp
cout << "输入第 3 天的销售量：";
cin >> day3;
total = day1 + day2 + day3;
cout << "\n销售数据\n";
cout << setprecision(2) << setiosflags(ios::fixed);
```
那么程序的输出结果，无论是否有小数，都将显示 2 位小数。
> $\red{注意}$:
> `setiosflags` 括号里的内容称为格式状态标志，`ios` 有许多状态标志。`setiosflags` 可用于许多方面的格式化输出，当它的状态标志设定为 `ios::fixed` 时，操作符 `setprecision` 括号内的数字指的是十进制小数的位数，而不再是整个数的位数。  
> 在上例的输出中，假设程序输出的销售总额是 5422.30。在一般情况下，`cout` 不会输出尾部的零，只有通过 `setiosflags` 和 `setprecision` 指定才会这样输出。在有些情况下，`cout` 也不会输出十进制小数点。例如，下面的语句输出 12，而不是 12.00：
```cpp
float number = 12.0f;
cout << setprecision(4) << number;
```
当需要同时指定多个状态标志时，只需在操作符 `setiosflags` 括号之内使用 `|` 连接各个状态标志位即可，例如：
```cpp
float number = 12.0f;
cout << setiosflags(ios::showpoint | ios::fixed)
     << setprecision(2) << number;
```
将输出 `12.00` 小数形式。

#### 采用函数成员实现格式化输出
格式化输出的第二种方法是使用 cout 对象的函数。输出项的域宽、精度和状态标志都可以由 cout 的函数成员指定。例如，下面的语句指定了输出项的域宽：
```cpp
cout.width(5);
```
`cout` 对象调用函数成员 `width`，设定输出项的域宽为 5，这和在变量前使用 `setw(5)` 是等同的。
`cout` 的另外一个函数成员是 `precision`，用来设定浮点数的精度。例如，下面的语句将精度设定为 2：
```cpp
cout.precision(2);
```
上述设定将会保持到重新设定或程序的结束。
cout 的函数成员 setf 用来设置状态标志，它与操作符 setiosflags 的功能相同，例如：
cout.setf(ios::fixed);
也可以在函数成员 setf 中采用 | 连接多个状态标志，例如：
cout.setf(ios::fixed | ios::showpoint | ios::left);
与 setf 功能相反的函数成员是 unsetf，用于清除已经设置的状态标志。例如，下列语句关闭状态标志 ios::fixed 和 ios::left：
cout.unsetf(ios::fixed | ios::left);

格式化输入
采用 cin 对象输入数据是最为频繁的一个方法，它的功能很多，就像 C 中常用的 scanf 函数一样，但它比 scanf 更为方便。
 指定输入域宽
cin 与 cout 的功能虽然不同，但它们有许多类似点。例如，都可以指定域宽。cin 的输入域宽可以使用操作符 setw 指定，也可使用 cin.width 函数成员指定。cin 在读入一个字符串时，不能根据字符数组的长度自动读入字符，如果用户输入过多的字符，超过了字符数组的长度，cin 会将多余字符存储到该数组的后面，这就有可能覆盖其他变量。如果为其指定了输入域宽，就可解决这一问题。
下面定义了一个长度为 10 的字符数组，采用 setw 规定 cin 读入的字符个数不能超过数组的有效范围：
char word[10];
cin >> setw(10) >> word;
同样也可以使用函数成员 width 指定输入域宽：
cin.width(10);
cin >> word;
在上述两种情况下，指定的输入域宽都是 10，cin 将最多读取 9 个字符，因为数组最后一个位置应存储字符 '\0'。
【例 】 使用操作符 setw 或函数成员 width 控制字符串输入。
#include <iostream>
using namespace std;
#include <iomanip>
int main()
{
    char word[5];
    cout << "请输入一个单词：";
    cin >> setw(5) >> word;
    cout << "你输入的是：" << word << endl;
    return 0;
}
【程序运行结果】
plaintext
请输入一个单词：Chinese [Enter]
你输入的是：Chin
【程序解析】 运行该程序时，最多只能读取 4 个有效的字符。可以将上例中：
cin >> setw(5) >> word;
修改成如下形式，效果等同：
cin.width(5);
cin >> word;
在上面程序中，cin 只读取 4 个字符到字符数组。如果没有指定输入域宽，cin 会读取整个字符串 "Chinese"，这将产生溢出。
关于 cin 的输入域宽，还要注意以下 3 点：(1) 域宽只对与其相邻的下一个输入有效。(2) 当 cin 遇到空字符时，它将停止读入。空字符包括回车、空格和 Tab 键。(3) 当 cin 读取一定的字符以后，多余的字符将留在缓冲区中。例如，在上例的输入中，由于只读取了 4 个字符，那么留在缓冲区中的字符是 "ese"。

读取一行
cin 提供的函数成员 getline，一次能够读取一行，例如：
cin.getline(sentence, 20);
函数的第一个参数是数组名，第二个参数是待读取的字符个数（含空字符）。上述语句将最多读取 19 个字符，最后一个位置用于存储 '\0'。

读取字符时容易出错的地方
如果将 cin>> 和 cin.get 混合使用，往往会出现难以发现的问题，例如：
cout << "请输入一个整数：";
cin >> number;
cout << "请输入一个字符：";
cin.get(ch);
假设要给 number 变量读入 100，给 ch 变量读入 H。首先输入 100，并按 Enter 键，结果发现 cin.get 语句被跳过了，根本不给输入字符 H 的机会，这是什么原因呢？
这是因为 cin>> 和 cin.get 都是从键盘缓冲区（实际上就是一块内存空间）中读入用户的按键。当用户输入 100 并按 Enter 键，此时 Enter 键引起的换行符 '\n' 被存储在键盘缓冲区中。当 cin>> 读入 100 后就停止了，换行符则留在键盘缓冲区中，这意味着 cin.get 读入的字符将是 '\n'，所以就没有输入字符 H 的机会。如何解决这个问题呢？答案是采用 cin 的函数成员 ignore，该函数能够使 cin 对象跳过键盘缓冲区的字符，它的一般形式如下：
cin.ignore(n, c);
ignore 括号中的参数都是可选的，其中 n 是一个整数，c 是一个字符。含义是 cin 跳越 n 个字符，或者是直到遇到字符 c 为止。例如，下面的语句使 cin 跳越 20 个字符，或者是遇到一个换行符，哪一种情况先出现都可以，都将停止 cin 的跳越：
cin.ignore(20, '\n');
如果 cin.ignore 没有参数，表示跳过键盘缓冲区中的第一个字符，例如：
cin.ignore();
解决 cin>> 和 cin.get 混合出现问题的方法是：在 cin>> 语句之后加一条 cin.ignore 语句：
cout << "请输入一个整数：";
cin >> number;
cin.ignore();                // 忽略 number 后面的一个字符
cout << "请输入一个字符：";
cin.get(ch);

### 引用用作函数参数
按值传递是 C 语言中常用的参数传递方法，C++ 除了支持按值传递以外，还支持按引用传递。通过引用作参数，可以修改调用函数中的变量，它比传递指针方便得多。
下面首先举一个通俗的例子说明什么是引用。假设你的大名叫张三，小名（即别名）叫李四，那么张三和李四都是你的名字，我们可以说张三和李四都是你的引用。张三的任何变化（如长高 2cm）在李四身上都有反映。C++ 的引用变量，简称为引用，它是另外一个变量的别名，对引用变量的任何修改都将影响该引用所代表的变量。通过引用作函数参数，一个函数就可改变另外一个函数中的变量。
定义引用与定义一般变量类似，只需在变量名前加一个符号 &。例如，下面的函数将参数 refVar 定义为引用：
void doubleNum(int & refVar)
{
    refVar *= 2;
}
在定义函数原型时，如果参数是引用，只要在类型之后加一个符号 & 即可。例如，下面是函数 doubleNum 的原型：
void doubleNum(int&);

#### 类型
对象、引用、函数（包括函数模板特化）和表达式都具有一个称为**类型**的属性，该属性既限制了这些实体允许的操作，又为原本通用的位序列提供了语义含义。

类型分类
C++ 类型系统包含以下类型

基本类型（另请参阅 std::is_fundamental）
类型 void（另请参阅 std::is_void）；
类型 std::nullptr_t（另请参阅 std::is_null_pointer）；
(C++11 起)
算术类型（另请参阅 std::is_arithmetic）
整型类型（包括cv 限定版本，另请参阅 std::is_integral，整型类型的同义词是整数类型）
类型 bool；
字符类型
窄字符类型
普通字符类型：char、signed char、unsigned char[1]
类型 char8_t
(C++20 起)
宽字符类型：char16_t、char32_t，(C++11 起)wchar_t；
有符号整型类型
标准有符号整型类型：signed char、short、int、long、long long；
扩展有符号整型类型（由实现定义）；
(C++11 起)
无符号整型类型
标准无符号整型类型：unsigned char、unsigned short、unsigned、unsigned long、unsigned long long；
扩展无符号整型类型（每个都对应一个扩展有符号整型类型，反之亦然）；
(C++11 起)
浮点类型（另请参阅 std::is_floating_point）
标准浮点类型：float、double、long double 及其cv 限定版本；
扩展浮点类型（包括cv 限定版本）
定宽浮点类型;
其他实现定义的扩展浮点类型；
(C++23 起)
复合类型（另请参阅 std::is_compound）
引用类型（另请参阅 std::is_reference）
左值引用类型（另请参阅 std::is_lvalue_reference）
到对象类型的左值引用；
到函数类型的左值引用；
右值引用类型（另请参阅 std::is_rvalue_reference）
到对象类型的右值引用；
到函数类型的右值引用；
(C++11 起)
指针类型（另请参阅 std::is_pointer）
对象指针类型;
函数指针类型;
成员指针类型（另请参阅 std::is_member_pointer）
数据成员指针类型（另请参阅 std::is_member_object_pointer）；
成员函数指针类型（另请参阅 std::is_member_function_pointer）；
数组类型（另请参阅 std::is_array）；
函数类型（另请参阅 std::is_function）；
枚举类型（另请参阅 std::is_enum）；
无作用域枚举类型;
有作用域枚举类型（另请参阅 std::is_scoped_enum）；
(C++11 起)
类类型:
非联合类型（另请参阅 std::is_class）；
联合类型（另请参阅 std::is_union）。
↑ signed char 和 unsigned char 是窄字符类型，但它们不是字符类型。换句话说，窄字符类型的集合不是字符类型集合的子集。
对于除引用和函数之外的每个非 cv 限定类型，类型系统支持该类型的三个额外的cv 限定版本（const、volatile 和 const volatile）。

#### 动态内存管理
##### new 表达式
 C++ C++ 语言 表达式 
创建并初始化具有动态存储期的对象，即生命期不一定受其创建范围限制的对象。

语法
::(可选) new (类型 ﻿) new-initializer ﻿(可选)	(1)	
::(可选) new 类型 new-initializer ﻿(可选)	(2)	
::(可选) new (placement-args ﻿) (类型 ﻿) new-initializer ﻿(可选)	(3)	
::(可选) new (placement-args ﻿) 类型 new-initializer ﻿(可选)	(4)	
1,2) 尝试创建由类型标识 类型 指示的类型的对象，它可以是数组类型，并且可以包含占位符类型说明符(C++11 起)，或者包含其参数将通过类模板参数推导进行推导的类模板名称(C++17 起)。
3,4) 同 (1,2)，但为分配函数提供附加参数，参见定位 new。
解释
类型	-	目标类型标识符
new-initializer	-	一个用括号括起来的表达式列表或用花括号括起来的初始化器列表(C++11 起)
placement-args	-	额外的定位参数

new 表达式尝试分配存储，然后尝试在分配的存储中构造并初始化一个无名对象或一个无名对象数组。new 表达式返回一个指向已构造对象的纯右值指针，如果构造的是对象数组，则返回指向数组初始元素的指针。

如果 类型 包含括号，则需要使用语法 (1) 或 (3)。

new int(*[10])();    // error: parsed as (new int) (*[10]) ()
new (int (*[10])()); // okay: allocates an array of 10 pointers to functions
此外，类型 会被贪婪地解析：它将包含所有可以作为声明符一部分的标记。

new int + 1; // okay: parsed as (new int) + 1, increments a pointer returned by new int
new int * 1; // error: parsed as (new int*) (1)
如果满足以下条件，则 new-initializer 不可省略：

类型 是未知边界的数组，
类型 中使用了占位符，即 auto 或 decltype(auto)(C++14 起)，可能与类型约束结合使用(C++20 起)，
(C++11 起)
类型 中使用了需要推导其参数的类模板。
(C++17 起)
double* p = new double[]{1, 2, 3}; // creates an array of type double[3]
auto p = new auto('c');            // creates a single object of type char. p is a char*
 
auto q = new std::integral auto(1);         // OK: q is an int*
auto q = new std::floating_point auto(true) // ERROR: type constraint not satisfied
 
auto r = new std::pair(1, true); // OK: r is a std::pair<int, bool>*
auto r = new std::vector;        // ERROR: element type can't be deduced
动态数组
如果 类型 是数组类型，则除第一个维度之外的所有维度都必须指定为正的整型常量表达式(C++14 前)转换为 std::size_t 类型的常量表达式(C++14 起)，但（仅在使用非括号语法 (2) 和 (4) 时）第一个维度可以是整型、枚举类型或具有单个非显式转换函数到整型或枚举类型的类类型表达式(C++14 前)任何可转换为 std::size_t 的表达式(C++14 起)。这是直接创建在运行时定义大小的数组的唯一方法，此类数组通常被称为动态数组。

int n = 42;
double a[n][5]; // error
auto p1 = new  double[n][5];  // OK
auto p2 = new  double[5][n];  // error: only the first dimension may be non-constant
auto p3 = new (double[n][5]); // error: syntax (1) cannot be used for dynamic arrays
如果第一个维度中的值（如果需要，转换为整型或枚举类型）为负，则行为未定义。

(C++11 前)
在以下情况下，指定第一个维度的表达式值无效：

表达式是非类类型，其在转换为 std::size_t 之前的值为负；
表达式是类类型，其在用户定义的转换函数之后和第二次标准转换之前的值为负；
表达式的值大于某个实现定义的最大值；
值小于花括号初始化器列表中提供的数组元素数量（包括字符串字面量末尾的 '\0'）。
如果第一个维度中的值由于上述任何原因无效，则：

如果在转换为 std::size_t 后，第一个维度是核心常量表达式并且它可能被求值，则程序格式错误，
否则，如果将要调用的分配函数是非抛出的（包括未声明 noexcept 的 std::nothrow 重载），则 new 表达式返回所需结果类型的空指针，
否则，new 表达式不调用分配函数，而是抛出类型为std::bad_array_new_length 的处理程序能够匹配的异常。
(C++11 起)
第一个维度为零是允许的，并且会调用分配函数。

如果 new-initializer 是花括号初始化器列表，并且第一个维度可能被求值且不是核心常量表达式，则会检查从空初始化器列表复制初始化数组假设元素的语义约束。

(C++11 起)
分配
new 表达式通过调用适当的分配函数来分配存储。如果 类型 是非数组类型，则函数名为 operator new。如果 类型 是数组类型，则函数名为 operator new[]。

如分配函数中所述，C++ 程序可以为这些函数提供全局和类特定的替换。如果 new 表达式以可选的 :: 运算符开头，如 ::new T 或 ::new T[n]，则类特定的替换将被忽略（该函数在全局作用域中查找）。否则，如果 T 是类类型，则查找从 T 的类作用域开始。

调用分配函数时，new 表达式将请求的字节数作为第一个类型为 std::size_t 的参数传递，对于非数组 T，这恰好是 sizeof(T)。


数组分配可能提供未指定的开销，此开销在每次 new 调用之间可能有所不同，除非所选分配函数是标准非分配形式。new 表达式返回的指针将与分配函数返回的指针偏移该值。许多实现使用数组开销来存储数组中的对象数量，delete[] 表达式使用此数量来调用正确数量的析构函数。此外，如果 new 表达式用于分配 char、unsigned char 或 std::byte(C++17 起) 的数组，如果需要，它可能会从分配函数请求额外的内存，以确保所有类型不大于请求数组大小的对象都能正确对齐（如果稍后将一个对象放入已分配的数组中）。

new 表达式可以省略或合并通过可替换分配函数进行的分配。在省略的情况下，存储可能由编译器提供，而无需调用分配函数（这也允许优化掉未使用的 new 表达式）。在合并的情况下，new 表达式 E1 的分配可以扩展以提供额外的存储给另一个 new 表达式 E2，如果满足以下所有条件：

1) E1 分配的对象的生命期严格包含 E2 分配的对象的生命期。
2) E1 和 E2 将调用相同的可替换全局分配函数。
3) 对于抛出异常的分配函数，E1 和 E2 中的异常将在同一个处理程序中首次捕获。
请注意，此优化仅在使用 new 表达式时才允许，而不是通过任何其他方法调用可替换分配函数：delete[] new int[10]; 可以被优化掉，但 operator delete(operator new(10)); 则不能。

(C++14 起)
在求值常量表达式期间，对分配函数的调用总是被省略。只有原本会导致调用可替换全局分配函数的 new 表达式才能在常量表达式中求值。

(C++20 起)

定位 new

如果提供了 placement-args，它们将作为附加参数传递给分配函数。此类分配函数被称为“定位 new”，得名于标准分配函数 void* operator new(std::size_t, void*)，它只是原封不动地返回其第二个参数。这用于在已分配的存储中构造对象。

// within any block scope...
{
    // Statically allocate the storage with automatic storage duration
    // which is large enough for any object of type “T”.
    alignas(T) unsigned char buf[sizeof(T)];
 
    T* tptr = new(buf) T; // Construct a “T” object, placing it directly into your 
                          // pre-allocated storage at memory address “buf”.
 
    tptr->~T();           // You must **manually** call the object's destructor
                          // if its side effects is depended by the program.
}                         // Leaving this block scope automatically deallocates “buf”.

注意：此功能由分配器（Allocator）类的成员函数封装。

当分配其对齐要求超过 __STDCPP_DEFAULT_NEW_ALIGNMENT__ 的对象或此类对象的数组时，new 表达式将对齐要求（封装在 std::align_val_t 中）作为分配函数的第二个参数传递（对于定位形式，placement-arg 出现在对齐参数之后，作为第三、第四等参数）。如果重载解析失败（当定义了具有不同签名的类特定分配函数时发生，因为它隐藏了全局函数），则会尝试第二次重载解析，此时参数列表中不包含对齐参数。这允许对齐不敏感的类特定分配函数优先于全局对齐敏感的分配函数。

(C++17 起)
new T;      // calls operator new(sizeof(T))
            // (C++17) or operator new(sizeof(T), std::align_val_t(alignof(T))))
new T[5];   // calls operator new[](sizeof(T)*5 + overhead)
            // (C++17) or operator new(sizeof(T)*5+overhead, std::align_val_t(alignof(T))))
new(2,f) T; // calls operator new(sizeof(T), 2, f)
            // (C++17) or operator new(sizeof(T), std::align_val_t(alignof(T)), 2, f)
如果一个不抛出异常的分配函数（例如通过 new(std::nothrow) T 选择的那个）由于分配失败而返回空指针，则 new 表达式立即返回，它不会尝试初始化对象或调用 deallocation 函数。如果将空指针作为参数传递给不分配内存的定位 new 表达式，这会使所选的标准不分配内存的定位分配函数返回空指针，则行为是未定义的。

初始化

由 new 表达式创建的对象根据以下规则初始化。

如果 类型 不是数组类型，则单个对象在获得的内存区域中构造：

如果 new-initializer 不存在，则对象是默认初始化的。
如果 new-initializer 是用括号括起来的表达式列表，则对象是直接初始化的。
如果 new-initializer 是用花括号括起来的初始化器列表，则对象是列表初始化的。
(C++11 起)
如果 类型 是数组类型，则初始化对象数组：

如果 new-initializer 不存在，则每个元素都默认初始化。
即使第一个维度为零，仍然需要满足默认初始化假设元素的语义约束。
如果 new-initializer 是一对括号，则每个元素都值初始化。
即使第一个维度为零，仍然需要满足值初始化假设元素的语义约束。
如果 new-initializer 是用花括号括起来的初始化器列表，则数组是聚合初始化的。
(C++11 起)
如果 new-initializer 是用括号括起来的非空表达式列表，则数组是聚合初始化的。
(C++20 起)
初始化失败
如果初始化通过抛出异常（例如来自构造函数）而终止，则程序会查找匹配的 deallocation 函数，然后：

如果可以找到合适的 deallocation 函数，则调用该 deallocation 函数来释放正在构造对象的内存。之后，异常在 new 表达式的上下文中继续传播。
如果找不到明确匹配的 deallocation 函数，则传播异常不会导致对象内存被释放。这仅在被调用的分配函数不分配内存时才适用，否则很可能会导致内存泄漏。
匹配 deallocation 函数的查找范围确定如下：

如果 new 表达式不以 :: 开头，且分配类型是类类型 T 或类类型 T 的数组，则在 T 的类作用域中搜索 deallocation 函数的名称。
否则，或者如果在 T 的类作用域中未找到任何内容，则通过在全局作用域中搜索来查找 deallocation 函数的名称。
对于非定位分配函数，使用正常的 deallocation 函数查找来查找匹配的 deallocation 函数（参见delete-expression）。

对于定位分配函数，匹配的 deallocation 函数必须具有相同数量的参数，并且除了第一个参数之外的每个参数类型都与分配函数的相应参数类型相同（在参数转换之后）。

如果查找找到一个匹配的 deallocation 函数，则将调用该函数；否则，将不调用任何 deallocation 函数。
如果查找找到一个非定位 deallocation 函数，并且该函数作为定位 deallocation 函数，本应被选为分配函数的匹配，则程序格式错误。
在任何情况下，匹配的 deallocation 函数（如果有）必须是未删除且(C++11 起)在 new 表达式出现的位置可访问的。

struct S
{
    // Placement allocation function:
    static void* operator new(std::size_t, std::size_t);
 
    // Non-placement deallocation function:
    static void operator delete(void*, std::size_t);
};
 
S* p = new (0) S; // error: non-placement deallocation function matches
                  //        placement allocation function
如果在 new 表达式中调用 deallocation 函数（由于初始化失败），则传递给该函数的参数确定如下：

第一个参数是从分配函数调用返回的值（类型为 void*）。
其他参数（仅适用于定位 deallocation 函数）是传递给定位分配函数的 placement-args。
如果允许实现引入临时对象或复制任何参数作为调用分配函数的一部分，则未指定是否在分配函数和 deallocation 函数的调用中使用相同的对象。

内存泄漏
由 new 表达式创建的对象（具有动态存储期的对象）会一直存在，直到 new 表达式返回的指针在匹配的delete-expression中使用。如果指针的原始值丢失，对象将无法访问且无法释放：发生内存泄漏。

这可能在以下情况下发生：指针被赋值，

int* p = new int(7); // dynamically allocated int with value 7
p = nullptr; // memory leak
或者指针超出作用域，

void f()
{
    int* p = new int(7);
} // memory leak
或者由于异常。

void f()
{
    int* p = new int(7);
    g();      // may throw
    delete p; // okay if no exception
} // memory leak if g() throws
为了简化动态分配对象的管理，new 表达式的结果通常存储在智能指针中：std::auto_ptr (C++17 前)std::unique_ptr 或 std::shared_ptr(C++11 起)。这些指针保证在上述情况下执行 delete 表达式。

##### delete 表达式
销毁先前由 new 表达式 分配的对象并释放获取的内存区域。

语法
::(可选) delete   表达式	(1)	
::(可选) delete[] 表达式	(2)	
表达式	-	以下之一
类类型表达式，可隐式转换为对象类型指针
对象类型指针的纯右值
1) 销毁由 new 表达式 创建的一个非数组对象。
2) 销毁由 new[] 表达式 创建的数组。
解释
给定从 表达式 评估出的指针（在可能的转换之后）为 ptr。

1) ptr 必须是以下之一
空指针，
指向由 new 表达式 创建的非数组对象的指针，或
指向由 new 表达式 创建的非数组对象的基子对象的指针。
 ptr 所指向的类型必须与对象类型（或基子对象的类型）相似。如果 ptr 是其他任何类型，包括通过 new 表达式 的数组形式获得的指针，则行为是未定义的。
2) ptr 必须是空指针，或者其值是通过 new 表达式 的数组形式先前获得的指针，且其分配函数不是非分配形式（即重载 (10)）。
 ptr 所指向的类型必须与数组对象的元素类型相似。如果 ptr 是其他任何类型，包括通过 new 表达式 的非数组形式获得的指针，则行为是未定义的。
delete 表达式的结果总是 void 类型。

如果在删除时，被删除的对象具有不完整的类类型，并且完整类具有非平凡析构函数或解除分配函数，则行为是未定义的(C++26 之前)则程序格式错误(C++26 起)。

如果 ptr 不是空指针且解除分配函数不是销毁性删除(C++20 起)，则 delete 表达式会为被销毁的对象或数组的每个元素（从数组的最后一个元素到第一个元素）调用析构函数（如果有）。析构函数必须从 delete 表达式出现的位置可访问。

之后，无论析构函数是否抛出异常，delete 表达式都会调用解除分配函数：operator delete（第一种形式）或 operator delete[]（第二种形式），除非匹配的 new 表达式与另一个 new 表达式结合使用(C++14 起)。

解除分配函数的名称在 ptr 所指向对象的动态类型的范围内进行查找，这意味着如果存在类特定的解除分配函数，它们会在全局解除分配函数之前被找到。如果 delete 表达式中存在 ::，则此查找仅检查全局命名空间。在任何情况下，除了常用解除分配函数之外的任何声明都将被丢弃。

如果找到任何解除分配函数，则按照以下方式选择要调用的函数（有关这些函数及其效果的更详细描述，请参阅解除分配函数）

如果至少有一个解除分配函数是销毁性删除，则所有非销毁性删除都被忽略。
(C++20 起)
如果类型的对齐要求超过 __STDCPP_DEFAULT_NEW_ALIGNMENT__，则优先选择对齐感知解除分配函数（带有 std::align_val_t 类型的参数）。对于其他类型，则优先选择对齐无关解除分配函数（不带 std::align_val_t 类型的参数）。
如果找到多个首选函数，则在下一步中仅考虑首选函数。
如果未找到首选函数，则在下一步中考虑非首选函数。
如果只剩下一个函数，则选择该函数。
(C++17 起)
如果找到的解除分配函数是类特定的，则无大小感知的类特定解除分配函数（不带 std::size_t 类型的参数）优先于大小感知的类特定解除分配函数（带 std::size_t 类型的参数）。
否则，查找到达全局作用域，并且
如果类型是完整的，并且（仅对于数组形式）操作数是指向具有非平凡析构函数的类类型或其（可能多维）数组的指针，则选择全局大小感知的全局函数（带 std::size_t 类型的参数）。
否则，是选择全局大小感知的解除分配函数（带 std::size_t 类型的参数）还是全局无大小感知的解除分配函数（不带 std::size_t 类型的参数）是未指定的。
(C++14 起)
选择的解除分配函数必须从 delete 表达式出现的位置可访问，除非解除分配函数是在动态类型的虚析构函数的定义点选择的。

要回收的存储块的指针作为第一个参数传递给上述过程选择的解除分配函数。块的大小作为可选的 std::size_t 参数传递。对齐要求作为可选的 std::align_val_t 参数传递。(C++17 起)

如果 ptr 是空指针值，则不调用析构函数，解除分配函数可能被调用也可能不被调用（未指定），但默认的解除分配函数保证在传递空指针时不做任何事情。

如果 ptr 是指向使用 new 分配的对象的基类子对象的指针，则基类的析构函数必须是虚函数，否则行为是未定义的。

## 二、文件操作

### 文件流类
**知识点：** C++提供三种文件流类

**类型：**
- `ifstream`：输入文件流（读）
- `ofstream`：输出文件流（写）
- `fstream`：输入输出文件流（读写）

**相关项目：** FileOperation, BankAccountProject, BankAccount2

### 文件读写操作
**打开文件：**
```cpp
ifstream fin("input.txt");
ofstream fout("output.txt");
```

**检查文件是否打开：**
```cpp
if (!fin) {
    cout << "文件打开失败" << endl;
}
```

**读取数据：**
```cpp
// 按单词读取
string word;
while (fin >> word) {
    // 处理
}

// 按行读取
string line;
while (getline(fin, line)) {
    // 处理
}
```

**写入数据：**
```cpp
fout << "Hello World" << endl;
fout << accountNumber << " " << name << " " << balance << endl;
```

**关闭文件：**
```cpp
fin.close();
fout.close();
```

**相关项目：** FileOperation, BankAccountProject, BankAccount2

### 文件操作模式
**ios::app**：追加模式
```cpp
ofstream fout("file.txt", ios::app);
```





三.
~~类
 C++ C++ 语言 类 
类是用户定义类型。

类类型由类说明符定义，其出现在声明语法的 decl-specifier-seq 中。参阅类声明以了解类说明符的语法。

类可以有以下种类的成员

1) 数据成员
a) 非静态数据成员，包括位域。
b) 静态数据成员
2) 成员函数
a) 非静态成员函数
b) 静态成员函数
3) 嵌套类型
a) 类定义中定义的嵌套类和枚举
b) 现有类型的别名，通过 typedef 或类型别名(C++11 起)声明定义
c) 类自身定义中的类名，在查找时作为其自身的公有成员类型别名（除了用于命名构造函数时）：这被称为注入类名
4) 类中定义的所有无作用域枚举的枚举器，或通过using-声明或using-enum-声明引入的枚举器(C++20 起)
5) 成员模板（变量模板、(C++14 起)类模板或函数模板）可以出现在任何非局部类/结构体/联合体的体中。
所有成员都在类定义中一次性定义，不能添加到已定义的类中（与命名空间成员不同）。

如果类 T 的成员是以下之一，则不能使用 T 作为其名称：

静态数据成员，
成员函数，
成员类型，
成员模板，
枚举的枚举器（除非枚举有作用域）(C++11 起)，或
成员匿名联合的成员。
然而，只要没有用户声明的构造函数，非静态数据成员可以使用名称 T。

一个至少有一个声明或继承的虚成员函数的类是多态的。此类型的对象是多态对象，并在对象表示中存储运行时类型信息，可以使用 dynamic_cast 和 typeid 查询。虚成员函数参与动态绑定。

一个至少有一个声明或继承的纯虚成员函数的类是抽象类。此类型的对象不能被创建。

具有 constexpr 构造函数的类是字面类型：此类型的对象可以在编译时由 constexpr 函数操纵。

(C++11 起)
类的属性
平凡可复制类

一个平凡可复制类是指：

至少有一个合格的复制构造函数、移动构造函数、复制赋值运算符或移动赋值运算符，
每个合格的复制构造函数都是平凡的
每个合格的移动构造函数都是平凡的
每个合格的复制赋值运算符都是平凡的
每个合格的移动赋值运算符都是平凡的，以及
有一个非删除的平凡析构函数。
平凡类
一个平凡类是指：

是平凡可复制的，并且
有一个或多个合格的默认构造函数，且每个都是平凡的。
（C++26 中已弃用）
标准布局类

一个标准布局类是指：

没有非标准布局类类型（或此类类型的数组）或引用类型的非静态数据成员，
没有虚函数且没有虚基类，
所有非静态数据成员具有相同的访问控制，
没有非标准布局基类，
继承层次中只有一个类拥有非静态数据成员，以及
非正式地说，没有基类与第一个非静态数据成员的类型相同。或，正式地说：给定类 S，其没有类型集合 M(S) 中的任何元素作为基类，其中类型 X 的 M(X) 定义如下：
如果 X 是一个没有（可能继承的）非静态数据成员的非联合类类型，则集合 M(X) 为空。
如果 X 是一个非联合类类型，其第一个非静态数据成员的类型为 X0（其中所述成员可能是匿名联合），则集合 M(X) 由 X0 和 M(X0) 的元素组成。
如果 X 是一个联合类型，则集合 M(X) 是所有 M(Ui) 和包含所有 Ui 的集合的并集，其中每个 Ui 是 X 的第 i 个非静态数据成员的类型。
如果 X 是一个元素类型为 Xe 的数组类型，则集合 M(X) 由 Xe 和 M(Xe) 的元素组成。
如果 X 是非类、非数组类型，则集合 M(X) 为空。
标准布局结构体是使用类关键词 struct 或类关键词 class 定义的标准布局类。标准布局联合体是使用类关键词 union 定义的标准布局类。

(C++11 起)
隐式生命周期类

一个隐式生命周期类是指：

是一个聚合体，其析构函数不是用户声明的(C++11 前)用户提供的(C++11 起)，或
至少有一个平凡的合格构造函数和一个平凡的、非删除的析构函数。
注：缺陷报告 P0593R6 澄清了隐式生命周期属性。

POD 类
一个POD 类是指：

是一个聚合体，
没有用户声明的复制赋值运算符，
没有用户声明的析构函数，以及
没有非POD类类型（或此类类型的数组）或引用类型的非静态数据成员。
(C++11 前)
是一个平凡类，
是一个标准布局类，以及
没有非POD类类型（或此类类型的数组）的非静态数据成员。
(C++11 起)
POD 结构体是非联合 POD 类。POD 联合体是作为 POD 类的联合体。





~~类声明
 C++ C++ 语言 类 
类是用户定义类型，由 class-specifier 定义，它出现在声明语法的 decl-specifier-seq 中。

语法
类说明符具有以下语法：

class-key attr ﻿(可选) class-head-name class-property-specs ﻿(可选) base-clause ﻿(可选)
{ member-specification }	(1)	
class-key attr ﻿(可选) base-clause ﻿(可选)
{ member-specification }	(2)	
1) 命名类定义
2) 匿名类定义
类键	-	其中之一是 class、struct 和 union。关键字 class 和 struct 除了默认成员访问权限和默认基类访问权限外是相同的。如果它是 union，则此声明引入一个联合类型。
属性	-	(C++11 起) 任意数量的属性，可以包含 alignas 说明符
class-head-name	-	正在定义的类的名称，可选地限定
class-property-specs	-	以下说明符的列表，每个说明符在每个序列中最多允许出现一次。
说明符	效果
final
(C++11 起)	指定类不能被派生
trivially_relocatable_if_eligible     
(C++26 起)	如果符合条件，将类标记为可平凡重定位
replaceable_if_eligible     
(C++26 起)	如果符合条件，将类标记为可替换
base-clause	-	一个或多个基类的列表，以及每个基类使用的继承模型（参见派生类）
member-specification	-	访问说明符、成员对象和成员函数声明和定义的列表（见下文）
前向声明

以下形式的声明

class-key attr identifier ;		
声明了一个将在该作用域中稍后定义的类类型。在定义出现之前，此类名具有不完整类型。这允许类之间相互引用


class Vector; // forward declaration
 
class Matrix
{
    // ...
    friend Vector operator*(const Matrix&, const Vector&);
};
 
class Vector
{
    // ...
    friend Vector operator*(const Matrix&, const Vector&);
};
如果特定源文件只使用指向类的指针和引用，这使得减少 #include 依赖成为可能。


// In MyStruct.h
#include <iosfwd> // contains forward declaration of std::ostream
 
struct MyStruct
{
    int value;
    friend std::ostream& operator<<(std::ostream& os, const S& s);
    // definition provided in MyStruct.cpp file which uses #include <ostream>
};
如果前向声明出现在局部作用域中，它会隐藏之前声明的类、变量、函数以及在封闭作用域中可能出现的同名所有其他声明。


struct s { int a; };
struct s; // does nothing (s already defined in this scope)
 
void g()
{
    struct s; // forward declaration of a new, local struct "s"
              // this hides global struct s until the end of this block
 
    s* p; // pointer to local struct s
 
    struct s { char* p; }; // definitions of the local struct s
}
请注意，新的类名也可以通过作为另一个声明的一部分出现的详细类型说明符引入，但前提是名称查找无法找到之前声明的同名类。


class U;
 
namespace ns
{
    class Y f(class T p); // declares function ns::f and declares ns::T and ns::Y
 
    class U f(); // U refers to ::U
 
    // can use pointers and references to T and Y
    Y* p;
    T* q;
}
成员规范

成员规范，或类定义的主体，是包含在花括号中的任意数量的以下内容的序列：


1) 以下形式的成员声明：
attr ﻿(可选) decl-specifier-seq ﻿(可选) member-declarator-list ﻿(可选) ;		
属性	-

(自 C++11 起) 任意数量的属性
声明说明符序列	-

说明符序列。它仅在构造函数、析构函数和用户定义的类型转换函数的声明中可选。
member-declarator-list	-

类似于init-declarator-list，但额外允许位域声明、纯说明符，以及 virt-specifier（override 或 final）(C++11 起)，并且不允许直接非列表初始化语法。
此声明可以声明静态和非静态数据成员和成员函数、成员typedefs、成员枚举和嵌套类。它也可以是友元声明。


class S
{
    int d1;             // non-static data member
    int a[10] = {1, 2}; // non-static data member with initializer (C++11)
 
    static const int d2 = 1; // static data member with initializer
 
    virtual void f1(int) = 0; // pure virtual member function
 
    std::string d3, *d4, f2(int); // two data members and a member function
 
    enum { NORTH, SOUTH, EAST, WEST };
 
    struct NestedS
    {
        std::string s;
    } d5, *d6;
 
    typedef NestedS value_type, *pointer_type;
};
2) 函数定义，既声明又定义成员函数或友元函数。成员函数定义后的分号是可选的。在类体内部定义的所有函数都会自动成为内联函数，除非它们附属于命名模块(C++20 起)。
class M
{
    std::size_t C;
    std::vector<int> data;
public:
    M(std::size_t R, std::size_t C) : C(C), data(R*C) {} // constructor definition
 
    int operator()(std::size_t r, std::size_t c) const // member function definition
    {
        return data[r * C + c];
    }
 
    int& operator()(std::size_t r, std::size_t c) // another member function definition
    {
        return data[r * C + c];
    }
};
3) 访问说明符 public:、protected: 和 private:
class S
{
public:
    S();          // public constructor
    S(const S&);  // public copy constructor
    virtual ~S(); // public virtual destructor
private:
    int* ptr; // private data member
};
4) using-声明
class Base
{
protected:
    int d;
};
 
class Derived : public Base
{
public:
    using Base::d;    // make Base's protected member d a public member of Derived
    using Base::Base; // inherit all bases' constructors (C++11)
};
5) static_assert 声明
template<typename T>
struct Foo
{
    static_assert(std::is_floating_point<T>::value, "Foo<T>: T must be floating point");
};
6) 成员模板声明
struct S
{
    template<typename T>
    void f(T&& n);
 
    template<class CharT>
    struct NestedS
    {
        std::basic_string<CharT> s;
    };
};
7) 别名声明
template<typename T>
struct identity
{
    using type = T;
};
(C++11 起)
8) 成员类模板的推导指南
struct S
{
    template<class CharT>
    struct NestedS
    {
        std::basic_string<CharT> s;
    };
 
    template<class CharT>
    NestedS(std::basic_string<CharT>) -> NestedS<CharT>;
};
(C++17 起)
9) using-enum-声明
enum class color { red, orange, yellow };
 
struct highlight
{
    using enum color;
};
(C++20 起)
局部类

类声明可以出现在函数体内，在这种情况下它定义了一个局部类。此类名称只存在于函数作用域内，在外部不可访问。

局部类的成员只能在该类的定义中声明，除了作为嵌套类的成员也可以在该类的最近的封闭块作用域中声明。
嵌套在局部类中的类也是一个局部类。
局部类不能有静态数据成员。
局部类的成员函数没有链接性。
局部类的成员函数必须完全在类体内定义。
局部类（除了闭包类型）(C++14 起)不能有成员模板。
局部类不能有友元模板。
局部类不能在类定义内部定义友元函数。
函数（包括成员函数）内部的局部类可以访问封闭函数可以访问的相同名称。
局部类不能用作模板参数。
(C++11 前)
运行此代码
#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> v{1, 2, 3};
 
    struct Local
    {
        bool operator()(int n, int m)
        {
            return n > m;
        }
    };
 
    std::sort(v.begin(), v.end(), Local()); // since C++11
 
    for (int n : v)
        std::cout << n << ' ';
    std::cout << '\n';
}
输出


3 2 1





~~非静态成员函数
 C++ C++ 语言 类 
非静态成员函数是在类的成员声明中声明的函数，没有 static 或 friend 说明符（有关这些关键字的作用，请参见静态成员函数和友元声明）。

class S
{
    int mf1(); // non-static member function declaration
    void mf2() volatile, mf3() &&; // can have cv-qualifiers and/or a reference-qualifier
        // the declaration above is equivalent to two separate declarations:
        // void mf2() volatile;
        // void mf3() &&;
 
    int mf4() const { return data; } // can be defined inline
    virtual void mf5() final; // can be virtual, can use final/override
    S() : data(12) {} // constructors are member functions too
    int data;
};
 
int S::mf1() { return 7; } // if not defined inline, has to be defined at namespace
构造函数、析构函数和转换函数使用特殊的语法进行声明。本页描述的规则可能不适用于这些函数。详情请参见各自的页面。

显式对象成员函数是没有显式对象参数的非静态成员函数。

(C++23 起)
隐式对象成员函数是没有显式对象参数的非静态成员函数（在 C++23 之前，这是唯一一种非静态成员函数，因此在文献中被称为“非静态成员函数”）。

说明
允许任何函数声明，并附加仅适用于非静态成员函数的语法元素：纯说明符、cv 限定符、引用限定符、final 和 override 说明符(C++11 起)以及成员初始化列表。

类 X 的非静态成员函数可以按以下方式调用：

1) 对于类型为 X 的对象，使用类成员访问运算符
2) 对于从 X 派生的类的对象
3) 直接从 X 的成员函数体内
4) 直接从从 X 派生的类的成员函数体内
在不是类型 X 或从 X 派生的类型的对象上调用类 X 的非静态成员函数会触发未定义行为。


在 X 的非静态成员函数体内，任何解析为 X 或 X 的基类的非类型非静态成员的id-expression e（例如标识符）都会转换为成员访问表达式 (*this).e（除非它已经是成员访问表达式的一部分）。这不会发生在模板定义上下文中，因此名称可能需要显式地加上 this-> 前缀才能成为依赖名称。

struct S
{
    int n;
    void f();
};
 
void S::f()
{
    n = 1; // transformed to (*this).n = 1;
}
 
int main()
{
    S s1, s2;
    s1.f(); // changes s1.n
}
在 X 的非静态成员函数体内，任何解析为 X 或 X 的基类的静态成员、枚举器或嵌套类型的 unqualified-id 都会转换为相应的 qualified-id。


struct S
{
    static int n;
    void f();
};
 
void S::f()
{
    n = 1; // transformed to S::n = 1;
}
 
int main()
{
    S s1, s2;
    s1.f(); // changes S::n
}
带 cv 限定符的成员函数

隐式对象成员函数可以声明为带cv 限定符序列（const、volatile，或 const 和 volatile 的组合），该序列出现在函数声明的参数列表之后。具有不同 cv 限定符序列（或没有序列）的函数具有不同的类型，因此可以相互重载。

在带 cv 限定符序列的函数体内，*this 是 cv 限定的，例如，在带 const 限定符的成员函数中，通常只能调用其他带 const 限定符的成员函数。如果应用了const_cast或通过不涉及this的访问路径，仍然可以调用不带 const 限定符的成员函数。

#include <vector>
 
struct Array
{
    std::vector<int> data;
    Array(int sz) : data(sz) {}
 
    // const member function
    int operator[](int idx) const
    {                     // the this pointer has type const Array*
        return data[idx]; // transformed to (*this).data[idx];
    }
 
    // non-const member function
    int& operator[](int idx)
    {                     // the this pointer has type Array*
        return data[idx]; // transformed to (*this).data[idx]
    }
};
 
int main()
{
    Array a(10);
    a[1] = 1;  // OK: the type of a[1] is int&
    const Array ca(10);
    ca[1] = 2; // Error: the type of ca[1] is int
}
带引用限定符的成员函数

隐式对象成员函数可以声明为不带引用限定符，带左值引用限定符（参数列表后的标记 &）或右值引用限定符（参数列表后的标记 &&）。在重载决议期间，带类 X 的 cv 限定符序列的隐式对象成员函数按以下方式处理：

不带引用限定符：隐式对象参数的类型是 cv 限定 X 的左值引用，并且还允许绑定右值隐含对象参数
左值引用限定符：隐式对象参数的类型是 cv 限定 X 的左值引用
右值引用限定符：隐式对象参数的类型是 cv 限定 X 的右值引用
#include <iostream>
 
struct S
{
    void f() &  { std::cout << "lvalue\n"; }
    void f() && { std::cout << "rvalue\n"; }
};
 
int main()
{
    S s;
    s.f();            // prints "lvalue"
    std::move(s).f(); // prints "rvalue"
    S().f();          // prints "rvalue"
}
注意：与 cv 限定不同，引用限定不会改变this指针的属性：在右值引用限定函数中，*this 仍然是一个左值表达式。

(C++11 起)
虚函数和纯虚函数

非静态成员函数可以声明为虚函数或纯虚函数。详情请参见虚函数和抽象类。

显式对象成员函数
对于未声明 cv 限定符或引用限定符的非静态非虚成员函数，其第一个参数（如果不是函数参数包）可以是显式对象参数（用前缀关键字 this 表示）

struct X
{
    void foo(this X const& self, int i); // same as void foo(int i) const &;
//  void foo(int i) const &; // Error: already declared
 
    void bar(this X self, int i); // pass object by value: makes a copy of “*this”
};
对于成员函数模板，显式对象参数允许推导类型和值类别，此语言特性称为“推导 this”


struct X
{
    template<typename Self>
    void foo(this Self&&, int);
};
 
struct D : X {};
 
void ex(X& x, D& d)
{
    x.foo(1);       // Self = X&
    move(x).foo(2); // Self = X
    d.foo(3);       // Self = D&
}
这使得可以消除 const 和非 const 成员函数的重复，请参阅数组下标运算符以获取示例。


在显式对象成员函数的函数体内，不能使用 this 指针：所有成员访问都必须通过第一个参数完成，就像在静态成员函数中一样

struct C
{
    void bar();
 
    void foo(this C c)
    {
        auto x = this; // error: no this
        bar();         // error: no implicit this->
        c.bar();       // ok
    }
};
指向显式对象成员函数的指针是普通的函数指针，而不是成员指针

struct Y 
{
    int f(int, int) const&;
    int g(this Y const&, int, int);
};
 
auto pf = &Y::f;
pf(y, 1, 2);              // error: pointers to member functions are not callable
(y.*pf)(1, 2);            // ok
std::invoke(pf, y, 1, 2); // ok
 
auto pg = &Y::g;
pg(y, 3, 4);              // ok
(y.*pg)(3, 4);            // error: “pg” is not a pointer to member function
std::invoke(pg, y, 3, 4); // ok











~~构造函数和成员初始化列表

 C++ C++ 语言 类 
构造函数是非静态的成员函数，它们使用特殊的声明符语法进行声明，用于初始化其类类型的对象。

构造函数不能是协程。

(C++20 起)
构造函数不能有显式对象参数。

(C++23 起)
语法
构造函数使用以下形式的成员函数声明符进行声明

类名 ( 参数列表 ﻿(可选) ) 异常规范 ﻿(可选) 属性 ﻿(可选)		
类名	-	一个标识符表达式，可能后跟属性列表，并(C++11 起)可能用一对括号括起来
参数列表	-	参数列表
异常规范	-	
动态异常规范

(C++11 前)
或者动态异常规范
或者noexcept 规范

(C++11 起)
(C++17 前)
noexcept 规范的一部分

(C++17 起)
属性	-	(C++11 起) 属性列表
构造函数声明的声明说明符中唯一允许的说明符是friend、inline、constexpr(C++11 起)、consteval(C++20 起)和explicit（特别地，不允许返回类型）。注意，cv-和引用限定符也不允许：正在构造的对象的 const 和 volatile 语义只在最派生构造函数完成之后才生效。


类名的标识符表达式必须具有以下形式之一

在友元声明中，标识符表达式是限定标识符，它命名一个构造函数。
否则，在属于类或类模板的成员规范的成员声明中
对于类，标识符表达式是立即封闭类的注入类名。
对于类模板，标识符表达式是命名当前实例化的类名(C++20 前)注入类名(C++20 起)的立即封闭类模板。
否则，标识符表达式是限定标识符，其末尾的非限定标识符是其查找上下文的注入类名。
成员初始化列表

任何构造函数的函数定义的主体，在复合语句的开括号之前，可以包含成员初始化列表，其语法是冒号字符:，后跟一个或多个逗号分隔的成员初始化器列表，每个成员初始化器具有以下语法

类或标识符 ( 表达式列表 ﻿(可选) )	(1)	
类或标识符 大括号初始化列表	(2)	(C++11 起)
参数包 ...	(3)	(C++11 起)
1) 使用直接初始化初始化由类或标识符命名的基类或成员，如果表达式列表为空，则使用值初始化

2) 使用列表初始化初始化由类或标识符命名的基类或成员（如果列表为空，则变为值初始化，如果初始化聚合类型，则变为聚合初始化）
3) 使用包扩展初始化多个基类
类或标识符	-	任何命名非静态数据成员的标识符，或任何命名类本身（用于委托构造函数）或直接基类或虚基类的类型名。
表达式-列表	-

可能为空的逗号分隔列表，表示要传递给基类或成员构造函数的参数
大括号初始化列表	-

大括号括起来的初始化列表
参数包	-

可变模板参数包的名称
运行此代码
struct S
{
    int n;
 
    S(int);       // constructor declaration
 
    S() : n(7) {} // constructor definition:
                  // ": n(7)" is the initializer list
                  // ": n(7) {}" is the function body
};
 
S::S(int x) : n{x} {} // constructor definition: ": n{x}" is the initializer list
 
int main()
{
    S s;      // calls S::S()
    S s2(10); // calls S::S(int)
}
解释

构造函数没有名称，不能直接调用。它们在初始化发生时被调用，并根据初始化规则进行选择。没有explicit说明符的构造函数是转换构造函数。带有constexpr说明符的构造函数使其类型成为字面类型。可以不带任何参数调用的构造函数是默认构造函数。接受相同类型的另一个对象作为参数的构造函数是拷贝构造函数和移动构造函数。


在构成构造函数函数体的复合语句开始执行之前，所有直接基类、虚基类和非静态数据成员的初始化都已完成。成员初始化列表是指定这些子对象非默认初始化的地方。对于不能默认初始化的基类和不能通过默认初始化或通过它们的默认成员初始化器（如果有）初始化的非静态数据成员(C++11 起)，例如引用类型和 const 限定类型的成员，必须指定成员初始化器。（请注意，如果成员类型或初始化器是依赖的，则类模板实例化中非静态数据成员的默认成员初始化器可能无效。）(C++11 起)对于没有成员初始化器或默认成员初始化器(C++11 起)的匿名联合体或变体成员，不执行任何初始化。


在构造不是正在构造的对象的最终派生类的任何类期间，类或标识符命名虚基类的初始化器将被忽略。


表达式列表或大括号初始化列表中出现的名称在构造函数的作用域中进行求值


class X
{
    int a, b, i, j;
public:
    const int& r;
    X(int i)
      : r(a) // initializes X::r to refer to X::a
      , b{i} // initializes X::b to the value of the parameter i
      , i(i) // initializes X::i to the value of the parameter i
      , j(this->i) // initializes X::j to the value of X::i
    {}
};
从成员初始化器抛出的异常可以通过函数try块来处理。

如果非静态数据成员具有默认成员初始化器，并且也出现在成员初始化列表中，则使用成员初始化器并忽略默认成员初始化器


struct S
{
    int n = 42;   // default member initializer
    S() : n(7) {} // will set n to 7, not 42
};
(C++11 起)
引用成员不能在成员初始化列表中绑定到临时对象


struct A
{
    A() : v(42) {} // Error
    const int& v;
};
注意：同样适用于默认成员初始化器。


构造和析构期间的操作

成员函数（包括虚成员函数）可以对正在构造或析构的对象进行调用。同样，正在构造或析构的对象可以是typeid或dynamic_cast的操作数。

但是，如果在以下任何评估期间执行这些操作，则行为是未定义的

构造函数的前置条件断言的评估
析构函数的后置条件断言的评估
(C++26 起)
在所有基类的成员初始化器完成之前，成员初始化列表的评估

~拷贝构造函数

 C++ C++ 语言 类 
拷贝构造函数是一种构造函数，它可以使用相同类类型的参数调用，并复制参数的内容而不改变参数。

语法
类名 ﻿(参数列表 ﻿);	(1)	
类名 ﻿(参数列表 ﻿) 函数体	(2)	
类名 ﻿(单一参数列表 ﻿) = default;	(3)	(C++11 起)
类名 ﻿(参数列表 ﻿) = delete;	(4)	(C++11 起)
类名 ﻿::类名 ﻿(参数列表 ﻿) 函数体	(5)	
类名 ﻿::类名 ﻿(单一参数列表 ﻿) = default;	(6)	(C++11 起)
类名	-	声明其拷贝构造函数的类
参数列表	-	非空的参数列表，满足以下所有条件：
给定类类型为T，第一个参数类型为T&、const T&、volatile T& 或 const volatile T&，并且
要么没有其他参数，要么所有其他参数都带有默认实参。
单一参数列表	-	仅含一个参数的参数列表，该参数类型为T&、const T&、volatile T& 或 const volatile T&，且没有默认实参。
函数体	-	拷贝构造函数的函数体
解释

1) 类定义内部的拷贝构造函数声明。
2-4) 类定义内部的拷贝构造函数定义。
3) 拷贝构造函数是显式默认的。

4) 拷贝构造函数是已删除的。
5,6) 类定义外部的拷贝构造函数定义（类必须包含声明(1)）。
6) 拷贝构造函数是显式默认的。

struct X
{
    X(X& other); // copy constructor
//  X(X other);  // Error: incorrect parameter type
};
 
union Y
{
    Y(Y& other, int num = 1); // copy constructor with multiple parameters
//  Y(Y& other, int num);     // Error: `num` has no default argument
};
当一个对象通过（直接初始化或拷贝初始化）从另一个相同类型的对象进行初始化时，就会调用拷贝构造函数（除非重载决议选择了更好的匹配或者调用被省略），这包括：

初始化：T a = b; 或 T a(b);，其中b的类型是T；
函数参数传递：f(a);，其中a的类型是T，且f是void f(T t)；
函数返回：函数T f()内部的return a;，其中a的类型是T，并且没有移动构造函数。






~~析构函数

 C++ C++ 语言 类 
析构函数是一种特殊的成员函数，它在对象的生存期结束时被调用。析构函数的目的是释放对象在其生存期内可能获取的资源。

析构函数不能是协程。

(C++20 起)
语法
析构函数(C++20 前)准析构函数(C++20 起)使用以下形式的成员函数声明符声明

带波浪号的类名 ( 形参列表 ﻿(可选) ) 异常说明 ﻿(可选) 属性 ﻿(可选)		
带波浪号的类名	-	一个标识符表达式，后面可以跟随一个属性列表，并且(C++11 起)可以被一对括号括起来
形参列表	-	形参列表 (必须为空或 void)
异常规范	-	
动态异常规范

(C++11 前)
或者动态异常规范
或者noexcept 规范

(C++11 起)
(C++17 前)
noexcept 规范的一部分

(C++17 起)
属性	-	(C++11 起) 属性列表
一个准(C++20 起)析构函数声明的声明说明符中允许的说明符只有constexpr、(C++11 起) friend、inline 和 virtual (特别地，不允许有返回类型)。


带波浪号的类名的标识符表达式必须具有以下形式之一

在属于类或类模板的成员说明，但不是友元声明的成员声明中
对于类，标识符表达式为 ~ 后跟直接外围类的注入类名。
对于类模板，标识符表达式为 ~ 后跟指名当前实例化的类名(C++20 前)直接外围类模板的注入类名(C++20 起)。
否则，标识符表达式是一个限定标识符，其末端的非限定标识符为 ~ 后跟由该限定标识符的非末端部分所指名的类的注入类名。
解释

每当对象的生存期结束时，就会隐式调用析构函数，这包括：

对于具有静态存储期的对象，在程序终止时
对于具有线程局部存储期的对象，在线程退出时
(C++11 起)
对于具有自动存储期的对象以及其生命周期因绑定到引用而被延长的临时对象，在作用域结束时
对于具有动态存储期的对象，在使用 delete 表达式时
对于无名临时对象，在完整表达式结束时
当异常逃离其块且未被捕获时，对于具有自动存储期的对象，在栈回溯期间
析构函数也可以被显式调用。

准析构函数

一个类可以有一个或多个准析构函数，其中一个被选为该类的析构函数。

为了确定哪个准析构函数是析构函数，在类定义结束时，会对类中声明的具有空参数列表的准析构函数执行重载决议。如果重载决议失败，则程序非良构。析构函数的选择不会ODR 式使用所选的析构函数，且所选的析构函数可以是被删除的。

所有准析构函数都是特殊成员函数。如果类 T 没有提供用户声明的准析构函数，编译器将总是隐式声明一个，并且这个隐式声明的准析构函数也就是 T 的析构函数。


运行此代码
#include <cstdio>
#include <type_traits>
 
template<typename T>
struct A
{
    ~A() requires std::is_integral_v<T> { std::puts("~A, T is integral"); }
    ~A() requires std::is_pointer_v<T> { std::puts("~A, T is a pointer"); }
    ~A() { std::puts("~A, T is anything else"); }
};
 
int main()
{
    A<int> a;
    A<int*> b;
    A<float> c;
}
输出

~A, T is anything else
~A, T is a pointer
~A, T is integral
(C++20 起)
可能被调用的析构函数

类 T 的析构函数在以下情况下是可能被调用的

它被显式或隐式调用。
一个 new 表达式创建了类型为 T 的对象数组。
return 语句的结果对象类型为 T。
一个数组正在进行聚合初始化，并且其元素类型是 T。
一个类对象正在进行聚合初始化，并且它有一个类型为 T 的成员，其中 T 不是匿名联合体类型。
一个可能被构造的子对象在非委托(C++11 起)构造函数中类型为 T。
构造了一个类型为 T 的异常对象。
如果一个可能被调用的析构函数是被删除的或(C++11 起)从调用上下文中不可访问的，则程序非良构。
销毁顺序
对于用户定义的或隐式定义的析构函数，在执行完析构函数体并销毁了函数体内分配的任何自动对象之后，编译器会以声明的相反顺序调用类的所有非静态非变体数据成员的析构函数，然后以构造的相反顺序调用所有直接非虚基类的析构函数（这些析构函数又会调用它们的成员和基类的析构函数等），然后，如果这个对象是最终派生类，它会调用所有虚基类的析构函数。


即使直接调用析构函数（例如 obj.~Foo();），~Foo() 中的 return 语句也不会立即将控制权返回给调用者：它会先调用所有那些成员和基类的析构函数。

虚析构函数

通过指向基类的指针删除对象会引发未定义行为，除非基类中的析构函数是 virtual 的

class Base
{
public:
    virtual ~Base() {}
};
 
class Derived : public Base {};
 
Base* b = new Derived;
delete b; // safe
一个常见的指导原则是，基类的析构函数必须是公有且虚的，或者是受保护且非虚的。


纯虚析构函数
一个准(C++20 起)析构函数可以被声明为纯虚的，例如在一个需要被设为抽象但没有其他合适的函数可以声明为纯虚的基类中。纯虚析构函数必须有定义，因为当派生类被销毁时，所有基类的析构函数总是会被调用。


class AbstractBase
{
public:
    virtual ~AbstractBase() = 0;
};
AbstractBase::~AbstractBase() {}
 
class Derived : public AbstractBase {};
 
// AbstractBase obj; // compiler error
Derived obj;         // OK



~~static 成员

 C++ C++ 语言 类 
在类定义中，关键词 static 声明不绑定到类实例的成员。

在类定义之外，它有不同的含义：参见存储期。

语法
静态成员的声明是一个成员声明，其声明说明符包含关键词 static。关键词 static 通常出现在其他说明符之前（这就是为什么语法常被非正式地描述为 static 数据成员 或 static 成员函数），但可以出现在说明符序列中的任何位置。

任何静态数据成员和静态成员函数的名称必须与包含该类的名称不同。

解释
类的静态成员不与类的对象关联：它们是具有静态或线程(C++11 起)存储期的独立变量，或者是常规函数。

关键词 static 仅用于在类定义内声明静态成员，而不用于定义该静态成员。

class X { static int n; }; // declaration (uses 'static')
int X::n = 1;              // definition (does not use 'static')
类体内的声明不是定义，并且可以声明成员为不完整类型（除了 void），包括声明该成员的类型。

struct Foo;
 
struct S
{
    static int a[]; // declaration, incomplete type
    static Foo x;   // declaration, incomplete type
    static S s;     // declaration, incomplete type (inside its own definition)
};
 
int S::a[10]; // definition, complete type
struct Foo {};
Foo S::x;     // definition, complete type
S S::s;       // definition, complete type
然而，如果声明使用 constexpr或 inline(C++17 起) 说明符，则成员必须声明为完整类型。

(C++11 起)
要引用类 T 的静态成员 m，可以使用两种形式：限定名 T::m 或成员访问表达式 E.m 或 E->m，其中 E 是一个分别评估为 T 或 T* 的表达式。在同一类作用域内，无需限定。


struct X
{
    static void f(); // declaration
    static int n;    // declaration
};
 
X g() { return X(); } // some function returning X
 
void f()
{
    X::f();  // X::f is a qualified name of static member function
    g().f(); // g().f is member access expression referring to a static member function
}
 
int X::n = 7; // definition
 
void X::f() // definition
{
    n = 1; // X::n is accessible as just n in this scope
}
静态成员遵循类成员访问规则（private, protected, public）。


静态成员函数
静态成员函数不与任何对象关联。调用时，它们没有 this 指针。

静态成员函数不能是 virtual、const、volatile 或引用限定的。

静态成员函数的地址可以存储在常规的函数指针中，但不能存储在成员函数指针中。

静态数据成员
静态数据成员不与任何对象关联。即使没有定义类的任何对象，它们也存在。在整个程序中，只有一个具有静态存储期的静态数据成员实例，除非使用关键词 thread_local，在这种情况下，每个线程有一个具有线程存储期的此类对象(C++11 起)。

静态数据成员不能是 mutable 的。

如果类本身具有外部链接（不是未命名命名空间的成员），则命名空间作用域中的类的静态数据成员具有外部链接。局部类（在函数内部定义的类）和未命名类，包括未命名类的成员类，不能拥有静态数据成员。

静态数据成员可以声明为 inline。内联静态数据成员可以在类定义中定义，并可以指定初始化器。它不需要类外定义。

struct X
{
    inline static int fully_usable = 1; // No out-of-class definition required, ODR-usable
    inline static const std::string class_name{"X"}; // Likewise
 
    static const int non_addressable = 1; // C.f. non-inline constants, usable
                                          // for its value, but not ODR-usable
    // static const std::string class_name{"X"}; // Non-integral declaration of this
                                                 // form is disallowed entirely
};
(C++17 起)
常量静态成员

如果一个整型或枚举类型的静态数据成员被声明为 const（而不是 volatile），它可以在类定义中直接用初始化器初始化，其中每个表达式都是常量表达式。

struct X
{
    const static int n = 1;
    const static int m{2}; // since C++11
    const static int k;
};
const int X::k = 3;
如果 LiteralType 的静态数据成员被声明为 constexpr，它必须在类定义中直接用初始化器初始化，其中每个表达式都是常量表达式。

struct X
{
    constexpr static int arr[] = { 1, 2, 3 };        // OK
    constexpr static std::complex<double> n = {1,2}; // OK
    constexpr static int k; // Error: constexpr static requires an initializer
};
(C++11 起)
如果 const 非 inline(C++17 起) 静态数据成员或 constexpr 静态数据成员(C++11 起)(C++17 前) 是ODR-used，仍需要在命名空间作用域提供定义，但它不能带有初始化器。

constexpr 静态数据成员隐式地是 inline，不需要在命名空间作用域重新声明。这种不带初始化器的重新声明（以前是必需的）仍然允许，但已弃用。

(C++17 起)
struct X
{
    static const int n = 1;
    static constexpr int m = 4;
};
 
const int *p = &X::n, *q = &X::m; // X::n and X::m are ODR-used
const int X::n;             // … so a definition is necessary
constexpr int X::m;         // … (except for X::m in C++17)
关键词

static








~~友元声明

 C++ C++ 语言 类 
友元声明出现在类体中，并授予函数或其他类访问该类（其中友元声明出现）的私有和保护成员的权限。

语法
friend function-declaration	(1)	
friend function-definition	(2)	
friend elaborated-type-specifier ;	(3)	（直到 C++26）
friend simple-type-specifier ;
friend typename-specifier ;

(4)	(C++11 起)
（直到 C++26）
friend friend-type-specifier-list ;	(5)	(C++26 起)
1,2) 函数友元声明。
3-5) 类友元声明。
function-declaration	-	一个函数声明
function-definition	-	一个函数定义
elaborated-type-specifier	-	一个详述类型说明符
simple-type-specifier	-	一个简单类型说明符
typename-specifier	-	关键字typename后跟一个限定标识符或限定简单模板标识符
friend-type-specifier-list	-	一个非空的逗号分隔的simple-type-specifier、elaborated-type-specifier和typename-specifier列表，每个说明符后面可以跟省略号（...）

描述
1) 将一个函数或多个函数指定为此类的友元。
class Y
{
    int data; // private member
 
    // the non-member function operator<< will have access to Y's private members
    friend std::ostream& operator<<(std::ostream& out, const Y& o);
    friend char* X::foo(int); // members of other classes can be friends too
    friend X::X(char), X::~X(); // constructors and destructors can be friends
};
 
// friend declaration does not declare a member function
// this operator<< still needs to be defined, as a non-member
std::ostream& operator<<(std::ostream& out, const Y& y)
{
    return out << y.data; // can access private member Y::data
}
2) （仅允许在非局部类定义中使用）定义一个非成员函数，并同时使其成为此类的友元。这样的非成员函数总是inline，除非它附加到命名模块(C++20起)。
class X
{
    int a;
 
    friend void friend_set(X& p, int i)
    {
        p.a = i; // this is a non-member function
    }
public:
    void member_set(int i)
    {
        a = i; // this is a member function
    }
};
3,4) 将一个类指定为此类的友元。这意味着友元的成员声明和定义可以访问此类的私有和保护成员，并且友元可以从此类的私有和保护成员继承。
3) 该类由elaborated-type-specifier命名。在此友元声明中使用的类名不需要事先声明。
4) 该类由simple-type-specifier或typename-specifier命名。如果命名的类型不是类类型，则此友元声明被忽略。此声明不会前向声明新类型。
5) 将friend-type-specifier-list中的所有类指定为此类的友元。这意味着友元的成员声明和定义可以访问此类的私有和保护成员，并且友元可以从此类的私有和保护成员继承。如果命名的类型不是类类型，则在此友元声明中被忽略。
 如果说明符后面没有省略号，则friend-type-specifier-list中的每个说明符都命名一个类，否则应用包扩展。
class Y {};
 
class A
{
    int data; // private data member
 
    class B {}; // private nested type
 
    enum { a = 100 }; // private enumerator
 
    friend class X; // friend class forward declaration (elaborated class specifier)
    friend Y; // friend class declaration (simple type specifier) (since C++11)
 
    // the two friend declarations above can be merged since C++26:
    // friend class X, Y;
};
 
class X : A::B // OK: A::B accessible to friend
{
    A::B mx; // OK: A::B accessible to member of friend
 
    class Y
    {
        A::B my; // OK: A::B accessible to nested member of friend
    };
 
    int v[A::a]; // OK: A::a accessible to member of friend
};
模板友元

函数模板和类模板声明都可以带有friend说明符出现在任何非局部类或类模板中（尽管只有函数模板可以在授予友元关系的类或类模板中定义）。在这种情况下，模板的每个特化都成为友元，无论是隐式实例化、部分特化还是显式特化。

class A
{
    template<typename T>
    friend class B; // every B<T> is a friend of A
 
    template<typename T>
    friend void f(T) {} // every f<T> is a friend of A
};
友元声明不能引用部分特化，但可以引用完全特化

template<class T>
class A {};      // primary
 
template<class T>
class A<T*> {};  // partial
 
template<>
class A<int> {}; // full
 
class X
{
    template<class T>
    friend class A<T*>;  // Error
 
    friend class A<int>; // OK
};

当友元声明引用函数模板的完全特化时，不能使用关键字inline、constexpr(C++11起)、consteval(C++20起)和默认参数

template<class T>
void f(int);
 
template<>
void f<int>(int);
 
class X
{
    friend void f<int>(int x = 1); // error: default args not allowed
};
模板友元声明可以命名类模板 A 的成员，该成员可以是成员函数或成员类型（该类型必须使用详述类型说明符）。只有当其嵌套名称说明符中的最后一个组件（最后一个::左侧的名称）是一个简单模板 ID（模板名后跟尖括号中的参数列表），并且该简单模板 ID 命名了类模板时，此类声明才是格式良好的。此类模板友元声明的模板参数必须可以从简单模板 ID 推导出来。

在这种情况下，A 的任何特化或 A 的部分特化的成员都成为友元。这不涉及实例化主模板 A 或 A 的部分特化：唯一的条件是，从该特化推导 A 的模板参数成功，并且将推导的模板参数代入友元声明会产生一个声明，该声明将是该特化成员的有效重新声明

// primary template
template<class T>
struct A
{ 
    struct B {};
 
    void f();
 
    struct D { void g(); };
 
    T h();
 
    template<T U>
    T i();
};
 
// full specialization
template<>
struct A<int>
{
    struct B {};
 
    int f();
 
    struct D { void g(); };
 
    template<int U>
    int i();
};
 
// another full specialization
template<>
struct A<float*>
{
    int *h();
};
 
// the non-template class granting friendship to members of class template A
class X
{
    template<class T>
    friend struct A<T>::B; // all A<T>::B are friends, including A<int>::B
 
    template<class T>
    friend void A<T>::f(); // A<int>::f() is not a friend because its signature
                           // does not match, but e.g. A<char>::f() is a friend
 
//  template<class T>
//  friend void A<T>::D::g(); // ill-formed, the last part of the nested-name-specifier,
//                            // D in A<T>::D::, is not simple-template-id
 
    template<class T>
    friend int* A<T*>::h(); // all A<T*>::h are friends:
                            // A<float*>::h(), A<int*>::h(), etc
 
    template<class T> 
    template<T U>       // all instantiations of A<T>::i() and A<int>::i() are friends, 
    friend T A<T>::i(); // and thereby all specializations of those function templates
};
只有当声明是定义，并且在该翻译单元中没有该函数模板的其他声明时，才允许在模板友元声明上使用默认模板参数。

(C++11 起)
模板友元运算符
模板友元的一个常见用例是声明作用于类模板的非成员运算符重载，例如operator<<(std::ostream&, const Foo<T>&)，用于某个用户定义的Foo<T>。

这样的运算符可以在类体内定义，其效果是为每个T生成一个单独的非模板operator<<，并使该非模板operator<<成为其Foo<T>的友元

运行此代码
#include <iostream>
 
template<typename T>
class Foo
{
public:
    Foo(const T& val) : data(val) {}
private:
    T data;
 
    // generates a non-template operator<< for this T
    friend std::ostream& operator<<(std::ostream& os, const Foo& obj)
    {
        return os << obj.data;
    }
};
 
int main()
{
    Foo<double> obj(1.23);
    std::cout << obj << '\n';
}
输出

1.23
或者函数模板必须在类体之前声明为模板，在这种情况下，Foo<T>内的友元声明可以引用其T的operator<<的完全特化

运行此代码
#include <iostream>
 
template<typename T>
class Foo; // forward declare to make function declaration possible
 
template<typename T> // declaration
std::ostream& operator<<(std::ostream&, const Foo<T>&);
 
template<typename T>
class Foo
{
public:
    Foo(const T& val) : data(val) {}
private:
    T data;
 
    // refers to a full specialization for this particular T 
    friend std::ostream& operator<< <> (std::ostream&, const Foo&);
 
    // note: this relies on template argument deduction in declarations
    // can also specify the template argument with operator<< <T>"
};
 
// definition
template<typename T>
std::ostream& operator<<(std::ostream& os, const Foo<T>& obj)
{
    return os << obj.data;
}
 
int main()
{
    Foo<double> obj(1.23);
    std::cout << obj << '\n';
}

链接
友元声明中不允许使用存储类说明符。

如果函数或函数模板首次在友元声明中声明和定义，并且外围类在导出声明中定义，则其名称具有与外围类名称相同的链接。

(C++20 起)
如果(C++20前)否则，如果(C++20起)函数或函数模板在友元声明中声明，并且相应的非友元声明是可达的，则该名称具有由该先前声明确定的链接。

否则，友元声明引入的名称的链接按常规确定。

注意
友元关系不是传递的（你的友元的朋友不是你的友元）。

友元关系不是继承的（你的友元的子类不是你的友元，你的友元也不是你的子类的友元）。

访问说明符对友元声明的含义没有影响（它们可以出现在private:或public:部分，没有区别）。


友元类声明不能定义新类（friend class X {};是错误的）。

当局部类将非限定函数或类声明为友元时，只查找最内层非类作用域中的函数和类，而不是全局函数

class F {};
 
int f();
 
int main()
{
    extern int g();
 
    class Local // Local class in the main() function
    {
        friend int f(); // Error, no such function declared in main()
        friend int g(); // OK, there is a declaration for g in main()
        friend class F; // friends a local F (defined later)
        friend class ::F; // friends the global F
    };
 
    class F {}; // local F
}
在类或类模板X中的友元声明中首次声明的名称成为X最内层外围命名空间的成员，但在命名空间作用域提供匹配声明之前，该名称对于查找（除了考虑X的依赖于参数的查找）是不可见的——详见命名空间。

功能测试宏	值	标准	特性
__cpp_variadic_friend	202403L	(C++26)	变长友元声明
关键字
friend

示例

流插入和提取运算符通常声明为非成员友元

运行此代码
#include <iostream>
#include <sstream>
 
class MyClass
{
    int i;                   // friends have access to non-public, non-static
    static inline int id{6}; // and static (possibly inline) members
 
    friend std::ostream& operator<<(std::ostream& out, const MyClass&);
    friend std::istream& operator>>(std::istream& in, MyClass&);
    friend void change_id(int);
public:
    MyClass(int i = 0) : i(i) {}
};
 
std::ostream& operator<<(std::ostream& out, const MyClass& mc)
{
    return out << "MyClass::id = " << MyClass::id << "; i = " << mc.i;
}
 
std::istream& operator>>(std::istream& in, MyClass& mc)
{
    return in >> mc.i;
}
 
void change_id(int id) { MyClass::id = id; }
 
int main()
{
    MyClass mc(7);
    std::cout << mc << '\n';
//  mc.i = 333*2;  // error: i is a private member
    std::istringstream("100") >> mc;
    std::cout << mc << '\n';
//  MyClass::id = 222*3;  // error: id is a private member
    change_id(9);
    std::cout << mc << '\n';
}
输出

MyClass::id = 6; i = 7
MyClass::id = 6; i = 100
MyClass::id = 9; i = 100













~~运算符重载

 C++ C++ 语言 表达式 
为用户定义类型的操作数定制 C++ 运算符。

语法
运算符函数 是具有特殊函数名称的函数

operator op	(1)	
operator new
operator new []	(2)	
operator delete
operator delete []	(3)	
operator co_await	(4)	(C++20 起)
op	-	以下任一运算符：+ - * / % ^ & | ~ ! = < > += -= *= /= %= ^= &= |= << >> >>= <<= == != <= >= <=>(C++20起) && || ++ -- , ->* -> () []
1) 重载的标点符号运算符。
2) 分配函数。
3) 解除分配函数。
4) 重载的 co_await 运算符，用于 co_await 表达式。
非标点运算符的行为在其各自页面中描述。除非另有说明，本页面中的其余描述不适用于这些函数。

解释

当运算符出现在表达式中，并且其操作数至少有一个是类类型或枚举类型时，则使用重载决议来确定要调用的用户定义函数，该函数是从所有签名匹配以下条件的函数中选择的

表达式	作为成员函数	作为非成员函数	示例
@a	(a).operator@ ( )	operator@ (a)	!std::cin 调用 std::cin.operator!()
a@b	(a).operator@ (b)	operator@ (a, b)	std::cout << 42 调用 std::cout.operator<<(42)
a=b	(a).operator= (b)	不能为非成员	给定 std::string s;，s = "abc"; 调用 s.operator=("abc")
a(b...)	(a).operator()(b...)	不能为非成员	给定 std::random_device r;，auto n = r(); 调用 r.operator()()
a[b...]	(a).operator[](b...)	不能为非成员	给定 std::map<int, int> m;，m[1] = 2; 调用 m.operator[](1)
a->	(a).operator->( )	不能为非成员	给定 std::unique_ptr<S> p;，p->bar() 调用 p.operator->()
a@	(a).operator@ (0)	operator@ (a, 0)	给定 std::vector<int>::iterator i;，i++ 调用 i.operator++(0)
在此表格中，@ 是一个占位符，表示所有匹配的运算符：@a 中的所有前缀运算符，a@ 中除 -> 之外的所有后缀运算符，a@b 中除 = 之外的所有中缀运算符。

此外，对于比较运算符 ==、!=、<、>、<=、>=、<=>，重载决议还会考虑重写的候选 operator== 或 operator<=>。

(C++20 起)
重载运算符（而非内置运算符）可以使用函数表示法调用

std::string str = "Hello, ";
str.operator+=("world");                      // same as str += "world";
operator<<(operator<<(std::cout, str), '\n'); // same as std::cout << str << '\n';
                                              // (since C++17) except for sequencing
静态重载运算符
作为成员函数的重载运算符可以声明为静态。然而，这只允许用于 operator() 和 operator[]。

此类运算符可以使用函数表示法调用。然而，当这些运算符出现在表达式中时，它们仍然需要一个类类型的对象。

struct SwapThem
{
    template<typename T>
    static void operator()(T& lhs, T& rhs) 
    {
        std::ranges::swap(lhs, rhs);
    }
 
    template<typename T>
    static void operator[](T& lhs, T& rhs)
    {
        std::ranges::swap(lhs, rhs);
    } 
};
inline constexpr SwapThem swap_them{};
 
void foo()
{
    int a = 1, b = 2;
 
    swap_them(a, b); // OK
    swap_them[a, b]; // OK
 
    SwapThem{}(a, b); // OK
    SwapThem{}[a, b]; // OK
 
    SwapThem::operator()(a, b); // OK
    SwapThem::operator[](a, b); // OK
 
    SwapThem(a, b); // error, invalid construction
    SwapThem[a, b]; // error
}
(C++23 起)
限制
运算符函数必须至少有一个函数参数或隐式对象参数，其类型为类、对类的引用、枚举或对枚举的引用。
运算符 ::（作用域解析）、.（成员访问）、.*（通过成员指针访问成员）和 ?:（三元条件）不能被重载。
不能创建新的运算符，例如 **、<> 或 &|。
不可能改变运算符的优先级、分组或操作数数量。
运算符 -> 的重载必须返回原始指针，或返回一个对象（通过引用或值），该对象的 -> 运算符又被重载。
运算符 && 和 || 的重载会失去短路求值特性。
当 &&、|| 和 , 被重载时，它们会失去特殊的序列化特性，即使不使用函数调用表示法，它们也表现得像常规函数调用。
(C++17 前)
规范实现
除了上述限制之外，语言对重载运算符的行为或返回类型（它不参与重载决议）没有其他限制，但通常，重载运算符预期尽可能与内置运算符的行为相似：operator+ 预期是加法，而不是乘法；operator= 预期是赋值等等。相关运算符预期行为相似（operator+ 和 operator+= 执行相同的加法类操作）。返回类型受限于运算符预期使用的表达式：例如，赋值运算符通过引用返回，以使 a = b = c = d 成为可能，因为内置运算符允许这样做。

常用的重载运算符具有以下典型的规范形式：[1]

赋值运算符
赋值运算符 operator= 具有特殊属性：详细信息请参见复制赋值和移动赋值。

规范的复制赋值运算符预期对自赋值是安全的，并通过引用返回左值

// copy assignment
T& operator=(const T& other)
{
    // Guard self assignment
    if (this == &other)
        return *this;
 
    // assume *this manages a reusable resource, such as a heap-allocated buffer mArray
    if (size != other.size)           // resource in *this cannot be reused
    {
        temp = new int[other.size];   // allocate resource, if throws, do nothing
        delete[] mArray;              // release resource in *this
        mArray = temp;
        size = other.size;
    }
 
    std::copy(other.mArray, other.mArray + other.size, mArray);
    return *this;
}
规范的移动赋值预期将移动源对象置于有效状态（即，类不变量保持不变的状态），并且在自赋值时不做任何事情或至少将对象置于有效状态，并通过对非 const 的引用返回左值，并且为 noexcept。

// move assignment
T& operator=(T&& other) noexcept
{
    // Guard self assignment
    if (this == &other)
        return *this; // delete[]/size=0 would also be ok
 
    delete[] mArray;                               // release resource in *this
    mArray = std::exchange(other.mArray, nullptr); // leave other in valid state
    size = std::exchange(other.size, 0);
    return *this;
}
(C++11 起)
在复制赋值不能从资源重用中受益（它不管理堆分配的数组，并且没有（可能是传递的）成员这样做，例如 std::vector 或 std::string 成员）的情况下，有一种流行的便捷简写：复制并交换赋值运算符，它通过值接收其参数（因此根据参数的值类别，既可作为复制赋值又可作为移动赋值），与参数交换，然后让析构函数清理它。

// copy assignment (copy-and-swap idiom)
T& T::operator=(T other) noexcept // call copy or move constructor to construct other
{
    std::swap(size, other.size); // exchange resources between *this and other
    std::swap(mArray, other.mArray);
    return *this;
} // destructor of other is called to release the resources formerly managed by *this

此形式自动提供强异常保证，但禁止资源重用。

流提取和插入
接受 std::istream& 或 std::ostream& 作为左操作数的 operator>> 和 operator<< 的重载称为插入和提取运算符。由于它们将用户定义类型作为右操作数（a @ b 中的 b），因此它们必须作为非成员函数实现。

std::ostream& operator<<(std::ostream& os, const T& obj)
{
    // write obj to stream
    return os;
}
 
std::istream& operator>>(std::istream& is, T& obj)
{
    // read obj from stream
    if (/* T could not be constructed */)
        is.setstate(std::ios::failbit);
    return is;
}
这些运算符有时作为友元函数实现。

函数调用运算符
当用户定义的类重载函数调用运算符 operator() 时，它成为一个函数对象类型。

这种类型的对象可以在函数调用表达式中使用

// An object of this type represents a linear function of one variable a * x + b.
struct Linear
{
    double a, b;
 
    double operator()(double x) const
    {
        return a * x + b;
    }
};
 
int main()
{
    Linear f{2, 1};  // Represents function 2x + 1.
    Linear g{-1, 0}; // Represents function -x.
    // f and g are objects that can be used like a function.
 
    double f_0 = f(0);
    double f_1 = f(1);
 
    double g_0 = g(0);
}

许多标准库算法接受函数对象以自定义行为。 operator() 没有特别值得注意的规范形式，但为了说明用法

运行此代码
#include <algorithm>
#include <iostream>
#include <vector>
 
struct Sum
{
    int sum = 0;
    void operator()(int n) { sum += n; }
};
 
int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    Sum s = std::for_each(v.begin(), v.end(), Sum());
    std::cout << "The sum is " << s.sum << '\n';
}

输出

The sum is 15
自增和自减
当后缀自增或自减运算符出现在表达式中时，相应的用户定义函数（operator++ 或 operator--）将以整数参数 ​0​ 调用。通常，它被声明为 T operator++(int) 或 T operator--(int)，其中参数被忽略。后缀自增和自减运算符通常通过前缀版本实现

struct X
{
    // prefix increment
    X& operator++()
    {
        // actual increment takes place here
        return *this; // return new value by reference
    }
 
    // postfix increment
    X operator++(int)
    {
        X old = *this; // copy old value
        operator++();  // prefix increment
        return old;    // return old value
    }
 
    // prefix decrement
    X& operator--()
    {
        // actual decrement takes place here
        return *this; // return new value by reference
    }
 
    // postfix decrement
    X operator--(int)
    {
        X old = *this; // copy old value
        operator--();  // prefix decrement
        return old;    // return old value
    }
};
尽管前缀自增和自减运算符的规范实现通过引用返回，但与任何运算符重载一样，返回类型是用户定义的；例如，std::atomic 的这些运算符的重载通过值返回。

二元算术运算符
二元运算符通常实现为非成员函数以保持对称性（例如，当添加一个复数和一个整数时，如果 operator+ 是复数类型的成员函数，那么只有 complex + integer 可以编译，而 integer + complex 则不能）。因为每个二元算术运算符都存在一个相应的复合赋值运算符，二元运算符的规范形式是通过其复合赋值来实现的

class X
{
public:
    X& operator+=(const X& rhs) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        /* addition of rhs to *this takes place here */
        return *this; // return the result by reference
    }
 
    // friends defined inside class body are inline and are hidden from non-ADL lookup
    friend X operator+(X lhs,        // passing lhs by value helps optimize chained a+b+c
                       const X& rhs) // otherwise, both parameters may be const references
    {
        lhs += rhs; // reuse compound assignment
        return lhs; // return the result by value (uses move constructor)
    }
};
比较运算符
标准库算法，例如 std::sort，以及容器，例如 std::set，默认要求为用户提供的类型定义 operator<，并要求它实现严格弱序（从而满足比较要求）。为结构实现严格弱序的惯用方法是使用 std::tie 提供的字典序比较

struct Record
{
    std::string name;
    unsigned int floor;
    double weight;
 
    friend bool operator<(const Record& l, const Record& r)
    {
        return std::tie(l.name, l.floor, l.weight)
             < std::tie(r.name, r.floor, r.weight); // keep the same order
    }
};
通常，一旦提供了 operator<，其他关系运算符都会通过 operator< 来实现。

inline bool operator< (const X& lhs, const X& rhs) { /* do actual comparison */ }
inline bool operator> (const X& lhs, const X& rhs) { return rhs < lhs; }
inline bool operator<=(const X& lhs, const X& rhs) { return !(lhs > rhs); }
inline bool operator>=(const X& lhs, const X& rhs) { return !(lhs < rhs); }
同样，不相等运算符通常通过 operator== 实现。

inline bool operator==(const X& lhs, const X& rhs) { /* do actual comparison */ }
inline bool operator!=(const X& lhs, const X& rhs) { return !(lhs == rhs); }
当提供了三路比较（例如 std::memcmp 或 std::string::compare）时，所有六个双向比较运算符都可以通过它来表达

inline bool operator==(const X& lhs, const X& rhs) { return cmp(lhs,rhs) == 0; }
inline bool operator!=(const X& lhs, const X& rhs) { return cmp(lhs,rhs) != 0; }
inline bool operator< (const X& lhs, const X& rhs) { return cmp(lhs,rhs) <  0; }
inline bool operator> (const X& lhs, const X& rhs) { return cmp(lhs,rhs) >  0; }
inline bool operator<=(const X& lhs, const X& rhs) { return cmp(lhs,rhs) <= 0; }
inline bool operator>=(const X& lhs, const X& rhs) { return cmp(lhs,rhs) >= 0; }
数组下标运算符
提供数组式访问并允许读写的用户定义类通常为 operator[] 定义两个重载：const 和非 const 变体

struct T
{
          value_t& operator[](std::size_t idx)       { return mVector[idx]; }
    const value_t& operator[](std::size_t idx) const { return mVector[idx]; }
};
或者，它们可以表示为使用显式对象参数的单个成员函数模板

struct T
{
    decltype(auto) operator[](this auto& self, std::size_t idx) 
    { 
        return self.mVector[idx]; 
    }
};
(C++23 起)
如果已知值类型为标量类型，则 const 变体应按值返回。

如果不需要或不可能直接访问容器的元素，或者需要区分左值 c[i] = v; 和右值 v = c[i]; 的用法，operator[] 可以返回一个代理。例如参见 std::bitset::operator[]。

operator[] 只能带一个下标。为了提供多维数组访问语义，例如实现 3D 数组访问 a[i][j][k] = x;，operator[] 必须返回一个 2D 平面的引用，该平面必须有自己的 operator[]，它返回一个 1D 行的引用，该行必须有 operator[]，它返回元素的引用。为了避免这种复杂性，一些库选择重载 operator()，以便 3D 访问表达式具有类似 Fortran 的语法 a(i, j, k) = x;。

(直至 C++23)
operator[] 可以接受任意数量的下标。例如，一个 3D 数组类的 operator[]，声明为 T& operator[](std::size_t x, std::size_t y, std::size_t z);，可以直接访问元素。

运行此代码
#include <array>
#include <cassert>
#include <iostream>
 
template<typename T, std::size_t Z, std::size_t Y, std::size_t X>
struct Array3d
{
    std::array<T, X * Y * Z> m{};
 
    constexpr T& operator[](std::size_t z, std::size_t y, std::size_t x) // C++23
    {
        assert(x < X and y < Y and z < Z);
        return m[z * Y * X + y * X + x];
    }
};
 
int main()
{
    Array3d<int, 4, 3, 2> v;
    v[3, 2, 1] = 42;
    std::cout << "v[3, 2, 1] = " << v[3, 2, 1] << '\n';
}
输出

v[3, 2, 1] = 42
(C++23 起)
位算术运算符
实现位掩码类型要求的用户定义类和枚举需要重载位算术运算符 operator&、operator|、operator^、operator~、operator&=、operator|= 和 operator^=，并且可以选择重载移位运算符 operator<< operator>>、operator>>= 和 operator<<=。规范实现通常遵循上述二元算术运算符的模式。

布尔非运算符

运算符 operator! 通常由旨在用于布尔上下文的用户定义类重载。此类类还提供一个用户定义的转换为布尔类型的函数（参见 std::basic_ios 的标准库示例），operator! 的预期行为是返回与 operator bool 相反的值。

(C++11 前)
由于内置运算符 ! 执行到 bool 的上下文转换，旨在用于布尔上下文的用户定义类可以只提供 operator bool 而无需重载 operator!。

(C++11 起)
不常重载的运算符
以下运算符很少重载

取址运算符，operator&。如果一元 & 应用于不完整类型的左值，并且完整类型声明了重载的 operator&，则未指定该运算符是具有内置含义还是调用运算符函数。因为此运算符可以重载，通用库使用 std::addressof 获取用户定义类型对象的地址。规范重载 operator& 最著名的例子是 Microsoft 类 CComPtrBase。该运算符在 EDSL 中的使用示例可以在 boost.spirit 中找到。
布尔逻辑运算符 operator&& 和 operator||。与内置版本不同，重载无法实现短路求值。也与内置版本不同，它们不会在右操作数之前对左操作数进行排序。(C++17 前) 在标准库中，这些运算符仅为 std::valarray 重载。
逗号运算符，operator,。与内置版本不同，重载不会在右操作数之前对其左操作数进行排序。(C++17 前) 由于此运算符可以重载，通用库使用诸如 a, void(), b 而非 a, b 来对用户定义类型的表达式执行排序。Boost 库在 boost.assign、boost.spirit 和其他库中使用了 operator,。数据库访问库 SOCI 也重载了 operator,。
通过成员指针进行成员访问 operator->*。重载此运算符没有特定的缺点，但在实践中很少使用。有人建议它可以作为智能指针接口的一部分，实际上，boost.phoenix 中的 actor 就以这种方式使用它。在 EDSLs（例如 cpp.react）中更常见。
注意








~~继承构造函数
如果 using-declaration 指的是正在定义的类的直接基类的构造函数（例如 using Base::Base;），那么当初始化派生类时，该基类的所有构造函数（忽略成员访问）都将对重载决议可见。

如果重载决议选择了一个继承的构造函数，那么当它用于构造相应基类的对象时，它是可访问的：引入它的 using 声明的可访问性被忽略。

如果在初始化这样的派生类对象时，重载决议选择了一个继承的构造函数，那么继承该构造函数的 Base 子对象将使用该继承的构造函数进行初始化，而 Derived 的所有其他基和成员都将像默认构造函数那样进行初始化（如果提供了默认成员初始化器，则使用它们，否则进行默认初始化）。整个初始化被视为一个单一的函数调用：继承构造函数参数的初始化在派生对象的任何基或成员的初始化之前进行。

struct B1 { B1(int, ...) {} };
struct B2 { B2(double)   {} };
 
int get();
 
struct D1 : B1
{
    using B1::B1; // inherits B1(int, ...)
    int x;
    int y = get();
};
 
void test()
{
    D1 d(2, 3, 4); // OK: B1 is initialized by calling B1(2, 3, 4),
                   // then d.x is default-initialized (no initialization is performed),
                   // then d.y is initialized by calling get()
 
    D1 e;          // Error: D1 has no default constructor
}
 
struct D2 : B2
{
    using B2::B2; // inherits B2(double)
    B1 b;
};
 
D2 f(1.0); // error: B1 has no default constructor
struct W { W(int); };
 
struct X : virtual W
{
    using W::W; // inherits W(int)
    X() = delete;
};
 
struct Y : X
{
    using X::X;
};
 
struct Z : Y, virtual W
{
    using Y::Y;
};
 
Z z(0); // OK: initialization of Y does not invoke default constructor of X
如果 `Base` 基类子对象不作为 `Derived` 对象的一部分进行初始化（即，`Base` 是 `Derived` 的虚基类，且 `Derived` 对象不是最派生对象），则会省略对继承构造函数的调用，包括任何参数的求值。


struct V
{
    V() = default;
    V(int);
};
 
struct Q { Q(); };
 
struct A : virtual V, Q
{
    using V::V;
    A() = delete;
};
 
int bar() { return 42; }
 
struct B : A
{
    B() : A(bar()) {} // OK
};
 
struct C : B {};
 
void foo()
{
    C c; // “bar” is not invoked, because the V subobject
         // is not initialized as part of B
         // (the V subobject is initialized as part of C,
         //  because “c” is the most derived object)
}
如果构造函数是从类型为 Base 的多个基类子对象继承的，则程序是病态的，类似于多重继承的非静态成员函数。


struct A { A(int); };
struct B : A { using A::A; };
struct C1 : B { using B::B; };
struct C2 : B { using B::B; };
 
struct D1 : C1, C2
{
    using C1::C1;
    using C2::C2;
};
D1 d1(0); // ill-formed: constructor inherited from different B base subobjects
 
struct V1 : virtual B { using B::B; };
struct V2 : virtual B { using B::B; };
 
struct D2 : V1, V2
{
    using V1::V1;
    using V2::V2;
};
D2 d2(0); // OK: there is only one B subobject.
          // This initializes the virtual B base class,
          //   which initializes the A base class
          // then initializes the V1 and V2 base classes
          //   as if by a defaulted default constructor
与任何其他非静态成员函数的 using 声明一样，如果继承的构造函数与 Derived 的某个构造函数签名匹配，则它会被 Derived 中的版本隐藏起来。如果 Base 的某个继承构造函数恰好具有与 Derived 的拷贝/移动构造函数匹配的签名，则它不会阻止 Derived 拷贝/移动构造函数的隐式生成（然后，它会隐藏继承的版本，类似于 using operator=）。


struct B1 { B1(int); };
struct B2 { B2(int); };
 
struct D2 : B1, B2
{
    using B1::B1;
    using B2::B2;
 
    D2(int); // OK: D2::D2(int) hides both B1::B1(int) and B2::B2(int)
};
D2 d2(0);    // calls D2::D2(int)
在一个模板类中，如果一个 using 声明引用了一个依赖名，则如果 嵌套名说明符 的末尾名称与 非限定 ID 相同，则它被认为是命名一个构造函数。


template<class T>
struct A : T
{
    using T::T; // OK, inherits constructors of T
};
 
template<class T, class U>
struct B : T, A<U>
{
    using A<U>::A; // OK, inherits constructors of A<U>
    using T::A;    // does not inherit constructor of T
                   // even though T may be a specialization of A<>
};
(C++11 起)


引入有作用域的枚举器

除了其他命名空间的成员和基类的成员，using 声明还可以将枚举的枚举器引入命名空间、块和类作用域。


using 声明也可以与无作用域枚举器一起使用。


enum class button { up, down };
 
struct S
{
    using button::up;
    button b = up; // OK
};
 
using button::down;
constexpr button non_up = down; // OK
 
constexpr auto get_button(bool is_up)
{
    using button::up, button::down;
    return is_up ? up : down; // OK
}
 
enum unscoped { val };
using unscoped::val; // OK, though needless
(C++20 起)
注意

只有在 using 声明中明确提及的名称才会被转移到声明性作用域：特别地，当枚举类型名称被 using 声明时，枚举器不会被转移。


using 声明不能引用命名空间、有作用域的枚举器(C++20 前)、基类的析构函数或用户定义转换函数的成员模板特化。


using 声明不能命名成员模板特化（语法不允许 template-id）


struct B
{
    template<class T>
    void f();
};
 
struct D : B
{
    using B::f;      // OK: names a template
//  using B::f<int>; // Error: names a template specialization
 
    void g() { f<int>(); }
};
using 声明也不能用于将依赖成员模板的名称作为 template-name 引入（不允许对依赖名使用 template 消歧符）。


template<class X>
struct B
{
    template<class T>
    void f(T);
};
 
template<class Y>
struct D : B<Y>
{
//  using B<Y>::template f; // Error: disambiguator not allowed
    using B<Y>::f;          // compiles, but f is not a template-name
 
    void g()
    {
//      f<int>(0);          // Error: f is not known to be a template name,
                            // so < does not start a template argument list
        f(0);               // OK
    }   
};
如果一个 using 声明将基类赋值运算符引入派生类，且其签名恰好与派生类的拷贝赋值或移动赋值运算符匹配，则该运算符会被派生类的隐式声明的拷贝/移动赋值运算符隐藏。同样适用于继承基类构造函数且恰好与派生类拷贝/移动构造函数匹配的 using 声明(C++11 起)。

继承构造函数的语义被针对 C++11 的缺陷报告追溯修改。此前，继承构造函数声明会在派生类中注入一组合成的构造函数声明，这导致冗余的参数拷贝/移动，与某些 SFINAE 形式存在问题，并且在某些情况下在主要 ABI 上无法实现。旧编译器可能仍实现以前的语义。


旧的继承构造函数语义

如果 using-declaration 指的是正在定义的类的直接基类的构造函数（例如 using Base::Base;），那么该基类的构造函数将根据以下规则被继承：


1) 一组候选继承构造函数由以下组成：

a) 基类的所有非模板构造函数（如果存在省略号参数，则省略）(C++14 起)
b) 对于每个带有默认参数或省略号参数的构造函数，通过逐个删除省略号和参数列表末尾的默认参数而形成的所有构造函数签名。
c) 基类的所有构造函数模板（如果存在省略号参数，则省略）(C++14 起)
d) 对于每个带有默认参数或省略号的构造函数模板，通过逐个删除省略号和参数列表末尾的默认参数而形成的所有构造函数签名。
2) 所有不是默认构造函数或拷贝/移动构造函数，且其签名不匹配派生类中用户定义构造函数的候选继承构造函数，都会在派生类中隐式声明。默认参数不被继承。
struct B1
{
    B1(int);
};
 
struct D1 : B1
{
    using B1::B1;
 
    // The set of candidate inherited constructors is 
    // 1. B1(const B1&)
    // 2. B1(B1&&)
    // 3. B1(int)
 
    // D1 has the following constructors:
    // 1. D1() = delete
    // 2. D1(const D1&) 
    // 3. D1(D1&&)
    // 4. D1(int) <- inherited
};
 
struct B2
{
    B2(int = 13, int = 42);
};
 
struct D2 : B2
{
    using B2::B2;
 
    // The set of candidate inherited constructors is
    // 1. B2(const B2&)
    // 2. B2(B2&&)
    // 3. B2(int = 13, int = 42)
    // 4. B2(int = 13)
    // 5. B2()
 
    // D2 has the following constructors:
    // 1. D2()
    // 2. D2(const D2&)
    // 3. D2(D2&&)
    // 4. D2(int, int) <- inherited
    // 5. D2(int) <- inherited
};
继承的构造函数等价于用户定义的构造函数，其拥有一个空函数体和一个由单个 嵌套名说明符 组成的成员初始化列表，该列表将其所有参数转发给基类构造函数。

它拥有与相应基构造函数相同的访问权限。如果用户定义的构造函数满足 constexpr 构造函数要求，它就是 constexpr 的。如果相应基构造函数被删除或默认的默认构造函数将被删除（除了构造正在继承其构造函数的基类不算在内），则它被删除。继承构造函数不能显式实例化或显式特化。

如果两个 using 声明继承了具有相同签名的构造函数（来自两个直接基类），则程序是病态的。

继承构造函数模板不应被显式实例化或显式特化。

(C++11 起)

using 声明中的包扩展使得无需递归即可形成一个暴露可变基类重载成员的类。

template<typename... Ts>
struct Overloader : Ts...
{
    using Ts::operator()...; // exposes operator() from every base
};
 
template<typename... T>
Overloader(T...) -> Overloader<T...>; // C++17 deduction guide, not needed in C++20
 
int main()
{
    auto o = Overloader{ [] (auto const& a) {std::cout << a;},
                         [] (float f) {std::cout << std::setprecision(3) << f;} };
}







~~virtual 函数说明符
 C++ C++ 语言 类 
virtual 说明符指定非静态成员函数是“虚”的并支持动态分派。它只能出现在非静态成员函数初始声明的decl-specifier-seq中（即在类定义中声明时）。

解释
虚函数是成员函数，其行为可以在派生类中被重写。与非虚函数不同，即使在编译时没有关于类的实际类型的信息，重写行为也会保留。也就是说，如果使用指向基类的指针或引用来处理派生类，则对重写的虚函数的调用将调用派生类中定义的行为。这种函数调用被称为“虚函数调用”或“虚调用”。如果使用限定名称查找选择函数（即，如果函数名称出现在作用域解析运算符::的右侧），则虚函数调用被抑制。

运行此代码
#include <iostream>
 
struct Base
{
    virtual void f()
    {
        std::cout << "base\n";
    }
};
 
struct Derived : Base
{
    void f() override // 'override' is optional
    {
        std::cout << "derived\n";
    }
};
 
int main()
{
    Base b;
    Derived d;
 
    // virtual function call through reference
    Base& br = b; // the type of br is Base&
    Base& dr = d; // the type of dr is Base& as well
    br.f(); // prints "base"
    dr.f(); // prints "derived"
 
    // virtual function call through pointer
    Base* bp = &b; // the type of bp is Base*
    Base* dp = &d; // the type of dp is Base* as well
    bp->f(); // prints "base"
    dp->f(); // prints "derived"
 
    // non-virtual function call
    br.Base::f(); // prints "base"
    dr.Base::f(); // prints "base"
}
详情

如果在类Base中某个成员函数vf被声明为virtual，并且某个类Derived（直接或间接派生自Base）有一个成员函数声明，该函数具有相同的

名称
参数类型列表（但不包括返回类型）
cv-限定符
ref-限定符
那么类Derived中的这个函数也是“虚”的（无论其声明中是否使用关键字virtual），并且“重写”Base::vf（无论其声明中是否使用关键字override）。

Base::vf不需要可访问或可见才能被重写。（Base::vf可以声明为private，或者Base可以使用private继承。Derived的基类中任何同名成员（其继承自Base）都不影响重写判断，即使它们会在名称查找期间隐藏Base::vf。）

class B
{
    virtual void do_f(); // private member
public:
    void f() { do_f(); } // public interface
};
 
struct D : public B
{
    void do_f() override; // overrides B::do_f
};
 
int main()
{
    D d;
    B* bp = &d;
    bp->f(); // internally calls D::do_f();
}
对于每个虚函数，都有“最终重写者”，在进行虚函数调用时执行。基类Base的虚成员函数vf是最终重写者，除非派生类声明或继承（通过多重继承）另一个重写vf的函数。


struct A { virtual void f(); };     // A::f is virtual
struct B : A { void f(); };         // B::f overrides A::f in B
struct C : virtual B { void f(); }; // C::f overrides A::f in C
 
struct D : virtual B {}; // D does not introduce an overrider, B::f is final in D
 
struct E : C, D          // E does not introduce an overrider, C::f is final in E
{
    using A::f; // not a function declaration, just makes A::f visible to lookup
};
 
int main()
{
    E e;
    e.f();    // virtual call calls C::f, the final overrider in e
    e.E::f(); // non-virtual call calls A::f, which is visible in E
}
如果一个函数有多个最终重写者，则程序格式错误。


struct A
{
    virtual void f();
};
 
struct VB1 : virtual A
{
    void f(); // overrides A::f
};
 
struct VB2 : virtual A
{
    void f(); // overrides A::f
};
 
// struct Error : VB1, VB2
// {
//     // Error: A::f has two final overriders in Error
// };
 
struct Okay : VB1, VB2
{
    void f(); // OK: this is the final overrider for A::f
};
 
struct VB1a : virtual A {}; // does not declare an overrider
 
struct Da : VB1a, VB2
{
    // in Da, the final overrider of A::f is VB2::f
};
具有相同名称但不同参数列表的函数不会重写同名的基函数，而是“隐藏”它：当非限定名称查找检查派生类的作用域时，查找会找到该声明，而不会检查基类。


struct B
{
    virtual void f();
};
 
struct D : B
{
    void f(int); // D::f hides B::f (wrong parameter list)
};
 
struct D2 : D
{
    void f(); // D2::f overrides B::f (doesn't matter that it's not visible)
};
 
int main()
{
    B b;
    B& b_as_b = b;
 
    D d;
    B& d_as_b = d;
    D& d_as_d = d;
 
    D2 d2;
    B& d2_as_b = d2;
    D& d2_as_d = d2;
 
    b_as_b.f();  // calls B::f()
    d_as_b.f();  // calls B::f()
    d2_as_b.f(); // calls D2::f()
 
    d_as_d.f();  // Error: lookup in D finds only f(int)
    d2_as_d.f(); // Error: lookup in D finds only f(int)
}
如果一个函数用说明符override声明，但没有重写虚函数，则程序格式错误。


struct B
{
    virtual void f(int);
};
 
struct D : B
{
    virtual void f(int) override;  // OK, D::f(int) overrides B::f(int)
    virtual void f(long) override; // Error: f(long) does not override B::f(int)
};
如果一个函数用说明符final声明，而另一个函数试图重写它，则程序格式错误。

struct B
{
    virtual void f() const final;
};
 
struct D : B
{
    void f() const; // Error: D::f attempts to override final B::f
};
(C++11 起)
非成员函数和静态成员函数不能是虚函数。


函数模板不能声明为virtual。这仅适用于函数本身是模板的情况——类模板的普通成员函数可以声明为虚函数。

虚函数（无论是声明为virtual还是重写一个）不能有任何相关的约束。

struct A
{
    virtual void f() requires true; // Error: constrained virtual function
};
consteval虚函数不得重写或被非consteval虚函数重写。

(C++20 起)
虚函数的默认参数在编译时替换。

协变返回类型
如果函数Derived::f重写函数Base::f，它们的返回类型必须相同或为“协变”。如果满足以下所有要求，则两种类型是协变的：

两种类型都是指向类的指针或引用（左值或右值）。不允许有多级指针或引用。
Base::f()返回类型中引用的/指向的类必须是Derived::f()返回类型中引用的/指向的类的明确且可访问的直接或间接基类。
Derived::f()的返回类型必须与Base::f()的返回类型具有相同或更低的cv-限定符。
Derived::f返回类型中的类必须是Derived本身，或者在Derived::f声明时必须是完整类型。


当进行虚函数调用时，最终重写者返回的类型会隐式转换为被调用的重写函数的返回类型。

class B {};
 
struct Base
{
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual B* vf4();
    virtual B* vf5();
};
 
class D : private B
{
    friend struct Derived; // in Derived, B is an accessible base of D
};
 
class A; // forward-declared class is an incomplete type
 
struct Derived : public Base
{
    void vf1();    // virtual, overrides Base::vf1()
    void vf2(int); // non-virtual, hides Base::vf2()
//  char vf3();    // Error: overrides Base::vf3, but has different
                   // and non-covariant return type
    D* vf4();      // overrides Base::vf4() and has covariant return type
//  A* vf5();      // Error: A is incomplete type
};
 
int main()
{
    Derived d;
    Base& br = d;
    Derived& dr = d;
 
    br.vf1(); // calls Derived::vf1()
    br.vf2(); // calls Base::vf2()
//  dr.vf2(); // Error: vf2(int) hides vf2()
 
    B* p = br.vf4(); // calls Derived::vf4() and converts the result to B*
    D* q = dr.vf4(); // calls Derived::vf4() and does not convert the result to B*
}
虚析构函数

尽管析构函数不会被继承，但如果基类将其析构函数声明为virtual，则派生析构函数总是会重写它。这使得可以通过指向基类的指针删除多态类型的动态分配对象。

class Base
{
public:
    virtual ~Base() { /* releases Base's resources */ }
};
 
class Derived : public Base
{
    ~Derived() { /* releases Derived's resources */ }
};
 
int main()
{
    Base* b = new Derived;
    delete b; // Makes a virtual function call to Base::~Base()
              // since it is virtual, it calls Derived::~Derived() which can
              // release resources of the derived class, and then calls
              // Base::~Base() following the usual order of destruction
}
此外，如果基类的析构函数不是虚函数，则通过指向基类的指针删除派生类对象是“未定义行为”，无论是否存在如果派生析构函数未被调用就会泄漏的资源，除非选定的解除分配函数是销毁性operator delete(C++20 起)。


一条有用的准则是，任何基类的析构函数必须是public 和虚函数，或 protected 和非虚函数，只要涉及删除表达式，例如在std::unique_ptr中隐式使用时(C++11 起)。

构造与析构期间
当虚函数直接或间接从构造函数或析构函数（包括在类的非静态数据成员的构造或析构期间，例如在成员初始化列表中）被调用时，并且调用所适用的对象是正在构造或析构的对象，则被调用的函数是构造函数或析构函数类中的最终重写者，而不是更派生类中重写它的函数。换句话说，在构造或析构期间，更派生类不存在。

在构造具有多个分支的复杂类时，属于一个分支的构造函数内部，多态性仅限于该类及其基类：如果它获取指向此子层次结构之外的基子对象的指针或引用，并尝试调用虚函数（例如，使用显式成员访问），则行为是未定义的。

struct V
{
    virtual void f();
    virtual void g();
};
 
struct A : virtual V
{
    virtual void f(); // A::f is the final overrider of V::f in A
};
 
struct B : virtual V
{
    virtual void g(); // B::g is the final overrider of V::g in B
    B(V*, A*);
};
 
struct D : A, B
{
    virtual void f(); // D::f is the final overrider of V::f in D
    virtual void g(); // D::g is the final overrider of V::g in D
 
    // note: A is initialized before B
    D() : B((A*) this, this) {}
};
 
// the constructor of B, called from the constructor of D 
B::B(V* v, A* a)
{
    f(); // virtual call to V::f (although D has the final overrider, D doesn't exist)
    g(); // virtual call to B::g, which is the final overrider in B 
 
    v->g(); // v's type V is base of B, virtual call calls B::g as before
 
    a->f(); // a’s type A is not a base of B. it belongs to a different branch of the
            // hierarchy. Attempting a virtual call through that branch causes
            // undefined behavior even though A was already fully constructed in this
            // case (it was constructed before B since it appears before B in the list
            // of the bases of D). In practice, the virtual call to A::f will be
            // attempted using B's virtual member function table, since that's what
            // is active during B's construction)
}






~~抽象类

 C++ C++ 语言 类 
定义一个不能被实例化但可作为基类的抽象类型。

语法
一个 纯虚 函数是一个 虚函数，其 声明符 具有以下语法

声明符 虚说明符 ﻿(可选) = 0		
这里的序列 = 0 被称为 纯说明符，它出现在 声明符 之后，或在可选的 虚说明符（override 或 final）之后。

纯说明符 不能出现在成员函数定义或 友元 声明中。

struct Base
{
    virtual int g();
    virtual ~Base() {}
};
 
struct A : Base
{
    // OK: declares three member virtual functions, two of them pure
    virtual int f() = 0, g() override = 0, h();
 
    // OK: destructor can be pure too
    ~A() = 0;
 
    // Error: pure-specifier on a function definition
    virtual int b() = 0 {}
};
一个 抽象类 是一个类，它定义或继承了至少一个函数，该函数的 最终覆盖器 是 纯虚 的。


解释
抽象类用于表示通用概念（例如，形状、动物），它们可以作为具体类（例如，圆形、狗）的基类。

不能创建抽象类的对象（除了从它派生的类的基子对象），也不能声明类型为抽象类的非静态数据成员。

抽象类型不能用作参数类型、函数返回类型或显式转换的类型（请注意，这在定义和函数调用点进行检查，因为在函数声明点，参数和返回类型可能不完整）。

可以声明指向抽象类的指针和引用。

运行此代码
struct Abstract
{
    virtual void f() = 0;  // pure virtual
}; // "Abstract" is abstract
 
struct Concrete : Abstract
{
    void f() override {}   // non-pure virtual
    virtual void g();      // non-pure virtual
}; // "Concrete" is non-abstract
 
struct Abstract2 : Concrete
{
    void g() override = 0; // pure virtual overrider
}; // "Abstract2" is abstract
 
int main()
{
    // Abstract a;   // Error: abstract class
    Concrete b;      // OK
    Abstract& a = b; // OK to reference abstract base
    a.f();           // virtual dispatch to Concrete::f()
    // Abstract2 a2; // Error: abstract class (final overrider of g() is pure)
}
可以提供纯虚函数的定义（如果纯虚函数是析构函数，则必须提供）：派生类的成员函数可以使用限定函数ID自由地调用抽象基类的纯虚函数。此定义必须在类体之外提供（函数声明的语法不允许同时存在纯说明符= 0和函数体）。


从抽象类的构造函数或析构函数对纯虚函数进行虚调用是未定义行为（无论它是否有定义）。

struct Abstract
{
    virtual void f() = 0; // pure virtual
    virtual void g() {}   // non-pure virtual
 
    ~Abstract()
    {
        g();           // OK: calls Abstract::g()
        // f();        // undefined behavior
        Abstract::f(); // OK: non-virtual call
    }
};
 
// definition of the pure virtual function
void Abstract::f()
{
    std::cout << "A::f()\n";
}
 
struct Concrete : Abstract
{
    void f() override
    {
        Abstract::f(); // OK: calls pure virtual function
    }
 
    void g() override {}
 
    ~Concrete()
    {
        g(); // OK: calls Concrete::g()
        f(); // OK: calls Concrete::f()
    }
};








四.~~模板



~类模板
C++ C++ 语言 声明 表达式 模板 
类模板定义了一系列类。

语法
template < 参数列表 > 类声明	(1)	
template < 参数列表 > requires 约束 类声明	(2)	(C++20 起)
export template < 参数列表 > 类声明	(3)	(在 C++11 中已移除)
解释
类声明	-	一个类声明。声明的类名成为模板名。
参数列表	-

一个非空的逗号分隔的模板参数列表，每个参数都是非类型参数、类型参数、模板参数或这些参数的参数包。
约束	-	一个约束表达式，它限制此类模板接受的模板参数。
export 是一个可选修饰符，用于将模板声明为已导出（与类模板一起使用时，它也将其所有成员声明为已导出）。实例化导出模板的文件不需要包含其定义：声明就足够了。export 的实现很少见，并且在细节上彼此不一致。	(C++11 前)
类模板实例化

类模板本身不是类型、对象或任何其他实体。仅包含模板定义的源文件不会生成任何代码。为了使任何代码出现，必须实例化模板：必须提供模板参数，以便编译器可以生成实际的类（或函数，来自函数模板）。


显式实例化
template 类键 模板名 < 参数列表 > ;	(1)	
extern template 类键 模板名 < 参数列表 > ;	(2)	(C++11 起)
类键	-	class, struct 或 union
1) 显式实例化定义

2) 显式实例化声明

显式实例化定义强制实例化它们所引用的类、结构体或联合体。它可以在模板定义之后的程序中的任何位置出现，对于给定的参数列表，在整个程序中只允许出现一次，不需要诊断。

显式实例化声明 (extern template) 跳过隐式实例化步骤：否则会导致隐式实例化的代码会使用其他地方提供的显式实例化定义（如果不存在此类实例化，则会导致链接错误）。这可以用于通过在所有使用它的源文件（除一个文件外）中显式声明模板实例化，并在剩余文件中显式定义它来减少编译时间。

(C++11 起)
类、函数、变量(C++14 起)和成员模板特化可以从它们的模板显式实例化。类模板的成员函数、成员类和静态数据成员可以从它们的成员定义显式实例化。


显式实例化只能出现在模板的包围命名空间中，除非它使用限定 ID


namespace N
{
    template<class T>
    class Y // template definition
    {
        void mf() {}
    };
}
 
// template class Y<int>; // error: class template Y not visible in the global namespace
using N::Y;
// template class Y<int>; // error: explicit instantiation outside
                          // of the namespace of the template
template class N::Y<char*>;       // OK: explicit instantiation
template void N::Y<double>::mf(); // OK: explicit instantiation
如果对于同一组模板参数，之前已经出现了显式特化，则显式实例化无效。


当显式实例化函数模板、变量模板(C++14 起)、类模板的成员函数或静态数据成员，或成员函数模板时，只需要声明可见。类模板、类模板的成员类或成员类模板的完整定义必须出现在显式实例化之前，除非之前出现了具有相同模板参数的显式特化。


如果函数模板、变量模板(C++14 起)、成员函数模板或类模板的成员函数或静态数据成员通过显式实例化定义进行显式实例化，则模板定义必须存在于同一翻译单元中。


当显式实例化命名类模板特化时，它作为其每个尚未在翻译单元中显式特化的非继承非模板成员的相同种类（声明或定义）的显式实例化。如果此显式实例化是一个定义，它也仅是此时已定义的成员的显式实例化定义。


显式实例化定义忽略成员访问说明符：参数类型和返回类型可以是私有的。


隐式实例化

当代码在需要完全定义类型的上下文中引用模板，或者当类型的完整性影响代码时，并且此特定类型尚未显式实例化时，会发生隐式实例化。例如，当此类型的对象被构造时，但当此类型的指针被构造时则不会。


这适用于类模板的成员：除非在程序中使用该成员，否则它不会被实例化，也不需要定义。


template<class T>
struct Z // template definition
{
    void f() {}
    void g(); // never defined
};
 
template struct Z<double>; // explicit instantiation of Z<double>
Z<int> a;                  // implicit instantiation of Z<int>
Z<char>* p;                // nothing is instantiated here
 
p->f(); // implicit instantiation of Z<char> and Z<char>::f() occurs here.
        // Z<char>::g() is never needed and never instantiated:
        // it does not have to be defined
如果在实例化点声明了类模板但未定义，则实例化会产生不完整的类类型

template<class T>
class X;    // declaration, not definition
 
X<char> ch; // error: incomplete type X<char>
局部类以及其成员中使用的任何模板，都作为声明局部类或枚举的实体实例化的一部分而实例化。	(C++17 起)


~函数模板

 C++ C++ 语言 声明 表达式 模板 
函数模板定义了一族函数。

语法
template < 参数列表 > 函数声明	(1)	
template < 参数列表 > requires 约束 函数声明	(2)	(C++20 起)
带占位符的函数声明	(3)	(C++20 起)
export template < 参数列表 > 函数声明	(4)	(C++11 中已移除)
解释
参数列表	-	一个非空的逗号分隔的模板参数列表，其中每个参数要么是非类型参数、类型参数、模板参数，或上述任意一种的参数包(C++11 起)。 如同任何模板一样，参数可以被约束(C++20 起)
函数声明	-

一个函数声明。声明的函数名成为模板名。
约束	-

一个约束表达式，用于限制此函数模板接受的模板参数
函数声明-
带占位符	-

一个函数声明，其中至少一个参数的类型使用占位符auto或Concept auto：模板参数列表将为每个占位符附加一个发明的参数（参阅下面的缩写函数模板）
export 是一个可选修饰符，用于将模板声明为 *导出*（当与类模板一起使用时，它也声明其所有成员都已导出）。实例化导出模板的文件不需要包含它们的定义：声明就足够了。export 的实现很少见，并且在细节上相互不一致。

(C++11 前)
缩写函数模板

当占位符类型（auto 或 Concept auto）出现在函数声明或函数模板声明的参数列表中时，该声明将声明一个函数模板，并且为每个占位符附加一个发明模板参数到模板参数列表。

void f1(auto); // same as template<class T> void f1(T)
void f2(C1 auto); // same as template<C1 T> void f2(T), if C1 is a concept
void f3(C2 auto...); // same as template<C2... Ts> void f3(Ts...), if C2 is a concept
void f4(const C3 auto*, C4 auto&); // same as template<C3 T, C4 U> void f4(const T*, U&);
 
template<class T, C U>
void g(T x, U y, C auto z); // same as template<class T, C U, C W> void g(T x, U y, W z);
缩写函数模板可以像所有函数模板一样被特化。

template<>
void f4<int>(const int*, const double&); // specialization of f4<int, const double>


(C++20 起)
函数模板签名

每个函数模板都有一个签名。


模板头的签名是模板参数列表，不包括模板参数名和默认实参，以及 requires 子句（如果有）(C++20 起)。


函数模板的签名包含名称、参数类型列表、返回类型、尾随 requires 子句（如果有）(C++20 起)以及模板头的签名。除了以下情况，其签名还包含封闭命名空间。


如果函数模板是一个类成员，其签名包含函数所属的类而不是封闭命名空间。其签名还包含尾随 requires 子句（如果有）(C++20 起)、引用限定符（如果有），以及(C++11 起) cv 限定符（如果有）。

如果函数模板是友元且约束涉及封闭模板参数，其签名包含封闭类而不是封闭命名空间。

(C++20 起)
函数模板实例化

函数模板本身不是类型，也不是函数。只包含模板定义的源文件不会生成任何代码。为了使任何代码出现，必须实例化模板：必须确定模板实参，以便编译器可以生成实际的函数（或类，来自类模板）。


显式实例化
template 返回类型 名称 < 实参列表 > ( 参数列表 ) ;	(1)	
template 返回类型 名称 ( 参数列表 ) ;	(2)	
extern template 返回类型 名称 < 实参列表 > ( 参数列表 ) ;	(3)	(C++11 起)
extern template 返回类型 名称 ( 参数列表 ) ;	(4)	(C++11 起)
1) 显式实例化定义（如果所有非默认模板参数都已显式指定，则不进行模板实参推导）

2) 显式实例化定义，对所有参数进行模板实参推导

3) 显式实例化声明（如果所有非默认模板参数都已显式指定，则不进行模板实参推导）

4) 显式实例化声明，对所有参数进行模板实参推导

显式实例化定义强制实例化它们所引用的函数或成员函数。它可以在模板定义之后的程序中的任何位置出现，并且对于给定的参数列表，在程序中只允许出现一次，不需要诊断。

显式实例化声明（`extern template`）阻止隐式实例化：否则会导致隐式实例化的代码必须使用程序中其他地方提供的显式实例化定义。

(C++11 起)
如果函数模板特化或成员函数模板特化的显式实例化中可以从函数参数推导出尾随模板实参，则可以不指定它。


template<typename T>
void f(T s)
{
    std::cout << s << '\n';
}
 
template void f<double>(double); // instantiates f<double>(double)
template void f<>(char);         // instantiates f<char>(char), template argument deduced
template void f(int);            // instantiates f<int>(int), template argument deduced
函数模板或类模板成员函数的显式实例化不能使用 inline 或 constexpr。如果显式实例化的声明命名了隐式声明的特殊成员函数，则程序是病态的。

构造函数的显式实例化不能使用模板参数列表（语法(1)），这也不是必需的，因为它们可以被推导出来（语法(2)）。

预期析构函数的显式实例化必须命名类的选定析构函数。

(C++20 起)
显式实例化声明不会抑制内联函数、`auto` 声明、引用和类模板特化的隐式实例化。（因此，当作为显式实例化声明主题的内联函数被 ODR 使用时，它会为内联而隐式实例化，但其非内联副本不会在此翻译单元中生成）

具有默认实参的函数模板的显式实例化定义不是实参的使用，也不会尝试初始化它们。

char* p = 0;
 
template<class T>
T g(T x = &p) { return x; }
 
template int g<int>(int); // OK even though &p isn’t an int.
隐式实例化
当代码在一个需要函数定义存在的上下文中使用函数，或者如果定义的存在影响程序的语义(C++11 起)，并且此特定函数尚未被显式实例化时，将发生隐式实例化。如果模板实参列表可以从上下文中推导出来，则不需要提供它。

运行此代码
#include <iostream>
 
template<typename T>
void f(T s)
{
    std::cout << s << '\n';
}
 
int main()
{
    f<double>(1); // instantiates and calls f<double>(double)
    f<>('a');     // instantiates and calls f<char>(char)
    f(7);         // instantiates and calls f<int>(int)
    void (*pf)(std::string) = f; // instantiates f<string>(string)
    pf("∇");                     // calls f<string>(string)
}
如果表达式需要常量求值的函数定义，则函数定义的出现被认为会影响程序的语义，即使表达式不需要常量求值，或者常量表达式求值不使用该定义。

template<typename T>
constexpr int f() { return T::value; }
 
template<bool B, typename T>
void g(decltype(B ? f<T>() : 0));
template<bool B, typename T>
void g(...);
 
template<bool B, typename T>
void h(decltype(int{B ? f<T>() : 0}));
template<bool B, typename T>
void h(...);
 
void x()
{
    g<false, int>(0); // OK: B ? f<T>() : 0 is not potentially constant evaluated
    h<false, int>(0); // error: instantiates f<int> even though B evaluates to false
                      // and list-initialization of int from int cannot be narrowing
}
(C++11 起)
注意：完全省略 <> 允许重载决议同时检查模板和非模板重载。

模板实参推导
为了实例化函数模板，必须知道每个模板实参，但并非每个模板实参都必须指定。如果可能，编译器将从函数实参中推导缺失的模板实参。这发生在尝试函数调用时和获取函数模板地址时。

template<typename To, typename From>
To convert(From f);
 
void g(double d) 
{
    int i = convert<int>(d);    // calls convert<int,double>(double)
    char c = convert<char>(d);  // calls convert<char,double>(double)
    int(*ptr)(float) = convert; // instantiates convert<int, float>(float)
}
此机制使得使用模板运算符成为可能，因为除了将其重写为函数调用表达式之外，没有指定运算符模板参数的语法。

#include <iostream>
 
int main() 
{
    std::cout << "Hello, world" << std::endl;
    // operator<< is looked up via ADL as std::operator<<,
    // then deduced to operator<<<char, std::char_traits<char>> both times
    // std::endl is deduced to &std::endl<char, std::char_traits<char>>
}
模板实参推导在函数模板名称查找（可能涉及实参依赖查找）之后、重载决议之前进行。

详情请参阅模板实参推导。

显式模板实参
函数模板的模板参数可以从以下来源获取：

模板实参推导
默认模板实参
显式指定，可以在以下上下文中进行：
在函数调用表达式中
当获取函数地址时
当初始化函数引用时
当形成成员函数指针时
在显式特化中
在显式实例化中
在友元声明中
没有办法为重载运算符、转换函数和构造函数显式指定模板参数，因为它们是在不使用函数名的情况下调用的。

指定的模板实参必须与模板形参类型匹配（即，类型对应类型，非类型对应非类型，模板对应模板）。实参的数量不能多于形参的数量（除非一个形参是形参包，在这种情况下，每个非包形参都必须有一个实参）(C++11 起)。

指定的非类型实参必须与相应非类型模板形参的类型匹配，或可转换为它们。

不参与模板实参推导的函数参数（例如，如果相应的模板实参被显式指定）将转换为相应函数参数的类型（如通常的重载决议）。

如果存在额外的实参，显式指定的模板参数包可以通过模板实参推导进行扩展。

template<class... Types>
void f(Types... values);
 
void g()
{
    f<int*, float*>(0, 0, 0); // Types = {int*, float*, int}
}
(C++11 起)
模板实参替换
当所有模板实参都已指定、推导或从默认模板实参获得时，函数形参列表中模板形参的每次使用都会被相应的模板实参替换。

函数模板的替换失败（即，无法将模板形参替换为推导或提供的模板实参）会从重载集中移除该函数模板。这允许通过模板元编程以多种方式操作重载集：详情请参阅SFINAE。

替换后，所有数组和函数类型的函数参数都调整为指针，所有顶级 cv 限定符都从函数参数中删除（如同常规函数声明）。

顶级 cv 限定符的移除不影响参数在函数内出现的类型。

template<class T>
void f(T t);
 
template<class X>
void g(const X x);
 
template<class Z>
void h(Z z, Z* zp);
 
// two different functions with the same type, but 
// within the function, t has different cv qualifications
f<int>(1);       // function type is void(int), t is int
f<const int>(1); // function type is void(int), t is const int
 
// two different functions with the same type and the same x
// (pointers to these two functions are not equal,
//  and function-local statics would have different addresses)
g<int>(1);       // function type is void(int), x is const int
g<const int>(1); // function type is void(int), x is const int
 
// only top-level cv-qualifiers are dropped:
h<const int>(1, NULL); // function type is void(int, const int*) 
                       // z is const int, zp is const int*
函数模板重载
函数模板和非模板函数可以重载。

非模板函数总是与具有相同类型的模板特化不同。即使具有相同的类型，不同函数模板的特化也总是彼此不同。两个具有相同返回类型和相同参数列表的函数模板是不同的，可以通过它们的显式模板参数列表来区分。

当在函数参数列表或返回类型中出现使用类型或非类型模板参数的表达式时，该表达式仍然是用于重载的函数模板签名的一部分。

template<int I, int J>
A<I+J> f(A<I>, A<J>); // overload #1
 
template<int K, int L>
A<K+L> f(A<K>, A<L>); // same as #1
 
template<int I, int J>
A<I-J> f(A<I>, A<J>); // overload #2
如果两个包含这些表达式的函数定义在ODR下是相同的，则称涉及模板参数的两个表达式是*等价的*，也就是说，这两个表达式包含相同序列的标记，它们的名称通过名称查找解析为相同的实体，除了模板参数可能命名不同。两个lambda 表达式永远不相等。(C++20 起)

template<int I, int J>
void f(A<I+J>); // template overload #1
 
template<int K, int L>
void f(A<K+L>); // equivalent to #1
在确定两个依赖表达式是否等价时，只考虑所涉及的依赖名称，而不考虑名称查找的结果。如果同一模板的多个声明在名称查找结果上有所不同，则使用第一个这样的声明。

template<class T>
decltype(g(T())) h(); // decltype(g(T())) is a dependent type
 
int g(int);
 
template<class T>
decltype(g(T())) h()
{                  // redeclaration of h() uses earlier lookup
    return g(T()); // although the lookup here does find g(int)
}
 
int i = h<int>(); // template argument substitution fails; g(int)
                  // was not in scope at the first declaration of h()
如果两个函数模板满足以下条件，则认为它们是*等价的*：

它们在同一作用域中声明。
它们具有相同的名称。
它们具有*等价的*模板参数列表，这意味着列表长度相同，并且对于每个对应的参数对，以下所有条件都为真：
两个参数属于同一类型（都是类型，都是非类型，或都是模板）
它们要么都是参数包，要么都不是。
(C++11 起)
如果是非类型，它们的类型是等价的，
如果是模板，它们的模板参数是等价的，
如果其中一个用概念名声明，则它们都是，并且概念名是等价的。
(C++20 起)
它们返回类型和参数列表中的涉及模板参数的表达式是*等价的*。
如果存在，它们在模板参数列表之后的 `requires` 子句中的表达式是等价的。
如果存在，它们在函数声明符之后的 `requires` 子句中的表达式是等价的。
(C++20 起)
涉及模板参数的两个潜在求值(C++20 起)表达式被称为*功能等价*，如果它们不是*等价的*，但对于任何给定的模板实参集，这两个表达式的求值结果相同。

如果两个函数模板*等价*，但其返回类型和参数列表中涉及模板参数的一个或多个表达式*功能等价*，则认为这两个函数模板是*功能等价*的。

此外，如果两个函数模板的约束指定方式不同，但它们接受并满足相同的模板实参列表，则它们是*功能等价*但不是*等价*的。

(C++20 起)
如果程序包含功能等价但不等价的函数模板声明，则程序是病态的；不需要诊断。

// equivalent
template<int I>
void f(A<I>, A<I+10>); // overload #1
template<int I>
void f(A<I>, A<I+10>); // redeclaration of overload #1
 
// not equivalent
template<int I>
void f(A<I>, A<I+10>); // overload #1
template<int I>
void f(A<I>, A<I+11>); // overload #2
 
// functionally-equivalent but not equivalent
// This program is ill-formed, no diagnostic required
template<int I>
void f(A<I>, A<I+10>);      // overload #1
template<int I>
void f(A<I>, A<I+1+2+3+4>); // functionally equivalent
当同一函数模板特化与多个重载函数模板匹配时（这通常是模板实参推导的结果），将执行*重载函数模板的部分排序*以选择最佳匹配。

具体来说，部分排序发生在以下情况：

1) 对函数模板特化调用的重载决议
template<class X>
void f(X a);
template<class X>
void f(X* a);
 
int* p;
f(p);
2) 当获取函数模板特化地址时
template<class X>
void f(X a);
template<class X>
void f(X* a);
 
void (*p)(int*) = &f;
3) 当选择作为函数模板特化的定位 delete 运算符来匹配定位 new 运算符时。
本节不完整
原因：微型示例
4) 当友元函数声明、显式实例化或显式特化引用函数模板特化时。
template<class X>
void f(X a);  // first template f
template<class X>
void f(X* a); // second template f
template<>
void f<>(int *a) {} // explicit specialization
 
// template argument deduction comes up with two candidates:
// f<int*>(int*) and f<int>(int*)
// partial ordering selects f<int>(int*) as more specialized
非正式地，“A 比 B 更特化”意味着“A 接受的类型比 B 少”。

正式地，要确定两个函数模板中哪一个更特化，部分排序过程首先按如下方式转换其中一个模板：

对于每个类型、非类型和模板参数，包括参数包，(C++11 起)生成一个唯一的虚构类型、值或模板并替换到模板的函数类型中。
如果正在比较的两个函数模板中只有一个是成员函数，并且该函数模板是某个类 A 的非静态成员，则在其参数列表中插入一个新的首参数。给定 cv 作为函数模板的 cv 限定符，以及 ref 作为函数模板的 ref 限定符(C++11 起)，新的参数类型是 cv A&，除非 ref 是 &&，或者 ref 不存在且另一个模板的第一个参数具有右值引用类型，在这种情况下类型是 cv A&&(C++11 起)。这有助于运算符的排序，因为运算符既作为成员函数又作为非成员函数进行查找。
struct A {};
 
template<class T>
struct B
{
    template<class R>
    int operator*(R&); // #1
};
 
template<class T, class R>
int operator*(T&, R&); // #2
 
int main()
{
    A a;
    B<A> b;
    b * a; // template argument deduction for int B<A>::operator*(R&) gives R=A 
           //                             for int operator*(T&, R&), T=B<A>, R=A
 
    // For the purpose of partial ordering, the member template B<A>::operator*
    // is transformed into template<class R> int operator*(B<A>&, R&);
 
    // partial ordering between 
    //     int operator*(   T&, R&)  T=B<A>, R=A
    // and int operator*(B<A>&, R&)  R=A 
    // selects int operator*(B<A>&, A&) as more specialized
}
在其中一个模板按照上述描述转换后，使用转换后的模板作为实参模板，另一个模板的原始模板类型作为形参模板执行模板实参推导。然后重复该过程，使用第二个模板（转换后）作为实参，第一个模板以其原始形式作为形参。

用于确定顺序的类型取决于上下文。

在函数调用上下文中，类型是函数调用具有实参的函数形参类型（不考虑默认函数实参、参数包、(C++11 起)和省略号形参——请参阅下面的示例）。
在调用用户定义的转换函数的上下文中，使用转换函数模板的返回类型。
在其他上下文中，使用函数模板类型。
从上述列表中，形参模板的每个类型都将被推导。在推导开始之前，形参模板的每个形参 P 和实参模板的相应实参 A 将按如下方式调整：

如果 P 和 A 之前都是引用类型，则确定哪个更具 cv 限定性（在所有其他情况下，cv 限定性在部分排序中被忽略）
如果 P 是引用类型，则它被其所引用的类型替换。
如果 A 是引用类型，则它被其所引用的类型替换。
如果 P 具有 cv 限定，则 P 被替换为其自身的 cv 非限定版本。
如果 A 具有 cv 限定，则 A 被替换为其自身的 cv 非限定版本。
在这些调整之后，按照从类型推导模板实参的方式进行 P 从 A 的推导。

如果 P 是函数参数包，则实参模板中每个剩余参数类型 A 将与函数参数包的声明符 id 的类型 P 进行比较。每次比较都会推导出由函数参数包展开的模板参数包中后续位置的模板参数。

如果 A 是从函数参数包转换而来的，则它与参数模板的每个剩余参数类型进行比较。

(C++11 起)
如果转换后的模板-1 的实参 A 可用于推导模板-2 的相应形参 P，但反之不行，则此 A 在此 P/A 对推导的类型方面比 P 更特化。

如果推导在两个方向都成功，并且原始 P 和 A 是引用类型，则进行额外的测试。

如果 A 是左值引用而 P 是右值引用，则 A 被认为比 P 更特化。
如果 A 比 P 具有更多的 cv 限定符，则 A 被认为比 P 更特化。
在所有其他情况下，对于此 P/A 对推导的类型，两个模板均不比另一个更特化。

在双向考虑了每个 P 和 A 之后，如果对于所考虑的每种类型：

模板-1 对于所有类型至少与模板-2 一样特化。
模板-1 对于某些类型比模板-2 更特化。
模板-2 对于任何类型都不比模板-1 更特化，或者对于任何类型都不至少与模板-1 一样特化。
那么模板-1 比模板-2 更特化。如果切换模板顺序后上述条件成立，则模板-2 比模板-1 更特化。否则，两个模板都不比另一个更特化。

在平局的情况下，如果一个函数模板有尾随参数包而另一个没有，则省略参数的模板被认为比带有空参数包的模板更特化。

(C++11 起)
如果，在考虑所有重载模板对之后，有一个模板明确地比所有其他模板更特化，则选择该模板的特化，否则编译失败。

在以下示例中，虚构的参数将被称为 U1, U2。

template<class T>
void f(T);        // template #1
template<class T>
void f(T*);       // template #2
template<class T>
void f(const T*); // template #3
 
void m()
{
    const int* p;
    f(p); // overload resolution picks: #1: void f(T ) [T = const int *]
          //                            #2: void f(T*) [T = const int]
          //                            #3: void f(const T *) [T = int]
 
    // partial ordering:
 
    // #1 from transformed #2: void(T) from void(U1*): P=T A=U1*: deduction ok: T=U1*
    // #2 from transformed #1: void(T*) from void(U1): P=T* A=U1: deduction fails
    // #2 is more specialized than #1 with regards to T
 
    // #1 from transformed #3: void(T) from void(const U1*): P=T, A=const U1*: ok
    // #3 from transformed #1: void(const T*) from void(U1): P=const T*, A=U1: fails
    // #3 is more specialized than #1 with regards to T
 
    // #2 from transformed #3: void(T*) from void(const U1*): P=T* A=const U1*: ok
    // #3 from transformed #2: void(const T*) from void(U1*): P=const T* A=U1*: fails
    // #3 is more specialized than #2 with regards to T
 
    // result: #3 is selected
    // in other words, f(const T*) is more specialized than f(T) or f(T*)
}
template<class T>
void f(T, T*);   // #1
template<class T>
void f(T, int*); // #2
 
void m(int* p)
{
    f(0, p); // deduction for #1: void f(T, T*) [T = int]
             // deduction for #2: void f(T, int*) [T = int]
 
    // partial ordering:
 
    // #1 from #2: void(T,T*) from void(U1,int*): P1=T, A1=U1: T=U1
    //                                            P2=T*, A2=int*: T=int: fails
 
    // #2 from #1: void(T,int*) from void(U1,U2*): P1=T A1=U1: T=U1
    //                                             P2=int* A2=U2*: fails
 
    // neither is more specialized w.r.t T, the call is ambiguous
}
template<class T>
void g(T);  // template #1
template<class T>
void g(T&); // template #2
 
void m()
{
    float x;
    g(x); // deduction from #1: void g(T ) [T = float]
          // deduction from #2: void g(T&) [T = float]
 
    // partial ordering:
 
    // #1 from #2: void(T) from void(U1&): P=T, A=U1 (after adjustment), ok
 
    // #2 from #1: void(T&) from void(U1): P=T (after adjustment), A=U1: ok
 
    // neither is more specialized w.r.t T, the call is ambiguous
}
template<class T>
struct A { A(); };
 
template<class T>
void h(const T&); // #1
template<class T>
void h(A<T>&);    // #2
 
void m()
{
    A<int> z;
    h(z); // deduction from #1: void h(const T &) [T = A<int>]
          // deduction from #2: void h(A<T> &) [T = int]
 
    // partial ordering:
 
    // #1 from #2: void(const T&) from void(A<U1>&): P=T A=A<U1>: ok T=A<U1>
 
    // #2 from #1: void(A<T>&) from void(const U1&): P=A<T> A=const U1: fails
 
    // #2 is more specialized than #1 w.r.t T
 
    const A<int> z2;
    h(z2); // deduction from #1: void h(const T&) [T = A<int>]
           // deduction from #2: void h(A<T>&) [T = int], but substitution fails
 
    // only one overload to choose from, partial ordering not tried, #1 is called
}
由于调用上下文只考虑有显式调用实参的参数，所以那些函数参数包、(C++11 起)省略号参数和带有默认实参但没有显式调用实参的参数将被忽略。

template<class T>
void f(T);         // #1
template<class T>
void f(T*, int = 1); // #2
 
void m(int* ip)
{
    int* ip;
    f(ip); // calls #2 (T* is more specialized than T)
}
template<class T>
void g(T);       // #1
template<class T>
void g(T*, ...); // #2
 
void m(int* ip)
{
    g(ip); // calls #2 (T* is more specialized than T)
}
template<class T, class U>
struct A {};
 
template<class T, class U>
void f(U, A<U, T>* p = 0); // #1
template<class U>
void f(U, A<U, U>* p = 0); // #2
 
void h()
{
    f<int>(42, (A<int, int>*)0); // calls #2
    f<int>(42);                  // error: ambiguous
}
template<class T>
void g(T, T = T()); // #1
template<class T, class... U>
void g(T, U...);    // #2
 
void h()
{
    g(42); // error: ambiguous
}
template<class T, class... U>
void f(T, U...); // #1
template<class T>
void f(T);       // #2
 
void h(int i)
{
    f(&i); // calls #2 due to the tie-breaker between parameter pack and no parameter
           // (note: was ambiguous between DR692 and DR1395)
}
template<class T, class... U>
void g(T*, U...); // #1
template<class T>
void g(T);        // #2
 
void h(int i)
{
    g(&i); // OK: calls #1 (T* is more specialized than T)
}
template<class... T>
int f(T*...);    // #1
template<class T>
int f(const T&); // #2
 
f((int*)0); // OK: selects #2; non-variadic template is more specialized than
            // variadic template (was ambiguous before DR1395 because deduction
            // failed in both directions)
template<class... Args>
void f(Args... args);        // #1
template<class T1, class... Args>
void f(T1 a1, Args... args); // #2
template<class T1, class T2>
void f(T1 a1, T2 a2);        // #3
 
f();        // calls #1
f(1, 2, 3); // calls #2
f(1, 2);    // calls #3; non-variadic template #3 is more
            // specialized than the variadic templates #1 and #2
在部分排序过程中进行模板实参推导时，如果实参未用于部分排序所考虑的任何类型，则模板参数不需要与实参匹配。

template<class T>
T f(int); // #1
template<class T, class U>
T f(U);   // #2
 
void g()
{
    f<int>(1); // specialization of #1 is explicit: T f(int) [T = int]
               // specialization of #2 is deduced:  T f(U) [T = int, U = int]
 
    // partial ordering (only considering the argument type):
 
    // #1 from #2: T(int) from U1(U2): fails
    // #2 from #1: T(U) from U1(int): ok: U=int, T unused
 
    // calls #1
}
包含模板参数包的函数模板的部分排序独立于这些模板参数包推导出的实参数量。

template<class...>
struct Tuple {};
 
template<class... Types>
void g(Tuple<Types...>);      // #1
template<class T1, class... Types>
void g(Tuple<T1, Types...>);  // #2
template<class T1, class... Types>
void g(Tuple<T1, Types&...>); // #3
 
g(Tuple<>());            // calls #1
g(Tuple<int, float>());  // calls #2
g(Tuple<int, float&>()); // calls #3
g(Tuple<int>());         // calls #3
(C++11 起)
本节不完整
原因：14.8.3[temp.over]
为了编译函数模板的调用，编译器必须在非模板重载、模板重载和模板重载的特化之间做出选择。

template<class T>
void f(T);      // #1: template overload
template<class T>
void f(T*);     // #2: template overload
 
void f(double); // #3: non-template overload
template<>
void f(int);    // #4: specialization of #1
 
f('a');        // calls #1
f(new int(1)); // calls #2
f(1.0);        // calls #3
f(1);          // calls #4
函数重载与函数特化
请注意，只有非模板和主模板重载参与重载决议。特化不是重载，不被考虑。只有在重载决议选择最佳匹配的主函数模板后，才会检查其特化以查看是否存在更好的匹配。

template<class T>
void f(T);    // #1: overload for all types
template<>
void f(int*); // #2: specialization of #1 for pointers to int
template<class T>
void f(T*);   // #3: overload for all pointer types
 
f(new int(1)); // calls #3, even though specialization of #1 would be a perfect match
在排列翻译单元的头文件时，记住这条规则很重要。有关函数重载和函数特化之间相互作用的更多示例，请展开以下内容：

示例
首先考虑一些不使用实参依赖查找的场景。为此，我们使用调用 (f)(t)。如ADL中所述，将函数名括在括号中会抑制实参依赖查找。

f() 的多个重载在 g() 中的 *引用点* (POR) 之前声明。
运行此代码
#include <iostream>
 
struct A {};
 
template<class T>
void f(T)  { std::cout << "#1\n"; } // overload #1 before f() POR
template<class T>
void f(T*) { std::cout << "#2\n"; } // overload #2 before f() POR
 
template<class T>
void g(T* t) 
{
    (f)(t); // f() POR
}
 
int main()
{
    A* p = nullptr;
    g(p); // POR of g() and f()
}
 
// Both #1 and #2 are added to the candidate list;
// #2 is selected because it is a better match.
输出

#2


一个更匹配的模板重载在 POR 之后声明。
运行此代码
#include <iostream>
 
struct A {};
 
template<class T>
void f(T)  { std::cout << "#1\n"; } // #1
 
template<class T>
void g(T* t) 
{
    (f)(t); // f() POR
}
 
template<class T>
void f(T*) { std::cout << "#2\n"; } // #2
 
int main()
{
    A* p = nullptr;
    g(p); // POR of g() and f()
}
 
// Only #1 is added to the candidate list; #2 is defined after POR;
// therefore, it is not considered for overloading even if it is a better match.
输出

#1


一个更匹配的显式模板特化在 POR 之后声明。
运行此代码
#include <iostream>
 
struct A {};
 
template<class T>
void f(T)    { std::cout << "#1\n"; } // #1
 
template<class T>
void g(T* t) 
{
    (f)(t); // f() POR
}
template<>
void f<>(A*) { std::cout << "#3\n"; } // #3
 
int main()
{
    A* p = nullptr;
    g(p); // POR of g() and f()
}
 
// #1 is added to the candidate list; #3 is a better match defined after POR. The
// candidate list consists of #1 which is eventually selected. After that, the explicit 
// specialization #3 of #1 declared after POI is selected because it is a better match. 
// This behavior is governed by 14.7.3/6 [temp.expl.spec] and has nothing to do with ADL.
输出

#3


一个更匹配的模板重载在 POR 之后声明。最佳匹配的显式模板特化在更匹配的重载之后声明。
运行此代码
#include <iostream>
 
struct A {};
 
template<class T>
void f(T)    { std::cout << "#1\n"; } // #1
 
template<class T>
void g(T* t) 
{
    (f)(t); // f() POR
}
 
template<class T>
void f(T*)   { std::cout << "#2\n"; } // #2
template<>
void f<>(A*) { std::cout << "#3\n"; } // #3
 
int main()
{
    A* p = nullptr;
    g(p); // POR of g() and f()
}
 
// #1 is the only member of the candidate list and it is eventually selected. 
// After that, the explicit specialization #3 is skipped because it actually 
// specializes #2 declared after POR.
输出

#1

现在让我们考虑使用实参依赖查找的情况（即，我们使用更常见的调用格式f(t)）。

一个更匹配的模板重载在 POR 之后声明。
运行此代码
#include <iostream>
 
struct A {};
 
template<class T>
void f(T)  { std::cout << "#1\n"; } // #1
 
template<class T>
void g(T* t) 
{
    f(t); // f() POR
}
 
template<class T>
void f(T*) { std::cout << "#2\n"; } // #2
 
int main()
{
    A* p = nullptr;
    g(p); // POR of g() and f()
}
 
// #1 is added to the candidate list as a result of the ordinary lookup;
// #2 is defined after POR but it is added to the candidate list via ADL lookup.
// #2 is selected being the better match.
输出

#2


一个更匹配的模板重载在 POR 之后声明。最佳匹配的显式模板特化在更匹配的重载之前声明。
运行此代码
#include <iostream>
 
struct A {};
 
template<class T>
void f(T)    { std::cout << "#1\n"; } // #1
 
template<class T>
void g(T* t) 
{
    f(t); // f() POR
}
 
template<>
void f<>(A*) { std::cout << "#3\n"; } // #3
template<class T>
void f(T*)   { std::cout << "#2\n"; } // #2
 
int main()
{
    A* p = nullptr;
    g(p); // POR of g() and f()
}
 
// #1 is added to the candidate list as a result of the ordinary lookup;
// #2 is defined after POR but it is added to the candidate list via ADL lookup.
// #2 is selected among the primary templates, being the better match.
// Since #3 is declared before #2, it is an explicit specialization of #1.
// Hence the final selection is #2.
输出

#2


一个更匹配的模板重载在 POR 之后声明。最佳匹配的显式模板特化最后声明。
运行此代码
#include <iostream>
 
struct A {};
 
template<class T>
void f(T)    { std::cout << "#1\n"; } // #1
 
template<class T>
void g(T* t) 
{
    f(t); // f() POR
}
 
template<class T>
void f(T*)   { std::cout << "#2\n"; } // #2
template<>
void f<>(A*) { std::cout << "#3\n"; } // #3
 
int main()
{
    A* p = nullptr;
    g(p); // POR of g() and f()
}
 
// #1 is added to the candidate list as a result of the ordinary lookup;
// #2 is defined after POR but it is added to the candidate list via ADL lookup.
// #2 is selected among the primary templates, being the better match.
// Since #3 is declared after #2, it is an explicit specialization of #2;
// therefore, selected as the function to call.
输出

#3

只要实参是某些 C++ 基本类型，就没有 ADL 关联的命名空间。因此，这些场景与上述非 ADL 示例相同。






~模板形参和模板实参
C++ C++ 语言 声明 表达式 模板 
模板形参
每个模板都由一个或多个模板形参参数化，这些形参在模板声明语法的形参列表中指出

template < parameter-list > declaration	(1)	
template < parameter-list > requires constraint declaration	(2)	(C++20 起)
形参列表中的每个形参可以是

非类型模板形参；
类型模板形参；
模板模板形参。


	P2841 (Concept and variable-template template-parameters) 将“非类型模板形参/实参”重命名为“常量模板形参/实参”，但未改变其含义。由于“非类型模板形参”及其缩写“NTTP”的广泛使用，当前术语得以保留。
非类型模板形参
type name ﻿(可选)	(1)	
type name ﻿(可选) = default	(2)	
type ... name ﻿(可选)	(3)	(C++11 起)
1) 非类型模板形参。
2) 带默认模板实参的非类型模板形参。
3) 非类型模板形参包。
类型	-	以下类型之一
结构化类型 (见下文)
包含占位符类型的类型
(C++17 起)
推导类类型的占位符
(C++20 起)
name	-	非类型模板形参的名称
default	-	默认模板实参
“结构化类型”是以下类型之一（可带有 cv 限定符，限定符会被忽略）

左值引用类型（指向对象或函数）；
整型类型；
指针类型（指向对象或函数）；
成员指针类型（指向成员对象或成员函数）；
枚举类型；
std::nullptr_t;
(C++11 起)
浮点类型；
没有捕获的 lambda 表达式的lambda 闭包类型；
非闭包字面类类型，具有以下属性
所有基类和非静态数据成员都是公共且不可变的，并且
所有基类和非静态数据成员的类型都是结构化类型或其（可能是多维）数组。
(C++20 起)
数组和函数类型可以在模板声明中书写，但它们会自动被替换为指向对象和指向函数的指针。

当非类型模板形参的名称在类模板主体内的表达式中使用时，它是一个不可修改的纯右值，除非其类型是左值引用类型，或者除非其类型是类类型(C++20 起)。

形式为 class Foo 的模板形参不是类型为 Foo 的无名非类型模板形参，即使 class Foo 否则是详尽类型说明符，并且 class Foo x; 声明 x 的类型为 Foo。


命名类类型 T 的非类型模板形参的标识符表示类型为 const T 的静态存储期对象，称为模板形参对象，它在转换为模板形参的类型后，与相应的模板实参模板实参等价。没有两个模板形参对象是模板实参等价的。

struct A
{
    friend bool operator==(const A&, const A&) = default;
};
 
template<A a>
void f()
{
    &a;                       // OK
    const A& ra = a, &rb = a; // Both bound to the same template parameter object
    assert(&ra == &rb);       // passes
}
(C++20 起)
类型模板形参
type-parameter-key name ﻿(可选)	(1)	
type-parameter-key name ﻿(可选) = default	(2)	
type-parameter-key ... name ﻿(可选)	(3)	(C++11 起)
type-constraint name ﻿(可选)	(4)	(C++20 起)
type-constraint name ﻿(可选) = default	(5)	(C++20 起)
type-constraint ... name ﻿(可选)	(6)	(C++20 起)
type-parameter-key	-	typename 或 class。在类型模板形参声明中，这两个关键词没有区别
type-constraint	-	概念的名称，或概念名称后跟模板实参列表（在尖括号中）。无论哪种情况，概念名称都可以是可选限定的
name	-	类型模板形参的名称
default	-	默认模板实参
1) 没有默认值的类型模板形参。
template<class T>
class My_vector { /* ... */ };
2) 带默认值的类型模板形参。
template<class T = void>
struct My_op_functor { /* ... */ };
3) 类型模板形参包。
template<typename... Ts>
class My_tuple { /* ... */ };
4) 没有默认值的受约束类型模板形参。
template<My_concept T>
class My_constrained_vector { /* ... */ };
5) 带默认值的受约束类型模板形参。
template<My_concept T = void>
class My_constrained_op_functor { /* ... */ };
6) 受约束类型模板形参包。
template<My_concept... Ts>
class My_constrained_tuple { /* ... */ };
形参的名称是可选的

// Declarations of the templates shown above:
template<class>
class My_vector;
template<class = void>
struct My_op_functor;
template<typename...>
class My_tuple;
在模板声明的主体中，类型形参的名称是一个 typedef-name，它别名为模板实例化时提供的类型。

每个受约束形参 P，其 type-constraint 指定概念 C，都会根据以下规则引入一个约束表达式 E

如果 Q 是 C（不带实参列表），
如果 P 不是形参包，则 E 简单地是 C<P>
否则，P 是一个形参包，E 是一个折叠表达式 (C<P> && ...)
如果 Q 是 C<A1,A2...,AN>，则 E 分别是 C<P,A1,A2,...AN> 或 (C<P,A1,A2,...AN> && ...)。
template<typename T>
concept C1 = true;
template<typename... Ts> // variadic concept
concept C2 = true;
template<typename T, typename U>
concept C3 = true;
 
template<C1 T>         struct s1; // constraint-expression is C1<T>
template<C1... T>      struct s2; // constraint-expression is (C1<T> && ...)
template<C2... T>      struct s3; // constraint-expression is (C2<T> && ...)
template<C3<int> T>    struct s4; // constraint-expression is C3<T, int>
template<C3<int>... T> struct s5; // constraint-expression is (C3<T, int> && ...)
(C++20 起)
模板模板形参
template < parameter-list > type-parameter-key name ﻿(可选)	(1)	
template < parameter-list > type-parameter-key name ﻿(可选) = default	(2)	
template < parameter-list > type-parameter-key ... name ﻿(可选)	(3)	(C++11 起)
type-parameter-key	-	class 或 typename(C++17 起)
1) 带可选名称的模板模板形参。
2) 带可选名称和默认值的模板模板形参。
3) 带可选名称的模板模板形参包。
在模板声明的主体中，此形参的名称是一个模板名（需要实参才能实例化）。

template<typename T>
class my_array {};
 
// two type template parameters and one template template parameter:
template<typename K, typename V, template<typename> typename C = my_array>
class Map
{
    C<K> key;
    C<V> value;
};
模板形参的名字解析
模板形参的名称不允许在其作用域（包括嵌套作用域）内重声明。模板形参不允许与模板名称同名。

template<class T, int N>
class Y
{
    int T;      // error: template parameter redeclared
    void f()
    {
        char T; // error: template parameter redeclared
    }
};
 
template<class X>
class X; // error: template parameter redeclared
在类模板的成员定义（出现在类模板定义之外）中，类模板成员的名称隐藏任何包围类模板的模板形参的名称，但如果成员是类模板或函数模板，则不隐藏其模板形参的名称。

template<class T>
struct A
{
    struct B {};
    typedef void C;
    void f();
 
    template<class U>
    void g(U);
};
 
template<class B>
void A<B>::f()
{
    B b; // A's B, not the template parameter
}
 
template<class B>
template<class C>
void A<B>::g(C)
{
    B b; // A's B, not the template parameter
    C c; // the template parameter C, not A's C
}
在类模板的成员定义（出现在包含类模板定义的命名空间之外）中，模板形参的名称隐藏此命名空间的成员名称。

namespace N
{
    class C {};
 
    template<class T>
    class B
    {
        void f(T);
    };
}
 
template<class C>
void N::B<C>::f(C)
{
    C b; // C is the template parameter, not N::C
}
在类模板的定义中，或在此类模板成员的定义中（出现在模板定义之外），对于每个非依赖基类，如果基类的名称或基类成员的名称与模板形参的名称相同，则基类名称或成员名称隐藏模板形参名称。

struct A
{
    struct B {};
    int C;
    int Y;
};
 
template<class B, class C>
struct X : A
{
    B b; // A's B
    C b; // error: A's C isn't a type name
};
模板实参
为了实例化模板，每个模板形参（类型、非类型或模板）都必须被相应的模板实参替换。对于类模板，实参可以是显式提供的、从初始化器推导的(C++17 起)，或默认的。对于函数模板，实参可以是显式提供的、从上下文推导的，或默认的。

如果一个实参可以同时被解释为type-id和表达式，它总是被解释为 type-id，即使相应的模板形参是非类型的

template<class T>
void f(); // #1
 
template<int I>
void f(); // #2
 
void g()
{
    f<int()>(); // "int()" is both a type and an expression,
                // calls #1 because it is interpreted as a type
}
非类型模板实参
可与非类型模板形参一起使用的模板实参可以是任何显然常量求值表达式。

(C++11 前)
可与非类型模板形参一起使用的模板实参可以是任何初始化子句。如果初始化子句是表达式，它必须是显然常量求值的。

(C++11 起)
给定非类型模板形参声明的类型为 T，为该形参提供的模板实参为 E。

虚构声明 T x = E; 必须满足constexpr 变量定义的语义约束，其存储期为静态。

(C++26 起)
如果 T 包含占位符类型，或者是推导类类型的占位符，则模板形参的类型是在虚构声明 T x = E; 中为变量 x 推导出的类型。

如果推导出的形参类型不是结构化类型，则程序是病态的。

对于类型使用占位符类型的非类型模板形参包，类型是为每个模板实参独立推导的，并且不必匹配。

(C++17 起)
template<auto n>
struct B { /* ... */ };
 
B<5> b1;   // OK: non-type template parameter type is int
B<'a'> b2; // OK: non-type template parameter type is char
B<2.5> b3; // error (until C++20): non-type template parameter type cannot be double
 
// C++20 deduced class type placeholder, class template arguments are deduced at the
// call site
template<std::array arr>
void f();
 
f<std::array<double, 8>{}>();
 
template<auto...>
struct C {};
 
C<'C', 0, 2L, nullptr> x; // OK
非类型模板形参 P 的值，其（可能推导出的）(C++17 起)类型为 T，从其模板实参 A 按如下方式确定

如果 A 是类型 T 的转换后的常量表达式，则 P 的值为 A（已转换）。
否则，程序格式错误。
(C++11 前)
如果 A 是表达式
如果 A 是类型 T 的转换后的常量表达式，则 P 的值为 A（已转换）。
否则，程序格式错误。
否则（A 是括号括起来的初始化列表），引入一个临时变量 constexpr T v = A;。P 的值是 v 的值。
v 的生命周期在初始化后立即结束。
(C++11 起)
(C++20 前)
如果 T 不是类类型且 A 是表达式
如果 A 是类型 T 的转换后的常量表达式，则 P 的值为 A（已转换）。
否则，程序格式错误。
否则（T 是类类型或 A 是括号括起来的初始化列表），引入一个临时变量 constexpr T v = A;。
如果 T 是类类型，则存在一个模板形参对象（也由 P 表示）。P 从与 v 模板实参等价的未指定候选初始化器进行复制初始化。
v 和 P 的生命周期在初始化后立即结束。
如果 P 的初始化满足以下任何条件，则程序是病态的
初始化将是病态的。
当作为显然常量求值表达式解释时，用于初始化的虚构声明符-初始化器序列的完整表达式不是常量表达式。
初始化将导致 P 与 v 不模板实参等价。
否则，P 的值是 v 的值。
(C++20 起)
template<int i>
struct C { /* ... */ };
 
C<{42}> c1; // OK
 
template<auto n>
struct B { /* ... */ };
 
struct J1
{
    J1* self = this;
};
 
B<J1{}> j1; // error: initialization of the template parameter object
            //        is not a constant expression
 
struct J2
{
    J2 *self = this;
    constexpr J2() {}
    constexpr J2(const J2&) {}
};
 
B<J2{}> j2; // error: the template parameter object is not
            //        template-argument-equivalent to introduced temporary
实例化具有非类型模板形参的模板时适用以下限制

对于整型和算术类型，实例化期间提供的模板实参必须是模板形参类型的转换后的常量表达式（因此适用某些隐式转换）。
对于指向对象的指针，模板实参必须指定具有静态存储期和链接（内部或外部）的完整对象的地址，或一个求值为适当空指针或 std::nullptr_t(C++11 起)值的常量表达式。
对于指向函数的指针，有效实参是指向具有链接的函数的指针（或求值为空指针值的常量表达式）。
对于左值引用形参，实例化时提供的实参不能是临时对象、无名左值或无链接的具名左值（换句话说，实参必须具有链接）。
对于指向成员的指针，实参必须是表示为 &Class::Member 的成员指针，或一个求为空指针或 std::nullptr_t(C++11 起)值的常量表达式。
特别是，这意味着字符串字面量、数组元素的地址和非静态成员的地址不能用作模板实参来实例化相应的非类型模板形参为指向对象的指针的模板。

(C++17 前)
引用或指针类型的非类型模板形参，以及类类型非类型模板形参及其子对象中引用或指针类型的非静态数据成员(C++20 起)不能引用/是以下对象的地址：

临时对象（包括在引用初始化期间创建的对象）；
字符串字面量；
typeid 的结果；
预定义变量 __func__；
或上述之一的子对象（包括非静态类成员、基子对象或数组元素）(C++20 起)。
(C++17 起)
template<const int* pci>
struct X {};
 
int ai[10];
X<ai> xi; // OK: array to pointer conversion and cv-qualification conversion
 
struct Y {};
 
template<const Y& b>
struct Z {};
 
Y y;
Z<y> z;   // OK: no conversion
 
template<int (&pa)[5]>
struct W {};
 
int b[5];
W<b> w;   // OK: no conversion
 
void f(char);
void f(int);
 
template<void (*pf)(int)>
struct A {};
 
A<&f> a;  // OK: overload resolution selects f(int)
template<class T, const char* p>
class X {};
 
X<int, "Studebaker"> x1; // error: string literal as template-argument
 
template<int* p>
class X {};
 
int a[10];
 
struct S
{
    int m;
    static int s;
} s;
 
X<&a[2]> x3; // error (until C++20): address of array element
X<&s.m> x4;  // error (until C++20): address of non-static member
X<&s.s> x5;  // OK: address of static member
X<&S::s> x6; // OK: address of static member
 
template<const int& CRI>
struct B {};
 
B<1> b2;     // error: temporary would be required for template argument
int c = 1;
B<c> b1;     // OK
类型模板实参
类型模板形参的模板实参必须是类型 ID，它可以命名不完整类型

template<typename T>
class X {}; // class template
 
struct A;            // incomplete type
typedef struct {} B; // type alias to an unnamed type
 
int main()
{
    X<A> x1;  // OK: 'A' names a type
    X<A*> x2; // OK: 'A*' names a type
    X<B> x3;  // OK: 'B' names a type
}
模板模板实参
模板模板形参的模板实参必须是命名类模板或模板别名的id-expression。

当实参是类模板时，只有主模板在匹配形参时被考虑。如果有部分特化，则只有在基于此模板模板形参的特化被实例化时才被考虑。

template<typename T> // primary template
class A { int x; };
 
template<typename T> // partial specialization
class A<T*> { long x; };
 
// class template with a template template parameter V
template<template<typename> class V>
class C
{
    V<int> y;  // uses the primary template
    V<int*> z; // uses the partial specialization
};
 
C<A> c; // c.y.x has type int, c.z.x has type long
为了将模板模板实参 A 匹配到模板模板形参 P，P 必须至少与 A 一样特化（见下文）。如果 P 的形参列表包含形参包，则 A 的模板形参列表中的零个或多个模板形参（或形参包）将由它匹配。(C++11 起)

形式上，如果给定以下对两个函数模板的重写，则模板模板形参 P 至少与模板模板实参 A 一样特化，即根据函数模板的部分排序规则，对应于 P 的函数模板至少与对应于 A 的函数模板一样特化。给定一个虚构的类模板 X，其模板形参列表与 A 相同（包括默认实参）

两个函数模板分别具有与 P 或 A 相同的模板形参。
每个函数模板都有一个单一的函数形参，其类型是 X 的特化，模板实参对应于相应函数模板的模板形参，其中，对于函数模板的模板形参列表中的每个模板形参 PP，形成相应的模板实参 AA。如果 PP 声明一个形参包，则 AA 是包展开 PP...；否则，(C++11 起) AA 是 id-expression PP。
如果重写产生无效类型，则 P 不至少与 A 一样特化。

template<typename T>
struct eval;                     // primary template
 
template<template<typename, typename...> class TT, typename T1, typename... Rest>
struct eval<TT<T1, Rest...>> {}; // partial specialization of eval
 
template<typename T1> struct A;
template<typename T1, typename T2> struct B;
template<int N> struct C;
template<typename T1, int N> struct D;
template<typename T1, typename T2, int N = 17> struct E;
 
eval<A<int>> eA;        // OK: matches partial specialization of eval
eval<B<int, float>> eB; // OK: matches partial specialization of eval
eval<C<17>> eC;         // error: C does not match TT in partial specialization
                        // because TT's first parameter is a
                        // type template parameter, while 17 does not name a type
eval<D<int, 17>> eD;    // error: D does not match TT in partial specialization
                        // because TT's second parameter is a
                        // type parameter pack, while 17 does not name a type
eval<E<int, float>> eE; // error: E does not match TT in partial specialization
                        // because E's third (default) parameter is a non-type
在采用P0522R0之前，A 的每个模板形参都必须与 P 的相应模板形参完全匹配。这阻碍了许多合理的模板实参被接受。

尽管它很早就被指出（CWG#150），但在它被解决时，这些更改已应用于 C++17 工作草案，并且该解决方案成为事实上的 C++17 功能。许多编译器默认禁用它

GCC 默认在 C++17 之前的所有语言模式中禁用它，只能通过在这些模式中设置编译器标志来启用它。
Clang 默认在所有语言模式中禁用它，只能通过设置编译器标志来启用它。
Microsoft Visual Studio 将其视为正常的 C++17 功能，并且仅在 C++17 及更高版本的语言模式中启用它（即在 C++14 语言模式中不支持，C++14 是默认模式）。
template<class T> class A { /* ... */ };
template<class T, class U = T> class B { /* ... */ };
template<class... Types> class C { /* ... */ };
 
template<template<class> class P> class X { /* ... */ };
X<A> xa; // OK
X<B> xb; // OK after P0522R0
         // Error earlier: not an exact match
X<C> xc; // OK after P0522R0
         // Error earlier: not an exact match
 
template<template<class...> class Q> class Y { /* ... */ };
Y<A> ya; // OK
Y<B> yb; // OK
Y<C> yc; // OK
 
template<auto n> class D { /* ... */ };   // note: C++17
template<template<int> class R> class Z { /* ... */ };
Z<D> zd; // OK after P0522R0: the template parameter
         // is more specialized than the template argument
 
template<int> struct SI { /* ... */ };
template<template<auto> class> void FA(); // note: C++17
FA<SI>(); // Error
默认模板实参

默认模板实参在形参列表中用 = 符号指定。默认值可以为任何类型的模板形参（类型、非类型或模板）指定，但不能为形参包指定(C++11 起)。


如果为主类模板、主变量模板(C++14 起)或别名模板的模板形参指定了默认值，则每个后续模板形参都必须具有默认实参，除了最后一个可以是模板形参包(C++11 起)。在函数模板中，默认值之后的形参没有限制，并且形参包之后可以有更多类型形参，仅当它们具有默认值或可以从函数实参推导时(C++11 起)。


不允许使用默认形参

在类模板成员的类外定义中（它们必须在类体内的声明中提供）。请注意，非模板类的成员模板可以在其类外定义中使用默认形参（参见GCC bug 53856）
在友元类模板声明中
在任何函数模板声明或定义中
(C++11 前)
在友元函数模板声明上，默认模板实参仅当声明是定义并且此函数在当前翻译单元中没有其他声明时才允许。

(C++11 起)
在声明中出现的默认模板参数的合并方式与默认函数参数类似。


template<typename T1, typename T2 = int> class A;
template<typename T1 = int, typename T2> class A;
 
// the above is the same as the following:
template<typename T1 = int, typename T2 = int> class A;
但在同一作用域中，同一参数不能被赋予两次默认参数。


template<typename T = int> class X;
template<typename T = int> class X {}; // error
当解析非类型模板参数的默认模板参数时，第一个非嵌套的 > 被视为模板参数列表的结束，而不是大于运算符。


template<int i = 3 > 4>   // syntax error
class X { /* ... */ };
 
template<int i = (3 > 4)> // OK
class Y { /* ... */ };
模板模板参数的模板参数列表可以有自己的默认参数，这些默认参数仅在模板模板参数本身的作用域内有效。


// class template, with a type template parameter with a default
template<typename T = float>
struct B {};
 
// template template parameter T has a parameter list, which
// consists of one type template parameter with a default
template<template<typename = float> typename T>
struct A
{
    void f();
    void g();
};
 
// out-of-body member function template definitions
 
template<template<typename TT> class T>
void A<T>::f()
{
    T<> t; // error: TT has no default in scope
}
 
template<template<typename TT = char> class T>
void A<T>::g()
{
    T<> t; // OK: t is T<char>
}
默认模板参数中使用的名称的成员访问是在声明处检查的，而不是在使用点检查的。


class B {};
 
template<typename T>
class C
{
protected:
    typedef T TT;
};
 
template<typename U, typename V = typename U::TT>
class D: public U {};
 
D<C<B>>* d; // error: C::TT is protected
当需要默认参数的值时，默认模板参数会隐式实例化，除非该模板用于命名函数。


template<typename T, typename U = int>
struct S {};
 
S<bool>* p; // The default argument for U is instantiated at this point
            // the type of p is S<bool, int>*
(C++14 起)
模板实参等价性

模板实参等价性用于确定两个模板标识符是否相同。


如果两个值类型相同且满足以下任一条件，则它们是模板实参等价的：

它们是整型或枚举类型，且它们的值相同。
它们是指针类型，且它们具有相同的指针值。
它们是指向成员的指针类型，且它们引用相同的类成员，或都是空成员指针值。
它们是左值引用类型，且它们引用相同的对象或函数。
它们是 std::nullptr_t 类型。
(C++11 起)
它们是浮点类型，且它们的值相同。
它们是数组类型（在这种情况下，数组必须是某个类/联合的成员对象），且它们的相应元素是模板实参等价的。
它们是联合类型，且它们要么都没有活动成员，要么具有相同的活动成员，并且它们的活动成员是模板实参等价的。
它们是 lambda 闭包类型。
它们是非联合类类型，且它们的相应直接子对象和引用成员是模板实参等价的。
(C++20 起)
注意
在模板参数中，类型约束可以用于类型和非类型参数，具体取决于是否存在 auto。


template<typename>
concept C = true;
 
template<C,     // type parameter 
         C auto // non-type parameter
        >
struct S{};
 
S<int, 0> s;


(C++20 起)
功能测试宏	值	标准	特性

__cpp_nontype_template_parameter_auto	201606L	(C++17)

使用 auto 声明非类型模板参数
__cpp_template_template_args	201611L	(c++17)
(DR)

模板模板实参的匹配
__cpp_nontype_template_args	201411L	(C++17)	允许对所有非类型模板实参进行常量求值
201911L	(C++20)	非类型模板参数中的类类型和浮点类型
示例
运行此代码
#include <array>
#include <iostream>
#include <numeric>
 
// simple non-type template parameter
template<int N>
struct S { int a[N]; };
 
template<const char*>
struct S2 {};
 
// complicated non-type example
template
<
    char c,             // integral type
    int (&ra)[5],       // lvalue reference to object (of array type)
    int (*pf)(int),     // pointer to function
    int (S<10>::*a)[10] // pointer to member object (of type int[10])
>
struct Complicated
{
    // calls the function selected at compile time
    // and stores the result in the array selected at compile time
    void foo(char base)
    {
        ra[4] = pf(c - base);
    }
};
 
//  S2<"fail"> s2;        // error: string literal cannot be used
    char okay[] = "okay"; // static object with linkage
//  S2<&okay[0]> s3;      // error: array element has no linkage
    S2<okay> s4;          // works
 
int a[5];
int f(int n) { return n; }
 
// C++20: NTTP can be a literal class type
template<std::array arr>
constexpr
auto sum() { return std::accumulate(arr.cbegin(), arr.cend(), 0); }
 
// C++20: class template arguments are deduced at the call site
static_assert(sum<std::array<double, 8>{3, 1, 4, 1, 5, 9, 2, 6}>() == 31.0);
// C++20: NTTP argument deduction and CTAD
static_assert(sum<std::array{2, 7, 1, 8, 2, 8}>() == 28);
 
int main()
{
    S<10> s; // s.a is an array of 10 int
    s.a[9] = 4;
 
    Complicated<'2', a, f, &S<10>::a> c;
    c.foo('0');
 
    std::cout << s.a[9] << a[4] << '\n';
}
输出

42