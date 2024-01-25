#include <iostream>
#include <cassert>


#include "GamerClass.h"

void test()
{
	GamerMap gamer;
	assert(gamer.numGamers() == 0);
	gamer.addGamer("Kash");
	gamer.play("Kash", 10);
	assert(gamer.hoursSpent("Kash") == 10);
	assert(gamer.numGamers() == 1);
}

int main()
{
	test();

	std::cout << "Passed All Test" << std::endl;

	return 0;
}
