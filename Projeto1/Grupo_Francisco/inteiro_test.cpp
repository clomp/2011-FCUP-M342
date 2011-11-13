
#include <iostream>
#include "inteiro.h"
#include <cstdlib>
#include <ctime>

#define TEST(t)                                 \
    do{                                         \
        if (t)                                  \
            cout << "\t" << #t << endl;         \
        else                                    \
            cout << "  FAIL\t" << #t << endl;     \
    } while(0)


// Auxiliary functions to make tests more readable.
inteiro i(int a1) {
    bool negativo = a1 < 0;
    if (a1 < 0) a1 = -a1;
    vector<unsigned int> coef;
    coef.push_back(a1);
    return inteiro(negativo, coef);
}
inteiro i(int a1, unsigned int a2) {
    bool negativo = a1 < 0;
    if (a1 < 0) a1 = -a1;
    vector<unsigned int> coef;
    coef.push_back(a2);
    coef.push_back(a1);
    return inteiro(negativo, coef);
}
inteiro i(int a1, unsigned int a2, unsigned int a3) {
    bool negativo = a1 < 0;
    if (a1 < 0) a1 = -a1;
    vector<unsigned int> coef;
    coef.push_back(a3);
    coef.push_back(a2);
    coef.push_back(a1);
    return inteiro(negativo, coef);
}
inteiro i(int a1, unsigned int a2, unsigned int a3, unsigned int a4) {
    bool negativo = a1 < 0;
    if (a1 < 0) a1 = -a1;
    vector<unsigned int> coef;
    coef.push_back(a4);
    coef.push_back(a3);
    coef.push_back(a2);
    coef.push_back(a1);
    return inteiro(negativo, coef);
}

void test_constructors() {
    cout << endl;
    cout << "--------" << endl;
    cout << "Constructor Tests:" << endl;
    cout << "--------" << endl;

    cout << endl;
    cout << "  inteiro()" << endl;
    TEST(inteiro() == inteiro());
    TEST(inteiro() == inteiro(0));
    TEST(inteiro() == inteiro(false, vector<unsigned int>()));
    TEST(inteiro() == inteiro(true,  vector<unsigned int>()));

    cout << endl;
    cout << "  inteiro(int valor)" << endl;
    TEST(inteiro() != inteiro(1));
    TEST(inteiro() != inteiro(-1));
    TEST(inteiro(-1) != inteiro(1));

    cout << endl;
    cout << "  inteiro(bool negativo, vector<unsigned int> coefs)" << endl;

    TEST(inteiro(10) == i(10));
    TEST(inteiro(-10) != i(10));
    TEST(inteiro(10) != i(-10));
    TEST(inteiro(-10) == i(-10));
    TEST(i(10) != i(-10));

    vector<unsigned int> v0; v0.push_back(0);
    TEST(inteiro(true, v0) == inteiro(false, v0));

    TEST(i(10)       == i(0, 10));
    TEST(inteiro(10) == i(0, 10));
    TEST(i(10,0) != i(10));
    TEST(i(-10,0) != i(10, 0));

    cout << endl;
    cout << "   inteiro(string str)" << endl;

    TEST(inteiro() == inteiro(""));
    TEST(inteiro() == inteiro("0"));
    TEST(inteiro() == inteiro("-0000000000000000000000000000000000000"));
    TEST(inteiro(10) == inteiro("10"));
    TEST(inteiro(20) == inteiro("0000000000000000000000000020"));
    TEST(i(10, 20, 30) == inteiro("10000000020000000030"));
    TEST(inteiro(-39) == inteiro("-39"));
    TEST(i(-123,456) == inteiro("-123000000456"));
}

void test_comparison() {
    cout << endl;
    cout << "--------" << endl;
    cout << "Comparison Tests:" << endl;
    cout << "--------" << endl;

    cout << endl;
    cout << "    bool operator < (inteiro)" << endl;
    TEST(inteiro() < inteiro(1));
    TEST(inteiro(-1) < inteiro());
    TEST(!(inteiro() < inteiro()));
    TEST(!(inteiro(1) < inteiro()));
    TEST(i(10, 20) < i(11, 0));
    TEST(i(10, 20) < i(10, 21));
    TEST(!(i(10, 20) < i(9, 100000)));
    TEST(i(-10, 20) < i(-9, 100000));
    TEST(i(-10, 20) < i(10, 20));
    TEST(i(-10, 20) < i(-10, 19));

    cout << endl;
    cout << "    bool operator <= (inteiro)" << endl;
    TEST(inteiro() <= inteiro(1));
    TEST(inteiro(-1) <= inteiro());
    TEST(inteiro() <= inteiro());
    TEST(!(inteiro(1) <= inteiro()));
    TEST(i(10, 20) <= i(11, 0));
    TEST(i(10, 20) <= i(10, 21));
    TEST(!(i(10, 20) <= i(9, 100000)));
    TEST(i(-10, 20) <= i(-9, 100000));
    TEST(i(-10, 20) <= i(10, 20));
    TEST(i(-10, 20) <= i(-10, 19));

    cout << endl;
    cout << "    bool operator > (inteiro)" << endl;
    TEST(!(inteiro() > inteiro(1)));
    TEST(!(inteiro(-1) > inteiro()));
    TEST(!(inteiro() > inteiro()));
    TEST(inteiro(1) > inteiro());
    TEST(!(i(10, 20) > i(11, 0)));
    TEST(!(i(10, 20) > i(10, 21)));
    TEST(i(10, 20) > i(9, 100000));
    TEST(!(i(-10, 20) > i(-9, 100000)));
    TEST(!(i(-10, 20) > i(10, 20)));
    TEST(!(i(-10, 20) > i(-10, 19)));

    cout << endl;
    cout << "    bool operator >= (inteiro)" << endl;
    TEST(!(inteiro() >= inteiro(1)));
    TEST(!(inteiro(-1) >= inteiro()));
    TEST(inteiro() >= inteiro());
    TEST(inteiro(1) >= inteiro());
    TEST(!(i(10, 20) >= i(11, 0)));
    TEST(!(i(10, 20) >= i(10, 21)));
    TEST(i(10, 20) >= i(9, 100000));
    TEST(!(i(-10, 20) >= i(-9, 100000)));
    TEST(!(i(-10, 20) >= i(10, 20)));
    TEST(!(i(-10, 20) >= i(-10, 19)));
}

