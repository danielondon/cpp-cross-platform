#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>
#include "variadic_templates.h"

using namespace std;

//  cout << "== TO STRING EXAMPLE =====" << endl;

template <typename T>
string convert_to_string(const T& t)
{
    stringstream ss;
    ss << typeid(T).name() <<" : "<< t ;
    return ss.str();
}

/// FIRST VERSION
// Add empty case (to compile
/*std::vector<string> convert_to_string_multiple()
{
    return {};
}

template <typename Param1, typename ... Param>
std::vector<string> convert_to_string_multiple(const Param1 & p1, const Param & ... param)
{
    vector<string> returnVector;
    returnVector.push_back(convert_to_string(p1));

    const auto remainder = convert_to_string_multiple(param...);
    returnVector.insert(returnVector.end(), remainder.begin(), remainder.end());
    return returnVector;
}
*/

/// Final Version
template <typename ... Param>
std::vector<string> convert_to_string_multiple(const Param & ... param)
{
    return{convert_to_string(param) ...};
}


// cout << "== ADDING EXAMPLE =====" << endl;

template <typename T>
T mysum(T t)
{
    std::cout << __FUNCSIG__ << " * \n";
    return t;
}

template <typename Param1, typename ... Param>
Param1 mysum(Param1 param1, Param ... param)
{
    std::cout << __FUNCSIG__ << "\n";
    return param1 + mysum(param...);
}

int main()
{
    cout << "== TO STRING EXAMPLE =====" << endl;

    // Converting one single thing at a time
    cout<< convert_to_string("Hello")<<endl;
    cout << convert_to_string(1234.9) << endl;
    cout << convert_to_string(234.87f) << endl;
    int x = 999;
    cout << convert_to_string(x) << endl;

    std::cout << "--- variadic_templates ----" << std::endl;


    // Converting Multiple things at a time
    const auto myvector = convert_to_string_multiple("hello", 12, 123.3f);
    for (const auto &myobject : myvector)
    {
        cout << myobject << endl;
    }


    cout << "== ADDING EXAMPLE =====" << endl;
    int y = 8;
    auto sum = mysum(123.8, x, y);
    cout << "The end result is " << sum << endl;

	return 0;
}