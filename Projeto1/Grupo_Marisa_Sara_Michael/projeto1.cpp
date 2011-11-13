#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>

#define BASE 1000000000
#define BASE_LEN 9

using namespace std;

// Comments:
// Most functions work, but the operators / and % are not well implemented (a 
// lot of computational effort is required, impossible for big numbers). As a 
// consequence, the second test (computing prime factors) does not work so far.
// There should exist a more efficent implementation for the function divisor 
// as well.

////////////////////////////////////////////////////////////////////////////////
// DECLARATION OF CLASS INTEIRO
////////////////////////////////////////////////////////////////////////////////

class inteiro {

    bool negativo;
    vector<unsigned int> coeficientes;

    public:
        inteiro();
        inteiro(int);
        inteiro(bool, vector<unsigned int>);
        inteiro(string);
        bool operator < (inteiro);
        bool operator > (inteiro);
        bool operator == (inteiro);
        bool operator != (inteiro);
        inteiro operator + (inteiro);
        inteiro operator - (inteiro);
        inteiro operator * (inteiro);
        inteiro operator / (inteiro);
        inteiro operator % (inteiro);

        string ConvertToString();
        inteiro ConvertToInteiro(string);

        void print();
        int valor();
};

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS
////////////////////////////////////////////////////////////////////////////////

inteiro::inteiro()
{
    negativo = false;
    coeficientes.push_back(0);
};

inteiro::inteiro(int n)
{
    if (n<0)
    {
        negativo = true;
        n = (-1)*n;
    }
    else negativo = false;

    while (n>0)
    {
        coeficientes.push_back(n%BASE);
        n=n/BASE;
    };
};

inteiro::inteiro(bool sinal, vector<unsigned int> coef)
{
    negativo = sinal;
    coeficientes = coef;
};

inteiro::inteiro(string s)
{
    inteiro x = ConvertToInteiro(s);
    coeficientes = x.coeficientes;
    negativo = x.negativo;
};

////////////////////////////////////////////////////////////////////////////////
// OPERATORS FOR COMPARISON
////////////////////////////////////////////////////////////////////////////////

bool inteiro::operator == (inteiro b)
{
    bool equal=true;
    int n=coeficientes.size();
    int m=b.coeficientes.size();
    if (negativo!=b.negativo)
        equal = false;
    else if (n!=m)
        equal = false;
    else
        for (unsigned i=0; i<n; i++)
            if (coeficientes[i] != b.coeficientes[i])
                equal = false;
    return equal;
};

bool inteiro::operator != (inteiro b)
{
    if (*this==b)
        return false;
    else return true;
};

bool inteiro::operator < (inteiro b)
{
    if (*this==b)
        return false;
    else if (negativo==false && b.negativo==false)
    {
        int n = coeficientes.size();
        int m = b.coeficientes.size();
        if (n>m)
            return false;
        else if (m>n)
            return true;
        else
        {
            for (unsigned int i=m-1; i>=0; i--)
            {
                if (coeficientes[i]<b.coeficientes[i])
                    return true;
                if (coeficientes[i]>b.coeficientes[i])
                    return false;
            }
        }
    }
    else if (negativo==false && b.negativo==true)
        return false;
    else if (negativo==true && b.negativo==false)
        return true;
    else
    {
        int n = coeficientes.size();
        int m = b.coeficientes.size();
        if (n>m)
            return true;
        else if (m>n)
            return false;
        else
        {
            for (unsigned int i=m-1; i>=0; i--)
            {
                if (coeficientes[i]<b.coeficientes[i])
                    return false;
                if (coeficientes[i]>b.coeficientes[i])
                    return true;
            }
        }
    }
};

bool inteiro::operator > (inteiro b)
{
    if (*this==b)
        return false;
    else if (*this<b)
        return false;
    else
        return true;
};

////////////////////////////////////////////////////////////////////////////////
// ARITHMETIC OPERATORS
////////////////////////////////////////////////////////////////////////////////

