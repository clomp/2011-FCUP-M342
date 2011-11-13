#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <strings.h>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BASE 1000000000
#define BASE_LEN 9
#define MAX 1000000

using namespace std;

class inteiro
{
public:


    bool negativo;
    vector<unsigned int> coeficientes;


public:

    inteiro(unsigned int n)
    {
        this->negativo = false;
        if (n == 0)
        {
            coeficientes.push_back(0);
        }
        else
        {
            while (n > 0)
            {
                coeficientes.push_back(n % BASE);
                n /= BASE;
            }
        }
    }

    inteiro(bool sinal, vector< unsigned int> n)
    {
        this->coeficientes = n;
        this->negativo = sinal;

    };

    inteiro(string n)
    {
        this->coeficientes = ConvertStringToVector(n);
        this->negativo = false;

    };

    void print()
    {
        int i;
        if (this->negativo == true)
        {
            printf("- ( ");
        }

        for (int i = coeficientes.size() - 1; i > 0; i--)
            printf("%d*(10^%d) + ", coeficientes.at(i), i * BASE_LEN);
        printf("%d*(10^%d)", coeficientes.at(0), (0) * BASE_LEN);

        if (this->negativo == true)
        {
            printf(" )");
        }
    }
    string ConvertVectorToString(vector<unsigned int> v)
    {
        int n = v.size();
        ostringstream vector_string;
        for (int i = n - 1; i >= 0; i--)
        {
           long long z = v[i];
            if (i < n - 1)
            {
                long long s = BASE / 10;
                while (z % s == z)
                {
                    vector_string << "0";
                    s = s / 10;
                };
            };
            vector_string << z;
        };
        return vector_string.str();
    };

    vector<unsigned int> ConvertStringToVector(string s)
    {
        vector<unsigned int> v;
        int n = s.length();
        int q = n / BASE_LEN;
        int r = n % BASE_LEN;
        string sub;
        for (int i = q - 1; i >= 0; i--)
        {
            sub = s.substr(r + i*BASE_LEN, BASE_LEN);
            v.push_back(atoi(sub.c_str()));
        };
        if (r > 0)
        {
            sub = s.substr(0, r);
            v.push_back(atoi(sub.c_str()));
        };
        return v;
    };
    bool operator<(inteiro b)
    {
        inteiro a(this->negativo, this->coeficientes);
        if (a.negativo == true && b.negativo == false)
        {
            return true;
        }
        else if (a.negativo == true && b.negativo == true)
        {
            if (a.coeficientes.size() > b.coeficientes.size())
            {
                return true;
            }
            else if (a.coeficientes.size() < b.coeficientes.size())
            {
                return false;
            }
            else
            {
                for (int idx = a.coeficientes.size() - 1; idx >= 0; idx--)
                {
                    if (a.coeficientes.at(idx) > b.coeficientes.at(idx))
                    {
                        return true;
                    }
                    else if (a.coeficientes.at(idx) < b.coeficientes.at(idx))
                    {
                        return false;
                    }
                }
                return false;
            }
        }
        else if (a.negativo == false && b.negativo == false)
        {
            if (a.coeficientes.size() > b.coeficientes.size())
            {
                return false;
            }
            else if (a.coeficientes.size() < b.coeficientes.size())
            {
                return true;
            }
            else
            {
                for (int idx = a.coeficientes.size() - 1; idx >= 0; idx--)
                {
                    if (a.coeficientes.at(idx) > b.coeficientes.at(idx))
                    {
                        return false;
                    }
                    else if (a.coeficientes.at(idx) < b.coeficientes.at(idx))
                    {
                        return true;
                    }
                }
                return false;

            }
        }
        else if (a.negativo == false && b.negativo == true)
        {
            return false;
        }
    }

