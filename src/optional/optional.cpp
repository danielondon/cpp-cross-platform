#include <optional>
#include <iostream>
#include <string>

using namespace std;

class UserName
{
public:
    explicit UserName(const std::string & str, optional<int> _age): mName(str), age(_age)
    {
        cout<<"UserName "<<mName<<endl;
    }

    ~UserName(){
        cout<<"~ Username "<<mName<<endl;
    }
private:
    string mName;
    optional<int> age;
};

void printName(optional<string> & name)
{
    if (name)
        cout<<"Name is "<<name.value() <<endl;
    else
        cout<<"no name provided"<<endl;
}

int main() {
    cout << "Optional Test c++ 17" << endl;
    { // TEST 1
        UserName ricardo { "Ricardo", nullopt };
        std::optional<UserName> eEmpty;
        cout << "---" << endl;
        eEmpty.emplace("Steve", 1);
        cout << "---" << endl;
        eEmpty.emplace("Mark", nullopt);
        cout << "---" << endl;
        eEmpty.reset();
        cout << "---" << endl;
        eEmpty.emplace("Fred", 3);
        cout << "---" << endl;
        eEmpty = UserName("Daniel", 4);
        cout << "---" << endl;
        eEmpty = UserName { "Francisco", nullopt };
        cout << "---" << endl;
        eEmpty = ricardo;
        cout << "---" << endl;
        std::optional<UserName> eEmpty2;
        eEmpty2.swap(eEmpty);
        cout << "---" << endl;
    }
cout<<"*************"<<endl;
    { // Test 2
        optional<string> myName;
        printName(myName);
        myName = "Daniel";
        printName(myName);
        //printName("Carlos");
        //printName();
    }

    cout<<"*************"<<endl;
    { // Test 3
        std::optional<int> oEmpty;
        std::optional<int> oTwo(2);
        std::optional<int> oTen(10);

        //std::cout <<"oEmpty "<< oEmpty.value()  << "\n"; // Throws std::bad_optional_access'
        std::cout <<"oEmpty "<< oEmpty.value_or(0)  << "\n"; // Returns default
        std::cout <<"oTen "<< oTen.value() << "\n";
        std::cout <<"oTwo "<< *oTwo << "\n";

        std::cout << std::boolalpha;
        std::cout << (oTen > oTwo) << "\n";
        std::cout << (oTen < oTwo) << "\n";
        std::cout << (oEmpty < oTwo) << "\n";
        std::cout << (oEmpty > oTwo) << "\n";
        std::cout << (oEmpty == std::nullopt) << "\n";
        std::cout << (oTen == 10) << "\n";
    }
    return 0;
}