#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

struct Light
{
vec3 position;
float ambient;
float diffuse;
float specular;
vec3 colour;
};

struct Material
{
	sampler2D diffuseMap;
	float shininess;
	float transparency;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


uniform vec3 camPos;
uniform Light light;
uniform Material material;

out vec4 fColour;

void main(){

//Ambient
vec3 ambient = light.ambient * material.ambient * texture(material.diffuseMap,
TexCoords).rgb * light.colour;

//Diffuse
vec3 norm = normalize(Normal);
vec3 lightDir = normalize(light.position - FragPosition);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.colour;

//Specular
vec3 viewDir = normalize(camPos - FragPosition);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
vec3 specular = (spec * material.specular) * light.colour;

vec3 result = ambient + diffuse + specular;

fColour = vec4(result, material.transparency);
}