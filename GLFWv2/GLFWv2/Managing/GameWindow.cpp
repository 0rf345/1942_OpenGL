#include "GameWindow.h"



GameWindow::GameWindow(bool running, GLfloat width, GLfloat height): _running(running), _width(width), _height(height)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glViewport(0, 0, _width, _height);

	glMatrixMode(GL_PROJECTION);
}

void GameWindow::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers();
}


GameWindow::~GameWindow() {}
