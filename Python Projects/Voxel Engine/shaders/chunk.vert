#version 330 core

layout (location = 0) in ivec3 in_position;
layout (location = 1) in int voxel_id;
layout (location = 2) in int face_id;

uniform mat4 m_proj;
uniform mat4 m_view;
uniform mat4 m_model;

out vec3 voxel_color;

vec3 hash31(float p)
{
    vec3 p3 = fract(vec3(p*21.2) * vec3(0.1031, 0.1030, 0.0973));
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.xxy + p3.yzz) * p3.zyx) + 0.05;
}

void main()
{
    voxel_color = hash31(voxel_id);
    gl_Position = m_proj * m_view * m_model * vec4(in_position, 1.0);
}