#include "World.h"

#include <iostream>
#include <ostream>

#include "CollisionHelper.h"
#include "PlayerController.h"
#include "WorldObject.h"
#include "../Actors/Sphere.h"

class PlayerController_;
class PlayerCharacter_;

World::World() = default;

void World::InitializeWorld()
{
	//iterate through all other spheres
	for (Sphere_& OtherSphere : OtherSpheres)
	{
		//add the sphere to the world objects
		WorldObjects.push_back(&OtherSphere);

		//add the sphere to the spheres
		Spheres.push_back(&OtherSphere);
	}

	//iterate through all container boxes
	for (ContainerBox_* Box : Boxes)
	{
		//add the box to the world objects
		WorldObjects.push_back(Box);
	}

	//create the player controller
	PlayerController = new PlayerController_();

	//iterate through all world objects
	for (WorldObject* Object : WorldObjects)
	{
		//begin play for the object
		Object->BeginPlay();
	}
}

void World::TickWorld(const float DeltaTime) const
{
	//tick the player controller first
	PlayerController->Tick(DeltaTime);

	//iterate through all world objects
	for (WorldObject* Object : WorldObjects)
	{
		//tick the object
		Object->Tick(DeltaTime);
	}
}

void World::UpdateWorld(const float InDeltaTime) const
{
	//iterate over the spheres
	for (Sphere_* Sphere : Spheres)
	{
		//check if the position has become NaN
		if (any(isnan(Sphere->Position)))
		{
			//reset the sphere
			Sphere->Position = glm::vec3(0.0f);
		}
	}

	//check for collisions
	CollisionHelper::CheckCollisions(Boxes, Spheres);

	//tick the world
	TickWorld(InDeltaTime);

	//render the world
	Renderer.RenderWorldObjects(WorldObjects);
}

std::vector<WorldObject*>& World::GetWorldObjects()
{
	//return the world objects
	return WorldObjects;
}

Camera* World::GetPlayerCamera()
{
	//return a pointer to the player camera
	return &PlayerCamera;
}

void World::AddSphere(Sphere_ Actor)
{
	//add the actor to the other world objects
	OtherSpheres.push_back(Actor);
}
