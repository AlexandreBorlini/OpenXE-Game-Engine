#version 330 core
layout (location = 0) in vec3 layoutPos;
layout (location = 1) in vec2 layoutTexPos;

out vec2 texPos;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main()
{

    gl_Position = projection * view * transform * vec4(layoutPos, 1.0); 
    texPos = layoutTexPos;
}