#pragma once
#include <string>
#include <vector>

#include "Camera.h"
#include "CollisionTreeNode.h"
#include "RenderHelper.h"


class Sphere_;
class ContainerBox_;
struct Vertex;
class PlayerController_;
class WorldObject;


class World
{
public:

	//constructor(s)
	World();

	//array to store all world objects (houses, npcs, pickups, player character, etc.)
	std::vector<WorldObject*> WorldObjects = {};

	//storage for objects that are not stored elsewhere
	std::vector<Sphere_> OtherSpheres = {};

	//storage for container boxes
	std::vector<ContainerBox_*> Boxes = {};

	//storage for the spheres
	std::vector<Sphere_*> Spheres = {};

	//the player controller
	PlayerController_* PlayerController = nullptr;

	//the camera
	Camera PlayerCamera = Camera();

	//the rendering helper
	RenderHelper Renderer = RenderHelper();

	//the current lowest valid id for any new world object
	int CurrentValidID = 0;

	//function to initialize the world
	void InitializeWorld();

	//function to tick the world
	void TickWorld(float DeltaTime) const;

	//function to update the world (tick and render)
	void UpdateWorld(float InDeltaTime) const;

	/** getters and setters */

	//function to get all the world objects
	std::vector<WorldObject*>& GetWorldObjects();

	//function to get a pointer to the current player camera
	Camera* GetPlayerCamera();

	void AddSphere(Sphere_ Actor);
};
