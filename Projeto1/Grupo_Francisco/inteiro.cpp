#include <cassert>
#include <cstdlib>
#include <utility>

#include "inteiro.h"

#define BASE 1000000000
#define BASELEN 9

// Funcoes auxiliares (Christian Lomp)

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
string ConvertVectorToString(vector<unsigned int> v)
{
	int n=v.size();
	ostringstream vector_string;
	for(int i=n-1; i>=0;i--) {
        unsigned int z=v[i];
        if(i<n-1) {
            unsigned int s=BASE/10;
            while(z < s) {
                vector_string << "0";
                s=s/10;
            }
        }
		vector_string << z;
    }
	return vector_string.str();
}

vector<unsigned int> ConvertStringToVector(string s)
{
	vector<unsigned int> v;
    int n=s.length();
	int q=n/BASELEN;
	int r=n%BASELEN;
	string sub;
    for(int i=q-1;i>=0;i--) {
		sub=s.substr(r+i*BASELEN,BASELEN);
		v.push_back(atoi(sub.c_str()));
	}
	if(r>0) {
		sub=s.substr(0,r);
		v.push_back(atoi(sub.c_str()));
	}
    return v;
}


// Construtores
inteiro::inteiro() {
    negativo = false;
}

inteiro::inteiro(int n) {
    negativo = n < 0;
    if (n <  0) n = -n;
    if (n == 0) return;
    if (n >= BASE) {
        coeficientes.push_back(n % BASE);
        coeficientes.push_back(n / BASE);
    } else {
        coeficientes.push_back(n);
    }
}

inteiro::inteiro(bool sinal, vector<unsigned int> coef) {
    negativo = sinal;
    coeficientes = coef;
    // trim any excessive zeros.
    while (coeficientes.size() && !coeficientes[coeficientes.size()-1]) {
        coeficientes.pop_back();
    }
    // if we are zero, we aren't negative.
    if (!coeficientes.size())
        negativo = false;
}

inteiro::inteiro(string str) {
    negativo = str[0] == '-';
    if (negativo)
        str = str.substr(1);
    coeficientes = ConvertStringToVector(str);
    // trim any excessive zeros.
    while (coeficientes.size() && !coeficientes[coeficientes.size()-1]) {
        coeficientes.pop_back();
    }
    // if we are zero, we aren't negative.
    if (!coeficientes.size())
        negativo = false;
}

// Comparacao

bool inteiro::operator == (inteiro b) {
    return negativo == b.negativo && coeficientes == b.coeficientes;
}

bool inteiro::operator != (inteiro b) {
    return !(*this == b);
}

bool inteiro::operator < (inteiro b) {
    if (negativo && !b.negativo)
        return true;
    if (!negativo && b.negativo)
        return false;
    if (negativo && b.negativo)
        return -b < -*this;
    if (b.coeficientes.size() > coeficientes.size())
        return true;
    if (b.coeficientes.size() < coeficientes.size())
        return false;
    for (int i = coeficientes.size()-1; i >= 0; i--) {
        if (b.coeficientes[i] > coeficientes[i])
            return true;
        if (b.coeficientes[i] < coeficientes[i])
            return false;
    }
    return false;
}

bool inteiro::operator > (inteiro b) {
    return b < *this;
}

bool inteiro::operator <= (inteiro b) {
    return *this == b || *this < b;
}

bool inteiro::operator >= (inteiro b) {
    return *this == b || b < *this;
}

// Operadores.

inteiro inteiro::operator - () {
    return inteiro(!negativo, coeficientes);
}

inteiro inteiro::operator + (inteiro b) {
    if (!negativo && b.negativo)
        return *this - (-b);
    if (negativo && !b.negativo)
        return b - (-*this);
    vector<unsigned int> coefs;
    unsigned long long carry = 0;
    unsigned int size = max(coeficientes.size(), b.coeficientes.size());
    for (unsigned int i = 0; i < size; i++) {
        unsigned long long result = carry;
        if (i < coeficientes.size())
            result += (unsigned long long)coeficientes[i];
        if (i < b.coeficientes.size())
            result += (unsigned long long)b.coeficientes[i];
        carry = result / BASE;
        coefs.push_back(result % BASE);
    }
    if (carry)
        coefs.push_back(carry);
    return inteiro(negativo, coefs);
}

inteiro inteiro::operator - (inteiro b) {
    if (negativo && b.negativo)
        return -((-*this) - (-b));
    if (negativo && !b.negativo)
        return -((-*this) + b);
    if (!negativo && b.negativo)
        return  *this + (-b);
    if (*this < b)
        return -(b - *this);

    vector<unsigned int> coefs;
    unsigned long long borrow = 0;
    unsigned int size = max(coeficientes.size(), b.coeficientes.size());
    for (unsigned int i = 0; i < size; i++) {
        long long result = -borrow;
        if (i < coeficientes.size())
            result += (unsigned long long)coeficientes[i];
        if (i < b.coeficientes.size())
            result -= (unsigned long long)b.coeficientes[i];
        borrow = 0;
        while (result < 0) {
            result += BASE;
            borrow += 1;
        }
        coefs.push_back(result);
    }
    assert(borrow == 0);
    return inteiro(false, coefs);
}

// Get an integer with digits:
//     coeficientes[start], ..., coeficientes[end-1]
inteiro inteiro::slice (int start, int end) {
    vector<unsigned int> coefs;
    if (start < 0)
        start = 0;
    if (end > (int)coeficientes.size())
        end = coeficientes.size();

    for (int i = start; i < end; i++)
        coefs.push_back(coeficientes[i]);
    return inteiro(negativo, coefs);
}

