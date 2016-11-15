#ifndef _SINGLETON_CONTAINER
#define _SINGLETON_CONTAINER

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>

#ifdef WIN32
#ifndef DLL_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#endif
#endif

class ISingleton
{
public:
	virtual void printContainer() = 0;
	virtual void addToContainer(int item) = 0;
};

//Define an STL compatible allocator of ints that allocates from the managed_shared_memory.
//This allocator will allow placing containers in the segment
typedef  boost::interprocess::allocator<int, boost::interprocess::managed_shared_memory::segment_manager>  SharedMemoryAllocator;

//Alias a vector that uses the previous STL-like allocator so that allocates
//its values from the segment
typedef  boost::interprocess::vector<int, SharedMemoryAllocator> MyVector;

class cSingleton : public ISingleton
{
public:
	cSingleton();
	~cSingleton();
	bool initSharedMemory(bool create);
	void printContainer();
	void addToContainer(int item);
private:
	boost::interprocess::managed_shared_memory * segment;
	boost::interprocess::named_mutex mutex;
	bool wasSharedMemoryCreated;
};

#ifdef WIN32
DLL_EXPORT ISingleton& GetSingleton();
#else
ISingleton& GetSingleton();
#endif

#endif