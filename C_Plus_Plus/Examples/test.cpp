#include "test.h"
#include <iomanip>

// ============================================================
// 知识点7: 静态成员变量 类外初始化
// ============================================================
int Person::totalCount = 0;

// ============================================================
// 知识点2: 构造函数与析构函数 - Person
// ============================================================

// 知识点2.1: 默认构造函数
Person::Person() : name("Unknown"), age(0), id(0) {
    totalCount++;
    cout << "[Person] 默认构造函数: " << name << endl;
}

// 知识点2.2: 带参数构造函数
Person::Person(const string& n, int a, long pid)
    : name(n), age(a), id(pid) {
    totalCount++;
    cout << "[Person] 带参数构造函数: " << name << endl;
}

// 知识点2.3: 拷贝构造函数
Person::Person(const Person& other)
    : name(other.name), age(other.age), id(other.id) {
    totalCount++;
    cout << "[Person] 拷贝构造函数: 拷贝 " << other.name << endl;
}

// 知识点2.5: 虚析构函数
Person::~Person() {
    totalCount--;
    cout << "[Person] 析构函数: " << name << " 被销毁, 剩余 " << totalCount << " 人" << endl;
}

// Getter / Setter
string Person::getName() const { return name; }
int Person::getAge() const { return age; }
long Person::getId() const { return id; }
void Person::setName(const string& n) { name = n; }
void Person::setAge(int a) { age = (a >= 0) ? a : 0; }

// 知识点5.1: 虚函数
void Person::displayInfo() const {
    cout << "姓名: " << name << ", 年龄: " << age << ", ID: " << id;
}

// 知识点6.2: 运算符重载 + (返回年龄较大者的拷贝)
Person Person::operator+(const Person& other) const {
    if (this->age >= other.age) {
        return Person(*this);   // 调用拷贝构造函数
    } else {
        return Person(other);   // 调用拷贝构造函数
    }
}

// 知识点6.1+8: 友元函数重载 <<
ostream& operator<<(ostream& os, const Person& p) {
    os << "[Person] " << p.name << ", 年龄: " << p.age << ", ID: " << p.id;
    return os;
}

// 知识点7.2: 静态成员函数
int Person::getTotalCount() {
    return totalCount;
}

// ============================================================
// 知识点4: 继承 - Student
// ============================================================

// 知识点4.3: 派生类构造函数调用基类构造函数
Student::Student() : Person(), major("未定"), score(0.0) {
    cout << "[Student] 默认构造函数: " << getName() << ", 专业: " << major << endl;
}

Student::Student(const string& n, int a, long pid, const string& m, double s)
    : Person(n, a, pid), major(m), score(s) {
    cout << "[Student] 带参数构造函数: " << n << ", 专业: " << m << endl;
}

Student::Student(const Student& other)
    : Person(other), major(other.major), score(other.score) {
    cout << "[Student] 拷贝构造函数: 拷贝 " << other.getName() << endl;
}

// 知识点2.4: 析构函数
Student::~Student() {
    cout << "[Student] 析构函数: " << getName() << " 学生对象被销毁" << endl;
}

// 知识点5.3: 重写虚函数 (override)
void Student::displayInfo() const {
    Person::displayInfo();
    cout << ", 专业: " << major << ", 成绩: " << fixed << setprecision(1) << score;
}

string Student::getMajor() const { return major; }
double Student::getScore() const { return score; }
void Student::setMajor(const string& m) { major = m; }
void Student::setScore(double s) { score = (s >= 0 && s <= 100) ? s : 0; }

ostream& operator<<(ostream& os, const Student& s) {
    os << "[Student] " << s.getName() << ", 专业: " << s.major
       << ", 成绩: " << fixed << setprecision(1) << s.score;
    return os;
}

// ============================================================
// 知识点12: 组合关系 + 知识点11: 动态内存管理 - Course
// ============================================================

Course::Course(const string& name, int cap)
    : courseName(name), capacity(cap), count(0) {
    // 知识点11: new 分配动态数组
    students = new Student[capacity];
    cout << "[Course] 创建课程 \"" << name << "\", 容量: " << capacity << endl;
}

Course::~Course() {
    // 知识点11: delete[] 释放动态数组
    delete[] students;
    cout << "[Course] 课程 \"" << courseName << "\" 被销毁, 内存已释放" << endl;
}

