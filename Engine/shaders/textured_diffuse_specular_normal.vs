#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;

out vec3 fragPos;
out vec2 texPos;
out vec3 tangLightPos;
out vec3 tangViewPos;
out vec3 tangFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform struct LightInfo {

  vec3 Position;
  vec3 cameraPos;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

} Light;

void main(){

	fragPos = vec3(model * vec4(aPos, 1.0));
	texPos = aTexCoords;

	mat3 normalMatrix = transpose(inverse(mat3(model)));
	
	vec3 tangent = normalize(normalMatrix * aTangent);
	vec3 normal  = normalize(normalMatrix * aNormal);

	tangent = normalize(tangent - dot(tangent, normal) * normal);

	vec3 binormal = cross(normal, tangent);

	if(dot(cross(normal, tangent), binormal) < 0.0){
	
		tangent = tangent * -1.0;
	}

	mat3 toObjectLocal = transpose(mat3(tangent, binormal, normal));

	tangLightPos = toObjectLocal * Light.Position;
	tangViewPos  = toObjectLocal * Light.cameraPos;
	tangFragPos  = toObjectLocal * fragPos;

	gl_Position = projection * view * model * vec4(aPos, 1.0);
}