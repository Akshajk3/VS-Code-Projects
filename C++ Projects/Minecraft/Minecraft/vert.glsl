#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in float aShading;
layout(location = 2) in vec2 aTex;

out float shading;
out vec2 texCoord;

uniform mat4 camMatrix;

void main()
{
	gl_Position = camMatrix * vec4(aPos, 1.0);
	shading = aShading;
	texCoord = aTex;
}
