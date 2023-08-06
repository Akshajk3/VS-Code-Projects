#version 330

#define CHUNK_WIDTH = 16
#define CHUNK_LENGTH = 16

uniform ivec3 u_ChunkPosition;
uniform mat4 u_MVPMatrix;
uniform float u_DayLight;

layout (location = 0) in vec3 a_LocalPosition;
layout (location = 1) in float a_TextureFetcher;
layout (location = 2)