#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#define Base 1000000000
#define BASE_LEN 9
using namespace std;

class inteiro
{
    bool negativo;
    vector <unsigned int> coeficientes;

    public:
    inteiro();
    inteiro(int n);
    inteiro(bool, vector<unsigned int>);
    inteiro(string);
    bool operator > (inteiro);
    bool operator < (inteiro);
    bool operator == (inteiro);
    bool operator != (inteiro);
    inteiro operator + (inteiro);
    inteiro operator - (inteiro);
    inteiro operator - ();
    inteiro operator * (inteiro);
    inteiro operator / (inteiro);
    inteiro operator % (inteiro);

    string ConvertToString();
    inteiro ConvertToInteiro(string);

    void Print();
};

inteiro::inteiro()
{
    negativo=false;
};

inteiro::inteiro(int n)
{
    negativo=false;
    if (n<0) {negativo=true; n=(-1)*n;}
    while(n!=0)
    {
        coeficientes.push_back(n%Base);
        n=n/Base;
    };
}

inteiro::inteiro(bool neg, vector<unsigned int> v)
{
    negativo=neg;
    coeficientes=v;
    for(int i=coeficientes.size()-1; i >= 0;i--)
    {
        if(coeficientes[i]==0) coeficientes.pop_back();
        else break;
    }
    if (coeficientes.size()==0) negativo=false;
};

string inteiro::ConvertToString()
{
    int n=coeficientes.size();
    ostringstream vector_string;
    for(int i=n-1;i>=0;i--)
    {
        unsigned int z=coeficientes[i];
        if(i<n-1)
        {
            int s=Base/10;
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

inteiro inteiro::ConvertToInteiro(string s)
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
    return inteiro(false,v);
};

inteiro::inteiro(string s)
{
    *this=ConvertToInteiro(s);
};


bool inteiro::operator > (inteiro b)
{
    if(negativo && !b.negativo) return false;
    if(!negativo && b.negativo) return true;

    int n=coeficientes.size();
    int m=b.coeficientes.size();
    if(n<m) return negativo;
    if(n>m) return !negativo;

        for(int i=0;i<n;i++)
        {
            if (coeficientes[i]>b.coeficientes[i]) return !negativo;
            if (coeficientes[i]<b.coeficientes[i]) return negativo;
        };
    return false;
};

bool inteiro::operator < (inteiro b)
{
    return b>(*this);
};

bool inteiro::operator == (inteiro b)
{
    if (negativo!=b.negativo) return false;
    int n=coeficientes.size();
    int m=coeficientes.size();
    if (n!=m) return false;
    for(int i=0;i<n;i++)
        {
            if (coeficientes[i]!=b.coeficientes[i]) return false;
        };
    return true;
};

bool inteiro::operator != (inteiro b)
{
    return !((*this)==b);
}

inteiro inteiro::operator + (inteiro b)
{

    if(!negativo && b.negativo) return (*this)-b;
    if(negativo && !b.negativo) return b-(*this);
    if(coeficientes.size()==0) return b;
    if(b.coeficientes.size()==0) return (*this);
    vector<unsigned int> soma;
    int somai;
    int exc=0;
    int n=coeficientes.size();
    int m=b.coeficientes.size();
    if (n<m)
    {
        for(int i=0;i<n;i++)
        {
            somai=coeficientes[i]+b.coeficientes[i];
            soma.push_back((somai+exc)%Base);
            exc=soma[i]/Base;
        };
        for(int i=n;i<m;i++)
        {
            soma.push_back((b.coeficientes[i]+exc)%Base);
            exc=soma[i]/Base;
        };
    }
    else
    {
       for(int i=0;i<m;i++)
        {
            somai=coeficientes[i]+b.coeficientes[i]+exc;
            soma.push_back((somai)%Base);
            exc=somai/Base;
        };
        for(int i=m;i<n;i++)
        {
            soma.push_back((coeficientes[i]+exc)%Base);
            exc=soma[i]/Base;
        };
    };
    if (exc!=0) soma.push_back(exc);

    return inteiro(negativo,soma);
};

inteiro inteiro::operator - ()
{
    return inteiro(!negativo,coeficientes);
};


inteiro inteiro::operator - (inteiro b)
{
    if(!negativo && b.negativo) return (*this)+(-b);
    if(negativo && !b.negativo) return -(-(*this)+b);
    if(coeficientes.size()==0) return -b;
    if(b.coeficientes.size()==0) return (*this);
    if((*this)<b) return -(b-(*this));
    vector<unsigned int> subt;
    int subti;
    int exc=0;
    int n=coeficientes.size();
    int m=b.coeficientes.size();
        for(int i=0;i<m;i++)
        {
            subti=coeficientes[i]-b.coeficientes[i];
            if(subti<0) { subti+=(-exc)+Base; exc=1; }
            else { subti+=(-exc); exc=0; }
            subt.push_back((subti));

        };
        for(int i=m;i<n;i++)
        {
            subt.push_back((coeficientes[i]-exc)%Base);
            exc=0;
        };
        return inteiro(false,subt);

};

inteiro inteiro::operator* (inteiro b)
{
    inteiro resultado;
    if(!negativo && b.negativo) return -((*this)*(-b));
    if(negativo && !b.negativo) return -(-(*this)*b);
    if(*this<b) return b*(*this);
    unsigned int n=coeficientes.size();
    unsigned int m=b.coeficientes.size();

    long long prod;
    long long aux;
    for(unsigned int i=0;i<m;i++)
    {
        long long exc=0;
        vector<unsigned int> resul;
        for(unsigned int p=0;p<i;p++) { resul.push_back(0); }
        for(unsigned int j=0;j<n;j++)
        {
            prod=(long long)b.coeficientes[i];
            prod*=(long long)coeficientes[j];
            aux=(prod+exc)%Base;
            resul.push_back(aux);
            exc=(prod+exc)/Base;
        };
        while(exc!=0)
            {
            resul.push_back(exc%Base);
            exc=exc/Base;
            };
        resultado=resultado+(inteiro(false,resul));
    };
    return resultado;
};

inteiro inteiro::operator/ (inteiro b)
{
    if(negativo && b.negativo) return (-(*this)/(-b))+1;
    if(negativo && !b.negativo) return -((-(*this)/(-b))+1);
    if(!negativo && b.negativo) return -((*this)/(-b));
    inteiro i;
    inteiro b1=b;
    while (!(*this<b1))
    {
        b1=b1+b;
        i=i+inteiro(1);
    };
    return i;
};

inteiro inteiro::operator% (inteiro b)
{
   return (*this)-(b*(*this/b));
};

void inteiro::Print()
{
    cout << negativo << " ";
    for(unsigned int i=0;i<coeficientes.size();i++) cout << coeficientes[i] << " ";
    cout << endl;
};

inteiro factorial(inteiro a)
{
    inteiro t(1);
    for(inteiro i=inteiro(1);i<a;i=i+inteiro(1))
    {
        t=t*i;
    };
    return t;
};

inteiro divisor(inteiro a)
{
    inteiro i(2);
    while(a%i!=0) i=i+inteiro(1);
    return i-inteiro(1);

};

int main()
{
    return 0;
}
