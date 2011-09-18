#include <iostream>
#include <vector>
using namespace std;

class polinomio
{

        vector<int> coef;
         bool nulo;
         unsigned int deg;

    public:
        polinomio()
        {
            nulo=true;
            coef.push_back(0);
            deg=0;
        };

        polinomio(vector<int> v)
        {
            if (!v.empty())
            {
                coef=v;
                nulo=false;
                deg=v.size();
            }
        };
        void print()
        {
            if(!nulo)
            {
                cout << coef[0];
                for(int i=1;i<deg;i++)
                  cout << " +" << coef[i] << "x "<< i;
            }
            else
                cout << "0";
            cout << endl;
        };
        unsigned int grau()
        {
            return deg;
        };

        void operator = (const polinomio &x)
        {
          coef=x.coef;
          nulo=x.nulo;
          deg=x.deg;
        };

        polinomio operator + (polinomio g)
        {
            polinomio h;
            h=g;
            unsigned int n=deg;
            unsigned int m=h.grau();
            unsigned int min;
            if (n<=m) min=n; else min=m;
            for (int i=0; i<=min; i++)
            {
               h.coef[i]=h.coef[i]+coef[i];
            };
            if(n>m)
            {
                for (int i=m+1; i<=n;i++)
                {
                   h.coef.push_back(coef[i]);
                };
            };
            h.nulo=false;
            h.deg=h.coef.size();
            return h;
        };

};



int main()
{
    cout << "Hello world!" << endl;
    vector<int> c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(1);
    polinomio f=(c);
    f.print();
    c[0]=5;
    c.pop_back();
    c[1]=4;
    polinomio g=(c);
    g.print();
    (f+g).print();
    return 0;
}
