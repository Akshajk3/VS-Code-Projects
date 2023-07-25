#include <iostream>
#include <memory>

#include "app.h"
#include "texture_array.h"
#include "buffers.h"
#include "shader.h"

#ifdef DEBUG
long long heap_allocation;
void* operator new(size_t size)
{
	heap_allocation += size;
	void* ptr = malloc(size);
	if(!ptr)
		throw std::bad_alloc();
	std::cout << "Current usage of heap: "
	<< heap_allocation << "bytes\n";
	return ptr;
}
void operator delete(void* _Block, size_t size)
{
	heap_allocation -= size;
	std::cout << "Freeing" << size << " bytes on the heap\n"
		<< "Current usage of heap: "
		<< heap_allocation << "bytes\n";
	free(_Block);
}
#endif

int main(void)
{
	App app(1280, 720, false, false, false);
	app.init();
	app.run();

	return 0;
}