#ifndef GAME_H
#define GAME_H

#include "Physics.h"
#include "Input.h"
#include "ShapeFactory.h"
#include "Designer.h"
#include "BodyLinker.h"
#include "Scoper.h"

class Game
{
private:
public:
	Input input;
	Physics physics;
	Designer designer;
	BodyLinker bodyLinker;
	Scoper scoper;
	static int frameRate, frameCount;
	static void FrameRateThreadFun(void *arg);
	bool MouseButtonEvent(int buttion, int action);
	bool MouseWheelEvent(int delta);
	bool KeyEvent(int key, int action);
	void Test1();
	void Test2();
	void Test3();
	void Test4();
	void Test5();
	void Test6();
	void Test7();
	void Initialize();
	void Run();
public:
	void PrepareRendering( Object *& target, Vector2D & shapeR );
	void Rendering( Object * target, Vector2D & shapeR );
};

void KeyEventCallback(GLFWwindow* window, int key, int action, int my_none1 = 0, int my_none2 = 0);
void MouseButtonCallback( GLFWwindow * window, int button, int action, int my_none = 0 );
void MousePosCallback( GLFWwindow * window, double x, double y );
void MouseWheelCallback( GLFWwindow* window, double pos, double my_none );

extern Game game;

#endif