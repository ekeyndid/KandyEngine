#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

struct Light
{
vec3 position;
float ambient;
float diffuse;
float specular;
vec3 colour;
};

uniform sampler2D inputTexture;
uniform vec3 camPos;
uniform Light light;

out vec4 fColour;

void main(){

vec3 ambient = light.ambient * texture(inputTexture, TexCoords).rgb * light.colour;

vec3 norm = normalize(Normal);
vec3 lightDir = normalize(light.position - FragPosition);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = (diff * light.diffuse) * texture(inputTexture, TexCoords).rgb * light.colour;

vec3 viewDir = normalize(camPos - FragPosition);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
vec3 specular = (spec * light.specular) * light.colour;
vec3 result = ambient + diffuse + specular;

fColour = vec4(result, 1.0f);
}