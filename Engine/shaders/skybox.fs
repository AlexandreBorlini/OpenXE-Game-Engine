#version 330 core

out vec4 FragColor;

in vec3 texPos;

uniform samplerCube texture_skybox;

void main(){

	FragColor = texture( texture_skybox, texPos );
}