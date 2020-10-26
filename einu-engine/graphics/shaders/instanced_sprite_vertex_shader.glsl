// VERTEX SHADER

#version 330 core

uniform mat4 u_camera;

in vec3 a_pos;
in mat4 a_inst_transform;
in vec4 a_inst_color;
in vec2 a_inst_tex_coords;

out vec4 f_color;
out vec2 f_tex_coords;


void main() {
  gl_Position = u_camera * a_transform * vec4(a_pos, 1);
  f_color = a_color / 255;
  f_tex_coords = a_texcoords;
}
