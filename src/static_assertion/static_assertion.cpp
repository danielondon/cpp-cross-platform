#include <iostream>
#include <vector>
#include <type_traits>
//#define NDEBUG 
#include <assert.h>

using namespace std;

class MyClass 
{
    
public:
    MyClass() = default;
    MyClass(MyClass const&) = delete;
    int value{ 10 };
};

template <typename T>
void checkAssert(T & x)
{
    assert(x.value >= 10);
    //static_assert(x > 10, "x must be greater than 10");
    cout << "All good x > 10" << endl;

    assert(is_copy_constructible<T>::value);
    //static_assert(is_copy_constructible<T>::value, "x must be copy constructuble");
    cout << "All good is copy constructuble" << endl;
}



int main()
{
    std::cout << std::boolalpha;
    std::cout << std::is_array<MyClass>::value << '\n';
    std::cout << std::is_array<MyClass[]>::value << '\n';
    std::cout << std::is_array<MyClass[3]>::value << '\n';
    std::cout << std::is_array<float>::value << '\n';
    std::cout << std::is_array<int>::value << '\n';
    std::cout << std::is_array<int[]>::value << '\n';
    std::cout << std::is_array<int[3]>::value << '\n';
    std::cout << std::is_array<std::vector<int>>::value << '\n';

    MyClass x;
    //--x.value;

    checkAssert(x);
}