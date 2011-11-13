#include "inteiro.h"
#include <iostream>

using namespace std;

inteiro factorial(inteiro n) {
    inteiro t(1);
    for (inteiro i(1); i <= n; i = i + inteiro(1))
        t = t * i;   
    return t;
}

int main(int argc, char** argv) {
    cout << "100!  = "
         << factorial(inteiro(100)).ConvertToString() << endl;
    cout << "1000! = "
         << factorial(inteiro(1000)).ConvertToString() << endl;
    return 0;
}

