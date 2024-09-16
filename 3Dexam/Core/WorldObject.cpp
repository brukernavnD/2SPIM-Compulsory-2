#include "WorldObject.h"

#include <glm/glm.hpp>

#include <fstream> 

#include "Helpers.h"

#include "glm/gtx/transform.hpp"
#include "Model/Vertex.h"
#include "World.h"

WorldObject::~WorldObject() = default;

WorldObject::WorldObject() = default;

WorldObject::WorldObject(const glm::vec3 InPosition, const glm::vec3 InSize, glm::vec3 InVelocity, std::string InName) : Position(InPosition), Size(InSize), Velocity(InVelocity), Name(std::move(InName))
{
	//get our id
	ID = IDCounter();

	////add ourselves to the world object vector
	//GetWorld()->GetWorldObjects().emplace_back(this);
}

bool WorldObject::operator==(const WorldObject* Other) const
{
	return ID == Other->ID;
}

void WorldObject::BeginPlay()
{
	
}

void WorldObject::Tick(float DeltaTime)
{
	//do nothing
}