#version 330 core

in vec2 texPos;
out vec4 color;

uniform sampler2D textTexture; // Monocolorido (r)
uniform vec3 textColor;

void main(){

	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(textTexture, texPos).r);
	color = vec4(textColor, 1.0) * sampled;

	if(color.a < 0.3)
        discard;
}