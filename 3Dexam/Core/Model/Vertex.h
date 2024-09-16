#pragma once

#include <glm/vec3.hpp>
#include "glm/vec2.hpp"

//based off of the vertex struct from learnopengl.com
struct Vertex
{
	//our position
	glm::vec3 Position = glm::vec3(0);

	//our colour
	glm::vec3 Normal = glm::vec3(0);

	//our texture coordinates
	glm::vec2 TexCoords = glm::vec2(0);

	//constructor(s)
	Vertex();
	explicit Vertex(glm::vec3 InPos);
	Vertex(glm::vec3 Vec, glm::vec3 Vec3);
	Vertex(glm::vec3 InPos, glm::vec3 InNormal, glm::vec2 InTextureCoordinates);
	Vertex(float InX, float InY, float InZ, float InU, float InV);
	Vertex(float InX, float InY, float InZ, float InR, float InG, float InB, float InU, float InV);
	Vertex(glm::vec3 Vec, const glm::vec3 Vec3, glm::vec2 Vec2, const glm::vec3 InU);

	//operator overloads
	bool operator==(const Vertex& InVertex) const;
};

