//PROJECTO 1 - CLASSE INTEIRO
//ÁLGEBRA COMPUTACIONAL

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sstream>
#define base 1000000000
#define base_len 9

using namespace std;

//definição da classe
class inteiro
{
    bool sinal;
    vector <unsigned int> coeficientes;

    public:
        inteiro();
        inteiro(int n);
        inteiro(string);
        inteiro(bool, vector <unsigned int>);

        bool operator < (inteiro);
        bool operator > (inteiro);
        bool operator == (inteiro);
        bool operator != (inteiro);
        inteiro operator + (inteiro);
        inteiro operator - (inteiro);
        inteiro operator * (inteiro);
        inteiro operator / (inteiro);
        inteiro operator % (inteiro);

        void print_inteiro();
        inteiro escalar(int,int);
        string ConvertVectorToString();
        inteiro ConvertStringToVector(string);

};


inteiro::inteiro()
{
    sinal=true;
};


//escreve o 'inteiro' dado por n
inteiro::inteiro(int n)
{
    if(n<0)
    {
        sinal=true;
        n=(-1)*n;
    }
    else
    {
        sinal=false;
    };
    while(n>0)
    {
        coeficientes.push_back(n%base);
        n=n/base;
    };
};


//define a estrutura de um 'inteiro'
inteiro::inteiro(bool s, vector <unsigned int> v)
{
    sinal=s;
    coeficientes=v;
};


//escreve o 'inteiro' dado numa string
inteiro::inteiro(string s)
{
    sinal=false;
    int n=s.length();
	int q=n/base_len;
	int r=n%base_len;
	vector <unsigned int> v;
	string sub;
        for(int i=q-1; i>=0;i--)
        {
            sub=s.substr(r+i*base_len,base_len);
            v.push_back(atoi(sub.c_str()));
        };
	if(r>0)
	{
		sub=s.substr(0,r);
		v.push_back(atoi(sub.c_str()));
	};
	coeficientes=v;
};


//imprime o inteiro
void inteiro::print_inteiro()
{
    int t=coeficientes.size();
    for(int i=0; i<t; i++)
    {
        cout << coeficientes[t-1-i] << ".";
    };
};


bool inteiro::operator < (inteiro b)
{
    bool resposta;
    int n=coeficientes.size();
    int m=b.coeficientes.size();

    if(sinal && !b.sinal) //negativo<positivo -> true
    {
        resposta=true;
        return resposta;
    };
    if(!sinal && b.sinal) //positivo<negativo -> false
    {
        resposta=false;
        return resposta;
    };

    if(n<m)
        resposta=true;
    if(n>m)
        resposta=false;
    if(n==m)              //compara-se elemento a elemento
    {
        for(int i=m-1; i>=0; i--)
        {
            if(coeficientes[i]<b.coeficientes[i])
            {
                resposta=true;
                return resposta;
            };
            if(coeficientes[i]==b.coeficientes[i])
            {
                resposta=false;
            };
            if(coeficientes[i]>b.coeficientes[i])
            {
                resposta=false;
                return resposta;
            };
        };
    };
    return resposta;
};


bool inteiro::operator > (inteiro b)
{
    bool resposta;
    int n=coeficientes.size();
    int m=b.coeficientes.size();

    if(sinal && !b.sinal) //negativo>positivo -> false
    {
        resposta=false;
        return resposta;
    };

    if(!sinal && b.sinal) //positivo>negativo -> true
    {
        resposta=true;
        return resposta;
    };

    if(n>m)
        resposta=true;
    if(n<m)
        resposta=false;
    if(n==m)              //compara-se elemento a elemento
    {
        for(int i=m-1; i>=0; i--)
        {
            if(coeficientes[i]>b.coeficientes[i])
            {
                resposta=true;
                return resposta;
            };
            if(coeficientes[i]==b.coeficientes[i])
            {
                resposta=false;
            };
            if(coeficientes[i]<b.coeficientes[i])
            {
                resposta=false;
                return resposta;
            };
        };
    };
    return resposta;
};


