#include "Helpers.h"
#include <iostream>
#include "Model/Vertex.h"
#include "World.h"
#include "WorldObject.h"

World* GetWorld()
{
	return &GameWorld;
}

GLenum glCheckError_(const WorldObject* InWorldObject, const char* function, const int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
			case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
			case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
			case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
			case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
			//0x0500 is the value of GL_INVALID_FRAMEBUFFER_OPERATION
			case 0x0506: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}

		//check if the world object is valid
		if (InWorldObject != nullptr)
		{
			std::cout << InWorldObject->Name << " | " << error << " | " << function << " (" << line << ")" << '\n';
		}
		else
		{
			std::cout << error << " | " << function << " (" << line << ")" << '\n';
		}
	}
	return errorCode;
}

int IDCounter()
{
	return GameWorld.CurrentValidID++;
}

float RandomFloat(const float Min, const float Max)
{
	return Min + static_cast <float> (rand()) / (RAND_MAX / (Max - Min));
}

glm::vec3 RandomVec3(const glm::vec3 Center, const float Offset)
{
	return { RandomFloat(Center.x - Offset, Center.x + Offset), RandomFloat(Center.y - Offset, Center.y + Offset), RandomFloat(Center.z - Offset, Center.z + Offset) };
}

unsigned CreateTexture(const glm::vec4& Colour)
{
	//create the texture
	unsigned int Texture;
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);

	//set the texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//create the texture
	const unsigned char Data[4] = { static_cast<unsigned char>(Colour.r * 255), static_cast<unsigned char>(Colour.g * 255), static_cast<unsigned char>(Colour.b * 255), static_cast<unsigned char>(Colour.a * 255) };
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//return the texture
	return Texture;
}