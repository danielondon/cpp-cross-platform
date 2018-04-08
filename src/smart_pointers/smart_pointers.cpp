
#include <iostream>
#include <memory>
#include <typeinfo>

using namespace std;

class Investment
{
public:
    virtual ~Investment()
    {
        cout << "~Investment" << endl;
    }
};

class Stock : public Investment
{

    ~Stock()
    {
        cout << "~Stock" << endl;
    }
};

class Bond : public Investment{
    ~Bond()
    {
        cout << "~Bond" << endl;
    }
};

void makeLogEntry(Investment * pInvestment)
{
    cout << "Log Entry " << typeid(*pInvestment).name() << endl;
}

auto delInvmt = [](Investment* pInvestment) // custom
{ // deleter
    makeLogEntry(pInvestment); // (a lambda
    delete pInvestment; // expression)
};


template<typename... Ts> // revised
std::unique_ptr<Investment, decltype(delInvmt)> // return type
makeInvestment(int type, Ts&&... params)
{
    std::unique_ptr<Investment, decltype(delInvmt)> // ptr to be
        pInv(nullptr, delInvmt); // returned

    if ( type == 0 )
    {
        pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    else
    {
        pInv.reset(new Bond(std::forward<Ts>(params)...));
    }

    return pInv;
}

int main()
{
	std::cout << "Smart Pointers -------" << std::endl << endl;
    std::cout << "--RAW--" << endl;
    {
        Investment * inv = new Bond;
        delete inv;
    }
    std::cout << "--"<<endl;
    {
        Investment * inv = new Stock;
        delete inv;
    }
    std::cout << "--UNIQUE--" << endl;
    {
        unique_ptr<Investment> inv(new Bond);
    }
    std::cout << "--" << endl;
    {
        unique_ptr<Investment> inv(new Stock);
    }

    std::cout << "--FACTORY--" << endl;
    {
        auto inv = makeInvestment(0);
    }
    std::cout << "--" << endl;
    {
        auto inv = makeInvestment(1);
    }

    return 0;
}