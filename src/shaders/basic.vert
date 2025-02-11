#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colour;
layout (location = 2) in vec2 texturePos;

uniform vec3 offset;

out vec4 frag_colour;
out vec2 texture_pos;

void main(){
    texture_pos = texturePos;
    frag_colour = vec4(colour.xyz, 1.0);
    gl_Position = vec4(pos.xyz, 1.0);
}