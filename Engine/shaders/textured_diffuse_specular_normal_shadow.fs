#version 330 core

out vec4 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D shadowMap;

in vec4 FragPosLightSpace;

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


float ShadowCalculation(vec4 fragPosLightSpace)
{

   vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    float currentDepth = projCoords.z;

	float bias = 0.005;

    float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -1; x <= 1; ++x)
	{
	    for(int y = -1; y <= 1; ++y)
	    {
	        float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
	        shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
	    }    
	}
	shadow /= 9.0;

	if(projCoords.z > 1.0)
		shadow = 0.0;

    return shadow;
}

void main()
{   
	vec3 normal = texture(texture_normal1, texPos).rgb;
	normal = normalize( normal * 2.0 - 1.0 );

	vec3 color = texture(texture_diffuse1, texPos).rgb;

	vec3 ambient = Light.ambient * color;

	vec3 lightDir = normalize( tangLightPos - tangFragPos );
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * color;

	vec3 viewDir = normalize( tangViewPos - tangFragPos );
	vec3 reflectDir = reflect( -lightDir, normal );
	vec3 halfwayDir = normalize( lightDir + viewDir );

	float spec = pow(max(dot( normal, halfwayDir ), 0.0), Shininess);

	vec3 specular = Light.specular * spec * texture(texture_specular1, texPos).rgb;

	float shadow = ShadowCalculation(FragPosLightSpace);

    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));    
    FragColor = vec4(lighting, 1.0);
}