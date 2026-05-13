# C++知识汇总

- 一、C++基础
    1. 输入输出
    2. 标识符类型
    3. 引用用作函数参数
    4. 内存动态的分配与释放
- 二、文件操作
    1. 文件命名与文件流
    2. 文件打开读写、关闭文件

- 三、类
    1. 类的函数成员
    2. 构造函数，析构函数
    3. 静态成员（static）
    4. 友元函数
    5. 运算符重载
    6. 继承，多态，虚函数，抽象类
- 四、模板
    1. 函数模板，类模板

---

## 1. 输入输出
### 简单的输入输出
```cpp
    cin >> width;
    cout << "矩形宽度为" << width << endl;
```
### [格式化输出](https://cppreference.cn/w/cpp/io/manip)
头文件[`#include <iomanip>`](https://cppreference.cn/w/cpp/header/iomanip)  
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
```cpp
cout.setf(ios::fixed);
```
也可以在函数成员 setf 中采用 | 连接多个状态标志，例如：
```cpp
cout.setf(ios::fixed | ios::showpoint | ios::left);
```
与 setf 功能相反的函数成员是 unsetf，用于清除已经设置的状态标志。例如，下列语句关闭状态标志 ios::fixed 和 ios::left：
```cpp
cout.unsetf(ios::fixed | ios::left);
```

### 格式化输入
采用 cin 对象输入数据是最为频繁的一个方法，它的功能很多，就像 C 中常用的 scanf 函数一样，但它比 scanf 更为方便。
#### 指定输入域宽  
cin 与 cout 的功能虽然不同，但它们有许多类似点。例如，都可以指定域宽。cin 的输入域宽可以使用操作符 setw 指定，也可使用 cin.width 函数成员指定。cin 在读入一个字符串时，不能根据字符数组的长度自动读入字符，如果用户输入过多的字符，超过了字符数组的长度，cin 会将多余字符存储到该数组的后面，这就有可能覆盖其他变量。如果为其指定了输入域宽，就可解决这一问题。
下面定义了一个长度为 10 的字符数组，采用 setw 规定 cin 读入的字符个数不能超过数组的有效范围：
```cpp
char word[10];
cin >> setw(10) >> word;
同样也可以使用函数成员 width 指定输入域宽：
cin.width(10);
cin >> word;
```
在上述两种情况下，指定的输入域宽都是 10，cin 将最多读取 9 个字符，因为数组最后一个位置应存储字符 '\0'。
【例 】 使用操作符 setw 或函数成员 width 控制字符串输入。
```cpp
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
```

【程序运行结果】

```plaintext
请输入一个单词：Chinese [Enter]
你输入的是：Chin
```

【程序解析】 运行该程序时，最多只能读取 4 个有效的字符。可以将上例中：

```cpp
cin >> setw(5) >> word;
```
修改成如下形式，效果等同：
```cpp
cin.width(5);
cin >> word;
```
在上面程序中，`cin` 只读取 4 个字符到字符数组。如果没有指定输入域宽，`cin` 会读取整个字符串 "Chinese"，这将产生溢出。
关于 `cin` 的输入域宽，还要注意以下 3 点：(1) 域宽只对与其相邻的下一个输入有效。(2) 当 `cin` 遇到空字符时，它将停止读入。空字符包括回车、空格和 Tab 键。(3) 当 `cin` 读取一定的字符以后，多余的字符将留在缓冲区中。例如，在上例的输入中，由于只读取了 4 个字符，那么留在缓冲区中的字符是 "ese"。

读取一行
`cin` 提供的函数成员 `getline` ，一次能够读取一行，例如：
```cpp
cin.getline(sentence, 20);
```
函数的第一个参数是数组名，第二个参数是待读取的字符个数（含空字符）。上述语句将最多读取 19 个字符，最后一个位置用于存储 `'\0'`。

读取字符时容易出错的地方
如果将 `cin >>` 和 `cin.get` 混合使用，往往会出现难以发现的问题，例如：
```cpp
cout << "请输入一个整数：";
cin >> number;
cout << "请输入一个字符：";
cin.get(ch);
```
假设要给 number 变量读入 100，给 ch 变量读入 H。首先输入 100，并按 Enter 键，结果发现 `cin.get` 语句被跳过了，根本不给输入字符 H 的机会，这是什么原因呢？
这是因为 `cin >>` 和 `cin.get` 都是从键盘缓冲区（实际上就是一块内存空间）中读入用户的按键。当用户输入 100 并按 Enter 键，此时 Enter 键引起的换行符 '\n' 被存储在键盘缓冲区中。当 `cin >>` 读入 100 后就停止了，换行符则留在键盘缓冲区中，这意味着 `cin.get` 读入的字符将是 '\n'，所以就没有输入字符 H 的机会。如何解决这个问题呢？答案是采用 cin 的函数成员 `ignore`，该函数能够使 cin 对象跳过键盘缓冲区的字符，它的一般形式如下：
```cpp
cin.ignore(n, c);
```
函数原型`std::basic_istream<CharT,Traits>::ignore`：
```cpp
basic_istream& ignore( std::streamsize count = 1, int_type delim = Traits::eof() );
```
从输入流中提取并丢弃字符，直到并包括 delim。  
`ignore` 括号中的参数都是可选的，其中 n 是一个整数，c 是一个字符。含义是 cin 跳越 n 个字符，或者是直到遇到字符 c 为止。例如，下面的语句使 cin 跳越 20 个字符，或者是遇到一个换行符，哪一种情况先出现都可以，都将停止 cin 的跳越：
```cpp
cin.ignore(20, '\n');
```
如果 cin.ignore 没有参数，表示跳过键盘缓冲区中的第一个字符，例如：
```cpp
cin.ignore();
```
解决 `cin >>` 和 `cin.get `混合出现问题的方法是：在 `cin >>` 语句之后加一条 `cin.ignore` 语句：
```cpp
cout << "请输入一个整数：";
cin >> number;
cin.ignore();                // 忽略 number 后面的一个字符
cout << "请输入一个字符：";
cin.get(ch);
```


## 类型
对象、引用、函数（包括函数模板特化）和表达式都具有一个称为**类型**的属性，该属性既限制了这些实体允许的操作，又为原本通用的位序列提供了语义含义。

### [类型分类](https://cppreference.cn/w/cpp/language/type)

### 引用用作函数参数
按值传递是 C 语言中常用的参数传递方法，C++ 除了支持按值传递以外，还支持按引用传递。通过引用作参数，可以修改调用函数中的变量，它比传递指针方便得多。  
下面首先举一个通俗的例子说明什么是引用。假设你的大名叫张三，小名（即别名）叫李四，那么张三和李四都是你的名字，我们可以说张三和李四都是你的引用。张三的任何变化（如长高 2cm）在李四身上都有反映。C++ 的引用变量，简称为引用，它是另外一个变量的别名，对引用变量的任何修改都将影响该引用所代表的变量。通过引用作函数参数，一个函数就可改变另外一个函数中的变量。  
定义引用与定义一般变量类似，只需在变量名前加一个符号 `&`。例如，下面的函数将参数 `refVar` 定义为引用：
```cpp
void doubleNum(int & refVar)
{
    refVar *= 2;
}
```
在定义函数原型时，如果参数是引用，只要在类型之后加一个符号 & 即可。例如，下面是函数 `doubleNum` 的原型：
```cpp
void doubleNum(int&);
// 建议还是写成void doubleNum(int &refVar);
```
## 动态内存管理([低级内存管理](https://cppreference.cn/w/cpp/memory/new))

### [`new` 表达式](https://cppreference.cn/w/cpp/memory/new/operator_new)

### [`delete` 表达式](https://cppreference.cn/w/cpp/memory/new/operator_delete)

只需记住`new`和`delete`总是成对出现，`new []`和`delete[]`也总是成对出现。

## 二、文件操作

### [文件流类](https://cppreference.cn/w/cpp/io#Stream-based_I.2FO)
C++提供三种文件流类

**类型：**
- [`ifstream`](https://cppreference.cn/w/cpp/io/basic_ifstream)：输入文件流（读）
- [`ofstream`](https://cppreference.cn/w/cpp/io/basic_ofstream)：输出文件流（写）
- [`fstream`](https://cppreference.cn/w/cpp/io/basic_fstream)：输入输出文件流（读写）

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

### 文件操作模式
**ios::app**：追加模式
```cpp
ofstream fout("file.txt", ios::app);
```

## 三. [类](https://cppreference.cn/w/cpp/language/classes)

### [类声明](https://cppreference.cn/w/cpp/language/class)

### 构造函数与析构函数

#### 默认构造函数
无参数的构造函数，创建对象时自动调用

- 函数名与类名相同
- 没有返回值
- 若未定义，编译器自动生成


```cpp
BankAccount::BankAccount() {
    accountNumber = 0;
    name = "Unknown";
    balance = 0;
}
```

#### 带参数构造函数
创建对象时可以直接初始化成员变量


```cpp
BankAccount::BankAccount(int acc, string n, double bal) {
    accountNumber = acc;
    name = n;
    balance = bal;
}
```

**使用：**
```cpp
BankAccount acc(1001, "Zhang San", 1000);
```

#### 拷贝构造函数
用已有对象初始化新对象

**语法：**
```cpp
ClassName(const ClassName& other);
```

**调用场景：**
- `BankAccount b2(b1);`
- `BankAccount b2 = b1;`
- 函数参数传递（值传递）
- 函数返回对象


```cpp
BankAccount::BankAccount(const BankAccount& other) {
    accountNumber = other.accountNumber;
    name = other.name;
    balance = other.balance;
}
```

#### 析构函数
对象销毁时自动调用，用于释放资源

- 名字为 `~类名`
- 没有参数和返回值
- 每个类只能有一个析构函数


```cpp
BankAccount::~BankAccount() {
    cout << "账户对象被销毁：" << name << endl;
}
```

#### 虚析构函数
基类析构函数应声明为virtual，确保正确释放派生类资源

**重要性：**
```cpp
virtual ~Account();  // 基类必须有虚析构函数

// 使用场景
Account* acc = new SavingsAccount(...);
delete acc;  // 正确调用派生类析构函数
```

### 封装与访问控制

#### 访问修饰符

- private（私有）
只能在类内部访问

**用途：** 保护数据安全，防止外部直接修改


```cpp
class BankAccount {
private:
    double balance;  // 外部无法直接访问
};
```

- protected（保护）
类内部和派生类可以访问

**用途：** 允许子类访问，但对外部隐藏


```cpp
class Person {
protected:
    int age;  // 子类可访问
};

class Student : public Person {
    void study() {
        age = 20;  // 可以访问父类的protected成员
    }
};
```
- public（公有）
任何地方都可以访问

**用途：** 提供对外接口


```cpp
class BankAccount {
public:
    void deposit(double money);  // 公有接口
    void withdraw(double money);
};
```


### 继承

#### 继承的基本概念
派生类继承基类的成员，实现代码复用

**语法：**
```cpp
class Derived : public Base {
    // 派生类成员
};
```

**is-a关系：** Student是一个Person

#### 继承方式

- public继承（最常用）

    - 基类的public成员在派生类中仍为public
    - 基类的protected成员在派生类中仍为protected
    - 基类的private成员在派生类中不可访问


    ```cpp
    class Student : public Person {
        // 继承Person的public和protected成员
    };
    ```

- 派生类构造函数
    派生类构造函数必须调用基类构造函数

    **语法：**
    ```cpp
    Student::Student(string n, int a, int sid, string m)
        : Person(n, a, "")  // 调用基类构造函数
    {
        studentID = sid;
        major = m;
    }
    ```
- 多层继承
    派生类可以继续被继承


    ```
    Person -> Student -> GraduateStudent
    ```

- 访问基类成员
    **规则：**
    - 派生类可以访问基类的public和protected成员
    - 派生类不能直接访问基类的private成员
    - 可以通过基类的public函数间接访问private成员

### 多态与虚函数

#### 虚函数
使用virtual关键字声明，支持运行时多态

**语法：**
```cpp
class Shape {
public:
    virtual void draw() const;
    virtual double area() const;
};
```


- 基类中用virtual声明
- 派生类可以重写（override）
- 通过基类指针/引用调用时，根据实际对象类型决定调用哪个版本

#### 纯虚函数与抽象类
使用`= 0`声明纯虚函数，包含纯虚函数的类是抽象类

**语法：**
```cpp
class Account {
public:
    virtual void showInfo() = 0;  // 纯虚函数
    virtual double getPower() const = 0;
};
```


- 抽象类不能实例化
- 派生类必须实现所有纯虚函数
- 用于定义接口规范

#### 多态的实现
基类指针指向派生类对象，调用虚函数实现多态


```cpp
// 基类指针数组
Shape* shapes[3];
shapes[0] = new Circle(5.0);
shapes[1] = new Rectangle(4.0, 6.0);

// 多态调用
for (int i = 0; i < 2; i++) {
    shapes[i]->draw();    // 调用实际对象的draw()
    shapes[i]->area();    // 调用实际对象的area()
}
```

**优势：**
- 统一接口处理不同对象
- 代码更灵活、易扩展
- 符合开闭原则

#### 动态绑定与静态绑定
**动态绑定（运行时多态）：**
- 虚函数调用在运行时确定
- 根据对象实际类型调用相应函数

**静态绑定（编译时）：**
- 非虚函数调用在编译时确定
- 根据指针/引用类型调用


### 运算符重载

#### 运算符重载基础
**知识点：** 为自定义类型定义运算符行为

**语法：**
```cpp
ReturnType operator运算符(参数列表);
```

**相关项目：** Operator, Template1

#### 重载<<运算符
**知识点：** 重载输出运算符，方便对象输出

**示例：**
```cpp
// 友元函数形式
friend ostream& operator<<(ostream& os, const Shape& s);

// 实现
ostream& operator<<(ostream& os, const Shape& s) {
    s.print(os);
    return os;
}

// 使用
Circle c(5.0);
cout << c << endl;
```

**相关项目：** Operator, Template1

#### 重载+运算符
**知识点：** 重载算术运算符

**示例：**
```cpp
class Point {
public:
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
};

// 使用
Point p3 = p1 + p2;
```

**相关项目：** Template1

---

### 静态成员

#### 静态成员变量
**知识点：** 属于类而不是对象，所有对象共享

**声明：**
```cpp
class Account {
public:
    static int totalAccounts;
    static double totalMoney;
};
```

**初始化（必须在类外）：**
```cpp
int Account::totalAccounts = 0;
double Account::totalMoney = 0.0;
```

**访问：**
```cpp
cout << Account::totalAccounts << endl;  // 通过类名访问
```

**相关项目：** Project_2, Project_3, BudgetProject

#### 静态成员函数
**知识点：** 属于类的函数，不依赖于对象

**特点：**
- 只能访问静态成员
- 通过类名调用
- 没有this指针

**示例：**
```cpp
class Budget {
public:
    static void mainOffice(float amount);
    static float getCorpBudget();
};

// 调用
Budget::mainOffice(10000);
```

**相关项目：** BudgetProject

---

### 友元

#### 友元类
**知识点：** 友元类可以访问另一个类的所有成员（包括private和protected）

**语法：**
```cpp
class Account {
    friend class BankManager;  // 声明友元类
private:
    double balance;
};

class BankManager {
public:
    void adjustBalance(Account& acc, double amount) {
        acc.balance += amount;  // 可以访问private成员
    }
};
```

**特点：**
- 破坏封装，谨慎使用
- 友元关系不能继承
- 友元关系不是双向的

**相关项目：** Project_2, Project_3, BudgetProject

#### 友元函数
**知识点：** 友元函数可以访问类的私有成员

**示例：**
```cpp
class Budget {
    friend void Aux::addBudget(float, Budget&);
};
```

**相关项目：** BudgetProject

---

### 模板

#### 函数模板
**知识点：** 编写与类型无关的函数

**语法：**
```cpp
template <typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}
```

**使用：**
```cpp
int max1 = getMax(10, 20);        // T = int
double max2 = getMax(3.14, 2.71); // T = double
```

**相关项目：** Template1

#### 类模板
**知识点：** 编写与类型无关的类

**语法：**
```cpp
template <typename T>
class Array {
private:
    T* data;
    int size;
public:
    Array(int s);
    void set(int index, T value);
    T get(int index);
};
```

**使用：**
```cpp
Array<int> intArray(5);
Array<double> doubleArray(10);
```

**相关项目：** Template1

#### 模板特化
**知识点：** 为特定类型提供特殊实现

**示例：**
```cpp
// 通用模板
template <typename T>
T add(T a, T b) {
    return a + b;
}

// 特化版本
template <>
string add<string>(string a, string b) {
    return a + " + " + b;
}
```
#### 模板参数
**类型参数：**
```cpp
template <typename T>
```

**非类型参数：**
```cpp
template <typename T, int SIZE>
class FixedArray {
    T data[SIZE];
};
```

**默认参数：**
```cpp
template <typename T = int, int SIZE = 10>
```


#### 动态内存与多态
**知识点：** 使用基类指针管理派生类对象

**示例：**
```cpp
// 创建
Account* accounts[3];
accounts[0] = new SavingsAccount(...);
accounts[1] = new CreditAccount(...);

// 使用
for (int i = 0; i < 2; i++) {
    accounts[i]->showInfo();  // 多态调用
}

// 释放
for (int i = 0; i < 2; i++) {
    delete accounts[i];  // 需要虚析构函数
}
```

---

### 组合关系

#### 组合的概念
**知识点：** 一个类包含另一个类的对象作为成员

**has-a关系：** Computer有CPU、Memory、Disk

**示例：**
```cpp
class Computer {
private:
    CPU cpu;        // 组合：Computer包含CPU
    Memory memory;  // 组合：Computer包含Memory
    Disk disk;      // 组合：Computer包含Disk
};
```


#### 组合与继承的区别
**继承（is-a）：**
- Student是一个Person
- 表示"是一个"的关系

**组合（has-a）：**
- Computer有CPU
- 表示"有一个"的关系

**选择原则：**
- 能用组合就不用继承
- 组合更灵活，耦合度低

