#include <iostream>
#include <iterator> // std::copy
#include <sstream>
#include <vector>
#include <tuple>
#include <cmath>
#include <typeinfo> // Avoids exception in clang/linux member access into incomplete type 'const std::type_info'

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

void printContainer(vector<int> const& container)
{
	cout << "printContainer Const& " << endl;
	std::copy(container.begin(), container.end(), ostream_iterator<int>(cout));
	cout <<endl;
}

void printContainer(vector<int> && container)
{
	cout << "printContainer && " << endl;
	std::copy(container.begin(), container.end(), ostream_iterator<int>(cout));
	cout << endl;
}

template <class Container>
void printContainerTemplate(Container && container)
{
	cout << "printContainer Template " << endl;
	std::copy(container.begin(), container.end(), ostream_iterator<int>(cout));
	cout << endl;
}

template <class Container, class Index>
auto doSomethingAndUpdate(Container && container, Index index) -> decltype(forward<Container>(container)[index])
{
	foo();
	return container[index];
}


auto get_fun(int arg) -> double(*)(double)	
{
	switch (arg)
	{
	case 1: return std::fabs;
	case 2: return std::sin;
	default: return std::cos;
	}
}

class Widget
{
public:
	int value;
};


template<typename It>    // algorithm to dwim ("do what I mean")
void printElementsFromContainer(It b, It e)    // for all elements in range from
{                        // b to e
	while (b != e) {
		typename std::iterator_traits<It>::value_type const& currValue = *b;
		//currValue++;
		cout << "Printing element from template " << currValue << endl;
		++b;
	}
}

float dummyFloatFunction(float x)
{
    return x;
}

int main()
{
	std::cout<<"auto and decltype using Clang"<<std::endl;

	vector<int> vector{ 1, 2, 3, 4};

	cout << "Type of vector "<< typeid(decltype(vector)).name() << endl;
	cout << "Type of foo() " << typeid(decltype(foo())).name() << endl;
	cout << "Type of foo " << typeid(decltype(foo)).name() << endl;

	cout << "Type of vector " << typeid(vector).name() << endl;
	cout << "Type of foo() " << typeid(foo()).name() << endl;
	cout << "Type of foo " << typeid(foo).name() << endl;

	/// LVALUE
	printContainerTemplate(vector);
	printContainer(vector);
	//cout<<"Result is " << doSomethingAndUpdate(vector, 0)<<endl;
	doSomethingAndUpdate(vector, 0) = 0;
	printContainerTemplate(vector);
	printContainer(vector);

	/// RVALUE
	printContainerTemplate(createVector());
	printContainer(createVector());
	int rvalue = doSomethingAndUpdate(createVector(), 2) ;
	cout<<"Result rvalue is " << rvalue <<endl;

	// auto for func
	auto my_fun = get_fun(2);
	std::cout << "type of my_fun: " << typeid(my_fun).name() << '\n';
    std::cout << "type of my_fun eval: " << typeid(my_fun(5)).name() << '\n';
    std::cout << "type of dummy float func: " << typeid(&dummyFloatFunction).name() << '\n';
    std::cout << "type of sin: " << typeid(std::sin(3.0f)).name() << '\n';
	std::cout << "my_fun: " << my_fun(3) << '\n';


	// Decltype
	Widget widget1{ 78 };
	Widget & widgetRef2 = widget1;
	widget1.value = 100;
	auto widget3 = widgetRef2;
	widget3.value = 200;
	decltype(auto) widgetRef4 = widgetRef2;
	widgetRef4.value = 500;

	cout << "widget1 " << widget1.value << endl;
	cout << "widgetRef2 " << widgetRef2.value << endl;
	cout << "widget3 " << widget3.value << endl;
	cout << "widgetRef4 " << widgetRef4.value << endl;

	// auto advantage, for removing complexity
	printElementsFromContainer(vector.begin(), vector.end());
	printContainerTemplate(vector);

	return 0;
}