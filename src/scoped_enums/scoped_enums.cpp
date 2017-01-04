#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <type_traits>
#include <tuple>
#include "../static_library/utilities.h"
#include "../static_library/enums.h"

using namespace std;

using Coordinates = std::tuple<int, int, int>;

int main()
{
	// Basic Print Outs
	std::cout<<"Scoped Enums using Clang"<<std::endl;
	
	// Using Static Library
	Utilities::foo();

	cout << "Scoped Enum sItem1 " << toUType(ScopedEnum::sItem1) << endl;
	cout << "Scoped Enum sItem4 " << toUType(ScopedEnum::sItem4) << endl;
	cout << "Scoped Enum sItem1 " << static_cast<int>(ScopedEnum::sItem1) << endl;
	cout << "Unscoped Enum uItem1 " << uItem1 << endl;

	Coordinates coordinates { 10, 30, 43 };
	cout << "x "<< get<uItem1>(coordinates) << endl;
	cout << "y " << get<uItem2>(coordinates) << endl;
	cout << "z " << get<uItem3>(coordinates) << endl;

	cout << "x " << get<toUType(ScopedEnum::sItem1)>(coordinates) << endl;
	cout << "y " << get<toUType(ScopedEnum::sItem2)>(coordinates) << endl;
	cout << "z " << get<toUType(ScopedEnum::sItem3)>(coordinates) << endl;

	Utilities::printScopedEnum(ScopedEnum::sItem4);
	Utilities::printUnscopedEnum(uItem2);

	//
	cout << "Variables: " << endl;
	ScopedEnum myScopedEnum{ ScopedEnum::sItem2 };
	UnscopedEnum myUnscopedEnum{ uItem3 };
	Utilities::printScopedEnum(myScopedEnum);
	Utilities::printUnscopedEnum(myUnscopedEnum);

	return 0;
}