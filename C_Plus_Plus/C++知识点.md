# C++ 程序设计知识点汇总

## 文档说明
本文档汇总了示例代码目录下所有项目涉及的C++核心知识点，帮助学生系统复习C++面向对象程序设计。

---

## 📚 目录
1. [基础语法与类的基本概念](#1-基础语法与类的基本概念)
2. [构造函数与析构函数](#2-构造函数与析构函数)
3. [封装与访问控制](#3-封装与访问控制)
4. [继承](#4-继承)
5. [多态与虚函数](#5-多态与虚函数)
6. [运算符重载](#6-运算符重载)
7. [静态成员](#7-静态成员)
8. [友元](#8-友元)
9. [模板](#9-模板)
10. [文件操作](#10-文件操作)
11. [动态内存管理](#11-动态内存管理)
12. [组合关系](#12-组合关系)

---

## 1. 基础语法与类的基本概念

### 1.1 类的定义
**知识点：** 类是C++中定义对象的模板或蓝图

**语法：**
```cpp
class ClassName {
private:
    // 私有成员
public:
    // 公有成员
protected:
    // 保护成员
};
```

**相关项目：** 所有项目

**示例：**
```cpp
class BankAccount {
private:
    int accountNumber;
    string name;
    double balance;
public:
    void deposit(double money);
    void withdraw(double money);
};
```

### 1.2 头文件与源文件分离
**知识点：** 将声明放在.h文件，实现放在.cpp文件

**优点：**
- 代码组织清晰
- 便于维护和复用
- 加快编译速度

**头文件保护：**
```cpp
#ifndef CLASSNAME_H
#define CLASSNAME_H
// 类声明
#endif
```

**相关项目：** BankAccountProject, BankAccount2, JiCheng, JiCheng2, 等所有项目

---

## 2. 构造函数与析构函数

### 2.1 默认构造函数
**知识点：** 无参数的构造函数，创建对象时自动调用

**特点：**
- 函数名与类名相同
- 没有返回值
- 若未定义，编译器自动生成

**示例：**
```cpp
BankAccount::BankAccount() {
    accountNumber = 0;
    name = "Unknown";
    balance = 0;
}
```

**相关项目：** BankAccountProject, BankAccount2

### 2.2 带参数构造函数
**知识点：** 创建对象时可以直接初始化成员变量

**示例：**
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

**相关项目：** BankAccountProject, BankAccount2, JiCheng, JiCheng2

### 2.3 拷贝构造函数
**知识点：** 用已有对象初始化新对象

**语法：**
```cpp
ClassName(const ClassName& other);
```

**调用场景：**
- `BankAccount b2(b1);`
- `BankAccount b2 = b1;`
- 函数参数传递（值传递）
- 函数返回对象

**示例：**
```cpp
BankAccount::BankAccount(const BankAccount& other) {
    accountNumber = other.accountNumber;
    name = other.name;
    balance = other.balance;
}
```

**相关项目：** BankAccountProject, BankAccount2

### 2.4 析构函数
**知识点：** 对象销毁时自动调用，用于释放资源

**特点：**
- 名字为 `~类名`
- 没有参数和返回值
- 每个类只能有一个析构函数

**示例：**
```cpp
BankAccount::~BankAccount() {
    cout << "账户对象被销毁：" << name << endl;
}
```

**相关项目：** 所有项目

### 2.5 虚析构函数
**知识点：** 基类析构函数应声明为virtual，确保正确释放派生类资源

**重要性：**
```cpp
virtual ~Account();  // 基类必须有虚析构函数

// 使用场景
Account* acc = new SavingsAccount(...);
delete acc;  // 正确调用派生类析构函数
```

**相关项目：** Project_2, Project_3, JiCheng2, Visitor

---

## 3. 封装与访问控制

### 3.1 访问修饰符

#### private（私有）
**知识点：** 只能在类内部访问

**用途：** 保护数据安全，防止外部直接修改

**示例：**
```cpp
class BankAccount {
private:
    double balance;  // 外部无法直接访问
};
```

**相关项目：** 所有项目

#### protected（保护）
**知识点：** 类内部和派生类可以访问

**用途：** 允许子类访问，但对外部隐藏

**示例：**
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

**相关项目：** JiCheng, Project_2, Project_3

#### public（公有）
**知识点：** 任何地方都可以访问

**用途：** 提供对外接口

**示例：**
```cpp
class BankAccount {
public:
    void deposit(double money);  // 公有接口
    void withdraw(double money);
};
```

**相关项目：** 所有项目

### 3.2 封装的意义
**优点：**
1. **数据安全**：防止非法修改
2. **接口稳定**：内部实现可以改变，接口保持不变
3. **易于维护**：修改内部实现不影响外部代码

**相关项目：** 所有项目

---

## 4. 继承

### 4.1 继承的基本概念
**知识点：** 派生类继承基类的成员，实现代码复用

**语法：**
```cpp
class Derived : public Base {
    // 派生类成员
};
```

**is-a关系：** Student是一个Person

**相关项目：** JiCheng, JiCheng2, Project_2, Project_3, Visitor

### 4.2 继承方式

#### public继承（最常用）
**特点：**
- 基类的public成员在派生类中仍为public
- 基类的protected成员在派生类中仍为protected
- 基类的private成员在派生类中不可访问

**示例：**
```cpp
class Student : public Person {
    // 继承Person的public和protected成员
};
```

**相关项目：** JiCheng, JiCheng2, Project_2, Project_3, Visitor

### 4.3 派生类构造函数
**知识点：** 派生类构造函数必须调用基类构造函数

**语法：**
```cpp
Student::Student(string n, int a, int sid, string m)
    : Person(n, a, "")  // 调用基类构造函数
{
    studentID = sid;
    major = m;
}
```

**相关项目：** JiCheng, Project_2, Project_3, Visitor

### 4.4 多层继承
**知识点：** 派生类可以继续被继承

**示例：**
```cpp
Person -> Student -> GraduateStudent
```

**相关项目：** JiCheng

### 4.5 访问基类成员
**规则：**
- 派生类可以访问基类的public和protected成员
- 派生类不能直接访问基类的private成员
- 可以通过基类的public函数间接访问private成员

**相关项目：** JiCheng, Project_2, Project_3

---

## 5. 多态与虚函数

### 5.1 虚函数
**知识点：** 使用virtual关键字声明，支持运行时多态

**语法：**
```cpp
class Shape {
public:
    virtual void draw() const;
    virtual double area() const;
};
```

**特点：**
- 基类中用virtual声明
- 派生类可以重写（override）
- 通过基类指针/引用调用时，根据实际对象类型决定调用哪个版本

**相关项目：** JiCheng2, Project_2, Project_3, Visitor, Operator

### 5.2 纯虚函数与抽象类
**知识点：** 使用`= 0`声明纯虚函数，包含纯虚函数的类是抽象类

**语法：**
```cpp
class Account {
public:
    virtual void showInfo() = 0;  // 纯虚函数
    virtual double getPower() const = 0;
};
```

**特点：**
- 抽象类不能实例化
- 派生类必须实现所有纯虚函数
- 用于定义接口规范

**相关项目：** Project_2, Project_3, Visitor

### 5.3 多态的实现
**知识点：** 基类指针指向派生类对象，调用虚函数实现多态

**示例：**
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

**相关项目：** JiCheng2, Project_2, Project_3, Visitor

### 5.4 动态绑定与静态绑定
**动态绑定（运行时多态）：**
- 虚函数调用在运行时确定
- 根据对象实际类型调用相应函数

**静态绑定（编译时）：**
- 非虚函数调用在编译时确定
- 根据指针/引用类型调用

**相关项目：** JiCheng2, Project_2, Project_3, Visitor

---

## 6. 运算符重载

### 6.1 运算符重载基础
**知识点：** 为自定义类型定义运算符行为

**语法：**
```cpp
ReturnType operator运算符(参数列表);
```

**相关项目：** Operator, Template1

### 6.2 重载<<运算符
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

### 6.3 重载+运算符
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

## 7. 静态成员

### 7.1 静态成员变量
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

### 7.2 静态成员函数
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

## 8. 友元

### 8.1 友元类
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

### 8.2 友元函数
**知识点：** 友元函数可以访问类的私有成员

**示例：**
```cpp
class Budget {
    friend void Aux::addBudget(float, Budget&);
};
```

**相关项目：** BudgetProject

---

## 9. 模板

### 9.1 函数模板
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

### 9.2 类模板
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

### 9.3 模板特化
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

**相关项目：** Template1

### 9.4 模板参数
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

**相关项目：** Template1

---

## 10. 文件操作

### 10.1 文件流类
**知识点：** C++提供三种文件流类

**类型：**
- `ifstream`：输入文件流（读）
- `ofstream`：输出文件流（写）
- `fstream`：输入输出文件流（读写）

**相关项目：** FileOperation, BankAccountProject, BankAccount2

### 10.2 文件读写操作
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

### 10.3 文件操作模式
**ios::app**：追加模式
```cpp
ofstream fout("file.txt", ios::app);
```

**相关项目：** FileOperation

---

## 11. 动态内存管理

### 11.1 new和delete运算符
**知识点：** 在堆上动态分配和释放内存

**分配内存：**
```cpp
int* p = new int;           // 分配单个int
int* arr = new int[10];     // 分配数组
Account* acc = new SavingsAccount(...);  // 分配对象
```

**释放内存：**
```cpp
delete p;        // 释放单个对象
delete[] arr;    // 释放数组
delete acc;      // 释放对象（调用析构函数）
```

**重要规则：**
- 每个new必须有对应的delete
- 数组用delete[]，单个对象用delete
- 避免内存泄漏

**相关项目：** Project_2, Project_3, Visitor, Template1

### 11.2 动态内存与多态
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

**相关项目：** Project_2, Project_3, Visitor

---

## 12. 组合关系

### 12.1 组合的概念
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

**相关项目：** ComputerPC

### 12.2 组合与继承的区别
**继承（is-a）：**
- Student是一个Person
- 表示"是一个"的关系

**组合（has-a）：**
- Computer有CPU
- 表示"有一个"的关系

**选择原则：**
- 能用组合就不用继承
- 组合更灵活，耦合度低

**相关项目：** ComputerPC

---

## 📖 项目与知识点对照表

| 项目名称 | 主要知识点 |
|---------|-----------|
| BankAccountProject | 类的基本概念、构造函数、析构函数、封装、文件操作 |
| BankAccount2 | 类的基本概念、构造函数、成员函数、文件操作 |
| JiCheng | 继承、访问控制（private/protected/public）、多层继承 |
| JiCheng2 | 继承、虚函数、多态、抽象类 |
| Operator | 运算符重载、虚函数、多态 |
| Template1 | 函数模板、类模板、模板特化、模板参数 |
| Project_2 | 抽象类、纯虚函数、多态、静态成员、友元类、虚析构函数、动态内存 |
| Project_3 | 抽象类、纯虚函数、多态、静态成员、友元类、虚析构函数、动态内存 |
| Visitor | 抽象类、纯虚函数、多态、动态绑定、虚析构函数 |
| FileOperation | 文件操作、封装、const成员函数 |
| BudgetProject | 静态成员、友元函数、静态成员函数 |
| ComputerPC | 组合关系、类的基本概念 |

---

## 🎯 学习建议

### 初学者路径
1. **BankAccountProject** → 理解类的基本概念
2. **BankAccount2** → 掌握成员函数和文件操作
3. **JiCheng** → 学习继承和访问控制
4. **ComputerPC** → 理解组合关系

### 进阶路径
5. **JiCheng2** → 掌握虚函数和多态
6. **Visitor** → 深入理解多态应用
7. **Operator** → 学习运算符重载
8. **FileOperation** → 掌握文件操作

### 高级路径
9. **Project_2** → 综合应用：抽象类、多态、静态成员、友元
10. **Project_3** → 综合应用：智能家居系统
11. **Template1** → 掌握模板编程
12. **BudgetProject** → 理解静态成员和友元

---

## 💡 重点难点

### 1. 多态机制
- 虚函数表（vtable）
- 动态绑定原理
- 虚析构函数的必要性

### 2. 内存管理
- 栈与堆的区别
- new/delete的正确使用
- 避免内存泄漏

### 3. 继承与组合
- 何时使用继承
- 何时使用组合
- 访问控制的理解

### 4. 模板编程
- 类型推导
- 模板特化
- 模板参数

---

## 📝 复习要点

### 考试常见题型
1. **概念题**：封装、继承、多态的理解
2. **代码阅读题**：分析程序输出
3. **代码填空题**：完成类的定义
4. **编程题**：设计类并实现功能

### 实践建议
1. 每个项目都要亲自编译运行
2. 修改代码观察结果变化
3. 尝试添加新功能
4. 画出类的继承关系图
5. 理解每个知识点的应用场景

---

**文档版本：** 1.0  
**最后更新：** 2026年4月  
**适用课程：** C++程序设计  
**编译环境：** Visual Studio 2010
