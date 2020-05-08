#version 330 core
out vec4 FragColor;

in vec2 texPos;

uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = vec4(0.4, 0.7, 0.5, 1.0);
}