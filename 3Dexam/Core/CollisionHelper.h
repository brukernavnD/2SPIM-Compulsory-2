#pragma once
#include "Helpers.h"

class CollisionTreeNode;
class Sphere_;
class ContainerBox_;

class CollisionHelper
{
	public:

	//function to check for collisions between container boxes and spheres
	static void CheckCollisions(const std::vector<ContainerBox_*>& ContainerBoxes, const std::vector<Sphere_*>& Spheres);

	//helper function to check for collisions between a sphere and a container box
	static bool CheckCollision(const ContainerBox_* Box, const Sphere_* Sphere);

	//helper function to check for collisions between two spheres
	static bool CheckCollision(const Sphere_* Sphere1, const Sphere_* Sphere2);

	//helper function to bounce a sphere off a container box
	static void BounceSphere(Sphere_* Sphere, const ContainerBox_* Box);

	//helper function to bounce two spheres off each other
	static void BounceSpheres(Sphere_* Sphere1, Sphere_* Sphere2);

	//function to construct a collision tree
	static CollisionTreeNode ConstructCollisionTree(const glm::vec3& InPosition, const glm::vec3& InHalfSize, const std::vector<Sphere_*> InSpheres, CollisionTreeNode* InParent = nullptr);
};