#pragma once
#include "Helpers.h"

class ContainerBox_;
class Sphere_;

class CollisionTreeNode
{
public:

	//the children of the node
	std::vector<CollisionTreeNode> Children;

	//the parent of the node (nullptr if the node is the root)
	CollisionTreeNode* Parent = nullptr;

	//the position of the node
	glm::vec3 Position = { 0,0,0 };

	//the half size of the node
	glm::vec3 HalfSize = { 0,0,0 };

	//the Spheres in the node
	std::vector<Sphere_*> Spheres;

	//the amount of children the each parent node has
	static constexpr int TreeType = 4;

	//the maximum number of Spheres a node can hold
	static constexpr int MaxSpheres = 500;

	//constructor(s)
	CollisionTreeNode();
	CollisionTreeNode(glm::vec3 Position, glm::vec3 HalfSize, int RemainingDepth = 0, CollisionTreeNode* Parent = nullptr);
	CollisionTreeNode(glm::vec3 InPosition, glm::vec3 InHalfSize, const std::vector<Sphere_*>& InSpheres, CollisionTreeNode* InParent = nullptr);

	//function to check if this node is a leaf node
	bool IsLeaf() const;

	//function to check if a sphere is colliding with the node
	bool CheckCollision(const Sphere_* InSphere) const;

	//function to assign a vector of Spheres to the node
	void AssignObjects(const std::vector<Sphere_*>& InSpheres);
};

