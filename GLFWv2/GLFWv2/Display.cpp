#include "Display.h"

Display::Display(int width, int height)
	{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);	
	window = glfwCreateWindow(width, height, "1942 by Olympia Xanthakis & Orfeas Kalipolitis", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
}

Display::~Display()
{
	glfwDestroyWindow(window);
}

bool Display::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Display::Buffer()
{
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void Display::Swap()
{
	glfwSwapBuffers(window);
}

GLFWwindow* Display::getWindow()
{
	return window;
}
