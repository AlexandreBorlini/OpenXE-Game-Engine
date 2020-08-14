#version 430 core
out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 texPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform float Shininess;

uniform struct LightInfo {

  vec4 Position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

} Light;

vec3 ads(){

	vec3 n = normalize(Normal);
	vec3 s = normalize( vec3( Light.Position) - Position );
	vec3 v = normalize(vec3(-Position));
	vec3 h =  normalize( v + s );

	return Light.ambient +
		   (Light.diffuse * max(dot(s, Normal), 0.0) * texture(texture_diffuse1, texPos).rgb) +
		   (Light.specular * pow(max(dot(h, n), 0.0), Shininess) * texture(texture_specular1, texPos).rgb);
}

void main()
{
   FragColor = vec4(ads(), 1.0);
} 