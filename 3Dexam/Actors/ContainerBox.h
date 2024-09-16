#pragma once
#include "../Core/WorldObject.h"
#include "../Core/Helpers.h"

constexpr int ContainerBoxClassID = 0;

//the size of each container box
constexpr glm::vec3 CBoxSize = glm::vec3(400);

//the center of the container box group
constexpr glm::vec3 CBoxCen = { 0, -10, 0 };

class ContainerBox_ : public WorldObject
{
public:

	//constructor(s)
	ContainerBox_(glm::vec3 InPos, glm::vec3 InSize);

	//storage for face normals
	std::vector<glm::vec3> FaceNormals;

	//override(s)
	static std::vector<Vertex> CreateVertices();
	static std::vector<unsigned int> CreateIndices();
	void BeginPlay() override;

	//function to efficiently get the normal of one of the faces of the container box using a vertex index (0-23)
	glm::vec3 GetFaceNormal(int Index) const;

};
