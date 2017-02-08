#pragma once
#include "Display.h"
#include <iostream>
#include "Globals.h"

static void Pause(Display* display)
{
	double time = glfwGetTime();
	_sleep(250);
	std::cout << "Paused" << std::endl;
	glfwPollEvents();
	while (!glfwGetKey((*display).getWindow(), PAUSE) == GLFW_PRESS)
	{
		glfwWaitEvents();
		if ((*display).shouldClose()) return;
	}
	_sleep(200);
	glfwPollEvents();
	glfwSetTime(time);
}