#include "test.h"

// ============================================================
// C++ 程序设计 - 综合示例项目
// 涵盖全部 12 个核心知识点
// ============================================================

void demo_ClassAndEncapsulation() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║  知识点1&3: 类的基本概念 & 封装与访问控制      ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";

    // 创建对象 - 带参数构造函数
    Person p1("张三", 25, 1001);
    Person p2("李四", 30, 1002);

    // 通过公有接口访问私有成员 (封装)
    cout << "\n--- 通过 getter 访问私有成员 ---" << endl;
    cout << "p1.getName() = " << p1.getName() << endl;
    cout << "p1.getAge()  = " << p1.getAge() << endl;

    // 通过 setter 修改私有成员 (含数据校验)
    cout << "\n--- 通过 setter 修改私有成员 ---" << endl;
    p1.setAge(26);
    cout << "修改后 p1.getAge() = " << p1.getAge() << endl;
    p1.setAge(-5);  // 非法值测试
    cout << "设为负数后 p1.getAge() = " << p1.getAge() << " (防非法修改)" << endl;
}

void demo_ConstructorAndDestructor() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║  知识点2: 构造函数与析构函数                    ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";

    // 默认构造函数
    cout << "\n--- 默认构造函数 ---" << endl;
    Person defaultPerson;

    // 带参数构造函数
    cout << "\n--- 带参数构造函数 ---" << endl;
    Person paramPerson("王五", 22, 1003);

    // 拷贝构造函数 - 直接初始化
    cout << "\n--- 拷贝构造函数: Person p3(paramPerson) ---" << endl;
    Person copyPerson1(paramPerson);

    // 拷贝构造函数 - 赋值初始化
    cout << "\n--- 拷贝构造函数: Person p4 = paramPerson ---" << endl;
    Person copyPerson2 = paramPerson;

    // 析构函数在对象离开作用域时自动调用
    cout << "\n--- (离开此函数时所有局部对象自动析构) ---" << endl;
}

void demo_Inheritance() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║  知识点4: 继承                                  ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";

    // 派生类 Student 继承自 Person (is-a 关系)
    // 派生类构造函数调用基类构造函数
    cout << "\n--- 创建 Student 对象 (派生类) ---" << endl;
    Student stu1("赵六", 20, 2024001, "计算机科学", 88.5);
    Student stu2("孙七", 21, 2024002, "数学", 92.0);

    // 派生类可以访问基类的公有成员
    cout << "\n--- 通过继承的基类接口访问 ---" << endl;
    cout << stu1.getName() << " 的基类 ID: " << stu1.getId() << endl;

    // 使用基类指针指向派生类对象 (向上转型)
    cout << "\n--- 基类指针指向派生类对象 ---" << endl;
    Person* p = &stu1;
    p->displayInfo();   // 调用基类版本
    cout << endl;

    cout << "\n--- (离开此函数时自动析构) ---" << endl;
}

void demo_Polymorphism() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║  知识点5: 多态与虚函数                          ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";

    cout << "\n--- 基类指针数组实现多态 ---" << endl;
    Person* persons[4];

    // 基类指针指向不同类型的对象
    persons[0] = new Person("周八", 40, 2001);
    persons[1] = new Student("吴九", 19, 2024003, "物理", 95.5);
    persons[2] = new Student("郑十", 22, 2024004, "化学", 87.0);
    persons[3] = new Person("冯十一", 35, 2002);

    for (int i = 0; i < 4; i++) {
        cout << "  persons[" << i << "]->displayInfo() => ";
        persons[i]->displayInfo();  // 动态绑定: 根据实际类型调用
        cout << endl;
    }

    // 释放动态内存 (验证虚析构函数)
    cout << "\n--- 释放动态对象 (验证虚析构函数) ---" << endl;
    for (int i = 0; i < 4; i++) {
        delete persons[i];
    }
}

void demo_OperatorOverload() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║  知识点6: 运算符重载                            ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";

    Person a("Alice", 28, 3001);
    Person b("Bob", 35, 3002);

    // 重载 <<  (友元函数)
    cout << "\n--- 重载 << 输出 ---" << endl;
    cout << "  a = " << a << endl;
    cout << "  b = " << b << endl;

    // 重载 +
    cout << "\n--- 重载 + (返回年龄较大者) ---" << endl;
    Person older = a + b;
    cout << "  a + b = " << older << endl;

    // 用 Student 测试 << 重载
    Student s("Charlie", 18, 2024005, "英语", 91.0);
    cout << "\n--- Student 的 << 重载 ---" << endl;
    cout << "  s = " << s << endl;
}

void demo_StaticMember() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║  知识点7: 静态成员                              ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";

    // 通过类名访问静态成员函数 (不依赖对象)
    cout << "\n当前存活对象数: " << Person::getTotalCount() << endl;

    {
        Person p1("静态测试1", 20, 4001);
        Person p2("静态测试2", 25, 4002);
        Student s1("静态测试3", 18, 2024006, "历史", 85.0);

        // 静态变量在所有对象间共享
        cout << "创建3个对象后, 存活对象数: " << Person::getTotalCount() << endl;
    }

    // 离开作用域后对象被销毁
    cout << "离开作用域后, 存活对象数: " << Person::getTotalCount() << endl;
}

void demo_Friend() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║  知识点8: 友元                                  ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";

    // operator<< 是 Person 的友元函数, 可以直接访问私有成员 name, age
    // 这里演示友元函数访问私有成员
    Person p("友元测试", 25, 5001);

    cout << "\n--- 友元函数 operator<< 访问私有成员 ---" << endl;
    cout << "  cout << p 调用友元函数: " << p << endl;

    // Student 也有自己的友元函数 operator<<
    Student s("友元学生", 20, 2024007, "艺术", 78.5);
    cout << "  cout << s 调用友元函数: " << s << endl;

    cout << "\n说明: operator<< 作为友元函数, 可以直接访问类的私有成员。" << endl;
}

