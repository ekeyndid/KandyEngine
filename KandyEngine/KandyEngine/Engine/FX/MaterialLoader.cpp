#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{
}

void MaterialLoader::LoadMaterial(std::string filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Log::Error("Can't open MTL file: " + filePath_,
			"MaterialLoader.cpp", __LINE__);
		return;
	}
	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 7) == "newmtl ")
		{
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}
		//line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
		if (line.substr(0, 3) == "Ns ")
		{
			std::stringstream ns(line.substr(3));
			float n;
			ns >> n;
			m.shininess = n;
		}
		if (line.substr(0, 2) == "d ")
		{
			std::stringstream d(line.substr(2));
			float n;
			d >> n;
			m.transparency = n;
		}
		if (line.substr(0, 3) == "Ka ")
		{
			std::stringstream ka(line.substr(3));
			float x, y, z;
			ka >> x >> y >> z;
			m.ambient = glm::vec3(x, y, z);
		}
		if (line.substr(0, 3) == "Kd ")
		{
			std::stringstream kd(line.substr(3));
			float x, y, z;
			kd >> x >> y >> z;
			m.diffuse = glm::vec3(x, y, z);
		}
		if (line.substr(0, 3) == "Ks ")
		{
			std::stringstream ks(line.substr(3));
			float x, y, z;
			ks >> x >> y >> z;
			m.specular = glm::vec3(x, y, z);
		}
	}
	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string filename_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(filename_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(filename_,
			"./Engine/Resources/Textures/" + filename_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(filename_);
	}
	return currentTexture;
}
