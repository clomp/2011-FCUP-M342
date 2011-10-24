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
    cout << "Deve introduzir uma lista de inteiros positivos que representa a lista dos coeficientes de um inteiro a base 10^9. Termine a lista com -1."<<endl;
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
