#include "inteiro.h"
#include <iostream>

using namespace std;

inteiro divisor(inteiro n) {
    for (inteiro i(2); i*i <= n; i = i + inteiro(1)) {
        if (n % i == inteiro(0))
            return i;
    }
    return n;
}

int main(int argc, char** argv) {
    inteiro n("10000000001");
    cout << "Factors of " << n.ConvertToString() << ":" << endl;
    while (n > inteiro(1)) {
        inteiro d = divisor(n);
        cout << "    " << d.ConvertToString() << endl;
        n = n / d;
    }
    return 0;
}

