#include "Model.h"

Model::Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_)
	:meshes(std::vector<Mesh*>()), shaderProgram(0), modelInstance(std::vector<glm::mat4>()),
thing(nullptr){
	shaderProgram = shaderProgram_;
	meshes.reserve(10);
	modelInstance.reserve(5);
	thing = new LoadOBJModel();
	thing->LoadModel(objPath_, matPath_);
	LoadModel();

}

Model::~Model(){
	if (meshes.size() > 0) {
		for (auto m : meshes) {
			delete m;
			m = nullptr;

		}
		meshes.clear();
	}
	if (modelInstance.size() < 0) {
		modelInstance.clear();
	}
}

void Model::Render(Camera* camera_){
	glUseProgram(shaderProgram);
	for (auto m : meshes) {
		m->Render(camera_, modelInstance);
	}

}

void Model::AddMesh(Mesh* mesh_){
	meshes.push_back(mesh_);
}

unsigned int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstance.push_back(CreateTransform(position_, angle_, rotation_, scale_));
	return modelInstance.size() - 1;
}

void Model::UpdateInstance(unsigned int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstance[index_] = CreateTransform(position_, angle_, rotation_, scale_);
}

glm::mat4 Model::GetTransform(unsigned int index_) const
{
	return modelInstance[index_];
}

GLuint Model::GetShaderProgram() const
{
	return shaderProgram;
}

glm::mat4 Model::CreateTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const
{
	glm::mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, rotation_);
	model = glm::scale(model, scale_);
	return model;
}

void Model::LoadModel()
{
	for (int i = 0; i < thing->GetSubMeshes().size(); i++) {
		meshes.push_back(new Mesh(thing->GetSubMeshes()[i], shaderProgram));
}
	delete thing;
	thing = nullptr;
}




