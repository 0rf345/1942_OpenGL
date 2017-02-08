#pragma once
#include <iostream>
#include <GLFW\glfw3.h>
#include <GL\glew.h>

class GameWindow
{
private:

	bool _running;
	GLfloat _width;
	GLfloat _height;

public:

	void setRunning(bool newRunning);
	bool getRunning();
	GameWindow(bool running, GLfloat width, GLfloat height);
	~GameWindow();
	void Render();
	void Update();
};

