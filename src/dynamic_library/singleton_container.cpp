#include <iostream>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include "singleton_container.h"

using namespace std;
using namespace boost::interprocess;


char const*const ID_SHARED_MEMORY = "shared_memory";
char const*const  ID_SHARED_OBJECT= "MyVector";
const size_t SIZE_SHARED_MEMORY = 65536;

ISingleton& GetSingleton()
{
	static cSingleton instance;
	return instance;
}

void cSingleton::printContainer()
{
    scoped_lock<named_mutex> lock(mutex);

	MyVector* myvector = segment->find<MyVector>(ID_SHARED_OBJECT).first;
	for (auto& el : *myvector)
		cout << el << " - ";
	cout<<endl;
}

void cSingleton::addToContainer(int item)
{
    scoped_lock<named_mutex> lock(mutex);

	MyVector* myvector = segment->find<MyVector>(ID_SHARED_OBJECT).first;
	myvector->push_back(item);
    std::sort(myvector->begin(), myvector->end());
}

bool cSingleton::initSharedMemory(bool create)
{
	if (create)
	{
		try
        {
            // Create Shared Memory
			shared_memory_object::remove(ID_SHARED_MEMORY);
			segment = new managed_shared_memory(create_only, ID_SHARED_MEMORY, SIZE_SHARED_MEMORY);

            // Create Vector
            SharedMemoryAllocator const alloc_inst (segment->get_segment_manager());
            segment->construct<MyVector>(ID_SHARED_OBJECT)(alloc_inst);

            wasSharedMemoryCreated = true;

		}
		catch (std::exception const& ex) {
			cout << "managed_shared_memory could not be created: "  << ex.what() <<endl;
			return false;
		}
	}
	else
	{
        // Access Shared Memory
		segment = new managed_shared_memory(open_only, ID_SHARED_MEMORY);

        wasSharedMemoryCreated = false;
	}

	return segment->check_sanity();
}

cSingleton::cSingleton() : segment(nullptr), wasSharedMemoryCreated(false), mutex(open_or_create, "mymutex")
{
	try
	{
		if(!initSharedMemory(false))
		{
			cout<<"Shared Memory is not correct"<<endl;
			return;
		}
	}
	catch (std::exception const& ex)
	{
		cout << "managed_shared_memory is not created: "  << ex.what() <<endl;
		cout<< "Creating Shared Memory"<<endl;
		if (!initSharedMemory(true))
		{
			cout<<"Shared Memory is not correct"<<endl;
			return;
		}
	}

    cout << "cSingleton was created" << endl;
}

cSingleton::~cSingleton()
{
    if (wasSharedMemoryCreated)
    {
        shared_memory_object::remove(ID_SHARED_MEMORY);
        cout << "Shared Memory was removed" << endl;
    }

    delete segment;
    segment = nullptr;

    cout << "cSingleton was destroyed" << endl;
}

