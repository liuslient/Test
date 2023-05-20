#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
    int a, b;
    char s;
    cin >> a >> b >> s;
    if (s == '+') {
        cout << a+b << endl;
    }
    else if (s == '-') {
        cout << a-b << endl;
    }
    else if (s == '*') {
        cout << a*b << endl;
    }
    else if (s == '/') {
        if (b == 0) cout << "Divided by zero!" << endl;
        else cout << a/b << endl;
    }
    else {
        cout << "Invalid operator!" << endl;
    }
    
}