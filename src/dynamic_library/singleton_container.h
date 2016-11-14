#include <vector>

class __declspec(dllexport) cSingleton
{
	static cSingleton* instance;
	cSingleton();
public:
	static cSingleton* getInstance();	
	static void destroy();

	~cSingleton();
	void printVector();
	void addToContainer(int item);
private:
	std::vector<int> m_vContainer;
};