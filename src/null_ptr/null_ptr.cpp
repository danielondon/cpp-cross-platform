
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

//void overloadedFunc(std::shared_ptr<Widget> sp) { cout << "overloaded with shared pointer" << endl; }
void overloadedFunc(std::unique_ptr<Widget> up) { cout << "overloaded with unique pointer" << endl; }
//void overloadedFunc(Widget * rp) { cout << "overloaded with raw pointer" << endl; }
//void overloadedFunc(void * vp) { cout << "overloaded with void pointer" << endl; }
void overloadedFunc(int pi) { cout << "overloaded with int" << endl; }

template<typename FuncType,	typename PtrType>
auto wrapperFunction(FuncType func, PtrType ptr) -> decltype(func(ptr))
{
	return func(ptr);
}

int main()
{
	std::cout << "nullptr -------" << std::endl;


    { // Overload Test
        overloadedFunc(0);
        overloadedFunc(NULL);
        overloadedFunc(nullptr);
    }

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
		//auto returnValue2 = wrapperFunction(f2, NULL);
		//auto returnValue3 = wrapperFunction(f3, 0);
	}

	return 0;
}