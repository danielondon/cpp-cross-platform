#ifndef _SINGLETON_CONTAINER
#define _SINGLETON_CONTAINER

#include <vector>

#ifndef DLL_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#endif

class ISingleton
{
public:
	virtual void printVector() = 0;
	virtual void addToContainer(int item) = 0;
};


class cSingleton : public ISingleton
{
	//static cSingleton* instance;
	
public:	
	//static void destroy();
	cSingleton();
	~cSingleton();
	void printVector();
	void addToContainer(int item);
private:
	std::vector<int> m_vContainer;
};

DLL_EXPORT ISingleton& GetSingleton();

#endif