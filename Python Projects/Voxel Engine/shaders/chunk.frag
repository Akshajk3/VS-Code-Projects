#version 330 core

layout (location = 0) out vec4 FragColor;

in vec3 voxel_color;

void main()
{
    FragColor = vec4(voxel_color, 1);
}