#version 330 core
out vec4 frag_color;

in vec4 f_color;
in vec2 f_texcoord;

uniform sampler2D tex;

void main()
{
    vec4 tex_color = f_color * texture(tex, f_texcoord);
    if(tex_color.a < 0.1f) discard;
    frag_color = tex_color;
}
