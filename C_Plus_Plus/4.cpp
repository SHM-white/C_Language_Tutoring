#include <iostream>
#include <cstring>
using namespace std;

class Employee {
protected:
    char name[20];
    int ID;

public:
    Employee(int id, const char *n) {
        ID = id;
        strncpy(name, n, 20);
    }

    virtual double getSal() = 0;

    void set(int id, const char *n) {
        ID = id;
        strncpy(name, n, 20);
    }

    char *getName() {
        return name;
    }

    int getID() {
        return ID;
    }

    void showSal() {
        cout << "\n姓名：" << name << " 工号：" << ID << " 工资：" << getSal() << endl;
    }
};

class Manger : public Employee {
    double sal;

public:
    Manger(int id, const char *n, double s) : Employee(id, n), sal(s) {}

    double getSal() override {
        return sal;
    }
};

class HourlyWorker : public Employee {
    double wage;
    int hours;

public:
    HourlyWorker(int id, const char *n, double w, int h) : Employee(id, n), wage(w), hours(h) {}

    double getSal() override {
        return wage * hours;
    }
};

int main() {
    Manger m(999, "Zhangsan", 9000);
    HourlyWorker h(777, "Lisi", 150, 60);

    Employee *e1 = &m;
    Employee *e2 = &h;

    e1->showSal();
    e2->showSal();

    return 0;
}
