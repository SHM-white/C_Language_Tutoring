#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

void toUpperCaseAndMerge(const char *file1, const char *file2, const char *file3) {
    ifstream in1(file1), in2(file2);
    ofstream out(file3);
    if (!in1 || !in2 || !out) {
        cerr << "Error opening files!" << endl;
        return;
    }

    char ch;
    while (in1.get(ch)) {
        out.put(toupper(ch));
        cout << (char)toupper(ch);
    }
    while (in2.get(ch)) {
        out.put(toupper(ch));
        cout << (char)toupper(ch);
    }
    cout << endl;

    in1.close();
    in2.close();
    out.close();
}

int main() {
    toUpperCaseAndMerge("file1.txt", "file2.txt", "file3.txt");
    return 0;
}