bool inteiro::operator == (inteiro b)
{
    bool resposta;
    int n=coeficientes.size();
    int m=b.coeficientes.size();

    if(sinal!=b.sinal)    //sinais diferentes -> false
    {
        resposta=false;
        return resposta;
    };

    if(n<m) resposta=false;
    if(n>m) resposta=false;
    if(n==m)              // compara-se elemento a elemento
    {
        for(int i=0; i<n; i++)
        {
            if(coeficientes[i]==b.coeficientes[i])
            {
                resposta=true;
            }
            else
            {
                resposta=false;
                return resposta;
            };
        };
    };
    return resposta;
};


bool inteiro::operator != (inteiro b)
{
    bool resposta;
    int n=coeficientes.size();
    int m=b.coeficientes.size();

    if(sinal!=b.sinal)    //sinais diferentes -> true
    {
        resposta=true;
        return resposta;
    };

    if(n<m) resposta=true;
    if(n>m) resposta=true;
    if(n==m)              //compara elemento a elemento
    {
        for(int i=0; i<n; i++)
        {
            if(coeficientes[i]!=b.coeficientes[i])
            {
                resposta=true;
                return resposta;
            }
            else
            {
                resposta=false;
            };
        };
    };
    return resposta;
};


inteiro inteiro::operator + (inteiro b)
{
    inteiro a;
    a.sinal=sinal;
    a.coeficientes=coeficientes;
    inteiro resultado;

    if(sinal && b.sinal)
        resultado.sinal=true;
    if(!sinal && !b.sinal)
        resultado.sinal=false;

    int n=coeficientes.size();
    int m=b.coeficientes.size();
    int maximo=max(n,m);
    int gamma=0;
    for(int i=0; i<maximo; i++)
    {
        int coef_a, coef_b;
        if (i<n)
            coef_a=coeficientes[i]; else coef_a=0;
        if (i<m)
            coef_b=b.coeficientes[i]; else coef_b=0;

        // faz a[i]+b[i]+gamma
        int auxiliar=coef_a+coef_b+gamma;

        // se maior que a base subtrai-lhe a base e vai um
        if(auxiliar>=base)
        {
            gamma=1;
            auxiliar=auxiliar-base;
            resultado.coeficientes.push_back(auxiliar);
        }
        else
        {
            gamma=0;
            resultado.coeficientes.push_back(auxiliar);
        };
    };
    // no fim se ainda existe um 'vai um' coloca-o no vector
    if(gamma!=0)
        resultado.coeficientes.push_back(gamma);

    return resultado;
};

// subtracção
inteiro inteiro::operator - (inteiro b)
{
    inteiro a;
    a.sinal=sinal;
    a.coeficientes=coeficientes;
    inteiro resultado;

    int n=coeficientes.size();
    int m=b.coeficientes.size();
    int maximo=max(n,m);
    int gamma=0;

    resultado.sinal=false;
    for(int i=0; i<maximo; i++)
    {
        int coef_a, coef_b;
        if (i<n)
            coef_a=coeficientes[i]; else coef_a=0;
        if (i<m)
            coef_b=b.coeficientes[i]; else coef_b=0;

        // faz a[i]-b[i]-gamma
        int auxiliar=coef_a-coef_b-gamma;

        // se menor que zero, soma-lhe a base e vai um
        if (auxiliar<0)
        {
            gamma=1;
            auxiliar=auxiliar+base;
            resultado.coeficientes.push_back(auxiliar);
        }
        else
        {
            gamma=0;
            resultado.coeficientes.push_back(auxiliar);
        };
    };
    return resultado;
};


//multiplicação por um coeficiente
inteiro inteiro::escalar(int b, int k)
{
    int gamma=0;
    long long bb=b;
    inteiro resultado;
    int n=coeficientes.size();

    //acrescenta zeros até à posição k
    for(int j=0; j<k; j++)
            resultado.coeficientes.push_back(0);

    //multiplica b[k] por todos os el. de a
    for(int i=0; i<n; i++)
    {
        long long t=((coeficientes[i])*bb)+gamma;
        gamma=0;
        if(t>base)
        {
            gamma=t/base;
            t=t%base;
        };
        resultado.coeficientes.push_back(t);
    };
    if(gamma!=0)
        resultado.coeficientes.push_back(gamma);

    return resultado;
};

