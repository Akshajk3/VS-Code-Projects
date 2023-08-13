#pragma once
#include <glm/glm.hpp>

struct Block
{
	glm::vec3 block_pos;
	bool is_transparent;
	bool is_cube;
	bool is_glass;

};