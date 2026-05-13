#ifndef _TEST_H
#define _TEST_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// ============================================================
// 知识点9: 模板 (Template) - 函数模板
// ============================================================
template <typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

// 模板特化 (inline 防止多重定义)
template <>
inline string getMax<string>(string a, string b) {
    return (a.length() > b.length()) ? a : b;
}

// ============================================================
// 知识点9: 模板 (Template) - 类模板
// ============================================================
template <typename T, int SIZE = 10>
class FixedArray {
private:
    T data[SIZE];
    int currentSize;
public:
    FixedArray();
    void set(int index, T value);
    T get(int index) const;
    int getSize() const;
    void display() const;
};

// ============================================================
// 知识点1: 基础语法与类的基本概念
// 知识点3: 封装与访问控制 (private / protected / public)
// 知识点7: 静态成员 (static)
// 知识点8: 友元 (friend)
// ============================================================
class Person {
private:        // 知识点3: private - 类内部访问
    string name;
    int age;

protected:      // 知识点3: protected - 派生类可访问
    long id;

public:         // 知识点3: public - 对外接口

    // ========================================================
    // 知识点2: 构造函数与析构函数
    // ========================================================
    // 知识点2.1: 默认构造函数
    Person();

    // 知识点2.2: 带参数构造函数
    Person(const string& n, int a, long pid);

    // 知识点2.3: 拷贝构造函数
    Person(const Person& other);

    // 知识点2.5: 虚析构函数
    virtual ~Person();

    // Getter / Setter
    string getName() const;
    int getAge() const;
    long getId() const;
    void setName(const string& n);
    void setAge(int a);

    // ========================================================
    // 知识点5: 多态与虚函数
    // ========================================================
    virtual void displayInfo() const;

    // ========================================================
    // 知识点6: 运算符重载
    // ========================================================
    // 重载 + 运算符
    Person operator+(const Person& other) const;

    // ========================================================
    // 知识点8: 友元 - 重载 << 为友元函数
    // ========================================================
    friend ostream& operator<<(ostream& os, const Person& p);

    // ========================================================
    // 知识点7: 静态成员函数
    // ========================================================
    static int getTotalCount();

    // ========================================================
    // 知识点7: 静态成员变量 (类外初始化)
    // ========================================================
    static int totalCount;
};

// ============================================================
// 知识点4: 继承 (Inheritance)
// 知识点5: 多态与虚函数 (override)
// ============================================================
class Student : public Person {
private:
    string major;
    double score;

public:
    // 知识点4.3: 派生类构造函数必须调用基类构造函数
    Student();
    Student(const string& n, int a, long pid, const string& m, double s);
    Student(const Student& other);

    // 知识点2.4: 析构函数
    ~Student();

    // 知识点5.3: 重写虚函数 (override)
    void displayInfo() const override;

    string getMajor() const;
    double getScore() const;
    void setMajor(const string& m);
    void setScore(double s);

    // 知识点8: 友元函数
    friend ostream& operator<<(ostream& os, const Student& s);
};

// ============================================================
// 知识点12: 组合关系 (Composition) - has-a
// 知识点11: 动态内存管理 (new/delete)
// ============================================================
class Course {
private:
    string courseName;
    Student* students;      // 知识点11: 动态数组
    int capacity;
    int count;

public:
    Course(const string& name, int cap);
    ~Course();

    // 知识点11: 动态内存 - 添加学生 (new)
    bool addStudent(const Student& s);

    // 知识点11: 动态内存 - 释放 (delete[])
    void clear();

    void displayAll() const;
    string getCourseName() const;
    int getStudentCount() const;
};

// ============================================================
// 知识点10: 文件操作 (File Operations)
// ============================================================
class FileManager {
public:
    static bool saveToFile(const string& filename, const Student& s);
    static void readFromFile(const string& filename);
};

// ============================================================
// 知识点9: 类模板特化
// ============================================================
template <>
class FixedArray<double, 10> {
private:
    double data[10];
    int currentSize;
public:
    FixedArray();
    void set(int index, double value);
    double get(int index) const;
    int getSize() const;
    void display() const;
};

#endif