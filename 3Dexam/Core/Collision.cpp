#include "Collision.h"
#include "../Actors/Sphere.h"
#include "../Actors/ContainerBox.h"

Collision::Collision(const Sphere_* InSphere1, const Sphere_* InSphere2)
{
	//calculate the normal of the 2 spheres
	N = normalize(InSphere2->Position - InSphere1->Position);
}

Collision::Collision(const Sphere_* InSphere, const ContainerBox_* InContainerBox)
{
	//get the normal of the collision
	N = normalize(InSphere->Position - InContainerBox->Position);
}
