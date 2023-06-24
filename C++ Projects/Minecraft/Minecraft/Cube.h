#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/hash.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/integer.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include <iostream>
#include <array>
#include <vector>

#include "Camera.h"
#include "shaderClass.h"
#include "Window.h"
#include "textureManager.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Cube
{
public:
	glm::vec3 Position;
	VAO VAO1;
	Shader shaderProgram = Shader("default.vert", "default.frag");
	TextureManager texture = TextureManager("cobblestone.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	void Init(const Window& window, glm::vec3 position);
	void Destroy();

	void Update();
	
};

#endif