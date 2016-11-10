#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	cout<<"CPP Cross Platform with C++ 11 Features "<<endl;

	printf("Hello Clang\n");
	vector<int> vect {1, 3, 2, 4, 5 };
	for (auto& el : vect)
		cout << " - " << el << endl;

	return 0;
}