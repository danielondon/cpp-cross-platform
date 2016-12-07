#include <stdio.h>
#include <iostream>
#include <iterator> // std::copy
#include <sstream>
#include <vector>
#include <type_traits>
#include <tuple>

using namespace std;

void foo()
{
	cout << "foo" << endl;
}

vector<int> createVector()
{
	vector<int> c = { 1, 2, 3, 4, 5, 6, 7 };
	return c;
}

template <class Container>
void printContainer(Container const& container)
{
	std::copy(container.begin(), container.end(), ostream_iterator<int>(cout));
	cout <<endl;
}

template <class Container, class Index>
auto doSomethingAndUpdate(Container && container, Index index) -> decltype(forward<Container>(container)[index])
{
	foo();
	return container[index];
}


int main()
{
	std::cout<<"auto and decltype using Clang"<<std::endl;

	vector<int> vector{ 1, 2, 3, 4};

	cout << "Type of vector "<< typeid(decltype(vector)).name() << endl;
	cout << "Type of foo() " << typeid(decltype(foo())).name() << endl;
	cout << "Type of foo " << typeid(decltype(foo)).name() << endl;

	/// LVALUE
	printContainer(vector);
	//cout<<"Result is " << doSomethingAndUpdate(vector, 0)<<endl;
	doSomethingAndUpdate(vector, 0) = 0;
	printContainer(vector);

	/// RVALUE
	printContainer(createVector());
	int rvalue = doSomethingAndUpdate(createVector(), 2) ;
	cout<<"Result rvalue is " << rvalue <<endl;

	return 0;
}