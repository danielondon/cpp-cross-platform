// Example program
#include <iostream>
#include <string>
#include <vector>
using namespace std;


vector<bool> returnBoolVector()
{
	return{ true, false, true, false };
}

int main()
{
	vector<bool> myVector{ true, false, true };

	for (bool flag : myVector)
	{
		cout << flag << endl;
	}

	int pos = 1;

	{
		bool myFlag = myVector[pos];
		cout << "Flag " << pos << " is " << myFlag << endl;
	}

	myVector[pos] = true;

	{
		auto myFlag = myVector[pos];
		cout << "Flag " << pos << " is " << myFlag << endl;
	}

	return 0;
}
