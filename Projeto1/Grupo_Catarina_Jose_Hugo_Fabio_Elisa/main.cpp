#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
#include <stdlib.h>

#define BASE 1000000000
#define BASE_LEN 9

using namespace std;


class inteiro{
       bool negativo;
       vector <unsigned int> coeficientes;
       public:
               inteiro();
               inteiro(int n);
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
               string ConvertToString ();
               inteiro convertToInteiro(string);
               inteiro Factorial(inteiro);
               inteiro Divisor(inteiro);
               void getCoeficientes()
               {
                   for(int i=coeficientes.size()-1;i>=0;i--)
                   {
                       cout << coeficientes[i];
                   }
                   cout << endl;
               };
};

// Definição do constructor inteiro()

inteiro::inteiro()
{
    coeficientes.push_back(0);
};

//Definição do constructor inteiro(int n)

inteiro::inteiro(int n)
{
       coeficientes.push_back(n);
};

//Definição do constructor inteiro(bool, vector)

inteiro::inteiro(bool sinal,vector <unsigned int> coef)
{
    negativo=sinal;
    coeficientes=coef;
};

//Definição do constructor inteiro(string s)

inteiro::inteiro(string s)
{
    istringstream buffer(s);
    int temp;
    buffer >> temp;
    coeficientes.push_back(temp);
};

//Definição comparação ==

bool inteiro::operator == (inteiro b)
{
    int n = coeficientes.size();
    int m = b.coeficientes.size();
    if( n != m) return false;
    for(int i=n-1; i>0; i--)
    {
         if ( coeficientes[i]!=b.coeficientes[i] ) return false;
    }
    return true;
};

//Definição comparação !=

bool inteiro::operator != (inteiro b)
{
    int n = coeficientes.size();
    int m = b.coeficientes.size();
    if( n != m) return true;
    for(int i=n-1 ; i>0; i--)
    {
        if ( coeficientes[i]!=b.coeficientes[i] ) return true;
    }
    return false;
};

//Definição comparação <

bool inteiro::operator < (inteiro b)
{
    int n = coeficientes.size();
    int m = b.coeficientes.size();
    if(n < m) return true;
    if(negativo && !b.negativo) return true;
    if(!negativo && b.negativo) return false;
    for(int i=n-1; i>=0; i--)
       {
           if(coeficientes[i] < b.coeficientes[i]) return true;
       };
    return false;
};

//Definição comparação >

bool inteiro::operator > (inteiro b)
{
    int n = coeficientes.size();
    int m = b.coeficientes.size();
    if(n > m) return true;
    if(negativo && !b.negativo) return false;
    if(!negativo && b.negativo) return true;
    for(int i=0; i<n; i++)
       {
           if(coeficientes[i] > b.coeficientes[i]) return true;
       };
    return false;
};

//Definição da operação aritmética +

inteiro inteiro:: operator + (inteiro b)
{
    int n = coeficientes.size();
    int m = b.coeficientes.size();
    int mynum=0;
    int num=0;
    bool sinal=false;
    for(int i=0;i<n;i++)
    {
        mynum += coeficientes[i]*pow(10,i);
    };
    for(int j=0;j<m;j++)
    {
        num += b.coeficientes[j]*pow(10,j);
    };
    if(negativo) mynum *=-1;
    if(b.negativo) num *=-1;

    int result = mynum+num;
    if(result<0) sinal = true;
    vector<unsigned int> v;
    while(result!= 0)
    {
        v.push_back(result%10);
        result /=10;
    };
    inteiro final(false,v);
    return final;
};

//Definição da operação aritmética -

inteiro inteiro::operator - (inteiro b)
{
    int n = coeficientes.size();
    int m = b.coeficientes.size();
    int mynum=0;
    int num=0;
    int maior=0;
    int menor=0;
    bool sinal=false;
    for(int i=0;i<n;i++)
    {
        mynum += coeficientes[i]*pow(10,i);
    };
    for(int j=0;j<m;j++)
    {
        num += b.coeficientes[j]*pow(10,j);
    };
    if(negativo) mynum *=-1;
    if(b.negativo) num *=-1;

    if(mynum>num)
    {
        maior = mynum;
        menor = num;
    };
    if(mynum==num)
    {
        inteiro done(0);
        return done;
    };
    if(mynum<num)
    {
        maior = num;
        menor = mynum;
    };

    int result = maior-menor;
    if(result<0)
    {
        sinal = true;
    };
    vector<unsigned int> v;
    while(result!= 0)
    {
        v.push_back(result%10);
        result /=10;
    };
    inteiro final(sinal,v);
    return final;
};

