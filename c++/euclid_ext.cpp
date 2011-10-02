#include <iostream>
using namespace std;

int mdc(int a, int b, int* x, int* y)
{
	int r0,s0,t0,r1,s1,t1;
	r0=a;	s0=1;	t0=0;
	r1=b;	s1=0;	t1=1;
	
	while(r1!=0)
	{
	  int q = r0/r1;	  
	  int h = r0%r1; r0=r1; r1=h;
	  h=s0-q*s1; s0=s1; s1=h;
	  h=t0-q*t1; t0=t1; t1=h;
	};
	(*x)=s0;
	(*y)=t0;
	return r0;
};

int main()
{
		int a,b,x,y;
		x=0;
		y=0;
		cin >> a >> b;
		cout << "mdc=" << mdc(a,b,&x,&y);
		cout << " = " << x << "*" << a << " + "<<  y << "*" << b << endl;
}
