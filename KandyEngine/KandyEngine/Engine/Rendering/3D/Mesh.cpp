#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) :
VAO(0), VBO(0), shaderProgram(0),
modelLoc(0), viewLoc(0), projectionLoc(0), textureLoc(0),
viewPosLoc(0), lightPosLoc(0), ambientLoc(0), diffuseLoc(0), specularLoc(0), colourLoc(0){
subMesh = subMesh_;
shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndice.size() > 0) {
		subMesh.meshIndice.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4>& instance_)
{
	glUniform1i(matDiffMap, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);
	


	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera_->GetPosition()));
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(camera_->GetLightSources()[0]->GetPosition()));
	glUniform1fv(ambientLoc, 1, new GLfloat(camera_->GetLightSources()[0]->GetAmbient()));
	glUniform1fv(diffuseLoc, 1, new GLfloat(camera_->GetLightSources()[0]->GetDiffuse()));
	glUniform1fv(specularLoc, 1, new GLfloat(camera_->GetLightSources()[0]->GetSpec()));
	glUniform3fv(colourLoc, 1, glm::value_ptr(camera_->GetLightSources()[0]->GetLightColour()));

	glUniform1f(matDiffMap, subMesh.material.diffuseMap);
	glUniform1f(matShine, subMesh.material.shininess);
	glUniform1f(matTrans, subMesh.material.transparency);
	glUniform3fv(matAmb, 1, glm::value_ptr(subMesh.material.ambient));
	glUniform3fv(matDiff, 1, glm::value_ptr(subMesh.material.diffuse));
	glUniform3fv(matSpec, 1, glm::value_ptr(subMesh.material.specular));

	glBindVertexArray(VAO);
	
	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < instance_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instance_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex),
		&subMesh.vertexList[0], GL_STATIC_DRAW);
	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	// normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
		(GLvoid*)offsetof(Vertex, normal));
	// tex coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
		(GLvoid*)offsetof(Vertex, textureCoordinates));


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	
	viewPosLoc = glGetUniformLocation(shaderProgram, "camPos");
	lightPosLoc = glGetUniformLocation(shaderProgram, "light.position");
	ambientLoc = glGetUniformLocation(shaderProgram, "light.ambient");
	diffuseLoc = glGetUniformLocation(shaderProgram, "light.diffuse");
	specularLoc = glGetUniformLocation(shaderProgram, "light.specular");
	colourLoc = glGetUniformLocation(shaderProgram, "light.colour");

	matDiffMap = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	matShine = glGetUniformLocation(shaderProgram, "material.shininess");
	matTrans = glGetUniformLocation(shaderProgram, "material.transparency");
	matAmb = glGetUniformLocation(shaderProgram, "material.ambient");
	matDiff = glGetUniformLocation(shaderProgram, "material.diffuse");
	matSpec = glGetUniformLocation(shaderProgram, "material.specular");
}
