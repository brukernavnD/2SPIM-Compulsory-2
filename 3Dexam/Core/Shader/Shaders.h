#pragma once
#include <string>

class Shaders
{
public:

	//function to get the vertex shader code
	static std::string GetVertexShader();

	//function to get the fragment shader code
	static std::string GetFragmentShader();

	 //function to create a glfw shader program
	static unsigned int CreateShader();
};