inteiro randint() {
    unsigned int size = rand() % 10;
    vector<unsigned int> coefs;
    bool negativo = rand() % 2;
    for (unsigned int i = 0; i < size; i++)
        coefs.push_back(rand()%1000000000);
    return inteiro(negativo, coefs);
}

inteiro randintnot0() {
    inteiro i;
    do {
        i = randint();
    } while(i == inteiro(0));
    return i;
}


void test_arithmetic() {
    cout << endl;
    cout << "--------" << endl;
    cout << "Arithmetic Tests:" << endl;
    cout << "--------" << endl;

    cout << endl;
    cout << "    inteiro operator + (inteiro)" << endl;
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(a + inteiro(0) == a);
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(inteiro(0) + a == a);
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(a + (-a) == inteiro(0));
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        inteiro b = randint();
        TEST(a + b == b + a);
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        inteiro b = randint();
        inteiro c = randint();
        TEST((a + b) + c == a + (b + c));
    }

    cout << endl;
    cout << "    inteiro operator - (inteiro)" << endl;
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(a - inteiro(0) == a);
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(inteiro(0) - a == -a);
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(a - a == inteiro(0));
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        inteiro b = randint();
        TEST(a - b == -(b - a));
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        inteiro b = randint();
        inteiro c = randint();
        TEST((a - b) - c == a - (b + c));

    }

    cout << endl;
    cout << "   inteiro operator * (inteiro)" << endl;
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(a * inteiro(0) == inteiro(0));
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(inteiro(0) * a == inteiro(0));
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(a * inteiro(1) == a);
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(inteiro(1) * a == a);
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(a * inteiro(-1) == -a);
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        inteiro b = randint();
        TEST(a * b == b * a);
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        inteiro b = randint();
        inteiro c = randint();
        TEST((a * b) * c == a * (b * c));
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        inteiro b = randint();
        inteiro c = randint();
        TEST((a + b) * c == (a * c) + (b * c));
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        inteiro b = randint();
        inteiro c = randint();
        TEST(a * (b + c) == (a * b) + (a * c));
    }

    cout << endl;
    cout << "   inteiro operator / (inteiro)" << endl;
    for (int i = 0; i < 5; i++) {
        inteiro a = randintnot0();
        TEST(inteiro(0) / a == inteiro(0));
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(a / inteiro(1) == a);
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(a / inteiro(-1) == -a);
    }
    for (int i = 0; i < 5; i++) {
        inteiro a, b;
        do {
            a = randint();
            b = randintnot0();
            if (a < inteiro(0)) a = -a;
            if (b < inteiro(0)) b = -b;
        } while(a >= b);
        TEST((a < b) && (a / b) == inteiro(0));
    }
    for (int i = 0; i < 10; i++) {
        inteiro a,b,c;
        do {
            a = randint();
            b = randintnot0();
            c = randintnot0();
        } while (a < inteiro(0) || b < inteiro(0) || c < inteiro(0));
        TEST((a / b) / c == a / (b * c));
    }
    for (int i = 0; i < 10; i++) {
        inteiro a,b,c;
        do {
            a = randint();
            b = randintnot0();
            c = randintnot0();
        } while (a < inteiro(0) || b < inteiro(0) || c < inteiro(0));
        TEST((a + b) / c >= (a / c) + (b / c));
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randintnot0();
        TEST(inteiro(0) % a == inteiro(0));
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(a % inteiro(1) == inteiro(0));
    }
    for (int i = 0; i < 5; i++) {
        inteiro a = randint();
        TEST(a % inteiro(-1) == inteiro(0));
    }
    for (int i = 0; i < 10; i++) {
        inteiro a,b, c = randint();
        do {
            a = randint();
            b = randintnot0();
        } while (a < inteiro(0) || b < inteiro(0) || a >= b);

        TEST((a < b) && ((a + b*c) % b == a));
    }
    for (int i = 0; i < 20; i++) {
        inteiro a = randint();
        inteiro b = randintnot0();
        inteiro q = a/b;
        inteiro r = a%b;
        TEST(a == q*b + r);
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    test_constructors();
    test_comparison();
    test_arithmetic();
}
