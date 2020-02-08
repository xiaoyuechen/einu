#version 330 core

in vec2 a_pos;
in vec2 a_texcoord;
in vec4 a_color;
in mat4 a_transform;
in vec3 a_scale;

uniform mat4 camera;
uniform mat4 local_transform;

out vec4 f_color;
out vec2 f_texcoord;

void main()
{
    gl_Position = camera * a_transform * local_transform * vec4(a_pos, 0, 1);
    f_texcoord = a_texcoord;
    f_color = a_color / 255;
}  