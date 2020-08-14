#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos; 
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform float Shininess;

uniform struct LightInfo {

  vec3 Position;
  vec3 cameraPos;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

} Light;

void main()
{
   
   vec3 ambient = Light.ambient * texture(texture_diffuse1, TexCoords).rgb;

   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize( Light.Position - FragPos );

   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = Light.diffuse * diff * texture(texture_diffuse1, TexCoords).rgb;

   vec3 viewDir = normalize( Light.cameraPos - FragPos );
   vec3 reflectDir = reflect( -lightDir, norm);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), Shininess);

   vec3 specular = Light.specular * spec * texture(texture_specular1,  TexCoords).rgb;

   vec3 result = ambient + diffuse + specular;
   FragColor = vec4(result, 1.0);
} 