#version 330 core

out vec4 FragColor;

in vec3 Position;
in vec3 Normal;

uniform vec3 cameraPos;
uniform samplerCube texture_skybox;


void main(){

	vec3 I = normalize( Position - cameraPos );
	vec3 R = reflect( I, normalize(Normal) );

	FragColor = vec4(texture( texture_skybox, R ).rgb, 1.0);
}