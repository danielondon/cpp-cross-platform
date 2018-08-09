#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>
#include <tuple>
#include <list>
#include <set>
#include <map>

using namespace std;

//  cout << "== TO STRING EXAMPLE =====" << endl;

template <typename T>
string convert_to_string(const T& t)
{
    stringstream ss;
    ss << typeid(T).name() <<" : "<< t ;
    //ss << t;
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

/// Variadic Templates Struct
template <class ... Ts>
struct MyTuple
{};

template <class T, class ... Ts>
struct MyTuple<T, Ts...> : MyTuple<Ts ...>
{
    MyTuple(T t, Ts ... ts) : MyTuple <Ts ...>(ts ...), tail(t) {}
    T tail;
};

/// Overload << to print the pair
template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const std::pair<T, U>& p) {
    out << "[" << p.first << ", " << p.second << "]";
    return out;
}

// 1. Very Generic, where template parameters are by default
//template <class Container>
//void printContainer(Container & container)
// 2. Only for containters which contain two template parameters (vector, list)
// template <template <typename, typename> class ContainerType, typename ValueType,  typename AllocType>
// void printContainer(const ContainerType<ValueType, AllocType>& container)
// 3. For containters which contains different template temparameters (set or map)
template <template <typename, typename...> class ContainerType,  typename ValueType, typename... Args>
void printContainer(const ContainerType<ValueType, Args...>& container)
{
    for (auto & o : container)
    {
        cout << o << " ";
    }
    cout << endl;
}

////  Print Tuple Example

template <class T, size_t N>
struct TuplePrinter {
    static string print(const T& t)
    {
        //std::cout << __FUNCSIG__ << " 1 \n";
        return TuplePrinter<T, N - 1>::print(t)+ " " + convert_to_string(std::get<N - 1>(t));
    }
};

template <class T>
struct TuplePrinter<T, 1> {
    static string print(const T& t)
    {
        //std::cout << __FUNCSIG__ << " 2 \n";
        return convert_to_string(std::get<0>(t));
    }
};


template <typename ... Param>
string printTuple(tuple<Param ...> t)
{
    //std::cout << __FUNCSIG__ << " 0 \n";
    return TuplePrinter<decltype(t), sizeof...(Param)>::print(t) ;
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

    cout << "== STRUCT with Variadic =====" << endl;
    MyTuple<int, float, double, string> myTuple(2, 3.5f, 345.65, "daniel");
    // Further implementation to access myTuple is needed... (to continue)

    cout << "== CONTAINER=====" << endl;
    list<int> mylist{ 1, 12, 3 };
    set<string> myset{ "daniel", "carlos", "pedro2" };
    map<int, char> mymap = { { 1, 'a' },{ 3, 'b' },{ 5, 'c' },{ 7, 'd' } };

    printContainer(myvector);
    printContainer(mylist);
    printContainer(myset);
    printContainer(mymap);


    cout << "== Print Tuple Variadic =====" << endl;
    auto mytuple = std::make_tuple("daniel",  123.54, 9, 12.4f, false);
    cout << "My Tuple " << printTuple(mytuple) << endl;

	return 0;
}