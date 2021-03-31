#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambient_, float diffuse_, float spec_, glm::vec3 lightColour_)
{
	position = position_;
	ambient = ambient_;
	diffuse = diffuse_;
	spec = spec_;
	lightColour = lightColour_;
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition()
{
	return position;
}

float LightSource::GetAmbient()
{
	return ambient;
}

float LightSource::GetDiffuse()
{
	return diffuse;
}

float LightSource::GetSpec()
{
	return spec;
}

glm::vec3 LightSource::GetLightColour()
{
	return lightColour;
}

glm::vec3 LightSource::SetPosition(glm::vec3 position_)
{
	position = position_;
	return position;
}

float LightSource::SetAmbient(float ambient_)
{
	ambient = ambient_;
	return ambient;
}

float LightSource::SetDiffuse(float diffuse_)
{
	diffuse = diffuse_;
	return diffuse;
}

float LightSource::SetSpec(float spec_)
{
	spec = spec_;
	return spec;
}

glm::vec3 LightSource::SetLightColour(glm::vec3 lightColour_)
{
	lightColour = lightColour_;
	return lightColour;
}
