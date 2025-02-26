#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colour;
layout (location = 2) in vec2 texturePos;

uniform vec3 offset;
uniform float rotation_degree;

out vec4 frag_colour;
out vec2 texture_pos;

vec3 rotate(float degree){


    float new_x, new_y;

    new_x = cos(degree) * pos.x - sin(degree) * pos.y;
    new_y = sin(degree) * pos.x + cos(degree) * pos.y;

    return vec3(new_x, new_y, pos.z); 
}

void main(){
    vec3 final_pos = pos;

    if(rotation_degree != 0.0){
        final_pos = rotate(rotation_degree) + offset;
    }

    texture_pos = texturePos;
    frag_colour = vec4(colour.xyz, 1.0);
    gl_Position = vec4(final_pos.xyz, 1.0);
}
