#include <iostream>

using namespace std;

class inteiro {

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

    string ConvertToString();
    inteiro ConvertToInteiro(string);
};

// 1. O construtor

// cria um objeto inteiro que representa o número 0.
inteiro::inteiro()
{
    negativo=true;
};

// cria um objeto inteiro que representa o número n.
inteiro::inteiro(int n)
{
    if (n<0)
    {
        negativo=true;
        n=(-1)*n;
    }
    else negativo=false;

    while (n>=0)
    {
        coeficientes.push_back(n%BASE);
        n=n/BASE;
    }
};

// cria um objeto inteiro que representa o número dado pela representação (sinal,coef).
inteiro::inteiro(bool sinal, vector<unsigned int> coef)
{
    coeficientes=coef;
    negativo=sinal;
};

// cria um objeto inteiro que representa o número positivo dado pelo texto em s.
inteiro::inteiro(string s)
{
    s=ConvertVectorToString(coeficientes);
};


// 2.Comparações

// o valor de retorno é true se os inteiros representados pelo objeto atual e pelo objeto b forem iguais.
bool inteiro::operator == (inteiro b)
{
  int a,b;
  if (a==b)
  return true;
  else;
  return false;
};

// o valor de retorno é true se os inteiros representados pelo objeto atual e pelo objeto b não forem iguais
bool inteiro::operator != (inteiro b)
{
  int a,b;
  if (a!=b)
  return true;
  else;
  return false;
};

// o valor de retorno é true se os inteiros representados pelo objeto atual for menor do que o inteiro representado pelo objeto b
bool inteiro::operator < (inteiro b)
{
    int a,b;
    if (negativo=true and b.negativo=false)
    return true;
    if (negativo=false and b.negativo=true)
    return false;
    if (negativo=true and b.negativo=true)
    return (-1)*b < (-1)*a;
    if (b.coeficientes.size() > coeficientes.size())
    return true;
    if (b.coeficientes.size() < coeficientes.size())
    return false;
    for (int i = coeficientes.size()-1; i >= 0; i--)
    {
        if (b.coeficientes[i] > coeficientes[i])
        return true;
        if (b.coeficientes[i] < coeficientes[i])
        return false;
    }
};

// o valor de retorno é true se os inteiros representados pelo objeto atual for maior do que o inteiro representado pelo objeto b
bool inteiro::operator > (inteiro b)
{
    int a,b;
    if (negativo=true and b.negativo=false)
    return false;
    if (negativo=false and b.negativo=true)
    return true;
    if (negativo=true and b.negativo=true)
    return (-1)*b < (-1)*a;
    if (b.coeficientes.size() > coeficientes.size())
    return false;
    if (b.coeficientes.size() < coeficientes.size())
    return true;
    for (int i = coeficientes.size()-1; i >= 0; i--)
    {
        if (b.coeficientes[i] < coeficientes[i])
        return true;
        if (b.coeficientes[i] > coeficientes[i])
        return false;
    }
};

// 3. Aritmética

/* o valor de retorno é um objeto inteiro que representa a soma dos inteiros representados pelo objeto atual e pelo objeto b
programa cedido pelo professor "folha1_5.cpp" */
inteiro inteiro::operator + (inteiro b)
{
    int a,b;
    if (negativo=false and b.negativo=true)
    return a-(-1)*b;
    if (negativo=true and b.negativo=false)
    return b-(-1)*a;
    vector<unsigned int> output;
    unsigned long long t = 0;
    int j=max(coeficientes.size(), coeficientes.size());
    for (int i = 0; i < j; i++)
    {
        unsigned long long resultado=t;
        if (i<coeficientes.size())
        resultado=resultado+(unsigned long long)coeficientes[i];
        if (i<b.coeficientes.size())
        resultado=resultado+(unsigned long long)b.coeficientes[i];
        t=resultado/BASE;
        output.push_back(resultado%BASE);
    }
    return inteiro(negativo,output);
};


/* o valor de retorno é um objeto inteiro que representa a diferença dos inteiros representados pelo objeto atual e pelo objeto b
Através da soma definimos a subtração */
inteiro inteiro::operator - (inteiro b)
{
    int a,b;
    return int (a+(-1)*b);
};

