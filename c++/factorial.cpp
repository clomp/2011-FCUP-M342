#include <iostream>
using namespace std;

class inteiro 
{
  unsigned int n;
  public:
    inteiro (unsigned int numero) { n=numero; };
    unsigned int factorial() { 
      unsigned int fact=1;  
      for (int i=1; i<=n; i++)   fact=fact*i;
      return fact;
    }    
};

main() {
  unsigned int n;
  cin >> n;
  inteiro numero(n);
  cout << numero.factorial() << endl;
}
