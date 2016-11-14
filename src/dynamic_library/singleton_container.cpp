#include <iostream>
#include "singleton_container.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace std;
using namespace boost::interprocess;

ISingleton& GetSingleton()
{
	static cSingleton instance;
	return instance;
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
	// Open or create a shared memory object with name "shared_memory" with read_only mode.
	shared_memory_object shm_obj(open_or_create, "shared_memory", read_write);
    // Original space for Shared Memory
	shm_obj.truncate(10000);

    cout << "cSingleton was created" << endl;
    // Initialize Container
	m_vContainer = { 1, 3, 2, 4, 5 };
}

cSingleton::~cSingleton()
{
	shared_memory_object::remove("shared_memory");
	cout << "cSingleton was destroyed" << endl;
}