//multiplicação
inteiro inteiro::operator * (inteiro b)
{
	inteiro resultado;

	if(sinal==b.sinal)
        resultado.sinal=false;
	else
        resultado.sinal=true;

	inteiro auxiliar;
	int m=b.coeficientes.size();

    for(int k=0; k<m; k++)
    {
        //multiplica o inteiro por b[k]
        auxiliar=escalar(b.coeficientes[k],k);
        //soma-se ao resultado
        resultado=resultado+auxiliar;
        //limpa o auxiliar
        auxiliar.coeficientes.clear();
    };
	return resultado;
};

//divisão (versão pouco eficiente)
inteiro inteiro::operator / (inteiro b)
{
    inteiro a;
    a.sinal=sinal;
    a.coeficientes=coeficientes;

    inteiro auxiliar;
    inteiro resultado;
    auxiliar.sinal=false;
    resultado.sinal=false;

    // se b>a b/a=0
    if(b>a)
    {
        resultado.coeficientes.push_back(0);
        return resultado;
    };
    // conta quantas vezes b cabe em a
    while(a>b)
    {
        auxiliar=auxiliar+a-b;
        a.coeficientes.clear();
        a=a+auxiliar;
        auxiliar.coeficientes.clear();
        resultado=resultado+1;
    };
    return resultado;
};

//resto - (versão pouco eficiente)
inteiro inteiro::operator % (inteiro b)
{
    inteiro a;
    a.sinal=sinal;
    a.coeficientes=coeficientes;

    inteiro auxiliar;
    inteiro resultado;
    auxiliar.sinal=false;
    resultado.sinal=false;

    // se b>a entao a(mod b)=a
    if(b>a)
    {
        resultado=a;
        return resultado;
    };
    //conta quantas vezes b cabe em a
    while(a>b)
    {
        auxiliar=auxiliar+a-b;
        a.coeficientes.clear();
        a=a+auxiliar;
        auxiliar.coeficientes.clear();
        resultado=resultado+1;
    };
    //retorna o resto
    return a;
};


string ConvertVectorToString(vector<unsigned int> v)
{
	int n=v.size();
	ostringstream vector_string;
	for(int i=n-1;i>=0;i--)
	{
        unsigned int z=v[i];
        if(i<n-1)
        {
            int s=base/10;
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
	int q=n/base_len;
	int r=n%base_len;
	string sub;
        for(int i=q-1; i>=0;i--)
        {
            sub=s.substr(r+i*base_len,base_len);
            v.push_back(atoi(sub.c_str()));
        };
	if(r>0)
	{
		sub=s.substr(0,r);
		v.push_back(atoi(sub.c_str()));
	};
    return v;
};


//PROBLEMAS ADICIONAIS

//factorial
inteiro factorial(inteiro b)
{
    inteiro fact=1;
    inteiro it=2;
    while(it!=b)
    {
        fact=fact*it;
        it=it+1;
    };
    fact=fact*b;
    return fact;
};

//função divisor
inteiro divisor(inteiro b)
{
    inteiro z=0;
    inteiro div=2;
    inteiro auxiliar=b%div;
    if(auxiliar==z)
    {
        return div;
    };
    while(auxiliar!=z)
    {
        div=div+1;
        auxiliar=b%div;
    };
    return div;
};


int main()
{
    string a="787981798721324214235";
    string b="1623515415324152192";
    inteiro x=a;
    inteiro y=b;

    cout << "x=" << a << endl;
    cout << "y=" << b << endl;

    inteiro r1=x+y;
    cout << " " << endl;
    cout << "x+y=";
    r1.print_inteiro();

    inteiro r2=x-y;
    cout << " " << endl;
    cout << "x-y=";
    r2.print_inteiro();

    inteiro r3=x*y;
    cout << " " << endl;
    cout << "x*y=";
    r3.print_inteiro();

    inteiro r4=x/y;
    cout << " " << endl;
    cout << "x/y=";
    r4.print_inteiro();

    inteiro r5=x%y;
    cout << " " << endl;
    cout << "x%y=";
    r5.print_inteiro();

    cout << " " << endl;
    inteiro q1=100;
    inteiro f1=factorial(q1);
    cout << " " << endl;
    cout << "100!=";
    f1.print_inteiro();

    cout << " " << endl;
    inteiro q2=1000;
    inteiro f2=factorial(q2);
    cout << " " << endl;
    cout << "1000!=";
    f2.print_inteiro();

    cout << " " << endl;
    inteiro d1=divisor(q1);
    cout << " " << endl;
    cout << "O menor";
    d1.print_inteiro();

}

