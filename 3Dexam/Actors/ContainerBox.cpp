#include "ContainerBox.h"

#include <iostream>
#include <ostream>

#include "../Core/Helpers.h"
#include "../Core/World.h"

ContainerBox_::ContainerBox_(glm::vec3 InPos, glm::vec3 InSize) : WorldObject(InPos, InSize, {0,0,0}, "ContainerBox (" + std::to_string(GameWorld.CurrentValidID + 1) + ")")
{
	ClassID = ContainerBoxClassID;
}

std::vector<Vertex> ContainerBox_::CreateVertices()
{
	//storage for the vertices
	std::vector<Vertex> ReturnVertices = {
		// Back face (looking towards -Z)
        {{-0.5, -0.5, -0.5f}, {0,  0, -1}, {0, 0}}, // Bottom-left
        {{ 0.5, -0.5, -0.5f}, {0,  0, -1}, {1, 0}}, // Bottom-right
        {{ 0.5,  0.5, -0.5f}, {0,  0, -1}, {1, 1}}, // Top-right
        {{-0.5,  0.5, -0.5f}, {0,  0, -1}, {0, 1}}, // Top-left

        // Front face (looking towards +Z)
        {{-0.5, -0.5,  0.5f}, {0,  0,  1}, {0, 0}}, // Bottom-left
        {{ 0.5, -0.5,  0.5f}, {0,  0,  1}, {1, 0}}, // Bottom-right
        {{ 0.5,  0.5,  0.5f}, {0,  0,  1}, {1, 1}}, // Top-right
        {{-0.5,  0.5,  0.5f}, {0,  0,  1}, {0, 1}}, // Top-left

        // Left face (looking towards -X)
        {{-0.5, -0.5, -0.5f}, {-1,  0,  0}, {1, 0}}, // Bottom-right
        {{-0.5, -0.5,  0.5f}, {-1,  0,  0}, {0, 0}}, // Bottom-left
        {{-0.5,  0.5,  0.5f}, {-1,  0,  0}, {0, 1}}, // Top-left
        {{-0.5,  0.5, -0.5f}, {-1,  0,  0}, {1, 1}}, // Top-right

        // Right face (looking towards +X)
        {{ 0.5, -0.5, -0.5f}, {1,  0,  0}, {0, 0}}, // Bottom-left
        {{ 0.5, -0.5,  0.5f}, {1,  0,  0}, {1, 0}}, // Bottom-right
        {{ 0.5,  0.5,  0.5f}, {1,  0,  0}, {1, 1}}, // Top-right
        {{ 0.5,  0.5, -0.5f}, {1,  0,  0}, {0, 1}}, // Top-left

        // Top face (looking towards +Y)
        {{-0.5,  0.5, -0.5f}, {0,  1,  0}, {0, 1}}, // Top-left
        {{ 0.5,  0.5, -0.5f}, {0,  1,  0}, {1, 1}}, // Top-right
        {{ 0.5,  0.5,  0.5f}, {0,  1,  0}, {1, 0}}, // Bottom-right
        {{-0.5,  0.5,  0.5f}, {0,  1,  0}, {0, 0}}, // Bottom-left

        // Bottom face (looking towards -Y)
        {{-0.5, -0.5, -0.5f}, {0, -1,  0}, {0, 1}}, // Top-left
        {{ 0.5, -0.5, -0.5f}, {0, -1,  0}, {1, 1}}, // Top-right
        {{ 0.5, -0.5,  0.5f}, {0, -1,  0}, {1, 0}}, // Bottom-right
        {{-0.5, -0.5,  0.5f}, {0, -1,  0}, {0, 0}}, // Bottom-left
	};

	//return the vertices
	return ReturnVertices;
}

std::vector<unsigned int> ContainerBox_::CreateIndices()
{
	//storage for the indices
	std::vector<unsigned int> ReturnIndices = {
        //bottom face
        0, 2, 1, 0, 3, 2,
        //top face
        4, 5, 6, 4, 6, 7,
        //left face
        8, 9, 10, 8, 10, 11,
        //right face
        12, 14, 13, 12, 15, 14,
        //front face
        16, 18, 17, 16, 19, 18,
        //back face
        20, 21, 22, 20, 22, 23
	};

	//return the indices
	return ReturnIndices;
}

void ContainerBox_::BeginPlay()
{
    //call the parent implementation
	WorldObject::BeginPlay();

    const std::vector<Vertex> WorldVertices = GetWorld()->Renderer.GetWorldVertices(this);

	//reserve space for the face normals
	FaceNormals.reserve(24);

	//iterate over the vertices in sets of 4
	for (int i = 0; i < 24; i += 4)
	{
		//get the face normal
		const glm::vec3 Normal = normalize(cross(WorldVertices[i + 1].Position - WorldVertices[i].Position, WorldVertices[i + 2].Position - WorldVertices[i].Position));

		//add the face normal to the face normals
		FaceNormals.push_back(Normal);
	}
}

glm::vec3 ContainerBox_::GetFaceNormal(int Index) const
{
	//return the face normal
	return FaceNormals[Index / 4];
}
