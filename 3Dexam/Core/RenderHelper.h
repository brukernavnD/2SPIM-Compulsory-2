#pragma once
#include "Helpers.h"
#include "Model/Vertex.h"

class RenderHelper
{
	//storage for unique vertex array buffer objects
	std::vector<unsigned int> VAOs;

	//storage for unique vertex buffer objects
	std::vector<unsigned int> VBOs;

	//storage for unique element buffer objects
	std::vector<unsigned int> EBOs;

	//storage for the vertices for different types of objects (using the class id of the object)
	std::vector<std::vector<Vertex>> Vertices;

	//storage for the indices for different types of objects (using the class id of the object)
	std::vector<std::vector<unsigned int>> Indices;

public:

	//storage for the current polygon mode (for everything except the terrain)
	mutable GLint SpherePolygonMode = GL_FILL;

	//storage for the current polygon mode (for the terrain)
	mutable GLint TerrainPolygonMode = GL_FILL;

	//function to add the vaos, vbos, and ebos to the for a world object
	void AddBuffers(const std::vector<Vertex>& InVertices, const std::vector<unsigned int>& InIndices);

	//function to get the model matrix for a world object
	static glm::mat4 GetModelMatrix(const WorldObject* WorldObject);

	//rendering function for the world objects
	void RenderWorldObjects(std::vector<WorldObject*> InWorldObjects) const;

	//function to draw a single object
	void DrawObject(int ClassIndex, const WorldObject* WorldObject) const;

	//function to get the world vertices of a world object
	std::vector<Vertex> GetWorldVertices(const WorldObject* InObject) const;
};

