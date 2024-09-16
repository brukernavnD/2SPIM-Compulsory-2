#pragma once
#include "WorldObject.h"

class ContainerBox_;
class Sphere_;

class Collision
{
	public:

	//constructor(s)
	Collision(const Sphere_* InSphere1, const Sphere_* InSphere2);
	Collision(const Sphere_* InSphere, const ContainerBox_* InContainerBox);

	//the normal of the collision
	glm::vec3 N = glm::vec3(0.0f);

	//the first object in the collision
	WorldObject* Obj1 = nullptr;

	//the second object in the collision
	WorldObject* Obj2 = nullptr;
};
