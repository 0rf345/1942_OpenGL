#pragma once
#include "Globals.h"
#include "Player.h"
#include <SFML\Audio.hpp>

static void Player2Control(Mesh* player2_m)
{
	static double timer = glfwGetTime();
	int count;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);
	static unsigned int debounce = 0;

	//FIRE
	if (buttons)
	{
		if (buttons[0] == GLFW_PRESS)
		{
			static sf::SoundBuffer monoShoot_buffer;
			if (!(monoShoot_buffer.loadFromFile("Resources/monoShoot.ogg")))
			{
				std::cout << "Couldn't load monoShoot\n";

			}
			static sf::Sound monoShoot_sound;
			monoShoot_sound.setBuffer(monoShoot_buffer);
			if (glfwGetTime() - timer > 0.15)
			{
				monoShoot_sound.play();
				double px, py;
				px = player2_m->getPos()[0][0]; py = player2_m->getPos()[0][1];

				playerFire_v.push_back(new Vertex(glm::vec3(player2_m->getPos()[1][0] - 0.1 - 0.02,
					player2_m->getPos()[0][1], 0.0), glm::vec2(0.0, 1.0)));

				playerFire_v.push_back(new Vertex(glm::vec3(player2_m->getPos()[1][0] - 0.1 - 0.02 + 0.04,
					player2_m->getPos()[0][1], 0.0), glm::vec2(1.0, 1.0)));

				playerFire_v.push_back(new Vertex(glm::vec3(player2_m->getPos()[1][0] - 0.1 - 0.02 + 0.04,
					player2_m->getPos()[0][1] - 0.06, 0.0), glm::vec2(1.0, 0.0)));

				playerFire_v.push_back(new Vertex(glm::vec3(player2_m->getPos()[1][0] - 0.1 - 0.02,
					player2_m->getPos()[0][1] - 0.06, 0.0), glm::vec2(0.0, 0.0)));

				int i = playerFire_v.size();

				Vertex temp_v[] = { *playerFire_v[i - 4], *playerFire_v[i - 3], *playerFire_v[i - 2], *playerFire_v[i - 1] };
				playerFire_m.push_back(new Mesh(temp_v, 4));

				playerFire_m[playerFire_m.size() - 1]->Buffer();

				timer = glfwGetTime();
				debounce = 4;
			}
			else debounce--;
		}

		// UP
		if (buttons[10] == GLFW_PRESS)
		{
			if (player2_m->getPos()[0][1] + move < 1.0)
			{
				player2_m->getPos()[0][1] += move;
				player2_m->getPos()[1][1] += move;
				player2_m->getPos()[2][1] += move;
				player2_m->getPos()[3][1] += move;

				glBindBuffer(GL_ARRAY_BUFFER, player2_m->getVBpos());
				glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(player2_m->getPos()[0]), &player2_m->getPos()[0]);
			}
		}

		//RIGHT
		if (buttons[11] == GLFW_PRESS)
		{
			if (player2_m->getPos()[1][0] + move < 1.0)
			{
				player2_m->getPos()[0][0] += move;
				player2_m->getPos()[1][0] += move;
				player2_m->getPos()[2][0] += move;
				player2_m->getPos()[3][0] += move;

				glBindBuffer(GL_ARRAY_BUFFER, player2_m->getVBpos());
				glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(player2_m->getPos()[0]), &player2_m->getPos()[0]);
			}
		}

		//DOWN
		if (buttons[12] == GLFW_PRESS)
		{
			if (player2_m->getPos()[3][1] - move > -1.0)
			{
				player2_m->getPos()[0][1] -= move;
				player2_m->getPos()[1][1] -= move;
				player2_m->getPos()[2][1] -= move;
				player2_m->getPos()[3][1] -= move;

				glBindBuffer(GL_ARRAY_BUFFER, player2_m->getVBpos());
				glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(player2_m->getPos()[0]), &player2_m->getPos()[0]);
			}
		}

		//LEFT
		if (buttons[13] == GLFW_PRESS)
		{
			if (player2_m->getPos()[0][0] - move > -1.0)
			{
				player2_m->getPos()[0][0] -= move;
				player2_m->getPos()[1][0] -= move;
				player2_m->getPos()[2][0] -= move;
				player2_m->getPos()[3][0] -= move;

				glBindBuffer(GL_ARRAY_BUFFER, player2_m->getVBpos());
				glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(player2_m->getPos()[0]), &player2_m->getPos()[0]);
			}
		}
	}


}