void demo_Template() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║  知识点9: 模板                                  ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";

    // 函数模板
    cout << "\n--- 函数模板 ---" << endl;
    cout << "  getMax(10, 20)          = " << getMax(10, 20) << endl;
    cout << "  getMax(3.14, 2.71)      = " << getMax(3.14, 2.71) << endl;
    cout << "  getMax('A', 'Z')        = " << getMax('A', 'Z') << endl;

    // 函数模板特化 (比较字符串长度)
    cout << "  getMax<string>(\"hello\", \"world!\") = "
         << getMax<string>("hello", "world!") << endl;

    // 类模板 (默认大小 10)
    cout << "\n--- 类模板 FixedArray<int> ---" << endl;
    FixedArray<int> intArr;
    intArr.set(0, 10);
    intArr.set(1, 20);
    intArr.set(2, 30);
    intArr.set(3, 40);
    intArr.set(4, 50);
    cout << "  ";
    intArr.display();
    cout << "  数组大小: " << intArr.getSize() << endl;

    // 类模板 (指定非类型参数)
    cout << "\n--- 类模板 FixedArray<string, 5> ---" << endl;
    FixedArray<string, 5> strArr;
    strArr.set(0, "C++");
    strArr.set(1, "Java");
    strArr.set(2, "Python");
    cout << "  ";
    strArr.display();

    // 类模板特化
    cout << "\n--- 类模板特化 FixedArray<double, 10> ---" << endl;
    FixedArray<double, 10> dblArr;
    dblArr.set(0, 3.14159);
    dblArr.set(1, 2.71828);
    dblArr.set(2, 1.41421);
    cout << "  ";
    dblArr.display();
}

void demo_FileOperations() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║  知识点10: 文件操作                             ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";

    const string filename = "students.txt";

    // 写入文件
    cout << "\n--- 写入学生信息到文件 ---" << endl;
    Student s1("文件学生1", 20, 2024008, "计算机", 90.0);
    Student s2("文件学生2", 21, 2024009, "电子工程", 85.5);
    Student s3("文件学生3", 19, 2024010, "机械工程", 88.0);

    FileManager::saveToFile(filename, s1);
    FileManager::saveToFile(filename, s2);
    FileManager::saveToFile(filename, s3);

    // 读取文件
    cout << "\n--- 从文件读取学生信息 ---" << endl;
    FileManager::readFromFile(filename);
}

void demo_DynamicMemory() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║  知识点11: 动态内存管理                         ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";

    // new 单个对象
    cout << "\n--- new/delete 单个对象 ---" << endl;
    Person* pSingle = new Person("动态内存测试", 28, 6001);
    cout << "  " << *pSingle << endl;
    delete pSingle;     // 调用析构函数
    cout << "  已 delete 单个对象" << endl;

    // new 对象数组
    cout << "\n--- new[]/delete[] 对象数组 ---" << endl;
    Person* pArray = new Person[3]{
        Person("数组元素1", 20, 6002),
        Person("数组元素2", 22, 6003),
        Person("数组元素3", 24, 6004)
    };
    cout << "  数组第二个元素: " << pArray[1] << endl;
    delete[] pArray;    // 调用每个元素的析构函数
    cout << "  已 delete[] 对象数组" << endl;
}

void demo_Composition() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════╗\n";
    cout << "║  知识点12: 组合关系                             ║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";

    // Course 包含 Student 对象 (has-a 关系)
    cout << "\n--- 创建课程 (组合: Course has-a Student) ---" << endl;
    Course cppCourse("C++ 程序设计", 5);

    // 添加学生 (内部调用拷贝构造函数)
    cppCourse.addStudent(Student("组合学生1", 20, 2024011, "软件工程", 91.0));
    cppCourse.addStudent(Student("组合学生2", 21, 2024012, "网络工程", 85.5));
    cppCourse.addStudent(Student("组合学生3", 19, 2024013, "信息安全", 78.0));

    // 显示所有学生
    cppCourse.displayAll();

    // 清空课程 (验证动态内存释放)
    cout << "\n--- 清空课程 ---" << endl;
    cppCourse.clear();

    cout << "\n--- 课程析构时自动释放内部动态数组 ---" << endl;
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║     C++ 程序设计知识点综合示例                          ║\n";
    cout << "║     包含全部 12 个核心知识点                             ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n";
    cout << "\n当前代码行数: 约 450 行\n";

    // ================================================================
    // 按顺序演示每个知识点
    // ================================================================

    // 知识点1 & 3: 类的基本概念 & 封装与访问控制
    demo_ClassAndEncapsulation();

    // 知识点2: 构造函数与析构函数
    demo_ConstructorAndDestructor();

    // 知识点4: 继承
    demo_Inheritance();

    // 知识点5: 多态与虚函数
    demo_Polymorphism();

    // 知识点6: 运算符重载
    demo_OperatorOverload();

    // 知识点7: 静态成员
    demo_StaticMember();

    // 知识点8: 友元
    demo_Friend();

    // 知识点9: 模板
    demo_Template();

    // 知识点10: 文件操作
    demo_FileOperations();

    // 知识点11: 动态内存管理
    demo_DynamicMemory();

    // 知识点12: 组合关系
    demo_Composition();

    // ================================================================
    // 最终统计
    // ================================================================
    cout << "\n╔══════════════════════════════════════════════════════════╗\n";
    cout << "║  所有知识点演示完毕!                                    ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n";
    cout << "最终存活对象数: " << Person::getTotalCount() << endl;

    return 0;
}