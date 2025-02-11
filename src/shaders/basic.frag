#version 460 core
out vec4 FragColor;

uniform sampler2D tex_image;

in vec4 frag_colour;
in vec2 texture_pos;

void main(){
    FragColor = texture(tex_image, texture_pos);
}