#include <iostream>
#include <vector>
using namespace std;


int min(int x, int y)
{
 if (x>y) return y; else return x;
};


// declaração da classe "polinomio"
class polinomio
{
	vector<int> coef;
	bool nulo;
	
	public:
		polinomio();
		polinomio(vector<int>);
		void print();
		polinomio multTerm(unsigned int, int);
		polinomio operator + (polinomio);
		polinomio operator - (polinomio);
		polinomio operator * (polinomio);
		polinomio quo(unsigned int k);
        polinomio rem(unsigned int k);
		polinomio karatsuba(polinomio,polinomio);
		int leadingCoeficient();
		void cleanup(void);
};


void polinomio::cleanup()
{
	int n=coef.size()-1;
	if (nulo) // se for nulo, então limpamos a lista dos coeficientes
	{
		for(int i=n; i>0; i--) coef.pop_back();
		coef[0]=0;
	}
	else
	{
		while(n>=0 && coef[n]==0)
		{
			coef.pop_back();
			n--;
		};
		if (n<0)  // era realmente o vector nulo
		{
			nulo=true;
			coef.push_back(0);
		};
	};
}

//definição das funções da classe "polinomio"

polinomio::polinomio()
{
	nulo=true;
};

polinomio::polinomio(vector<int> c)
{
	coef=c;
	nulo=false;
	cleanup();
};

void polinomio::print()
{
   if(nulo)
   {
   	cout << "0" << endl;
   }
   else
   {
     unsigned int n=coef.size();
     for (int i=0; i<n-1; i++)
     	cout << coef[i] << "x^" << i << "+";
     cout << coef[n-1] << "x^" << n-1 << endl;
   }
};

polinomio polinomio::operator + (polinomio g)
{

// coef é a lista dos coeficientes do primeiro termo
// g.coef é a lista dos coeficientes do segundo termo

	polinomio h;
	h.nulo=false;
	int n=coef.size();
	int m=g.coef.size();
	if (n<=m)
	{
		for(int i=0; i<n; i++)
     		h.coef.push_back(coef[i]+g.coef[i]);
     	for(int i=n; i<m; i++)
     		h.coef.push_back(g.coef[i]);
	}
	else
	{
		for(int i=0; i<m; i++)
     		h.coef.push_back(coef[i]+g.coef[i]);
     	for(int i=m; i<n; i++)
     		h.coef.push_back(coef[i]);
	};
    h.cleanup();
	return h;
};

polinomio polinomio::multTerm(unsigned int k, int a)
{
	polinomio h;
	if (a==0) return h;
	h.coef=coef;
	h.nulo=nulo;
	int n=coef.size();
	for(int i=0;i<k;i++)
		(h.coef).push_back(0);
	
	for(int i=n-1; i>=0; i--)
		h.coef[i+k]=a*(h.coef[i]);
    
    for(int i=0;i<k;i++)
		h.coef[i]=0;
	h.cleanup();
	return h;
};

polinomio polinomio::operator - (polinomio b)
{
   polinomio diff=(*this)+b.multTerm(0,-1);
   diff.cleanup();
   return diff;
};

polinomio polinomio::operator * (polinomio b)
{
	polinomio aux;
	int n=coef.size();
	for(int i=0;i<n; i++)
		aux=aux+b.multTerm(i,coef[i]);
	aux.cleanup();
	return aux;
};


int polinomio::leadingCoeficient()
{
	return coef[coef.size()-1];
};

polinomio polinomio::rem(unsigned int k)
{
	unsigned int h=min(k,coef.size());
	polinomio resto;
	for(int i=0;i<h;i++)
	  resto.coef.push_back(coef[i]);
	resto.nulo=false;
	resto.cleanup();
	return resto;
    
};

polinomio polinomio::quo(unsigned int k)
{
	polinomio quociente;
	for(int i=k;i<coef.size();i++)
	  quociente.coef.push_back(coef[i]);
	quociente.nulo=false;
	quociente.cleanup();
	return quociente;
	
};

/// karatsuba
int max(int x, int y)
{
 if (x<y) return y; else return x;
};

polinomio polinomio::karatsuba(polinomio f, polinomio g)
{
  int n=f.coef.size();
  int m=g.coef.size();
  int maximo=max(n,m);
  int d=maximo/2 + maximo%2;
  if (d<2) return f*g;
  polinomio f0=f.rem(d);
  polinomio f1=f.quo(d);
  polinomio g0=g.rem(d);
  polinomio g1=g.quo(d);
  polinomio u=karatsuba(f1,g1);
  polinomio v=karatsuba(f0,g0);
  polinomio w=karatsuba(f0+f1,g0+g1);
  return u.multTerm(2*d,1)+(w-u-v).multTerm(d,1)+v;
};




//////// main /////////


int main()
{
   polinomio f;
   
   vector<int> c;
   c.push_back(2);
   c.push_back(1);
   c.push_back(-1);
   c.push_back(4);
   c.push_back(1);
   c.push_back(1);
   
   polinomio g(c);


   vector<int> d;
   d.push_back(-2);
   d.push_back(4);
   d.push_back(-1);
   d.push_back(1);
   d.push_back(-2);
   d.push_back(1);
   
   polinomio h(d);

 
   f=g*h;
   f.print();
   (g+h).print();
   (g-h).print();
   
   g.print();
   g.rem(3).print();
   g.quo(3).print();
   f.karatsuba(g,h).print();
   
}



