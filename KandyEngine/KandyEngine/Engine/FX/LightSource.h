#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>

class LightSource
{
public:
	LightSource(glm::vec3 position_, float ambient_, float diffuse_,
		float spec_, glm::vec3 lightColour_);
	~LightSource();

	// the getters
	glm::vec3 GetPosition();
	
	float GetAmbient();
	float GetDiffuse();
	float GetSpec();
	
	glm::vec3 GetLightColour();

	// the setters
	glm::vec3 SetPosition(glm::vec3 position_);

	float SetAmbient(float ambient_);
	float SetDiffuse(float diffuse_);
	float SetSpec(float spec_);

	glm::vec3 SetLightColour(glm::vec3 lightColour_);

private:
	glm::vec3 position;
	
	float ambient;
	float diffuse;
	float spec;
	
	glm::vec3 lightColour;

};

#endif // !LIGHTSOURCE_H