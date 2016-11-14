#include <iostream>
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
	for (auto& el : m_vContainer)
		cout << el << " - ";
	cout<<endl;
}

void cSingleton::addToContainer(int item)
{
	m_vContainer.push_back(item);
}

cSingleton::cSingleton()
{
	cout << "cSingleton was created" << endl;
	m_vContainer = { 1, 3, 2, 4, 5 };
}

cSingleton::~cSingleton()
{
	cout << "cSingleton was destroyed" << endl;
}

