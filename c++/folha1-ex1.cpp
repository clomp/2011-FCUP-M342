#include <iostream>
#include <vector>

using namespace std;

int main()
{
	unsigned int x,q;
	cout << "Um numero e a base: ";
	cin >> x >> q;
	vector<unsigned int> v;
	while (x>0)
	{
		v.push_back(x%q);
		x=x/q; 
	}
	cout << "( ";
	for(int i=v.size()-1; i>=0; i--)
	{
		cout << v[i] ;
		if (i>0) cout << ", "; else cout << " )" << endl;
	}
	cout <<endl;
}
