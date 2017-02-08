#pragma once
#include "Globals.h"

static void InputControl(Display* display)
{
	if (glfwGetKey((*display).getWindow(), LEFT) == GLFW_PRESS) 
	{
		if(startX1 - x1 <= 1.0) x1 -= move;
	}

	if (glfwGetKey((*display).getWindow(), RIGHT) == GLFW_PRESS) 
	{
		if(startX1 + x1 <= 1.0)x1 += move;
	}

	if (glfwGetKey((*display).getWindow(), UP) == GLFW_PRESS) 
	{
		if(startY1 + Y1 <= 1.0)Y1 += move;
	}

	if (glfwGetKey((*display).getWindow(), DOWN) == GLFW_PRESS)
	{
		if(startY1 - Y1 <= 1.0)Y1 -= move;
	}

	if (glfwGetKey((*display).getWindow(), FIRE) == GLFW_PRESS) 
	{
		// Attack();
	}

	if (glfwGetKey((*display).getWindow(), AVOID) == GLFW_PRESS)
	{
		// Avoid();
	}

	// Maybe key callback this which make for clear separation between key presses
	// Pauses the game - cannot get this out of here without crahing
	if (glfwGetKey((*display).getWindow(), PAUSE) == GLFW_PRESS)
	{
		Pause(display);
	}
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (STATE == MainMenu)
	{
		if (key == DOWN && action == GLFW_PRESS)
			if (CHOICE + 1 < NUMOFCHOICES) CHOICE++;
			else CHOICE = 0;

			if (key == UP && action == GLFW_PRESS)
				if (CHOICE - 1 > -1) CHOICE--;
				else CHOICE = 2;
		if ((key == FIRE) && action == GLFW_PRESS)
			CHOSE = true;
	}
	else if (STATE == ControlsConfig)
	{
		if (UP == 0 && action == GLFW_PRESS) UP = key;
		else if (DOWN == 0 && action == GLFW_PRESS) DOWN = key;
		else if (LEFT == 0 && action == GLFW_PRESS) LEFT = key;
		else if (RIGHT == 0 && action == GLFW_PRESS) RIGHT = key;
		else if (FIRE == 0 && action == GLFW_PRESS) FIRE = key;
		else if (AVOID == 0 && action == GLFW_PRESS) AVOID = key;
		else if (PAUSE == 0 && action == GLFW_PRESS) PAUSE = key;
		else std::cout << "Manually setting up controls\n";
		_sleep(200);
	}
	else if (STATE == GamePlay1)
	{
		if (key == FIRE && action == GLFW_PRESS)
		{
			
			//Vertex temp_v[] = { (Vertex(glm::vec3(-startX1 + x1 + 0.08, startY1 + Y1,0.0), glm::vec2(0.0,1.0))),
			//						(Vertex(glm::vec3(-startX1 + x1 + 0.12, startY1 + Y1, 0.0), glm::vec2(1.0, 1.0))),
			//						(Vertex(glm::vec3(-startX1 + x1 + 0.12,-startY1 + Y1 + 0.36, 0.0), glm::vec2(1.0, 0.0))),
			//						(Vertex(glm::vec3(-startX1 + x1 + 0.08,-startY1 + Y1 + 0.36, 0.0), glm::vec2(0.0, 0.0))) };
			//Mesh temp_m(temp_v, 4);

			playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.08, startY1 + Y1, 0.0), glm::vec2(0.0, 1.0)));
			playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.08, startY1 + Y1, 0.0), glm::vec2(0.0, 1.0)));
			playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.08, startY1 + Y1, 0.0), glm::vec2(0.0, 1.0)));
			playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.08, startY1 + Y1, 0.0), glm::vec2(0.0, 1.0)));

			Vertex temp_v[] = {*playerFire_v[0], *playerFire_v[1], *playerFire_v[2], *playerFire_v[3]};

			Mesh temp_m(temp_v, 4);

			playerFire_m.push_back(&temp_m);
			
			std::cout << "FIRE!!!! " << std::endl;// << playerFire_v[0]->getPos()[0][1] << std::endl;
			// this makes no sense if (playerFire_v.size() > 1) std::cout << (playerFire_v[0])[3].getPos()[0][1] << std::endl;
		}
	}
}

static void saveControls()
{
	std::ofstream file("Resources/config.ini");
	if (file.is_open())
	{
		file << UP << std::endl;
		file << DOWN << std::endl;
		file << LEFT << std::endl;
		file << RIGHT << std::endl;
		file << FIRE << std::endl;
		file << AVOID << std::endl;
		file << PAUSE << std::endl;
	}
	std::cout << "Save new controls in config file." << std::endl;
	file.close();
}

static void deInitializeControls()
{
	UP = 0;
	DOWN = 0;
	LEFT = 0;
	RIGHT = 0;
	FIRE = 0;
	AVOID = 0;
	PAUSE = 0;
}

static void loadConfig()
{
	std::string line;
	std::ifstream file("Resources/config.ini");
	if (file.is_open())
	{
		int i = 0;
		while (std::getline(file, line)) 
		{
			if (i == 0) UP			= atoi(line.c_str());
			else if(i == 1) DOWN	= atoi(line.c_str());
			else if(i == 2) LEFT		= atoi(line.c_str());
			else if(i == 3) RIGHT	= atoi(line.c_str());
			else if(i == 4) FIRE	= atoi(line.c_str());
			else if(i == 5) AVOID	= atoi(line.c_str());
			else if (i == 6) PAUSE	= atoi(line.c_str());
			i++;
		}
		file.close();
	}
	else std::cerr << "Could not load configuration file" << std::endl;
	std::cout << "Configuration file loaded successfully." << std::endl;
}

static void SetControls(Display* display)
{
	std::ofstream file;
	file.open("Resources/config_1.ini");
	glfwSetKeyCallback((*display).getWindow(), key_callback);

	UP		= 0;
	DOWN	= 0;
	LEFT	= 0;
	RIGHT	= 0;
	FIRE	= 0;
	AVOID	= 0;
	PAUSE	= 0;

	while (UP || DOWN || LEFT || RIGHT || FIRE || AVOID || PAUSE) 
	{
		glfwPollEvents();
		_sleep(50);
	}

	for (unsigned int i = 0; i < NUMOFBUTTONS; i++)
	{
		if (i == 0) file << UP << std::endl;
		else if (i == 1) file << DOWN << std::endl;
		else if (i == 2) file << LEFT << std::endl;
		else if (i == 3) file << RIGHT << std::endl;
		else if (i == 4) file << FIRE << std::endl;
		else if (i == 5) file << AVOID << std::endl;
		else if (i == 6) file << PAUSE << std::endl;
		i++;
	}
	file.close();
	std::cout << "Done updating config.ini" << std::endl;
}