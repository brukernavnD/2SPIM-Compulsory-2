#pragma once
#include <vector>
#include <string>
#include "glm/glm.hpp"

//include opengl and glfw for the rest of the project
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//forward declaration(s)
class WorldObject;
class World;
struct Vertex;

//storage variables for inputs to the shaders
const std::string ProjectionKey = "Projection";
const std::string ViewKey = "View";
const std::string ModelKey = "Model";

//get the model key location in the shader program
extern GLint ModelKeyLocation;

//the culling distance used when rendering objects
static float CullingDistance = 10000000.0f;

//the window's width and height
static float WindowWidth = 2048;
static float WindowHeight = 1080;

//the current shader program
extern unsigned int ShaderProgram;

//function to get a pointer to the game world
World* GetWorld();

//the current game world
extern World GameWorld;

//the window the game is running in
extern GLFWwindow* GameWindow;

//opengl error checking code from https://learnopengl.com/In-Practice/Debugging (modified)
GLenum glCheckError_(const WorldObject* InWorldObject, const char* function, const int line);

//function to get the next valid id for a world object
int IDCounter();

//function to get a random float between two values
float RandomFloat(float Min, float Max);

//function to get a position around a center point with a random offset
glm::vec3 RandomVec3(glm::vec3 Center, float Offset);

//function to create a texture for opengl using a single rgba value
unsigned int CreateTexture(const glm::vec4& Colour);

//define for the error checking outside of world objects
#define glCheckError() glCheckError_(nullptr, __FUNCTION__, __LINE__)

//define for the error checking inside of world objects
#define glWCheckError() glCheckError_(this, __FUNCTION__, __LINE__)