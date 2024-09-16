#pragma once
#include "ContainerBox.h"
#include "../Core/WorldObject.h"


class CollisionTreeNode;
//the sphere class id
constexpr int SphereClassID = 1;

//much of this code was taken from https://www.songho.ca/opengl/gl_sphere.html
class Sphere_ : public WorldObject
{
public:

	//constructor(s)
	Sphere_(glm::vec3 InPos, glm::vec3 InSize, glm::vec3 InVelocity);

	//override(s)
	static std::vector<Vertex> CreateVertices();
	static std::vector<unsigned int> CreateIndices();
	void Tick(float DeltaTime) override;
};

