#include "RenderHelper.h"
#include "glm/gtx/transform.hpp"
#include "WorldObject.h"
#include "../Actors/ContainerBox.h"
#include "../Actors/Sphere.h"

void RenderHelper::AddBuffers(const std::vector<Vertex>& InVertices, const std::vector<unsigned int>& InIndices)
{
	//storage for the vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//storage for the vertex buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, InVertices.size() * sizeof(Vertex), InVertices.data(), GL_STATIC_DRAW);

	//storage for the element buffer object
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, InIndices.size() * sizeof(unsigned int), InIndices.data(), GL_STATIC_DRAW);

	//position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Position)));

    //normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Normal)));

    //texture attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, TexCoords)));

	//add the vaos, vbos, and ebos to the storage
	VAOs.push_back(VAO);
	VBOs.push_back(VBO);
	EBOs.push_back(EBO);

	//add the vertices and indices to the storage
	Vertices.push_back(InVertices);
	Indices.push_back(InIndices);
}

glm::mat4 RenderHelper::GetModelMatrix(const WorldObject* WorldObject)
{
	////get a unit matrix
	//glm::mat4 ModelMat = glm::mat4(1);

	////translate the model matrix
	//ModelMat = translate(ModelMat, WorldObject->Position);

	////scale the model matrix
	//ModelMat = scale(ModelMat, WorldObject->Size);

	//create the model matrix
	const glm::mat4 ModelMat = {
		WorldObject->Size.x, 0, 0, 0,
		0, WorldObject->Size.y, 0, 0,
		0, 0, WorldObject->Size.z, 0,
		WorldObject->Position.x, WorldObject->Position.y, WorldObject->Position.z, 1
	};

	//return the model matrix
	return ModelMat;
}

void RenderHelper::RenderWorldObjects(std::vector<WorldObject*> InWorldObjects) const
{
	//the current class index used for picking the correct vertices
	int ClassIndex = -1;

	//loop through the world objects
	for (WorldObject* WorldObject : InWorldObjects)
	{
		//check if the class id is different
		if (WorldObject->ClassID != ClassIndex)
		{
			//check if the current class index is valid
			if (ClassIndex != -1)
			{
				//unbind the previous vertex array object
				glBindVertexArray(0);
			}

			//set the class index
			ClassIndex = WorldObject->ClassID;

			//bind the vertex array object
			glBindVertexArray(VAOs[ClassIndex]);

			//check if the current class index is the one for the container box
			if (ClassIndex == ContainerBoxClassID)
			{
				//set the current polygon mode
				glPolygonMode(GL_FRONT_AND_BACK, TerrainPolygonMode);
			}

			//check if the current class index is the one for the sphere
			if (ClassIndex == SphereClassID)
			{
				//set the current polygon mode
				glPolygonMode(GL_FRONT_AND_BACK, SpherePolygonMode);
			}
		}

		//create the model matrix
		const glm::mat4 Model = {
			WorldObject->Size.x, 0, 0, 0,
			0, WorldObject->Size.y, 0, 0,
			0, 0, WorldObject->Size.z, 0,
			WorldObject->Position.x, WorldObject->Position.y, WorldObject->Position.z, 1
		};

		//set the model matrix
		glUniformMatrix4fv(ModelKeyLocation, 1, GL_FALSE, &Model[0][0]);

		//draw the world object
		glDrawElements(GL_TRIANGLES, Indices.at(ClassIndex).size(), GL_UNSIGNED_INT, 0);
	}
}

void RenderHelper::DrawObject(const int ClassIndex, const WorldObject* WorldObject) const
{
	//create the model matrix
	const glm::mat4 Model = {
		WorldObject->Size.x, 0, 0, 0,
		0, WorldObject->Size.y, 0, 0,
		0, 0, WorldObject->Size.z, 0,
		WorldObject->Position.x, WorldObject->Position.y, WorldObject->Position.z, 1
	};

	//set the model matrix
	glUniformMatrix4fv(ModelKeyLocation, 1, GL_FALSE, &Model[0][0]);

	//draw the world object
	glDrawElements(GL_TRIANGLES, Indices.at(ClassIndex).size(), GL_UNSIGNED_INT, 0);
}

std::vector<Vertex> RenderHelper::GetWorldVertices(const WorldObject* InObject) const
{
	//get the model matrix of the object
	const glm::mat4 Model = GetModelMatrix(InObject);

	//create a vector to store the world vertices
	std::vector<Vertex> WorldVertices;
	WorldVertices.reserve(Vertices.at(InObject->ClassID).size());

	//loop through the vertices and add the world position to the world vertices
	for (Vertex LocVertex : Vertices.at(InObject->ClassID))
	{
		//get the world position
		const glm::vec3 WorldPosition = Model * glm::vec4(LocVertex.Position, 1);

		//add the world position to the world vertices
		WorldVertices.emplace_back(WorldPosition, LocVertex.Normal, LocVertex.TexCoords);
	}

	return WorldVertices;
}
