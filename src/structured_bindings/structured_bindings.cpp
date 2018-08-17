#include <iostream>
#include <string>
#include <tuple>

using namespace std;

tuple<int, string> returnTwoValues()
{
    return make_tuple(100, "Daniel");
}

int main() {
    cout << "Strutured bingindss" << endl;

    //int number1; string name1;
    //tie(number1, name1) = returnTwoValues();
    // C++17
    auto[number1, name1] = returnTwoValues();

    cout << "Number : " << number1 << endl;
    cout << "Name : " << name1 << endl;

    return 0;
}