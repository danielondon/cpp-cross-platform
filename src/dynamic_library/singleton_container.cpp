#include <iostream>
#include <vector>
#include "singleton_container.h"

using namespace std;

cSingleton* cSingleton::instance = nullptr;
cSingleton* cSingleton::getInstance()
{
	if (!instance)
		instance = new cSingleton;
	return instance;
}

void cSingleton::destroy()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void cSingleton::printVector()
{
	vector<int> vect{ 1, 3, 2, 4, 5 };
	for (auto& el : vect)
		cout << " - " << el << endl;
}

cSingleton::cSingleton()
{
	cout << "cSingleton was created" << endl;
}

cSingleton::~cSingleton()
{
	cout << "cSingleton was destroyed" << endl;
}