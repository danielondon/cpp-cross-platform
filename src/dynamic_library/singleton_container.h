class __declspec(dllexport) cSingleton
{
	static cSingleton* instance;
	cSingleton();
public:
	static cSingleton* getInstance();	
	static void destroy();

	~cSingleton();
	void printVector();
};