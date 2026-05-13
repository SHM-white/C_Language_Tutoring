#include <iostream>
using namespace std;

class Integer {
    int *pval;

public:
    Integer(int i = 0) {
        pval = new int(i);
    }

    Integer(const Integer &other) {
        pval = new int(*other.pval);
    }

    ~Integer() {
        delete pval;
    }

    Integer operator+(const Integer &right) {
        return Integer(*pval + *right.pval);
    }

    Integer &operator=(const Integer &right) {
        if (this != &right) {
            *pval = *right.pval;
        }
        return *this;
    }

    void outprint() const {
        cout << *pval << endl;
    }
};

int main() {
    Integer a(10), b(20), c;
    c = a + b;
    c.outprint();
    a = b;
    a.outprint();
    return 0;
}