static void InputControl(Display* display)
{
	if (glfwGetKey((*display).getWindow(), LEFT) == GLFW_PRESS) 
	{
		if(startX1 - x1 <= player1.getLeftBorder()) x1 -= move;
	}

	if (glfwGetKey((*display).getWindow(), RIGHT) == GLFW_PRESS) 
	{
		if(startX1 + x1 <= player1.getRightBorder())x1 += move;
	}

	if (glfwGetKey((*display).getWindow(), UP) == GLFW_PRESS) 
	{
		if(startY1 + Y1 <= 1.0)Y1 += move;
	}

	if (glfwGetKey((*display).getWindow(), DOWN) == GLFW_PRESS)
	{
		if(startY1 - Y1 <= 1.035)Y1 -= move;
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
		double timesss = glfwGetTime();
		Pause(display);
		glfwSetTime(timesss);
	}
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static sf::SoundBuffer stereoShoot_buffer;
	if (!(stereoShoot_buffer.loadFromFile("Resources/stereoShoot.ogg")))
		std::cout << "Couldn't load stereoShoot\n";
	static sf::Sound stereoShoot_sound;
	stereoShoot_sound.setBuffer(stereoShoot_buffer);

	static sf::SoundBuffer quadShoot_buffer;
	if (!(quadShoot_buffer.loadFromFile("Resources/quadShoot.ogg")))
	{
		std::cout << "Couldn't load quadShoot\n";

	}
	static sf::Sound quadShoot_sound;
	quadShoot_sound.setBuffer(quadShoot_buffer);


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
			if (!player1.getQuadGun())
			{
				stereoShoot_sound.play();
				// Left Fire
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.065, startY1 + Y1 - 0.08, 0.0), glm::vec2(0.0, 1.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.115, startY1 + Y1 - 0.08, 0.0), glm::vec2(1.0, 1.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.115, startY1 + Y1 - 0.115, 0.0), glm::vec2(1.0, 0.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.065, startY1 + Y1 - 0.115, 0.0), glm::vec2(0.0, 0.0)));

				int i = playerFire_v.size();

				Vertex temp_v[] = { *playerFire_v[i - 4], *playerFire_v[i - 3], *playerFire_v[i - 2], *playerFire_v[i - 1] };
				playerFire_m.push_back(new Mesh(temp_v, 4));

				// Right Fire
				playerFire_v.push_back(new Vertex(glm::vec3( startX1 + x1 - 0.115, startY1 + Y1 - 0.08, 0.0), glm::vec2(0.0, 1.0)));
				playerFire_v.push_back(new Vertex(glm::vec3( startX1 + x1 - 0.065, startY1 + Y1 - 0.08, 0.0), glm::vec2(1.0, 1.0)));
				playerFire_v.push_back(new Vertex(glm::vec3( startX1 + x1 - 0.065, startY1 + Y1 - 0.115, 0.0), glm::vec2(1.0, 0.0)));
				playerFire_v.push_back(new Vertex(glm::vec3( startX1 + x1 - 0.115, startY1 + Y1 - 0.115, 0.0), glm::vec2(0.0, 0.0)));

				i = playerFire_v.size();
				Vertex temp_v2[] = { *playerFire_v[i - 4], *playerFire_v[i - 3], *playerFire_v[i - 2], *playerFire_v[i - 1] };
				playerFire_m.push_back(new Mesh(temp_v2, 4));

				playerFire_m[playerFire_m.size() - 2]->Buffer();
				playerFire_m[playerFire_m.size() - 1]->Buffer();
			}
			else
			{
				quadShoot_sound.play();
				// 1st Fire
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.04, startY1 + Y1 - 0.08, 0.0), glm::vec2(0.0, 1.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.08, startY1 + Y1 - 0.08, 0.0), glm::vec2(1.0, 1.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.08, startY1 + Y1 - 0.115, 0.0), glm::vec2(1.0, 0.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.04, startY1 + Y1 - 0.115, 0.0), glm::vec2(0.0, 0.0)));

				int i = playerFire_v.size();
				Vertex temp_v[] = { *playerFire_v[i - 4], *playerFire_v[i - 3], *playerFire_v[i - 2], *playerFire_v[i - 1] };
				playerFire_m.push_back(new Mesh(temp_v, 4));

				// 2nd Fire
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.10, startY1 + Y1 - 0.08, 0.0), glm::vec2(0.0, 1.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.14, startY1 + Y1 - 0.08, 0.0), glm::vec2(1.0, 1.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.14, startY1 + Y1 - 0.115, 0.0), glm::vec2(1.0, 0.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.10, startY1 + Y1 - 0.115, 0.0), glm::vec2(0.0, 0.0)));

				i = playerFire_v.size();
				Vertex temp_v2[] = { *playerFire_v[i - 4], *playerFire_v[i - 3], *playerFire_v[i - 2], *playerFire_v[i - 1] };
				playerFire_m.push_back(new Mesh(temp_v2, 4));

				// 3rd Fire
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.16, startY1 + Y1 - 0.08, 0.0), glm::vec2(0.0, 1.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.20, startY1 + Y1 - 0.08, 0.0), glm::vec2(1.0, 1.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.20, startY1 + Y1 - 0.115, 0.0), glm::vec2(1.0, 0.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.16, startY1 + Y1 - 0.115, 0.0), glm::vec2(0.0, 0.0)));

				i = playerFire_v.size();
				Vertex temp_v3[] = { *playerFire_v[i - 4], *playerFire_v[i - 3], *playerFire_v[i - 2], *playerFire_v[i - 1] };
				playerFire_m.push_back(new Mesh(temp_v3, 4));

				// 4th Fire
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.22, startY1 + Y1 - 0.08, 0.0), glm::vec2(0.0, 1.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.26, startY1 + Y1 - 0.08, 0.0), glm::vec2(1.0, 1.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.26, startY1 + Y1 - 0.115, 0.0), glm::vec2(1.0, 0.0)));
				playerFire_v.push_back(new Vertex(glm::vec3(-startX1 + x1 + 0.22, startY1 + Y1 - 0.115, 0.0), glm::vec2(0.0, 0.0)));

				i = playerFire_v.size();
				Vertex temp_v4[] = { *playerFire_v[i - 4], *playerFire_v[i - 3], *playerFire_v[i - 2], *playerFire_v[i - 1] };
				playerFire_m.push_back(new Mesh(temp_v4, 4));

				playerFire_m[playerFire_m.size() - 4]->Buffer();
				playerFire_m[playerFire_m.size() - 3]->Buffer();
				playerFire_m[playerFire_m.size() - 2]->Buffer();
				playerFire_m[playerFire_m.size() - 1]->Buffer();
			}
		}

		if (key == AVOID && action == GLFW_PRESS)
		{
			if(player1.getLoops())
				if (avoid1time == 0)
				{
					player1.setInvincible(true);
					player1.subLoop();
					avoid1time = 1.8;
					GLtimer = glfwGetTime();
					std::cout << "AVOID!!!!" << std::endl;
				}
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

	/* IF THEY ARE INITIALIZED */
	if(UP && DOWN && LEFT && RIGHT && FIRE && AVOID && PAUSE)std::cout << "Configuration file loaded successfully." << std::endl;
	else
	{
		
		std::cout << "Default configuration loaded, something is wrong with config file." << std::endl;
	}
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