    bool operator ==(inteiro b)
    {
        inteiro a(this->negativo, this->coeficientes);
        if (a.coeficientes.size() < b.coeficientes.size())
        {
            for (int i = b.coeficientes.size() - a.coeficientes.size(); i > 0; i--)
            {
                a.coeficientes.push_back(0);
            }
        }
        else if (a.coeficientes.size() > b.coeficientes.size())
        {
            for (int i = a.coeficientes.size() - b.coeficientes.size(); i > 0; i--)
            {
                b.coeficientes.push_back(0);
            }
        }
        if (((a.negativo == false && b.negativo == false) || (a.negativo == true && b.negativo == true)))
        {
            for (int idx = a.coeficientes.size() - 1; idx >= 0; idx--)
            {
                if (a.coeficientes.at(idx) != b.coeficientes.at(idx))
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator>(inteiro b)
    {
        inteiro a(this->negativo, this->coeficientes);
        if (a < b || a == b)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    bool operator !=(inteiro b)
    {
        inteiro a(this->negativo, this->coeficientes);
        if (a == b)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    inteiro operator +(inteiro b)
    {

        inteiro aux_a(this->negativo, this->coeficientes);
        inteiro aux_b(b.negativo, b.coeficientes);
        vector<unsigned int> result;
        inteiro resposta(0);
        unsigned int carry = 0;

        if (aux_a.negativo == true && aux_b.negativo == true)
        {
            aux_a.negativo = false;
            aux_b.negativo = false;
            inteiro aux_resposta = aux_a + aux_b;
            aux_resposta.negativo = true;
            return aux_resposta;
        }
        else if (aux_a.negativo == true && aux_b.negativo == false)
        {
            aux_a.negativo = false;
            inteiro aux_resposta = aux_b - aux_a;
            return aux_resposta;
        }
        else if (aux_a.negativo == false && aux_b.negativo == true)
        {
            aux_b.negativo = false;
            inteiro aux_resposta = aux_a - aux_b;
            return aux_resposta;
        }

        if (aux_a.coeficientes.size() < aux_b.coeficientes.size())
        {
            for (int i = aux_a.coeficientes.size(); i < aux_b.coeficientes.size(); i++)
            {
                aux_a.coeficientes.push_back(0);
            }
        }
        else if (aux_a.coeficientes.size() > aux_b.coeficientes.size())
        {
            for (int i = aux_b.coeficientes.size(); i < aux_a.coeficientes.size(); i++)
            {
                aux_b.coeficientes.push_back(0);
            }
        }
        unsigned int aux_soma = 0;
        for (int i = 0; i < aux_a.coeficientes.size(); i++)
        {
            aux_soma = aux_a.coeficientes.at(i) + aux_b.coeficientes.at(i) + carry;
            if (aux_soma >= BASE)
            {
                aux_soma = aux_soma % BASE;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            result.push_back(aux_soma);
        }
        if (carry == 1)
        {
            result.push_back(carry);
        }
        resposta.coeficientes = result;
        return resposta;
    }
    inteiro operator -(inteiro b)
    {
        inteiro aux_a(this->negativo, this->coeficientes);
        inteiro aux_b(b.negativo, b.coeficientes);
        vector<unsigned int> result;
        inteiro resposta(0);
        int carry = 0;
        int aux_subt = 0;
        if (aux_a.coeficientes.size() < aux_b.coeficientes.size())
        {
            for (int i = aux_b.coeficientes.size() - aux_a.coeficientes.size(); i > 0; i--)
            {
                aux_a.coeficientes.push_back(0);
            }
        }
        else if (aux_a.coeficientes.size() > aux_b.coeficientes.size())
        {
            for (int i = aux_a.coeficientes.size() - aux_b.coeficientes.size(); i > 0; i--)
            {
                aux_b.coeficientes.push_back(0);
            }
        }

        if ((aux_a.negativo == false && aux_b.negativo == false) && (aux_a < aux_b))
        {
            inteiro aux_resposta = aux_b - aux_a;
            aux_resposta.negativo = true;
            return aux_resposta;
        }
        else if (aux_a.negativo == true && aux_b.negativo == true)
        {
            aux_b.negativo = false;
            aux_a.negativo = false;
            inteiro aux_resposta = aux_b - aux_a;
            return aux_resposta;
        }
        else if (aux_a.negativo == true && aux_b.negativo == false)
        {
            aux_b.negativo = true;
            inteiro aux_resposta = aux_a + aux_b;
            return aux_resposta;
        }
        else if (aux_a.negativo == false && aux_b.negativo == true)
        {
            aux_b.negativo = false;
            inteiro aux_resposta = aux_a + aux_b;
            return aux_resposta;
        }

        for (int i = 0; i < aux_a.coeficientes.size(); i++)
        {
            aux_subt = aux_a.coeficientes.at(i) - aux_b.coeficientes.at(i) - carry;
            if (aux_subt < 0)
            {
                aux_subt = (aux_subt + BASE);
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            result.push_back(aux_subt);
        }
        resposta.coeficientes = result;
        return resposta;
    }


    inteiro operator *(inteiro num)
    {
        inteiro resposta(0);
        int i, j;
        long long k;
        resposta.negativo=negativo^num.negativo;
        for( i=0 ; i<coeficientes.size() ; i++ )
        {
            for( j=0 ; j<num.coeficientes.size() ; j++ )
            {
                k=coeficientes[i];
                k*=num.coeficientes[j];
                resposta.adiciona(k,i+j);
            }
        }
        resposta.arruma();
        return resposta;
    }

    void adiciona( long long valor, int pos )
    {
        int i;
        for( i=pos ; valor>0 ; i++ )
        {
            while( coeficientes.size()<=i )
            {
                coeficientes.push_back(0);
            }
            coeficientes[i]+=valor%BASE;
            valor=(valor/BASE)+(coeficientes[i]/BASE);
            coeficientes[i]%=BASE;
        }
    }

    void arruma()
    {
        while( coeficientes.back()==0 && coeficientes.size()>1 )
        {
            coeficientes.pop_back();
        }
    }

    inteiro operator /(inteiro num)
    {
        inteiro aux_a(this->negativo, this->coeficientes);
        inteiro um(1);
        inteiro result(0);
        inteiro zero(0);
        if (num == zero)
        {
            printf("Divisao por zero\n");
            return NULL;
        }
        if (aux_a == num)
        {
            printf("a igual b\n");
            return um;
        }
        if (aux_a < num)
        {
            printf("ambos sao iguais\n");
            return zero;
        }
        while ((aux_a.negativo == false))
        {
            aux_a = aux_a - num;
            result = result + um;

        }
        if ((this->negativo == false && num.negativo == true) || (this->negativo == true && num.negativo == false))
        {
            result.negativo = true;
        }
        result = result - um;
        return result;

    }
    inteiro operator %(inteiro num)
    {
        inteiro aux_a(this->negativo, this->coeficientes);
        inteiro result(0);
        inteiro zero(0);
        if (num == zero)
        {
            printf("Divisao por zero\n");
            return NULL;
        }
        if (aux_a == num)
        {
            printf("a igual b\n");
            return zero;
        }
        if (aux_a < num)
        {
            printf("a menor b\n");
            return aux_a;
        }
        while ((aux_a.negativo == false))
        {
            aux_a = aux_a - num;
        }
        result = aux_a + num;
        return result;

    }

    inteiro fatorial()
    {
        inteiro num(this->negativo,this->coeficientes);
        inteiro um(1);
        inteiro result(1);
        result = result * num;
        while(num>um)
        {
            inteiro fat_aux = num - um;
            result =result * (fat_aux);
            num = fat_aux;
        }
        return result;
    }

    inteiro divisor()
    {
        inteiro num(this->negativo,this->coeficientes);
        inteiro zero(0);
        inteiro dois(2);
        inteiro um(1);
        while((num%dois)!= zero)
        {
            dois = dois + um;
        }
        return dois;
    }
    bool isPrime(inteiro num)
    {
        inteiro cont(2);
        inteiro um(1);
        inteiro zero(0);
        while(cont < num)
        {
            if((num%cont) == zero)
            {
                return false;
            }
            cont = cont + um;
        }
        return true;
    }
    inteiro mmc()
    {
        inteiro zero(0);
        inteiro um(1);
        inteiro num(this->negativo,this->coeficientes);
        inteiro cont(2);
        int i=0;
        while(num != cont)
        {
            cont.print();
            if(isPrime(cont)==true)
            {
                if((num%cont)==zero)
                {
                    num = num/cont;
                    printf("( ");
                    cont.print();
                    printf(" ) * ");
                }
                else
                {
                    cont = cont + um;
                }
            }
            else
            {
                cont = cont + um;
            }
        }
        return cont;
    }

};

int main()
{
    inteiro fat100("100");
    printf("Fatorial de 100: \n");
    inteiro respfat100 = fat100.fatorial();
    respfat100.print();
    printf("\n-------------------------------------------------------------------------------------------------------\n");

    printf("\nFatorial de 1000: \n");
    inteiro fat1000("1000");
    inteiro respfat1000 = fat1000.fatorial();
    respfat1000.print();
    printf("\n-------------------------------------------------------------------------------------------------------\n");

    printf("\nMenor divisor de: ");
    inteiro divisor("7125");
    divisor.print();
    printf(" é:\n ");
    inteiro respdivisor = divisor.divisor();
    respdivisor.print();
    printf("\n-------------------------------------------------------------------------------------------------------\n");

    inteiro fatorprimo("100000");
    printf("\nOs fatores primos de: ");
    fatorprimo.print();
    printf(" são: \n");
    inteiro respfatprimo = fatorprimo.mmc();
    respfatprimo.print();
    printf("\n-------------------------------------------------------------------------------------------------------\n");
    return 0;
}