// Shift an integer up -- i.e. multiply by q^k;
inteiro inteiro::shift (int k) {
    vector<unsigned int> coefs;
    for (int i = 0; i < k; i++)
        coefs.push_back(0);
    for (int i = 0; i < coeficientes.size(); i++)
        coefs.push_back(coeficientes[i]);
    return inteiro(negativo, coefs);
}

inteiro inteiro::operator * (inteiro b) {
    if (negativo &&  b.negativo)
        return (-*this) * (-b);
    if (negativo && !b.negativo)
        return -((-*this) * b);
    if (!negativo && b.negativo)
        return -(*this * (-b));

    int size = max(coeficientes.size(), b.coeficientes.size());
    if (size < 5) {
        inteiro result;
        for (unsigned int i = 0; i < coeficientes.size(); i++) {
            vector<unsigned int> c;
            vector<unsigned int> d;
            for (unsigned int j = 0; j < b.coeficientes.size(); j++) {
                unsigned long long x =   coeficientes[i];
                unsigned long long y = b.coeficientes[j];
                unsigned long long r = x * y;
                c.push_back(r % BASE);
                d.push_back(r / BASE);
            }
            result = result + inteiro(false, c).shift(i);
            result = result + inteiro(false, d).shift(i+1);
        }

        return result;
    } else {
        unsigned int mid = (size+1)/2;

        inteiro a1 =   slice(mid, size);
        inteiro a2 =   slice(0,   mid);
        inteiro b1 = b.slice(mid, size);
        inteiro b2 = b.slice(0,   mid);

        inteiro u  = a1 * b1;
        inteiro v  = a2 * b2;
        inteiro w  = (a1+a2) * (b1+b2);

        return u.shift(2*mid) + (w - u - v).shift(mid) + v;
    }
}

pair<inteiro, inteiro> inteiro::divmod (inteiro b) {
    assert(*this >= 0);
    assert(b > 0);

    int ka =   coeficientes.size();
    int kb = b.coeficientes.size();

    // approximate b from above, so bcoef*BASE^kb >= b > (bcoef-1)*BASE^kb:
    unsigned long long bcoef = b.coeficientes[kb-1];
    if (b.slice(0, kb-2) != inteiro(0))
        bcoef++;

    inteiro q;
    inteiro r = *this;

    while (r >= b && ka > kb) {
        unsigned long long boundary = 0;
        boundary  = r.coeficientes[ka-1];
        boundary *= BASE;
        boundary += r.coeficientes[ka-2];

        unsigned long long step = boundary / bcoef;
        vector<unsigned int> cstep;
        cstep.push_back(step % BASE);
        cstep.push_back(step / BASE);
        inteiro istep = inteiro(false, cstep).shift(ka-kb-1);

        if (istep * b > r) {
            step = boundary / (b.coeficientes[kb-1]+1);
            vector<unsigned int> cstep;
            cstep.push_back(step % BASE);
            cstep.push_back(step / BASE);
            istep = inteiro(false, cstep).shift(ka-kb-1);
        }

        q = q + istep;
        r = r - istep * b;

        ka = r.coeficientes.size();
    }

    assert(r >= inteiro(0));

    if (r >= b && ka == kb) {
        // first estimate (quickly)
        unsigned int a = r.coeficientes[ka-1] / bcoef;
        inteiro ia = inteiro(a);
        q = q + ia;
        r = r - ia*b;
        // then find exact value (slowly)
        while (r >= b) {
            q = q + inteiro(1);
            r = r - b;
        }
    }
    
    assert(r < b);
    assert(r >= inteiro(0));

    return pair<inteiro, inteiro>(q, r);
}

inteiro inteiro::operator / (inteiro b) {
    if (b.negativo)
        return -*this / -b;

    if (negativo) {
        // This is floor division, so when a is negative,
        // and b doesn't divide a evenly, we must subtract
        // one from the result -- i.e. (a/b) = -((-a)/b) - 1.
        pair<inteiro, inteiro> p = (-*this).divmod(b);
        if (p.second == 0)
            return -p.first;
        else
            return -p.first - inteiro(1);
    } else {
        return divmod(b).first;
    }
}

inteiro inteiro::operator % (inteiro b) {
    // This is defined in order to satisfy the identity
    //   a = qb + r, when q= a / b and r = a % b.
    // The "special cases" come about because a/b is floor
    // division, which behaves slightly differently for
    // positive and negative numbers.
    if (negativo && b.negativo) {
        pair<inteiro, inteiro> p = (-*this).divmod(-b);
        return -p.second;
    }
    if (negativo && !b.negativo) {
        pair<inteiro, inteiro> p = (-*this).divmod(b);
        return p.second != inteiro(0) ? b - p.second : 0;
    }
    if (!negativo && b.negativo) {
        pair<inteiro, inteiro> p = divmod(-b);
        return p.second != inteiro(0) ? b + p.second : 0;
    }
    if (!negativo && !b.negativo) {
        pair<inteiro, inteiro> p = divmod(b);
        return p.second;
    }
}

string inteiro::ConvertToString( ) {
    string s = ConvertVectorToString(coeficientes);
    if (negativo)
        return "-" + s;
    else
        return s;
}

inteiro inteiro::ConvertToInteiro( string str ) {
    return inteiro(str);
}

