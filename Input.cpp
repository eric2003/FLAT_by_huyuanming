#include "Input.h"
#include "Constants.h"
#include "Graphics.h"

void Input::Update() {
	double xpos, ypos;
	glfwGetCursorPos( window, & xpos, & ypos );
	int x = xpos;
	int y = ypos;
	y = screenHeight - y;
	mouse.SetPos(x, y);
	for (int i = 0; i < 512; i++)
	{
		keyboard.Set( i, glfwGetKey(window, i) == GLFW_PRESS );
	}
	mouse.Set(GLFW_MOUSE_BUTTON_1, glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS);
	mouse.Set(GLFW_MOUSE_BUTTON_2, glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS);
	mouse.Set(GLFW_MOUSE_BUTTON_3, glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_3) == GLFW_PRESS);
}
