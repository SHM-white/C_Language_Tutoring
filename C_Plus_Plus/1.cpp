#include <iostream>
#include <cstring>
using namespace std;

class Student {
    char name[10];
    int id;
    int age;
    char *college;
    static int studentNum;

public:
    Student(const char *name, int id, int age, const char *college) {
        strncpy(this->name, name, 10);
        this->id = id;
        this->age = age;
        this->college = new char[strlen(college) + 1];
        strcpy(this->college, college);
        studentNum++;
    }

    Student(const Student &other) {
        strncpy(this->name, other.name, 10);
        this->id = other.id;
        this->age = other.age;
        this->college = new char[strlen(other.college) + 1];
        strcpy(this->college, other.college);
        studentNum++;
    }

    ~Student() {
        delete[] college;
    }

    void display() const {
        cout << "Name: " << name << ", ID: " << id << ", Age: " << age << ", College: " << college << endl;
    }

    static int getStudentNum() {
        return studentNum;
    }
};

int Student::studentNum = 0;

int main() {
    Student s1("Alice", 1001, 20, "Engineering");
    Student s2("Bob", 1002, 21, "Science");
    s1.display();
    s2.display();
    cout << "Total students: " << Student::getStudentNum() << endl;
    return 0;
}