inteiro inteiro::operator + (inteiro b)
{
    inteiro resultado(0);
    if (negativo==b.negativo)       // both inteiros positive or negative
    {
        if (negativo==true)
            resultado.negativo=true;
        int gamma=0;
        int n=coeficientes.size();
        int m=b.coeficientes.size();
        int maximo;
        if (n>m) maximo=n;
        else maximo=m;

        for (int i=0; i<maximo; i++)
        {
            int coef_a, coef_b;
            if (i<n) coef_a = coeficientes[i]; else coef_a = 0;
            if (i<m) coef_b = b.coeficientes[i]; else coef_b = 0;
            int auxiliar = coef_a+coef_b+gamma;
            if (auxiliar>=BASE)
            {
                gamma=1;
                auxiliar=auxiliar-BASE;
            }
            else gamma=0;
            resultado.coeficientes.push_back(auxiliar);
        };
        if (gamma!=0)
            resultado.coeficientes.push_back(gamma);
    }
    else                            // inteiros have different sign
    {
        if (negativo==false)       // a>=0, b<0
        {
            inteiro c(false,b.coeficientes);    // = -b = |b|
            if (*this>c)
                resultado = *this-c;
            else if (*this<c)
            {
                resultado = c-*this;
                resultado.negativo = false;
            }
        }
        else                        // b>=0, a<0
        {
            inteiro c(false,coeficientes);      // = -a = |a|
            if (b>c)
                resultado = b-c;
            else if (b<c)
            {
                resultado = c-b;
                resultado.negativo = false;
            }
        }
    }
    return resultado;
};

inteiro inteiro::operator - (inteiro b)
{
    inteiro resultado(0);
    if (negativo==b.negativo)       // both inteiros have the same sign
        if (negativo==false)        // both inteiros positive
            if (*this<b)
            {
                resultado = b-*this;
                resultado.negativo = true;
            }
            else
            {
                int gamma=0;
                int n=coeficientes.size();
                int m=b.coeficientes.size();
                int maximo;
                if (n>m) maximo=n;
                else maximo=m;

                for (int i=0; i<maximo; i++)
                {
                    int coef_a, coef_b;
                    if (i<n) coef_a = coeficientes[i]; else coef_a = 0;
                    if (i<m) coef_b = b.coeficientes[i]; else coef_b = 0;
                    int auxiliar = coef_a-coef_b-gamma;
                    if (auxiliar<0)
                    {
                        gamma=1;
                        auxiliar=auxiliar+BASE;
                    }
                    else gamma=0;
                    resultado.coeficientes.push_back(auxiliar);
                };
            }
        else                // both inteiros negative
        {
            inteiro c(false,coeficientes);      // = -a = |a|
            inteiro d(false,b.coeficientes);    // = -b = |b|
            resultado = c-d;
            if (resultado.negativo==true)
                resultado.negativo=false;
            else
                resultado.negativo=true;
        }
    else
    {
        if (negativo==false)        // a>=0, b<0
        {
            inteiro c(false,b.coeficientes);    // = -b = |b|
            resultado = *this+c;
        }
        else                        // a<0, b>=0
        {
            inteiro c(true,b.coeficientes);      // = -b = -|b|
            resultado = *this+c;
        }
    }
    return resultado;
};

inteiro inteiro::operator * (inteiro b)
{
    unsigned int n=coeficientes.size();
    unsigned int m=b.coeficientes.size();
    inteiro resultado(0);
    vector<unsigned int> coef;
    unsigned int gamma;
    long h;
    
    for (unsigned int j=0; j<m; j++)
    {
        coef.clear();
        for (unsigned int i=0; i<j; i++)
            coef.push_back(0);
        gamma = 0;
        for (unsigned int i=0; i<n; i++)
        {
            h=coeficientes[i]*b.coeficientes[j]+gamma;
            coef.push_back(h%BASE);
            gamma = h/BASE;
        }
        if (gamma!=0)
           coef.push_back(gamma);
        inteiro auxiliar(false,coef);
        resultado = resultado + auxiliar;
    }
    
    if (negativo!=b.negativo) resultado.negativo=true;
    return resultado;
};

inteiro inteiro::operator / (inteiro b)
{
    int i=0;
    inteiro a_pos(false,coeficientes);      // = |a|
    inteiro b_pos(false,b.coeficientes);    // = |b|
    while (b_pos<a_pos || b_pos==a_pos)
    {
        a_pos = a_pos-b_pos;
        i++;
    }
    inteiro resultado(i);
    if (negativo!=b.negativo)
        resultado.negativo = true;
    return resultado;
};

