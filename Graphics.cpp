#include "Graphics.h"

Graphics graphics;
GLFWwindow * window = 0;

void WindowSizeCB( GLFWwindow* window, int width, int height )
{
    TwWindowSize(width, height);
}

int Graphics::Initialize()
{
	return 0;	
}
