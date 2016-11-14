#include <iostream>
#include "singleton_container.h"

using namespace std;
using namespace boost::interprocess;

const char* ID_SHARED_MEMORY = "shared_memory";
const char* ID_SHARED_OBJECT= "MyVector";
const size_t SIZE_SHARED_MEMORY = 65536;

ISingleton& GetSingleton()
{
	static cSingleton instance;
	return instance;
}

void cSingleton::printVector()
{
	MyVector *myvector = segment->find<MyVector>(ID_SHARED_OBJECT).first;
	for (auto& el : *myvector)
		cout << el << " - ";
	cout<<endl;
}

void cSingleton::addToContainer(int item)
{
	MyVector *myvector = segment->find<MyVector>(ID_SHARED_OBJECT).first;
	myvector->push_back(item);
}

bool cSingleton::initSharedMemory(bool create)
{
	if (create)
	{
		try {
			shared_memory_object::remove(ID_SHARED_MEMORY);
			segment = new managed_shared_memory(create_only, ID_SHARED_MEMORY, SIZE_SHARED_MEMORY);
		}
		catch (std::exception const& ex) {
			cout << "managed_shared_memory could not be created: "  << ex.what() <<endl;
			return false;
		}
	}
	else
	{
		segment = new managed_shared_memory(open_only, "MySharedMemory");
	}

	return segment->check_sanity();
}

cSingleton::cSingleton() : segment(nullptr)
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


	// Open or create a shared memory object with name "shared_memory" with read_only mode.
	//shared_memory_object shm_obj(open_or_create, "shared_memory", read_write);
    // Original space for Shared Memory
	//shm_obj.truncate(10000);
	SharedMemoryAllocator const alloc_inst (segment->get_segment_manager());
	MyVector *myvector = segment->construct<MyVector>(ID_SHARED_OBJECT)(alloc_inst);

    cout << "cSingleton was created" << endl;
    // Initialize Container
	//m_vContainer = { 1, 3, 2, 4, 5 };
	myvector->push_back(1);
}

cSingleton::~cSingleton()
{
    delete segment;
    segment = nullptr;
	shared_memory_object::remove(ID_SHARED_MEMORY);
	cout << "cSingleton was destroyed" << endl;
}

