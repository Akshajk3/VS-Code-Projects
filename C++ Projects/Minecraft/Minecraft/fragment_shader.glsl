#version 330 core

out vec4 fragment_color;

in vec3 v_tex_coords;
in float v_shading_value;

uniform sampler2DArray texture_array_sampler;

void main(void)
{
    vec4 texture_color = texture(texture_array_sampler, v_tex_coords);
    fragment_color = texture_color * v_shading_value;
}