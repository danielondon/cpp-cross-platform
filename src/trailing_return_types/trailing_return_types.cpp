#include <iostream>
using namespace std;

template<class T>
auto multiply(T a, T b) -> decltype(a*b)
{
	return a*b;
}


int main()
{
	cout << "Trailing Return Types" << endl;
	int a = 12;
	int b = 3;

	cout << "Multiplication result is " << multiply(12, 3) << endl;

	return 0;
}