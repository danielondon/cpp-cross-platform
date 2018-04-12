
#include <iostream>
#include <memory>
#include <typeinfo>
#include <unordered_map>

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
public:
    Stock()
    {
        cout << "Stock" << endl;
    }

};

class Bond : public Investment
{ 
    ~Bond()
    {
        cout << "~Bond" << endl;
    }
public:
    Bond()
    {
        cout << "Bond" << endl;
    }

};

void makeLogEntry(Investment * pInvestment)
{
    cout << "Log Entry " << typeid(*pInvestment).name() << endl;
}

// Custom Deleter with Lambda
auto delInvmt = [](Investment* pInvestment) 
{ 
    makeLogEntry(pInvestment); 
    delete pInvestment; 
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



shared_ptr<const Investment> fastLoadStock(int stockId)
{
    static unordered_map<int, weak_ptr<Investment>> cache;
    auto objPtr = cache[stockId].lock();
    if (!objPtr)
    {
        objPtr = makeInvestment(0);
        cache[stockId] = objPtr;
    }

    return objPtr;

}

int main()
{
	std::cout << "----------- Unique Pointers -------" << std::endl << endl;
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

    std::cout << std::endl << endl << "--------- Weak Pointers -------" << std::endl << endl;
    {
        auto inv1 = fastLoadStock(1);  
        std::cout << "--" << endl;
        {
            auto inv2 = fastLoadStock(2);
        }
        std::cout << "--" << endl;
        {
            auto inv2 = fastLoadStock(1);
        }
        std::cout << "--" << endl;
        {
            auto inv2 = fastLoadStock(2);
        }
        std::cout << "--" << endl;
    }

    return 0;
}