
#version 330 core
out vec4 FragColor;

in vec2 texPos;


uniform sampler2D textureSampler;

void main()
{
	
    FragColor = texture(textureSampler, texPos);
	
	if(FragColor.a < 0.3)
        discard;
}