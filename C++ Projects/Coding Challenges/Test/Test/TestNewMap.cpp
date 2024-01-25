#include <iostream>
#include <cassert>

#include "NewMap.h"

const KeyType TEST_KEY = "John Doe";
const ValueType TEST_VALUE = 1023.234;

void test()
{
	Map map;
	assert(map.empty());
	map.insert(TEST_KEY, TEST_VALUE);
	assert(map.size() == 1);
	assert(map.get(0, TEST_KEY, TEST_VALUE);
}

int main()
{
	test();

	std::cout << "Passed All Test" << std::endl;

	return 0;
}
