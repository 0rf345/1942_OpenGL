#pragma once
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <string>


static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

class Display
{
private:
	GLFWwindow* window;

public:
	Display(int width, int height);
	~Display();
	bool shouldClose();
	void Buffer();
	void Swap();
	GLFWwindow* getWindow();
};