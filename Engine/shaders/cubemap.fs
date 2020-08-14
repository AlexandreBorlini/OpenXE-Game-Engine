#version 330 core

out vec4 FragColor;

in vec3 Position;
in vec3 Normal;

uniform samplerCube texture_skybox;

uniform struct LightInfo {

	vec3 cameraPos;
} Light;

void main(){

	vec3 I = normalize( Position - Light.cameraPos );
	vec3 R = reflect( I, normalize(Normal) );

	FragColor = vec4(texture( texture_skybox, R ).rgb, 1.0);
}