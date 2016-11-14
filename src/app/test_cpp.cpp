#include <stdio.h>
#include <iostream>
#include <vector>
#include "../dynamic_library/singleton_container.h"

using namespace std;

int main()
{
	std::cout<<"CPP Cross Platform with C++ 11 Features "<<std::endl;
	printf("Hello Clang\n");
	
	cSingleton * singleton = cSingleton::getInstance();
	singleton->printVector();
	
	cSingleton::destroy();
	return 0;
}