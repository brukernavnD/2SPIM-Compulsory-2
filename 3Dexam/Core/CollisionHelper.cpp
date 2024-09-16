#include "CollisionHelper.h"

#include <iostream>
#include <ostream>

#include "CollisionTreeNode.h"
#include "World.h"
#include "../Actors/ContainerBox.h"
#include "../Actors/Sphere.h"

void CollisionHelper::CheckCollisions(const std::vector<ContainerBox_*>& ContainerBoxes, const std::vector<Sphere_*>& Spheres)
{
	////iterate through all container boxes
	//for (const ContainerBox_* ContainerBox : ContainerBoxes)
	//{
	//	//iterate through all spheres
	//	for (Sphere_* Sphere : Spheres)
	//	{
	//		//check if the sphere is not moving
	//		if (Sphere->Velocity == glm::vec3(0.0f))
	//		{
	//			//skip the sphere
	//			continue;
	//		}

	//		//check if the sphere is colliding with the container box
	//		if (!CheckCollision(ContainerBox, Sphere))
	//		{
	//			//bounce the sphere off the container box
	//			BounceSphere(Sphere, ContainerBox);
	//		}
	//	}
	//}

	//create a collision tree
	const CollisionTreeNode Root = CollisionTreeNode(CBoxCen, CBoxSize, Spheres);

	////assign the spheres to the collision tree
	//Root.AssignObjects(Spheres);

	////solve for collisions in the collision tree
	//Root.SolveCollisions(ContainerBoxes);

	////iterate through all the spheres
	//for (int I = 0; I < Spheres.size(); ++I)
	//{
	//	//iterate through all the spheres
	//	for (int J = I + 1; J < Spheres.size(); ++J)
	//	{
	//		//check if the spheres are colliding with each other
	//		if (CheckCollision(Spheres[I], Spheres[J]))
	//		{
	//			//bounce the spheres off each other
	//			BounceSpheres(Spheres[I], Spheres[J]);
	//		}
	//	}
	//}
}

bool CollisionHelper::CheckCollision(const ContainerBox_* Box, const Sphere_* Sphere)
{
    //get the half size of the sphere
    const glm::vec3 SphereHalfSize = Sphere->Size / 2.0f;

    //get the half size of the container box
    const glm::vec3 BoxHalfSize = Box->Size / 2.0f;

    //get the distance between the sphere and the container box
    glm::vec3 Distance = Sphere->Position - Box->Position;

    //get the distance between the sphere and the container box
    const glm::vec3 Clamped = clamp(Distance, -BoxHalfSize, BoxHalfSize);

    //get the closest point on the container box to the sphere
    const glm::vec3 Closest = Box->Position + Clamped;

    //get the distance between the sphere and the closest point on the container box
    Distance = Sphere->Position - Closest;

    ////get the length of the distance
    //const float Length = length(Distance);

	//get the length of the distance
	const float Length = sqrt(Distance.x * Distance.x + Distance.y * Distance.y + Distance.z * Distance.z);

    //check if the length is less than or equal to the radius of the sphere
    if (Length + SphereHalfSize.x / 2 < SphereHalfSize.x)
    {
        //return true
        return true;
    }

    //return false
    return false;
}

bool CollisionHelper::CheckCollision(const Sphere_* Sphere1, const Sphere_* Sphere2)
{
	//get the distance between the two spheres
	const glm::vec3 Distance = Sphere1->Position - Sphere2->Position;

	////get the length of the distance
	//const float Length = length(Distance);

	//get the length of the distance
	const float Length = sqrt(Distance.x * Distance.x + Distance.y * Distance.y + Distance.z * Distance.z);

	//check if the length is less than or equal to the sum of the radii of the two spheres
	if (Length <= Sphere1->Size.x + Sphere2->Size.x)
	{
		//return true
		return true;
	}

	//return false
	return false;
}

void CollisionHelper::BounceSphere(Sphere_* Sphere, const ContainerBox_* Box)
{
	//get the half size of the sphere
	const glm::vec3 SphereHalfSize = Sphere->Size / 2.0f;

	//get the half size of the container box
	const glm::vec3 BoxHalfSize = Box->Size / 2.0f;

	//get the distance between the sphere and the container box
	glm::vec3 Distance = Sphere->Position - Box->Position;

	//get the distance between the sphere and the container box
	const glm::vec3 Clamped = clamp(Distance, -BoxHalfSize, BoxHalfSize);

	//get the closest point on the container box to the sphere
	const glm::vec3 Closest = Box->Position + Clamped;

	//get the distance between the sphere and the closest point on the container box
	Distance = Sphere->Position - Closest;

	//get the length of the distance
	const float Length = length(Distance);

	//get the normal of the distance
	const glm::vec3 Normal = normalize(Distance);

	//get the penetration
	const float Penetration = SphereHalfSize.x - Length;

	//get the new position of the sphere
	Sphere->Position += Normal * Penetration;

	//get the new velocity of the sphere
	Sphere->Velocity = reflect(Sphere->Velocity, Normal);
}

void CollisionHelper::BounceSpheres(Sphere_* Sphere1, Sphere_* Sphere2)
{
	//get the distance between the two spheres
	const glm::vec3 Distance = Sphere1->Position - Sphere2->Position;

	//get the length of the distance
	const float Length = length(Distance);

	//get the normal of the distance
	const glm::vec3 Normal = normalize(Distance);

	//get the penetration
	const float Penetration = Sphere1->Size.x + Sphere2->Size.x - Length;

	//get the new position of the first sphere
	Sphere1->Position += Normal * Penetration;

	//get the new position of the second sphere
	Sphere2->Position -= Normal * Penetration;

	//get the new velocity of the first sphere
	Sphere1->Velocity = reflect(Sphere1->Velocity, Normal);

	//get the new velocity of the second sphere
	Sphere2->Velocity = reflect(Sphere2->Velocity, -Normal);
}

CollisionTreeNode CollisionHelper::ConstructCollisionTree(const glm::vec3& InPosition, const glm::vec3& InHalfSize, const std::vector<Sphere_*> InSpheres, CollisionTreeNode* InParent)
{
	//create a new collision tree node
	CollisionTreeNode Node = CollisionTreeNode(InPosition, InHalfSize, InSpheres, InParent);

	//check if the node is a leaf node
	if (Node.IsLeaf())
	{
		//return the node
		return Node;
	}

	//get the half size of the node
	const glm::vec3 HalfSize = InHalfSize / 2.0f;

	//get the children of the node
	std::vector<CollisionTreeNode> Children;

	//iterate through all the children
	for (int I = 0; I < CollisionTreeNode::TreeType; ++I)
	{
		//get the position of the child
		const glm::vec3 Position = InPosition + HalfSize * glm::vec3((I & 1) ? 1.0f : -1.0f, (I & 2) ? 1.0f : -1.0f, (I & 4) ? 1.0f : -1.0f);

		//create a new collision tree node
		CollisionTreeNode Child = ConstructCollisionTree(Position, HalfSize, InSpheres, &Node);

		//add the child to the children
		Children.push_back(Child);
	}

	//set the children of the node
	Node.Children = Children;

	//return the node
	return Node;
}
