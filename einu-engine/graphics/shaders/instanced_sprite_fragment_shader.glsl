// FRAGMENT SHADER

#version 330 core

out vec4 frag_color;

in vec4 f_color;
in vec2 f_tex_coords;

uniform sampler2D tex;

void main() {
    vec4 tex_color = f_color * texture(tex, f_tex_coords);
    if(tex_color.a < 0.1f) discard;
    frag_color = tex_color;
}
