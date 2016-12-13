#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Sum
{
	Sum() : sum{ 0 } { }
	void operator()(int n) { sum += n; }
	int sum;
};

class MyVector
{
public:
	MyVector(std::initializer_list<int> items) : m_Collection(items)
	{}

	vector<int>::const_iterator begin() const
		//auto begin()
	{
		//return &m_Collection[0];
		return m_Collection.begin();
	}

	//int* end()
	vector<int>::const_iterator end() const
		//auto end()
	{
		//return &m_Collection[m_Collection.size()];
		return m_Collection.end();
	}


	vector<int>::iterator begin()
	{
		return m_Collection.begin();
	}

	vector<int>::iterator end()
	{
		return m_Collection.end();
	}

	vector<int> m_Collection;
};


int main()
{
	std::cout << "Range Based Loops with Clang" << std::endl;

	//std::vector<int> nums{ 3, 4, 2, 8, 15, 267 };
	MyVector nums{ 3, 4, 2, 8, 15, 267 };

	std::cout << "before:";
	for (auto const& n : nums)
	{
		std::cout << ' ' << n;
	}
	std::cout << '\n';

	std::for_each(nums.begin(), nums.end(), [](int &n) { n++; });

	std::cout << "after: ";
	for (auto const &n : nums)
	{
		std::cout << ' ' << n;
	}
	cout << endl;

	// calls Sum::operator() for each number

	Sum s = std::for_each(nums.begin(), nums.end(), Sum());
	cout << "SUM is "<< s.sum << endl;


	map<string, int> myMap;
	myMap["a"] = 10;
	myMap["b"] = 20;
	myMap["c"] = 30;

	for (auto const& keyValue : myMap)
	{
		cout << "Key " << keyValue.first.c_str() << " Value " << keyValue.second << endl;
	}

	cout << endl;

	for (auto const n : {2, 5, 1, -3}) // the initializer may be a braced-init-list
		std::cout << n << ' ';
	cout << endl;

	std::initializer_list<int> myList = { 2, 5, 1, -3 };
	for (auto & n : myList) // the initializer may be a braced-init-list
		std::cout << n << ' ';
	cout << endl;

	return 0;
}