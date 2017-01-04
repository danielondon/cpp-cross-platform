#include <iostream>
#include "utilities.h"
#include "enums.h"

using namespace std;

void Utilities::foo()
{
	cout<<"foo"<<endl;
}

void Utilities::printScopedEnum(ScopedEnum myenum)
{
	cout << "printScopedEnum " << toUType(myenum) << endl;
	//cout << "printScopedEnum " << static_cast<int>(myenum) << endl;
}

void Utilities::printUnscopedEnum(UnscopedEnum myenum){	cout << "printUnscopedEnum " << myenum<< endl;}