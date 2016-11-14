#ifndef _SINGLETON_CONTAINER
#define _SINGLETON_CONTAINER

#include <vector>

#ifdef WIN32
#ifndef DLL_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#endif
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

#ifdef WIN32
DLL_EXPORT ISingleton& GetSingleton();
#else
ISingleton& GetSingleton();
#endif

#endif