inteiro inteiro::operator % (inteiro b)
{
    inteiro a_pos(false,coeficientes);      // = |a|
    inteiro b_pos(false,b.coeficientes);    // = |b|
    while (b_pos<a_pos || b_pos==a_pos)
        a_pos=a_pos-b_pos;
    if (negativo!=b.negativo)
        a_pos.negativo = true;
    return a_pos;
};

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS FOR TYPE CONVERSION
////////////////////////////////////////////////////////////////////////////////

string ConvertVectorToString(vector<unsigned int> v)
{
	int n=v.size();
	ostringstream vector_string;
	for(int i=n-1;i>=0;i--)
	{
        unsigned int z=v[i];
        if(i<n-1)
        {
            int s=BASE/10;
            while(z%s == z)
            {
                vector_string << "0";
                s=s/10;
            };
        };
		vector_string << z;
    };
	return vector_string.str();
};

vector<unsigned int> ConvertStringToVector(string s)
{
	vector<unsigned int> v;
        int n=s.length();
	int q=n/BASE_LEN;
	int r=n%BASE_LEN;
	string sub;
        for(int i=q-1;i>=0;i--)
	{
		sub=s.substr(r+i*BASE_LEN,BASE_LEN);
		v.push_back(atoi(sub.c_str()));
	};
	if(r>0)
	{
		sub=s.substr(0,r);
		v.push_back(atoi(sub.c_str()));
	};
        return v;
};

string inteiro::ConvertToString()
{
    string s;
    if (negativo==true)
        s = '-';
    s.append(ConvertVectorToString(coeficientes));
    return s;
};

inteiro inteiro::ConvertToInteiro(string s)
{
    inteiro a(0);
    a.negativo = false;
    a.coeficientes = ConvertStringToVector(s);
    return a;
};

////////////////////////////////////////////////////////////////////////////////
// OUTPUT FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

void inteiro::print()
{
    int m=coeficientes.size();
    if (negativo==true)
        cout << "- ";
    cout << "( ";
    for (unsigned int i=0; i<m; i++)
        cout << coeficientes[m-1-i] << " ";
    cout << ")" << endl;
};

int inteiro::valor()
{
    int soma=0;
    unsigned int potencia=1;
    int m=coeficientes.size();
    for (unsigned int i=0; i<m; i++)
    {
        soma = soma + coeficientes[i]*potencia;
        potencia = potencia*BASE;
    }
    if (negativo==true)
        soma = (-1)*soma;
    return soma;
};

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS FOR ADDITIONAL PROBLEMS
////////////////////////////////////////////////////////////////////////////////

inteiro factorial(inteiro a)
{
    inteiro one(1);
    if (a>1)
       return a*factorial(a-one);
    else
       return one;
};

inteiro divisor(inteiro a)
{
    inteiro one(1);
    inteiro div(1), rest(1);
    do
    {
        div = div+one;
        rest = a%div;
    } while (rest != 0);
    return div;
};

////////////////////////////////////////////////////////////////////////////////
// MAIN PROGRAM
////////////////////////////////////////////////////////////////////////////////

int main()
{   
    cout << "First test: Calculate factorial of inteiros\n\n";
    inteiro a(10), b(100),c(1000);
    cout << a.valor() << "! = \n";
    factorial(a).print();
    cout << endl << endl;
    cout << b.valor() << "! = \n";
    factorial(b).print();
    cout << endl << endl;
    cout << c.valor() << "! = \n";
    factorial(c).print();
    cout << endl << endl;

    // The second test is not working yet, there's still a problem in one of 
    // the functions /, % or divisor
    cout << "Second test: Calculate prime factors of inteiros\n\n";
    vector<unsigned int> coef;
    coef.push_back(1);
    coef.push_back(1);
    inteiro x(false,coef), y, one(1);
    vector<inteiro> primefactors;
    while (x>one)
    {
        y = divisor(x);
        primefactors.push_back(y);
        x = x/y;
    }
    cout << "Prime factors of " << endl;
    x.print();
    cout << ": " << endl;
    for (unsigned int i=0; i<primefactors.size(); i++)
        cout << primefactors[i].valor() << " ";

    return 0;
}
