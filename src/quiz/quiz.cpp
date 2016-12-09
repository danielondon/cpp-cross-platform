#include <stdio.h>
#include <iostream>
#include <iterator> // std::copy
#include <sstream>
#include <vector>
#include <type_traits>
#include <tuple>

using namespace std;

template <typename T> 
void P(const T & x) { std::cout << x; }

void foo(const void*) { P("v"); }
void foo(const std::string&) { P("s"); }

int main()
{
	
	std::cout << "QUIZ 1" << std::endl;
	// Guess Result= 3210123zs
	unsigned int i;
	for (i = 3; i>0; i--)
		P(i);
	for (; i<4; i++)
		P(i);
	// Is unsigned int greater than -1?
	// What is cast to what? i to int, or -1 to unsigned ?
	if (i > -1)
		P("z");
	// foo overload to void*, instead of const&, why?
	foo("Conan!");
	
	// Final Result : 3210123v
	std::cout << std::endl;


	return 0;
}