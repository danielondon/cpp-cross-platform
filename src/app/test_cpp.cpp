#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "../dynamic_library/singleton_container.h"
#include "test_cpp.h"

using namespace std;

int main()
{
	std::cout<<"CPP Cross Platform with C++ 11 Features "<<std::endl;
	printf("Hello Clang\n");
	
	cSingleton * singleton = cSingleton::getInstance();
	
	// Initial State of Vector
	singleton->printVector();

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
				singleton->addToContainer(inputNumber);

				// Print New State of the vector
				singleton->printVector();
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

	// Last State of Vector
	singleton->printVector();
	
	
	cSingleton::destroy();
	return 0;
}