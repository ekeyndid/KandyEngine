#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()),
textureCoords(std::vector<glm::vec2>()), indice(std::vector<unsigned int>()),
normalIndice(std::vector<unsigned int>()), textureIndice(std::vector<unsigned int>()),
meshVertices(std::vector<Vertex>()), subMeshes(std::vector<SubMesh>()), currentTexture(0) {
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indice.reserve(200);
	normalIndice.reserve(200);
	textureIndice.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);

}

LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indice.clear();
	normalIndice.clear();
	textureIndice.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indice.size(); i++) {
		Vertex vert;
		vert.position = vertices[indice[i]];
		vert.normal = normals[normalIndice[i]];
		vert.textureCoordinates = textureCoords[textureIndice[i]];
		meshVertices.push_back(vert);
}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndice = indice;
	mesh.textureID = currentTexture;

	subMeshes.push_back(mesh);

	indice.clear();
	normalIndice.clear();
	textureIndice.clear();
	meshVertices.clear();

	currentTexture = 0;
}

void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Log::Error("Can't open OBJ file: " + filePath_,
			"LoadOBJModel.cpp", __LINE__);
		return;
	}
	currentTexture = 0;
	
	std::string line;
	
	while (std::getline(in, line)) {
		//vertex
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));
		}

		// normal
		else if (line.substr(0, 3) == "vn ")
		{
			std::stringstream n(line.substr(3));
			float x, y, z;
			n >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		
		//texture
		else if (line.substr(0, 3) == "vt ")
		{
			std::stringstream n(line.substr(3));
			float x, y, z;
			n >> x >> y >> z;
			textureCoords.push_back(glm::vec2(x, y));
		}

		//face
		else if (line.substr(0, 2) == "f ")
		{
			std::string vert;
			std::string num;
			unsigned int v, vn, vt;
			int count = 0;
			std::stringstream f(line.substr(2));
			while (std::getline(f, vert, ' ')) {
				std::stringstream f2(vert);
				while (std::getline(f2, num, '/')) {
					std::stringstream f3(num);
					if (count % 3 == 0) {
						f3 >> v;
						indice.push_back(v - 1);
					}
					else if (count % 3 == 1) {
						f3 >> vt;
						textureIndice.push_back(vt - 1);
					}
					else {
						f3 >> vn;
						normalIndice.push_back(vn - 1);
					}
					count++;
				}
			}
		}

		// new mesh
		else if (line.substr(0, 7) == "usemtl ") {
			if (indice.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	in.close();
	PostProcessing();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentTexture = TextureHandler::GetInstance()->GetTexture(matName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(matName_, "Engine/Resources/Textures/" + matName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(matName_);
	}
}

void LoadOBJModel::LoadMaterialLibary(const std::string& matFilePath_)
{
	std::ifstream in(matFilePath_.c_str(), std::ios::in);
	if (!in) {
		Log::Error("Cannot open MTL file: " + matFilePath_, "LoadOBJModel", __LINE__);
	}
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl "){
			LoadMaterial(line.substr(7));
		}
	}
}
