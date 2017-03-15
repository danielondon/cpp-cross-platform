#include <iostream>
#include <memory>

using namespace std;

class Base {
public:
    virtual void doWork() {
        cout << "doWork Base" << endl;
    }

    void doWork2() {
        cout << "doWork2 Base" << endl;
    }
};
class Derived : public Base {
public:
    virtual void doWork() override {
        cout << "doWork derived" << endl;
    }

    void doWork2() {
        cout << "doWork2 derived" << endl;
    }
};                               


void functionUsingUniquePointer(std::unique_ptr<Base> & myUniquePointer)
{
    cout << "functionUsingUniquePointer " << endl;
}

int main()
{
    std::unique_ptr<Base> upb = std::make_unique<Derived>();   // to derived class object;
    upb->doWork();
    upb->doWork2(); // Because of no virtual in the base, then the call to the base will be callsed

    functionUsingUniquePointer(upb);
}