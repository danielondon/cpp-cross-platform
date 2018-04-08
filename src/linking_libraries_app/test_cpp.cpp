#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "../dynamic_library/singleton_container.h"
#include "../static_library/utilities.h"

using namespace std;

int main()
{
	// Basic Print Outs
	std::cout<<"CPP Cross Platform with C++ 11 Features "<<std::endl;
	printf("Hello Clang\n");
	
	// Using Static Library
	Utilities::foo();

	// Initial State of Vector
	GetSingleton().printContainer();

	string input = "";
	int inputNumber = { 0 };

	while (true) {
		cout << "Please enter number to add to the container: ";
		getline(cin, input);

		if (input.length() > 0) 
		{
			//  converts from string to number
			stringstream myStream(input);
			if (myStream >> inputNumber)
			{
				// Add Item to the container
				GetSingleton().addToContainer(inputNumber);

				// Print New State of the vector
				GetSingleton().printContainer();
			}
			else
			{
				cout << "Invalid Input, try again or leave empty to exit " << endl;
			}
			
		}
		else
		{
			cout << "Bye Bye "<<endl;
			break;
		}
	}

	// Print Last State of Vector
	GetSingleton().printContainer();
	
	return 0;
}