bool Course::addStudent(const Student& s) {
    if (count >= capacity) {
        cout << "[Course] 课程已满, 无法添加 " << s.getName() << endl;
        return false;
    }
    // 知识点2.3: 调用拷贝构造函数
    students[count] = s;
    count++;
    cout << "[Course] 添加学生: " << s.getName() << " (当前人数: " << count << "/" << capacity << ")" << endl;
    return true;
}

void Course::clear() {
    // 知识点11: 重置
    delete[] students;
    students = new Student[capacity];
    count = 0;
    cout << "[Course] 课程已清空" << endl;
}

void Course::displayAll() const {
    cout << "\n========== 课程 \"" << courseName << "\" 学生列表 ==========" << endl;
    if (count == 0) {
        cout << "  (暂无学生)" << endl;
    } else {
        for (int i = 0; i < count; i++) {
            cout << "  " << (i + 1) << ". ";
            students[i].displayInfo();
            cout << endl;
        }
    }
    cout << "==============================================" << endl;
}

string Course::getCourseName() const { return courseName; }
int Course::getStudentCount() const { return count; }

// ============================================================
// 知识点10: 文件操作 - FileManager
// ============================================================

bool FileManager::saveToFile(const string& filename, const Student& s) {
    ofstream fout(filename, ios::app);   // 追加模式
    if (!fout) {
        cout << "[文件] 打开文件失败: " << filename << endl;
        return false;
    }
    fout << s.getName() << " "
         << s.getAge() << " "
         << s.getId() << " "
         << s.getMajor() << " "
         << s.getScore() << endl;
    fout.close();
    cout << "[文件] 成功保存学生信息到: " << filename << endl;
    return true;
}

void FileManager::readFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "[文件] 打开文件失败: " << filename << endl;
        return;
    }

    cout << "\n========== 从文件读取数据: " << filename << " ==========" << endl;
    string name, major;
    int age;
    long id;
    double score;
    int count = 0;

    while (fin >> name >> age >> id >> major >> score) {
        count++;
        cout << "  " << count << ". " << name
             << ", 年龄: " << age
             << ", ID: " << id
             << ", 专业: " << major
             << ", 成绩: " << fixed << setprecision(1) << score << endl;
    }

    if (count == 0) {
        cout << "  (文件为空或无有效数据)" << endl;
    } else {
        cout << "  共读取 " << count << " 条记录" << endl;
    }

    fin.close();
    cout << "==============================================" << endl;
}

// ============================================================
// 知识点9: 类模板实现
// ============================================================
template <typename T, int SIZE>
FixedArray<T, SIZE>::FixedArray() : currentSize(0) {}

template <typename T, int SIZE>
void FixedArray<T, SIZE>::set(int index, T value) {
    if (index >= 0 && index < SIZE) {
        data[index] = value;
        if (index >= currentSize) currentSize = index + 1;
    }
}

template <typename T, int SIZE>
T FixedArray<T, SIZE>::get(int index) const {
    return (index >= 0 && index < SIZE) ? data[index] : T();
}

template <typename T, int SIZE>
int FixedArray<T, SIZE>::getSize() const { return SIZE; }

template <typename T, int SIZE>
void FixedArray<T, SIZE>::display() const {
    cout << "FixedArray<" << typeid(T).name() << ", " << SIZE << ">: [";
    for (int i = 0; i < currentSize; i++) {
        if (i > 0) cout << ", ";
        cout << data[i];
    }
    cout << "]" << endl;
}

// ============================================================
// 知识点9: 类模板特化实现 (double)
// 注意: 特化类的成员函数定义不需要 template<> 前缀
// ============================================================
FixedArray<double, 10>::FixedArray() : currentSize(0) {}

void FixedArray<double, 10>::set(int index, double value) {
    if (index >= 0 && index < 10) {
        data[index] = value;
        if (index >= currentSize) currentSize = index + 1;
    }
}

double FixedArray<double, 10>::get(int index) const {
    return (index >= 0 && index < 10) ? data[index] : 0.0;
}

int FixedArray<double, 10>::getSize() const { return 10; }

void FixedArray<double, 10>::display() const {
    cout << "FixedArray<double, 10> (特化版本): [";
    for (int i = 0; i < currentSize; i++) {
        if (i > 0) cout << ", ";
        cout << fixed << setprecision(2) << data[i];
    }
    cout << "]" << endl;
}

// ============================================================
// 显式实例化 (Explicit Instantiation)
// 使模板在 test.cpp 中实例化, 供 main.cpp 链接
// ============================================================
template class FixedArray<int, 10>;
template class FixedArray<string, 5>;