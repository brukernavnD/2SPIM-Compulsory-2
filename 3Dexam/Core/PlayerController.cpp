#include "PlayerController.h"

#include <map>
#include <ostream>
#include "../Actors/Sphere.h"
#include "Helpers.h"
#include "World.h"
#include "WorldObject.h"

PlayerInput_::PlayerInput_() = default;

EInputState PlayerInput_::GetKeyState(const int Key)
{
	//get the current key state
	const EInputState CurrentKeyState = glfwGetKey(GameWindow, Key) == GLFW_PRESS ? EInputState::Pressed : EInputState::NotPressed;

	//check if the key is not in the keys to check vector
	if (std::count(KeysToCheck.begin(), KeysToCheck.end(), std::pair<int, EInputState>(Key, EInputState::Pressed)) == 0)
	{
		//check if the key is currently pressed
		if (CurrentKeyState == EInputState::Pressed)
		{
			//add the key to the keys to check vector
			KeysToCheck.emplace_back(Key, EInputState::Pressed);
		}

		//return the current key state
		return CurrentKeyState;
	}

	//get the index of the key in the keys to check vector
	const int KeyIndex = std::distance(KeysToCheck.begin(), std::find(KeysToCheck.begin(), KeysToCheck.end(), std::pair<int, EInputState>(Key, EInputState::Pressed)));

	//check if the key was pressed last frame and isn't currently pressed
	if (KeysToCheck.at(KeyIndex).second == EInputState::Pressed && CurrentKeyState == EInputState::NotPressed)
	{
		//set the key state to released
		KeysToCheck.at(KeyIndex) = std::pair<int, EInputState>(Key, EInputState::Released);

		//return the released key state
		return EInputState::Released;
	}

	//return the current key state
	return CurrentKeyState;
}

bool PlayerInput_::IsPressed(const int Key)
{
	//return the key state
	return GetKeyState(Key) == EInputState::Pressed;
}

bool PlayerInput_::WasReleased(const int Key)
{
	//return the key state
	return GetKeyState(Key) == EInputState::Released;
}

void PlayerInput_::ResetKeysData()
{
	//iterate through the keys to check vector
	for (std::pair<int, EInputState>& Key : KeysToCheck)
	{
		//check if the key was released last frame
		if (Key.second == EInputState::Released)
		{
			//remove the key from the keys to check vector
			KeysToCheck.erase(std::remove(KeysToCheck.begin(), KeysToCheck.end(), Key), KeysToCheck.end());
		}
	}
}

PlayerController_::PlayerController_() = default;

void PlayerController_::ProcessKeyboardInput(GLFWwindow* Window, int Key, int ScanCode, int Action, int Mods)
{
	//check if the escape key is pressed or held
    if (Key == GLFW_KEY_ESCAPE && (Action == GLFW_PRESS || Action == GLFW_REPEAT)) 
	{
		glfwSetWindowShouldClose(Window, true);
	}


	//check if the 1 key was just released
	if (PlayerInput.WasReleased(GLFW_KEY_1))
	{
		//check if the polygon mode is GL_FILL
		if (GetWorld()->Renderer.SpherePolygonMode == GL_FILL)
		{
			//set the polygon mode to GL_LINE
			GetWorld()->Renderer.SpherePolygonMode = GL_LINE;
		}
		else
		{
			//set the polygon mode to GL_FILL
			GetWorld()->Renderer.SpherePolygonMode = GL_FILL;
		}
	}

	//check if the 2 key was just released
	if (PlayerInput.WasReleased(GLFW_KEY_2))
	{
		//check if the polygon mode is GL_FILL
		if (GetWorld()->Renderer.TerrainPolygonMode == GL_FILL)
		{
			//set the polygon mode to GL_LINE
			GetWorld()->Renderer.TerrainPolygonMode = GL_LINE;
		}
		else
		{
			//set the polygon mode to GL_FILL
			GetWorld()->Renderer.TerrainPolygonMode = GL_FILL;
		}
	}

	//check if the 3 key was just released
	if (PlayerInput.WasReleased(GLFW_KEY_3))
	{
		//get all the objects in the world
		const std::vector<WorldObject*> Objects = GetWorld()->GetWorldObjects();

		//iterate through all world objects
		for (WorldObject* Object : Objects)
		{
			//check if the object is a sphere
			if (Object->ClassID != SphereClassID)
			{
				//skip the object
				continue;
			}

			//set the velocity of the sphere to 0
			Object->Velocity = { 0,0,0 };
		}
	}

	//check if the 4 key was just released
	if (PlayerInput.WasReleased(GLFW_KEY_4))
	{
		//get all the objects in the world
		const std::vector<WorldObject*> Objects = GetWorld()->GetWorldObjects();

		//iterate through all world objects
		for (WorldObject* Object : Objects)
		{
			//check if the object is a sphere
			if (Object->ClassID != SphereClassID)
			{
				//skip the object
				continue;
			}

			//set the velocity of the sphere to a random value
			Object->Velocity = {(rand() % 40), (rand() % 40), (rand() % 40)};
		}
	}
}

void PlayerController_::ProcessMouseInput(const float XPos, const float YPos) const
{
	//process the mouse movement
	GetWorld()->GetPlayerCamera()->ProcessMouseInput(XPos, YPos, true);
}

void PlayerController_::ProcessMouseScroll(const float yoffset) const
{
	GetWorld()->GetPlayerCamera()->ProcessMouseScroll(yoffset);
}

void PlayerController_::Tick(const float DeltaTime)
{
	constexpr float MovementSpeed = 50;

	//check if the w key is pressed
	if (PlayerInput.IsPressed(GLFW_KEY_W))
	{
		GetWorld()->GetPlayerCamera()->Position += GetWorld()->GetPlayerCamera()->Front * DeltaTime * MovementSpeed;
	}

	//check if the a key is pressed
	if (PlayerInput.IsPressed(GLFW_KEY_A))
	{
		GetWorld()->GetPlayerCamera()->Position -= GetWorld()->GetPlayerCamera()->Right * DeltaTime * MovementSpeed;
	}

	//check if the s key is pressed
	if (PlayerInput.IsPressed(GLFW_KEY_S))
	{
		GetWorld()->GetPlayerCamera()->Position -= GetWorld()->GetPlayerCamera()->Front * DeltaTime * MovementSpeed;
	}

	//check if the d key is pressed
	if (PlayerInput.IsPressed(GLFW_KEY_D))
	{
		GetWorld()->GetPlayerCamera()->Position += GetWorld()->GetPlayerCamera()->Right * DeltaTime * MovementSpeed;
	}

	//update the camera
	GetWorld()->GetPlayerCamera()->updateCameraVectors();

	//reset the keys data
	PlayerInput.ResetKeysData();
}
