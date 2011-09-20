#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

//////////////////////////////////////////////////////
// M342 Álgebra Computacional
// class inteiro
// 	permite aritmética multi-precisão
//////////////////////////////////////////////////////


class inteiro
{

	bool s;
	vector<unsigned int> v;

   public:
	inteiro(bool, vector<unsigned int>);
	inteiro(int);
	inteiro(string);
	void  print();
	inteiro operator + (inteiro);
};

////////////////// os construtores ////////////

inteiro::inteiro(bool sign, vector<unsigned int> coeficientes) {
                s=sign;
                v=coeficientes;
};

inteiro::inteiro(int a) {
	if(a<0){
		s=1;
                v.push_back((-1)*a);
        }
	else
	{
                s=0;
                v.push_back(a);
        }
};

inteiro::inteiro(string num_str){
        int n=num_str.length();
        int m=n%9;

	for(int i=n/9-1;i>=0; i--)
{
	int d=atoi((num_str.substr(m+9*i,9)).c_str());
	cout << d << ":";
                v.push_back(d);
}

        if (m>0) {
		int d=atoi((num_str.substr(0,m)).c_str()); 
		cout << d;
		v.push_back(d);
	}
cout << endl;
};

////////// inteiro:print ///////////
void  inteiro::print() {
	for(int i=v.size()-1; i>=0;i--) cout << v[i];
};

///////// inteiro:+///////////
inteiro inteiro::operator + (inteiro b) {
	inteiro aux(0);
        int m=b.v.size();
        int n=v.size();
        cout << n << ", " << m<<endl;
        return aux;
};
////////////////////////////////////////////


int main()
{
	string num_str;
        cin >> num_str;
        inteiro zahl(num_str);
        zahl.print();
        cout << endl;
	cin >> num_str;
	inteiro zahl2(num_str);
	zahl2.print();
	cout << endl;

}
