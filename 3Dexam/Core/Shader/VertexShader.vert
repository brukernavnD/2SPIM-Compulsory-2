#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;
layout (location = 2) in vec2 aTexCoord;

out vec3 Colour;
out vec3 FragPos;
out vec2 TexCoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	gl_Position = Projection * View * Model * vec4(aPos, 1.0);
	FragPos = vec3(Model * vec4(aPos, 1.0));
	Colour = aColour;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}