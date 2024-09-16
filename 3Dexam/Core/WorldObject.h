#pragma once
#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "Model/Vertex.h"
#include "Helpers.h"

class WorldObject
{
public:

	//our position
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);

	//our size
	glm::vec3 Size = glm::vec3(1.0f, 1.0f, 1.0f);

	//our velocity
	glm::vec3 Velocity = glm::vec3(0.0f, 0.0f, 0.0f);

	//the class id of the object class
	int ClassID = -1;

	//the id of this object (defined with a preprocessor macro)
	int ID = -1;

	//our name
	std::string Name = "UnNamed";

	//destructor
	virtual ~WorldObject();

	//constructor(s)
	WorldObject();
	explicit WorldObject(glm::vec3 InPosition, glm::vec3 InSize, glm::vec3 InVelocity, std::string InName);

	//operator overload(s)
	bool operator==(const WorldObject* Other) const;

	//function called when beginning play
	virtual void BeginPlay();

	//tick function
	virtual void Tick(float DeltaTime);
};