// o valor de retotno é um objeto inteiro que representa a multiplicação dos inteiros representados pelo objeto atual e pelo objeto b
inteiro inteiro::operator * (inteiro b)
{
    int a,b;
    if (negativo=true and b.negativo=true)
    return ((-1)*a)*((-1)*b);
    if (negativo=true and b.negativo=false)
    return -(((-1)*a)*b);
    if (negativo=false and b.negativo=true)
    return -(a*((-1)*b));

    vector <unsigned int> coef;
    vector <unsigned int> output;
    unsigned long long t = 1;
    int j=max(coeficiente.size(), b.coeficiente.size());
    for (int i=0; i<j; i++)
    {
        unsigned long long resultado=t;
        if (i<coeficientes.size())
        resultado=resultado*(unsigned long long)coeficientes[i];
        if (i<b.coeficientes.size())
        resultado=resultado*(unsigned long long)b.coeficientes[i];
        t=resultado/BASE;
        output.push_back(resultado%BASE);
    }
    return inteiro(negativo,output);
};

/* o valor de retotno é um objeto inteiro que representa o quociente da divisão dos inteiros representados
pelo objeto atual e pelo objeto b */
inteiro inteiro::operator / (inteiro b)
{
    int a,b;
    if (negativo=true and b.negativo=true)
    return ((-1)*a)/((-1)*b);
    if (negativo=true and b.negativo=false)
    return -(((-1)*a)/b);
    if (negativo=false and b.negativo=true)
    return -(a/((-1)*b));

    vector <unsigned int> coef;
    vector <unsigned int> output;
    unsigned long long t = 1;
    int j=max(coeficiente.size(), b.coeficiente.size());
    for (int i=0; i<j; i++)
    {
        unsigned long long resultado=t;
        if (i<coeficientes.size())
        resultado=resultado/(unsigned long long)coeficientes[i];
        if (i<b.coeficientes.size())
        resultado=resultado/(unsigned long long)b.coeficientes[i];
        t=resultado/BASE;
        output.push_back(resultado%BASE);
    }
    return inteiro(negativo,output);
};

/* o valor de retotno é um objeto inteiro que representa o resto da divisão dos inteiros representados
pelo objeto atual e pelo objeto b */
inteiro inteiro::operator % (inteiro b)
{
    int a,b;
    if (negativo=true and b.negativo=true)
    return ((-1)*a)%((-1)*b);
    if (negativo=true and b.negativo=false)
    return -(((-1)*a)%b);
    if (negativo=false and b.negativo=true)
    return -(a%((-1)*b));

    vector <unsigned int> coef;
    vector <unsigned int> output;
    unsigned long long t = 1;
    int j=max(coeficiente.size(), b.coeficiente.size());
    for (int i=0; i<j; i++)
    {
        unsigned long long resultado=t;
        if (i<coeficientes.size())
        resultado=resultado%(unsigned long long)coeficientes[i];
        if (i<b.coeficientes.size())
        resultado=resultado%(unsigned long long)b.coeficientes[i];
        t=resultado%BASE;
        output.push_back(t);
    }
    return inteiro(negativo,output);



// 4. Funções de Conversão
// 1. Recurso Auxiliar
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#define BASE 1000000000
#define BASE_LEN 9

using namespace std;




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


void testar()
{
    vector<unsigned int> lista;
    int n=0;
    cin >> n;
    while (n>0)
    {
        lista.push_back(n);
        cin >> n;
    };
    cout << "A lista representa o número:" << ConvertVectorToString(lista)<<endl;
};

int main()
{
    cout << "Lista d inteiros positivos q representa a lista dos coeficientes d um inteiro a base 10^9. Termine a lista com -1."<<endl;
    cout << "(por exemplo: 1 "<<endl;
    cout << "78" << endl;
    cout << " 2" << endl;
    cout << "-1" << endl;
    cout << "representa 1+ 78*10^9 + 2*10^18 = 2.000000078.000000001)"<<endl;
    cout << "-----------------------------------"<<endl;
    string resposta;
    do{
        testar();
        cout << "Quer mais ? (sim/não):";
        cin >> resposta;
    }while(resposta=="sim");

    string s;
    do{
      cout << "Transformar um texto num vector:";
      cin >> s;
      vector<unsigned int> v=ConvertStringToVector(s);
      cout << "Os coeficientes são:" << endl;
      for(int i=0;i<v.size(); i++)
         cout << "v["<<i<<"] = "<< v[i] << endl;
      cout << "Quer mais ? (sim/nao)";
      cin >> resposta;
    }while(resposta=="sim");
}

