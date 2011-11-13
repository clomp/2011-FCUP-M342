# include <iostream>
using namespace std;

int main()
{
    cout <<"Número a factorizar" ;
    long long n;
    cin >> n;

    long long factorial=1;
    for (long long i=1; i<=n; i++)
    {
        factorial=factorial*i;
    }

    cout << n <<"!= " <<factorial <<endl;
    return 0;
};
