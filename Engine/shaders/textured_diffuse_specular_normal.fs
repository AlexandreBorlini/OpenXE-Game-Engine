#version 430 core
out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

in vec3 fragPos;
in vec2 texPos;
in vec3 tangLightPos;
in vec3 tangViewPos;
in vec3 tangFragPos;

uniform float Shininess;

uniform struct LightInfo {

  vec3 Position;
  vec3 cameraPos;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

} Light;

void main(){

	vec3 normal = texture(texture_normal1, texPos).rgb;
	normal = normalize( normal * 2.0 - 1.0 );

	vec3 color = texture(texture_diffuse1, texPos).rgb;

	vec3 ambient = Light.ambient;

	vec3 lightDir = normalize( tangLightPos - tangFragPos );
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * color;

	vec3 viewDir = normalize( tangViewPos - tangFragPos );
	vec3 reflectDir = reflect( -lightDir, normal );
	vec3 halfwayDir = normalize( lightDir + viewDir );

	float spec = pow(max(dot( normal, halfwayDir ), 0.0), Shininess);

	vec3 specular = Light.specular * spec * texture(texture_specular1, texPos).rgb;
	FragColor = vec4( ambient + diffuse + specular, 1.0 );
}