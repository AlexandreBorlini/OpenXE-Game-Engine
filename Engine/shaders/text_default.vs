#version 330 core

layout (location = 0) in vec4 vertex;

out vec2 texPos;

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 view;

void main(){

	gl_Position = projection * view * transform * vec4(vertex.xy, 0.0, 1.0);
	texPos = vertex.zw;
}