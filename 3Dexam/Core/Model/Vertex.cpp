#include "Vertex.h"

Vertex::Vertex()
{
	Position = glm::vec3(0);
	Normal = glm::vec3(-1);
}

Vertex::Vertex(const glm::vec3 InPos)
{
	Position = InPos;
	Normal = glm::vec3(1);
	TexCoords = glm::vec2(0);
}

Vertex::Vertex(const glm::vec3 Vec, const glm::vec3 Vec3)
{
	Position = Vec;
	Normal = Vec3;
	TexCoords = glm::vec2(0);
}

Vertex::Vertex(const glm::vec3 InPos, const glm::vec3 InNormal, const glm::vec2 InTextureCoordinates)
{
	Position = InPos;
	Normal = InNormal;
	TexCoords = InTextureCoordinates;
}

Vertex::Vertex(const float InX, const float InY, const float InZ, const float InU, const float InV)
{
	Position = glm::vec3(InX, InY, InZ);
	Normal = glm::vec3(-1);
	TexCoords = glm::vec2(InU, InV);
}

Vertex::Vertex(const float InX, const float InY, const float InZ, const float InR, const float InG, const float InB, const float InU, const float InV)
{
	Position = glm::vec3(InX, InY, InZ);
	Normal = glm::vec3(InR, InG, InB);
	TexCoords = glm::vec2(InU, InV);
}

Vertex::Vertex(glm::vec3 Vec, const glm::vec3 Vec3, glm::vec2 Vec2, const glm::vec3 InU)
{
	Position = Vec;
	Normal = Vec3;
	TexCoords = Vec2;
}

bool Vertex::operator==(const Vertex& InVertex) const
{
	return Position == InVertex.Position && Normal == InVertex.Normal && TexCoords == InVertex.TexCoords;
}
