#pragma once

#include <glad/glad.h>
#include "Models.h"

class Block
{
public:
	Block(int x, int y, int z);

	void Render();

private:
	int m_x;
	int m_y;
	int m_z;
};