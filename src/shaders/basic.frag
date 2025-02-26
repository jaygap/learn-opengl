#version 460 core
out vec4 FragColor;

uniform sampler2D base_image;
uniform sampler2D overlay_image;

in vec4 frag_colour;
in vec2 texture_pos;

void main(){
    FragColor = mix(texture(base_image, texture_pos), texture(overlay_image, texture_pos), 0.2);
    
}