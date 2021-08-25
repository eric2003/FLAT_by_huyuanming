#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include<chrono>
#include<thread>
using namespace std;

double gravity = 0;

int Game::frameCount, Game::frameRate;
void MySleep( int milisecond )
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milisecond));
}

void Game::FrameRateThreadFun(void *arg) {
	frameCount = 0;
	while (1) {
		MySleep(1000);
		settings.frameRate = frameCount;
		frameCount = 0;
	}
}

bool Game::MouseButtonEvent(int button, int action) {
	if (designer.MouseButtonEvent(button, action)) return true;
	if (bodyLinker.MouseButtonEvent(button, action)) return true;
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
		Object *object = ShapeFactory::Generate();
		object->SetPosition(input.mouse.position);
		physics.AddObject(object);
		return true;
	}
	
	return false;
}

bool Game::KeyEvent(int key, int action) {
	if (designer.KeyEvent(key, action)) return true;
	if (bodyLinker.KeyEvent(key, action)) return true;
	if (ShapeFactory::KeyEvent(key, action)) return true;

	if (action == GLFW_RELEASE) return false;	
	if (key == GLFW_KEY_PAUSE) return settings.pause ^= 1, true;
	if (key == GLFW_KEY_F1) return Test1(), true;
	if (key == GLFW_KEY_F2) return Test2(), true;
	if (key == GLFW_KEY_F3) return Test3(), true;
	if (key == GLFW_KEY_F4) return Test4(), true;
	if (key == GLFW_KEY_F5) return Test5(), true;
	if (key == GLFW_KEY_F6) return Test6(), true;
	if (key == GLFW_KEY_F7) return Test7(), true;
	
	return false;
}

bool Game::MouseWheelEvent(int delta)
{
	return scoper.MouseWheelEvent(delta);
}

void WindowSizeCallback( GLFWwindow * window, int width, int height );
void processInput( GLFWwindow* window );

void processInput( GLFWwindow* window )
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void WindowSizeCallback( GLFWwindow * window, int width, int height )
{
    glViewport(0, 0, width, height);// Draw into entire window
}

void Game::Initialize()
{
	srand((unsigned int)time(0));
    glfwInit();
	window = glfwCreateWindow( screenWidth, screenHeight, "Physics Engine", NULL, NULL );
    if ( window == NULL )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent( window );
    glfwSetFramebufferSizeCallback( window, WindowSizeCallback );

    if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

	TwInit( TW_OPENGL, NULL );
	TwWindowSize( screenWidth, screenHeight );

	glClearColor(0.0f , 0.0f , 0.0f , 0.0f );
	glColor3f(1.0f , 1.0f , 1.0f );
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screenWidth, 0, screenHeight, -1.0f, 1.0f);
	glEnable(GL_POINT_SMOOTH);  
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST); // Make round points, not square points  
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points  
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines  
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		
	glfwSetWindowSizeCallback(window, WindowSizeCB);
	glfwSetCharCallback( window, (GLFWcharfun)TwEventCharGLFW );

	glfwSetCursorPosCallback( window, MousePosCallback );
	glfwSetMouseButtonCallback( window, MouseButtonCallback );
	glfwSetKeyCallback( window, KeyEventCallback );
	glfwSetScrollCallback( window, MouseWheelCallback );
	frameRate = 0;
	frameCount = 0;
	ShapeFactory::Init();
	settings.Init();
	designer.SetGame( this );
	bodyLinker.SetGame( this );
	scoper.SetGame( this );
}

void Game::PrepareRendering( Object *& target, Vector2D & shapeR )
{
	input.Update();
	{
		if ( input.keyboard.NeedProcess((int)'X'))
		{
			if ( physics.objects.size() > 1 )
				while (physics.objects.size() > 1) physics.DeleteLastObject();
			else if (physics.objects.size() == 1)
				physics.DeleteLastObject();
		}
	}

	if ( input.mouse.NeedProcess(GLFW_MOUSE_BUTTON_2) )
	{
		physics.SelectObject(input.mouse.position, target, shapeR);
	}

	if ( target != NULL )
	{
		if ( input.mouse.IsPressed(GLFW_MOUSE_BUTTON_2) )
		{
			physics.MouseAdjust(target, shapeR, input.mouse.position, &scoper);
			if (input.keyboard.NeedProcess('S'))
			{
				target->SetFixed( !target->GetFixed() );
			}
		}
		else
		{
			target = NULL;
		}
	}
	if ( target != NULL )
	{
		if ( input.keyboard.NeedProcess(GLFW_KEY_DELETE) && target != physics.GetWorldBox() )
		{
			physics.DeleteObject(target);
			target = NULL;
		}
	}

	if ( ! settings.pause )
	{
		physics.Proceed( timeInterval );
	}
	else
	{
		MySleep( 20 );
	}
}

void Game::Rendering( Object * target, Vector2D & shapeR )
{
	graphics.BeginRendering();

	physics.Redraw();
	if ( target != NULL && input.mouse.IsPressed(GLFW_MOUSE_BUTTON_2) )
	{
		Vector2D p = target->GetTransformToWorld()(shapeR + Vector2D::Origin);
		graphics.DrawLine(p.x, p.y, input.mouse.position.x, input.mouse.position.y, HSB3f(0.0f, 0.8f, 0.8f), 5.0);
	}
	designer.Redraw();
	bodyLinker.Redraw();

	graphics.EndRendering();
}

void Game::Run()
{
	Initialize();

	Test1();

	Object *target = NULL;
	Vector2D shapeR;

    while ( !glfwWindowShouldClose( window ) )
    {
		this->PrepareRendering( target, shapeR );
		this->Rendering( target, shapeR );
    }
    glfwMakeContextCurrent( window );
    return;
}

Game game;

void KeyEventCallback( GLFWwindow* window, int key, int action, int my_none1, int my_none2 )
{
	if (TwEventKeyGLFW(key, action)) return;
	if (game.KeyEvent(key, action)) return;
}

void MouseButtonCallback( GLFWwindow* window, int botton, int action, int my_none )
{
	if (TwEventMouseButtonGLFW(botton, action)) return;
	if (game.MouseButtonEvent(botton, action)) return;
}

void MousePosCallback( GLFWwindow* window, double x, double y )
{
	TwEventMousePosGLFW(x, y);	
}

void MouseWheelCallback( GLFWwindow* window, double pos, double my_none )
{
	static int lastPos;
	int delta = pos - lastPos;
	lastPos = pos;
	TwEventMouseWheelGLFW(pos);
	game.MouseWheelEvent(delta);
}
