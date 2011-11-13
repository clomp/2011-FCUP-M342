#ifndef INTEIRO_H
#define INTEIRO_H

#include <string>
#include <vector>
using namespace std;

class inteiro {
    bool negativo;
    vector<unsigned int> coeficientes;

    inteiro shift(int);
    inteiro slice(int, int);
    pair<inteiro, inteiro> divmod(inteiro);

public:
    inteiro();
    inteiro( int n );
    inteiro( bool, vector<unsigned int> );
    inteiro( string );

    bool operator < ( inteiro );
    bool operator > ( inteiro );
    bool operator <= ( inteiro );
    bool operator >= ( inteiro );
    bool operator == ( inteiro );
    bool operator != ( inteiro );
    inteiro operator + ( inteiro );
    inteiro operator - ( );
    inteiro operator - ( inteiro );
    inteiro operator * ( inteiro );
    inteiro operator / ( inteiro );
    inteiro operator % ( inteiro );
    string ConvertToString( );
    inteiro ConvertToInteiro( string );
};

#endif

