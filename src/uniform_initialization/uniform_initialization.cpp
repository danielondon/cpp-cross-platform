#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Widget {
public:
	Widget() { cout << "constructor DEFAULT" << endl; }

	Widget(int i, bool b) { value = i; cout << "constructor int bool" << endl; }
	Widget(int i, double d) { value = i;  cout << "constructor int double" << endl; }
	//Widget(Widget const& another) { value = another.value; cout << "constructor copy" << endl; }
	//Widget(initializer_list<bool> il) { cout<<"constructor initializer list bool"<<endl; }
	Widget(initializer_list<string> il) { cout << "constructor initializer list string" << endl; }
	Widget(initializer_list<long double> il) { value = *il.begin(); cout << "constructor initializer list long double" << endl; }
	operator float const() {
		return value;
	}

	float value{ 0 };

	Widget(Widget const& w) {
		value = w.value;
		cout << "constructor COPY" << endl;
	}
};


int main()
{
	std::cout << "Uniform Initialization with CLANG" << std::endl;

	cout << "----" << endl;
	Widget w1{ 10, 5.0 };
	cout << "----" << w1 <<endl; 
	Widget w2(15, 5.0);
	cout << "----" << w2 << endl;
	Widget w3;
	w3 = w1;
	cout << "----" << w3 << endl;
	Widget w4 = Widget();
	cout << "----" << w4 << endl;
	Widget w5{ w2 };
	cout << "----" << w5 << endl;

	double x = 1;
	double y = 23;
	double sum{ x + y };
	cout << "Sum " << sum << endl;

	return 0;
}