//Definição da operação aritmética *

inteiro inteiro::operator * (inteiro b)
{
	int n = coeficientes.size();
    int m = b.coeficientes.size();
    int mynum=0;
    int num=0;
    bool sinal = false;
    for(int i=0;i<mysize;i++)
    {
        mynum += coeficientes[i]*pow(10,i);
    };
    for(int j=0;j<size;j++)
    {
        num += b.coeficientes[j]*pow(10,j);
    };
    if(negativo) mynum *=-1;
    if(b.negativo) num *=-1;
    int result = mynum*num;
    if(result<0) sinal = true;
    vector<unsigned int> v;
    while(result!= 0)
    {
        v.push_back(result%10);
        result /=10;
    };
    inteiro final(sinal,v);
    return final;
};

//Definição da operação aritmética /

inteiro inteiro::operator / (inteiro b)
{
	int n = coeficientes.size();
    int m = b.coeficientes.size();
    int mynum=0;
    int num=0;
    bool sinal = false;
    for(int i=0;i<mysize;i++)
    {
        mynum += coeficientes[i]*pow(10,i);
    };
    for(int j=0;j<size;j++)
    {
        num += b.coeficientes[j]*pow(10,j);
    };
    if(negativo) mynum *=-1;
    if(b.negativo) num *=-1;
    int result = mynum/num;
    if(result<0) sinal = true;
    vector<unsigned int> v;
    while(result!= 0)
    {
        v.push_back(result%10);
        result /=10;
    };
    inteiro final(sinal,v);
    return final;
};

//Definição da operação aritmética %

inteiro inteiro::operator % (inteiro coef)
{
	int n = coeficientes.size();
    int m = b.coeficientes.size();
    int mynum=0;
    int num=0;
    bool sinal = false;
    for(int i=0;i<n;i++)
    {
        mynum += coeficientes[i]*pow(10,i);
    };
    for(int j=0;j<m;j++)
    {
        num += b.coeficientes[j]*pow(10,j);
    };
    if(negativo) mynum *=-1;
    if(b.negativo) num *=-1;
    int result = mynum%num;
    if(result<0) sinal = true;
    vector<unsigned int> v;
    while(result!= 0)
    {
        v.push_back(result%10);
        result /=10;
    };
    inteiro final(sinal,v);
    return final;
};

// converter de vector para string

string inteiro::ConvertToString()
{
    int n = coeficientes.size();
	ostringstream vector_string;
	for(int i=n-1; i>=0; i--)
	{
		unsigned int z=coeficientes[i];
		if(i<n-1)
		{
			int s=BASE/10;
			while(z%s==z)
			{
				vector_string << "0";
				s=s/10;
			};
		};
		vector_string << z;
	};
	return vector_string.str();
};

// converter de string para vector

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
	inteiro final(false,v);
	return final;
};


inteiro inteiro::Factorial(inteiro b)
{
    int m = b.coeficientes.size();
    int num=0;
    bool sinal = false;
    for(int i=0;i<m;i++)
    {
        num += b.coeficientes[i]*pow(10,i);
    };
    int result = 1;
    for(int j=1;j<=num;j++)
    {
        result*=j;
    };
    vector<unsigned int> v;
    while(result!= 0)
    {
        v.push_back(result%10);
        result /=10;
    };
    inteiro final(sinal,v);
    return final;
};

inteiro inteiro::Divisor(inteiro b)
{
    int m= b.coeficientes.size();
    int num=0;
    bool sinal = false;

    for(int i=0;i<m;i++)
    {
        num += b.coeficientes[i]*pow(10,i);
    };
    int result =0;
    for(int j=2;j<=num;j++)
    {
        if(num%j==0)
        {
			result = j;
			break;
		};
    };
    vector<unsigned int> v;
    while(result!= 0)
    {
        v.push_back(result%10);
        result /=10;
    };
    inteiro final(sinal,v);
    return final;
};

int main(){
	vector<unsigned int> v1;
	v1.push_back(0);
	v1.push_back(0);
	v1.push_back(1);

    vector<unsigned int> v2;
    v2.push_back(0);
	v2.push_back(0);
	v2.push_back(0);
	v2.push_back(1);

	inteiro i1(false,v1);
	inteiro i2(false,v2);
	inteiro i3 = i1.Factorial(100);
    inteiro i4 = i1.Factorial(1000);
//	i1.getCoeficientes();
//	cout << endl;
//	i2.getCoeficientes();
//	cout << endl;
	i3.getCoeficientes();
    cout << endl;
    i4.getCoeficientes();
    cout << endl;
	return i3;
};
