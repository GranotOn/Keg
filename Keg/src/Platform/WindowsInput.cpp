#include "stadx.h"
#include "WindowsInput.h"
#include "WindowBuilder.h"

#include "Core/Logger/Logger.h"
#include <GLFW/glfw3.h>

namespace Keg
{

	GLFWwindow* GetWindow()
	{
		return static_cast<GLFWwindow*>(WindowBuilder::GetInstance()->GetNativeWindow());
	}


	bool WindowsInput::IsMousePressed(MouseCode button)
	{
		GLFWwindow* window = GetWindow();
		if (!window)
		{
			KEG_ENGINE_ERROR("WindowsInput::IsMousePressed() No Window");
			return false;
		}

		int state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	bool WindowsInput::IsKeyPressed(KeyCode key)
	{
		GLFWwindow* window = GetWindow();
		if (!window)
		{
			KEG_ENGINE_ERROR("WindowsInput::IsKeyPressed() No Window");
			return false;
		}

		int state = glfwGetKey(window, key);

		return state == GLFW_PRESS;
	}

	std::pair<double, double> WindowsInput::GetMousePosition()
	{
		
		GLFWwindow* window = GetWindow();

		if (!window)
		{
			KEG_ENGINE_ERROR("WindowsInput::GetMousePosition() No Window");
			return { 0.0, 0.0 };
		}

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { xpos, ypos };
	}

	double WindowsInput::GetMouseX() { return GetMousePosition().first; }
	double WindowsInput::GetMouseY() { return GetMousePosition().second; }

}