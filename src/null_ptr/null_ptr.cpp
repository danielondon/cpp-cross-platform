
#include <iostream>
#include <memory>

using namespace std;

class Widget
{
public:
	int value;
};

int f1(std::shared_ptr<Widget> spw) { cout << "f1: " << endl; return 0; }  // call these only when
double f2(std::unique_ptr<Widget> upw) { cout << "f2: " << endl; return 1; }  // the appropriate
float f3(Widget* pw) { cout << "f3: " << endl; return 3.0f; }              // mutex is locked

template<typename FuncType,	typename PtrType>
auto wrapperFunction(FuncType func, PtrType ptr) -> decltype(func(ptr))
{
	return func(ptr);
}

int main()
{
	std::cout << "nullptr CLANG" << std::endl;
	
	{	
		f1(0);
		f2(0);
		f3(0);

		f1(NULL);
		f2(NULL);
		f3(NULL);

		f1(nullptr);
		f2(nullptr);
		f3(nullptr);
	}
	cout << endl << "----Using Wrappers-----" << endl;

	{
		auto returnValue1 = wrapperFunction(f1, nullptr);
		auto returnValue2 = wrapperFunction(f2, nullptr);
		auto returnValue3 = wrapperFunction(f3, nullptr);
	}
	// This does not build, because template can not resolve 0 as a pointer
	{
		//auto returnValue1 = wrapperFunction(f1, 0);
		//auto returnValue2 = wrapperFunction(f2, 0);
		//auto returnValue3 = wrapperFunction(f3, 0);
	}

	return 0;
}