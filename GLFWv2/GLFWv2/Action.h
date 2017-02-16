#pragma once
#include <vector>
#include <GLFW/glfw3.h>
#include "Mesh.h"
#define base_points 50
#define small_points 100
#define medium_points 1000
#define big_points 1500

unsigned int pow_counter = 0;
unsigned int big_counter = 20;
unsigned int med_counter = 12;
bool pow_done = false;
bool ofa1_done = false;
bool jet_done = false;
bool big_air_done = false;
bool small_grey_done = false;
bool medium_done = false;

Vertex big_airship_v[] = { 
	Vertex(glm::vec3(-0.9, -1, 0.0), glm::vec2(0.0, 1.0)),		// 0.0, 1.0  Top Left
	Vertex(glm::vec3(-0.5, -1, 0.0), glm::vec2(1.0, 1.0)),		// 1.0, 1.0  Top Right
	Vertex(glm::vec3(-0.5, -1.4, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
	Vertex(glm::vec3(-0.9, -1.4, 0.0), glm::vec2(0.0, 0.0))		// 0.0, 0.0  Bottom Left 
};  

Vertex pow_plane_v1[] = {
	Vertex(glm::vec3(-1.15, 0.9, 0.0), glm::vec2(0.0, 1.0)),
	Vertex(glm::vec3(-1.00, 0.9, 0.0), glm::vec2(1.0, 1.0)),
	Vertex(glm::vec3(-1.00, 0.75, 0.0), glm::vec2(1.0, 0.0)),
	Vertex(glm::vec3(-1.15, 0.75, 0.0), glm::vec2(0.0, 0.0))
};
Vertex pow_plane_v2[] = {
	Vertex(glm::vec3(-1.40, 0.9, 0.0), glm::vec2(0.0, 1.0)),
	Vertex(glm::vec3(-1.25, 0.9, 0.0), glm::vec2(1.0, 1.0)),
	Vertex(glm::vec3(-1.25, 0.75, 0.0), glm::vec2(1.0, 0.0)),
	Vertex(glm::vec3(-1.40, 0.75, 0.0), glm::vec2(0.0, 0.0))
};
Vertex pow_plane_v3[] = {
	Vertex(glm::vec3(-1.65, 0.9, 0.0), glm::vec2(0.0, 1.0)),
	Vertex(glm::vec3(-1.50, 0.9, 0.0), glm::vec2(1.0, 1.0)),
	Vertex(glm::vec3(-1.50, 0.75, 0.0), glm::vec2(1.0, 0.0)),
	Vertex(glm::vec3(-1.65, 0.75, 0.0), glm::vec2(0.0, 0.0))
};
Vertex pow_plane_v4[] = {
	Vertex(glm::vec3(-1.90, 0.9, 0.0), glm::vec2(0.0, 1.0)),
	Vertex(glm::vec3(-1.75, 0.9, 0.0), glm::vec2(1.0, 1.0)),
	Vertex(glm::vec3(-1.75, 0.75, 0.0), glm::vec2(1.0, 0.0)),
	Vertex(glm::vec3(-1.90, 0.75, 0.0), glm::vec2(0.0, 0.0))
};
Vertex pow_plane_v5[] = {
	Vertex(glm::vec3(-2.15, 0.9, 0.0), glm::vec2(0.0, 1.0)),
	Vertex(glm::vec3(-2.00, 0.9, 0.0), glm::vec2(1.0, 1.0)),
	Vertex(glm::vec3(-2.00, 0.75, 0.0), glm::vec2(1.0, 0.0)),
	Vertex(glm::vec3(-2.15, 0.75, 0.0), glm::vec2(0.0, 0.0))
};

Vertex ofa_plane_v[] = {
	Vertex(glm::vec3(-1.0, 1.0, 0.0), glm::vec2(0.0, 1.0)),
	Vertex(glm::vec3(-0.85, 1.0, 0.0), glm::vec2(1.0, 1.0)),
	Vertex(glm::vec3(-0.85, 0.9, 0.0), glm::vec2(1.0, 0.0)),
	Vertex(glm::vec3(-1.0, 0.9, 0.0), glm::vec2(0.0, 0.0))
};

static void initiliaze_random_planes(std::vector<Mesh*>* random_circle_m, int num_of_planes, float* random_circle_x, float* random_circle_y, bool* random_circles, float* random_angle,
	int* random_options, double* random_pos) {


	//Creating and initiliazing planes
	for (int i = 0; i < num_of_planes; i++) {
		double randy = randd(-0.90, 0.85);
		double randx = rand() % 2;
		double randxm;
		if (randx == 0) {
			randx--;
			randxm = randx + 0.15;
		}
		else {
			randxm = randx + 0.15;
		}

		Vertex random_circle_v[] = { Vertex(glm::vec3(randx, randy, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
			Vertex(glm::vec3(randxm, randy, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
			Vertex(glm::vec3(randxm, randy - 0.1, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
			Vertex(glm::vec3(randx, randy - 0.1, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left

		//Add to the vector of meshes
		(*random_circle_m).push_back(new Mesh(random_circle_v, 4));
		(*random_circle_m)[i]->Buffer();

		random_circle_x[i] = 0.0;
		random_circle_y[i] = 0.0;
		random_circles[i] = false;
		random_angle[i] = 0.0;


	}

	//Initializing their "circle" options
	for (int i = 0; i < (*random_circle_m).size(); i++) {
		if ((*random_circle_m)[i]->getPos()[0][0] < 0 && random_options[i] == 0) {
			random_pos[i] = randd(-0.65, 0.5);
			//Left and low side of screen
			if ((*random_circle_m)[i]->getPos()[0][1] < -0.4) {
				random_options[i] = 2;
			}
			else {
				//Left and high side of screen
				random_options[i] = 1;
			}
		}
		else if (random_options[i] == 0) {
			random_pos[i] = randd(-0.5, 0.65);
			//Right and low side of screen
			if ((*random_circle_m)[i]->getPos()[0][1] < -0.4) {
				random_options[i] = 4;
			}
			else {
				//Right and high side of screen
				random_options[i] = 3;
			}
		}
	}
}

static void action(std::vector<Mesh*>* pow_m, float* pow_angle, bool* pow_circle,
	std::vector<Mesh*>* ofa_m, double* ofa_y,
	std::vector<Mesh*>* jet_m, int num_of_jets, float* jet_x, float* jet_y, bool* jet_circles, float* jet_angle, int* jet_options, std::vector<Texture*>* jet_t,
	std::vector<Mesh*>* big_m, double* big_x,
	std::vector<Mesh*>* small_grey_airship_m, int small_grey_num, float* small_grey_airship_x,
	std::vector<Mesh*>* medium_airship_m, double* medium_x, double* medium_y)
{
	if (!medium_done  && glfwGetTime() > 20) 
	{
		medium_done = true;

		Vertex medium_airship_v[] = { Vertex(glm::vec3(-0.9, 1, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
			Vertex(glm::vec3(-0.5, 1, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
			Vertex(glm::vec3(-0.5, 0.75, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
			Vertex(glm::vec3(-0.9, 0.75, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left

		(*medium_airship_m).push_back(new Mesh(medium_airship_v, 4));

		for (int i = 0; i < (*medium_airship_m).size(); i++) {
			medium_x[i] = 0.0;
			medium_y[i] = -0.004;
			(*medium_airship_m)[i]->Buffer();

		}
	}

	if (!small_grey_done && glfwGetTime() > 40)//45) 
	{

		small_grey_done = true;

		//Create as many as small_grey_num indicates
		for (int i = 0; i < small_grey_num; i++) {

			double randx_small = randd(-0.9, 0.85);

			Vertex small_airship_v[] = { Vertex(glm::vec3(randx_small, 1.0, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
				Vertex(glm::vec3(randx_small + 0.15, 1.0, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
				Vertex(glm::vec3(randx_small + 0.15,  0.9, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
				Vertex(glm::vec3(randx_small, 0.9, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left

			(*small_grey_airship_m).push_back(new Mesh(small_airship_v, 4));

		}

		for (int i = 0; i < (*small_grey_airship_m).size(); i++) {
			small_grey_airship_x[i] = 0.0;
			(*small_grey_airship_m)[i]->Buffer();
		}
	}


	if (!big_air_done && glfwGetTime() > 35)
	{
		big_air_done = true;
		//TODO pushback

		Vertex big_airship_v[] = { Vertex(glm::vec3(-0.9, -1, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
			Vertex(glm::vec3(-0.3, -1, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
			Vertex(glm::vec3(-0.3, -1.4, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
			Vertex(glm::vec3(-0.9, -1.4, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left

		(*big_m).push_back(new Mesh(big_airship_v, 4));


		for (int i = 0; i < (*big_m).size(); i++)
		{
			big_x[i] = 0.0;
			(*big_m)[i]->Buffer();
		}
	}



	if (!jet_done && glfwGetTime() > 30) {

		//Initiliazing the textures
		for (int i = 0; i < 6; i++) {
			//std::string arg = "Resources/jet_plane0";
			//sprintf(arg, "%d",i);
			//arg += static_cast<char>(i);

			char arg[50];
			sprintf(arg, "Resources/jet_plane0%d.png", i);

			//itoa(i, arg, 10);
			//arg += ".png";
			std::cout << arg << "\n\n";
			//Texture jet_plane_t(arg);
			(*jet_t).push_back(new Texture(arg));
		}


		//Creating and initiliazing planes
		for (int i = 0; i < num_of_jets; i++) {
			double randx = rand() % 2;
			double randxm;
			if (randx == 0) {
				randx--;
				randxm = randx + 0.1;
			}
			else {
				randxm = randx + 0.1;
			}

			Vertex jet_v[] = { Vertex(glm::vec3(randx, 0.6, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
				Vertex(glm::vec3(randxm, 0.6, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
				Vertex(glm::vec3(randxm, 0.5, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
				Vertex(glm::vec3(randx, 0.5, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left

				
			(*jet_m).push_back(new Mesh(jet_v, 4));

			(*jet_m)[i]->Buffer();
			jet_x[i] = 0.0;
			jet_y[i] = 0.0;
			jet_circles[i] = false;
			jet_angle[i] = 0.0;
			jet_options[i] = 0;
		}
		jet_done = true;
	}

	if (pow_done == false && glfwGetTime() >= 10.0)
	{
		pow_m->push_back(new Mesh(pow_plane_v1, 4));
		(*pow_m)[(*pow_m).size() - 1]->Buffer();
		pow_m->push_back(new Mesh(pow_plane_v2, 4));
		(*pow_m)[(*pow_m).size() - 1]->Buffer();
		pow_m->push_back(new Mesh(pow_plane_v3, 4));
		(*pow_m)[(*pow_m).size() - 1]->Buffer();
		pow_m->push_back(new Mesh(pow_plane_v4, 4));
		(*pow_m)[(*pow_m).size() - 1]->Buffer();
		pow_m->push_back(new Mesh(pow_plane_v5, 4));
		(*pow_m)[(*pow_m).size() - 1]->Buffer();
		pow_done = true;

		for (int i = 0; i < pow_m->size(); i++)
		{
			pow_angle[i] = 0.000000;
			pow_circle[i] = false;
		}

	}
	
	if (ofa1_done == false && glfwGetTime() >= 5.0)
	{
		int count = 5;
		while (--count >= 0)
		{
			int seed = rand() % 5;
			float offx = 0.0;
			float offy = 0.5;
			if (seed == 0)
			{
				offy = 0.4;
				offx = 0.05;
			}
			else if (seed == 1)
			{
				offx = 0.1;
				offy = 0.3;
			}
			else if (seed == 2)
			{
				offx = 0.15;
				offy = 0.2;
			}
			else if (seed == 3)
			{
				offx = 0.2;
				offy = 0.1;
			}
			for (int i = 0; i < 4; i++)
			{
				ofa_plane_v[i].getPos()[0][0] += offx;
				ofa_plane_v[i].getPos()[0][1] += offy;
			}
			ofa_m->push_back(new Mesh(ofa_plane_v, 4));
			(*ofa_m)[(*ofa_m).size() - 1]->Buffer();
		}
		for (int i = 0; i < ofa_m->size(); i++) ofa_y[i] = -enemy_speed;
		ofa1_done = true;
	}
}

static void collision_detection(std::vector<Mesh*>* enemies, Mesh* player, Mesh* player2_m, bool* inCircle, float* angle, Mesh* power_m,
	std::vector<Mesh*>* ofa_m, double* ofa_y,
	std::vector<Mesh*>* big_m, double* big_x,
	std::vector<Mesh*>* medium_m, double* medium_x, double* medium_y,
	std::vector<Mesh*>* small_grey_m, float* small_grey_x,
	std::vector<Mesh*>* jet_m, float* jet_x, float* jet_y, bool* jet_circles, float* jet_angle, int* jet_options,
	std::vector<Mesh*>* random_circle_m, double* random_circle_randx, bool* random_circle_inCircle, float* random_circle_x, float* random_circle_y, float* random_circle_angle, int* random_circle_option)
{
	std::vector<unsigned int> fire_i;
	std::vector<unsigned int> enemy_i;
	std::vector<unsigned int> ofa_i;
	std::vector<unsigned int> big_i;
	std::vector<unsigned int> medium_i;
	std::vector<unsigned int> small_grey_i;
	std::vector<unsigned int> jet_i;
	std::vector<unsigned int> random_circle_i;

	static sf::SoundBuffer die_buffer;
	if (!die_buffer.loadFromFile("Resources/die.ogg"))
	{
		std::cout << "Couldn't load die.wav\n";

	}
	static sf::Sound die_sound;
	die_sound.setBuffer(die_buffer);

	if(pow_ready)
		if ((((player->getPos()[0][0] + player->getPos()[1][0]) / 2) > power_m->getPos()[0][0]) &&
			(((player->getPos()[0][0] + player->getPos()[1][0]) / 2) < power_m->getPos()[1][0]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) > power_m->getPos()[3][1]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) < power_m->getPos()[0][1]))
		{
			pow_counter = 0;
			big_counter = 20;
			med_counter = 12;
			if (powerup_type == quad) player1.setQuadGun();
			pow_ready = false;
		}
	for (int k = 0; k < (*random_circle_m).size(); k++)
	{
		if (!player1.getInvincible() && (((player->getPos()[0][0] + player->getPos()[1][0]) / 2) >(*random_circle_m)[k]->getPos()[0][0]) &&
			(((player->getPos()[0][0] + player->getPos()[1][0]) / 2) < (*random_circle_m)[k]->getPos()[1][0]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) > (*random_circle_m)[k]->getPos()[3][1]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) < (*random_circle_m)[k]->getPos()[0][1]))
		{
			die_sound.play();
			player1.hit();

			pow_counter = 0;
			big_counter = 20;
			med_counter = 12;
			pow_done = false;
			ofa1_done = false;
			jet_done = false;
			medium_done = false;
			small_grey_done = false;
			big_air_done = false;

			if (random_circle_i.size() == 0 || random_circle_i[random_circle_i.size() - 1] != k) random_circle_i.push_back(k);
			explosions_m.push_back(new Mesh(pow_plane_v1, 4));
			explosions_timers.push_back(glfwGetTime());
			for (int j = 0; j < 4; j++)
				explosions_m[explosions_m.size() - 1]->getPos()[j] = (*random_circle_m)[k]->getPos()[j];
			explosions_m[explosions_m.size() - 1]->Buffer();
		}
		if (player2)
		{
			if ((((player2_m->getPos()[0][0] + player2_m->getPos()[1][0]) / 2) >(*random_circle_m)[k]->getPos()[0][0]) &&
				(((player2_m->getPos()[0][0] + player2_m->getPos()[1][0]) / 2) < (*random_circle_m)[k]->getPos()[1][0]) &&
				(((player2_m->getPos()[0][1] + player2_m->getPos()[2][1]) / 2) > (*random_circle_m)[k]->getPos()[3][1]) &&
				(((player2_m->getPos()[0][1] + player2_m->getPos()[2][1]) / 2) < (*random_circle_m)[k]->getPos()[0][1]))
			{
				player2 = false;
				if (random_circle_i.size() == 0 || random_circle_i[jet_i.size() - 1] != k) random_circle_i.push_back(k);
				explosions_m.push_back(new Mesh(pow_plane_v1, 4));
				explosions_timers.push_back(glfwGetTime());
				for (int j = 0; j < 4; j++)
					explosions_m[explosions_m.size() - 1]->getPos()[j] = (*random_circle_m)[k]->getPos()[j];
				explosions_m[explosions_m.size() - 1]->Buffer();
			}
		}
		for (int i = 0; i < playerFire_m.size(); i++)
		{
			if (((playerFire_m[i]->getPos()[0][0] + playerFire_m[i]->getPos()[1][0]) / 2 >(*random_circle_m)[k]->getPos()[3][0]) &&
				((playerFire_m[i]->getPos()[0][0] + playerFire_m[i]->getPos()[1][0]) / 2 < (*random_circle_m)[k]->getPos()[2][0]) &&
				(playerFire_m[i]->getPos()[0][1] > (*random_circle_m)[k]->getPos()[3][1]) &&
				(playerFire_m[i]->getPos()[0][1] < (*random_circle_m)[k]->getPos()[0][1]))
			{
				if (fire_i.size() == 0 || fire_i[fire_i.size() - 1] != i)fire_i.push_back(i);
				if (random_circle_i.size() == 0 || random_circle_i[random_circle_i.size() - 1] != k) random_circle_i.push_back(k);
				explosions_m.push_back(new Mesh(pow_plane_v1, 4));
				explosions_timers.push_back(glfwGetTime());
				for (int j = 0; j < 4; j++)
					explosions_m[explosions_m.size() - 1]->getPos()[j] = (*random_circle_m)[k]->getPos()[j];
				explosions_m[explosions_m.size() - 1]->Buffer();
			}

		}
	}
	for (int k = 0; k < (*jet_m).size(); k++)
	{
		if (!player1.getInvincible() && (((player->getPos()[0][0] + player->getPos()[1][0]) / 2) >(*jet_m)[k]->getPos()[0][0]) &&
			(((player->getPos()[0][0] + player->getPos()[1][0]) / 2) < (*jet_m)[k]->getPos()[1][0]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) > (*jet_m)[k]->getPos()[3][1]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) < (*jet_m)[k]->getPos()[0][1]))
		{
			die_sound.play();
			player1.hit();

			pow_counter = 0;
			big_counter = 20;
			med_counter = 12;
			pow_done = false;
			ofa1_done = false;
			jet_done = false;
			medium_done = false;
			small_grey_done = false;
			big_air_done = false;

			if (jet_i.size() == 0 || jet_i[jet_i.size() - 1] != k) jet_i.push_back(k);
			explosions_m.push_back(new Mesh(pow_plane_v1, 4));
			explosions_timers.push_back(glfwGetTime());
			for (int j = 0; j < 4; j++)
				explosions_m[explosions_m.size() - 1]->getPos()[j] = (*jet_m)[k]->getPos()[j];
			explosions_m[explosions_m.size() - 1]->Buffer();
		}
		if (player2)
		{
			if ((((player2_m->getPos()[0][0] + player2_m->getPos()[1][0]) / 2) >(*jet_m)[k]->getPos()[0][0]) &&
				(((player2_m->getPos()[0][0] + player2_m->getPos()[1][0]) / 2) < (*jet_m)[k]->getPos()[1][0]) &&
				(((player2_m->getPos()[0][1] + player2_m->getPos()[2][1]) / 2) > (*jet_m)[k]->getPos()[3][1]) &&
				(((player2_m->getPos()[0][1] + player2_m->getPos()[2][1]) / 2) < (*jet_m)[k]->getPos()[0][1]))
			{
				player2 = false;
				if (jet_i.size() == 0 || jet_i[jet_i.size() - 1] != k) jet_i.push_back(k);
				explosions_m.push_back(new Mesh(pow_plane_v1, 4));
				explosions_timers.push_back(glfwGetTime());
				for (int j = 0; j < 4; j++)
					explosions_m[explosions_m.size() - 1]->getPos()[j] = (*jet_m)[k]->getPos()[j];
				explosions_m[explosions_m.size() - 1]->Buffer();
			}
		}
		for (int i = 0; i < playerFire_m.size(); i++)
		{
			if (((playerFire_m[i]->getPos()[0][0] + playerFire_m[i]->getPos()[1][0]) / 2 >(*jet_m)[k]->getPos()[3][0]) &&
				((playerFire_m[i]->getPos()[0][0] + playerFire_m[i]->getPos()[1][0]) / 2 < (*jet_m)[k]->getPos()[2][0]) &&
				(playerFire_m[i]->getPos()[0][1] > (*jet_m)[k]->getPos()[3][1]) &&
				(playerFire_m[i]->getPos()[0][1] < (*jet_m)[k]->getPos()[0][1]))
			{
				if (fire_i.size() == 0 || fire_i[fire_i.size() - 1] != i)fire_i.push_back(i);
				if (jet_i.size() == 0 || jet_i[jet_i.size() - 1] != k) jet_i.push_back(k);
				explosions_m.push_back(new Mesh(pow_plane_v1, 4));
				explosions_timers.push_back(glfwGetTime());
				for (int j = 0; j < 4; j++)
					explosions_m[explosions_m.size() - 1]->getPos()[j] = (*jet_m)[k]->getPos()[j];
				explosions_m[explosions_m.size() - 1]->Buffer();
			}

		}
	}
	for (int k = 0; k < (*small_grey_m).size(); k++)
	{
		if (!player1.getInvincible() && (((player->getPos()[0][0] + player->getPos()[1][0]) / 2) > (*small_grey_m)[k]->getPos()[0][0]) &&
			(((player->getPos()[0][0] + player->getPos()[1][0]) / 2) < (*small_grey_m)[k]->getPos()[1][0]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) > (*small_grey_m)[k]->getPos()[3][1]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) < (*small_grey_m)[k]->getPos()[0][1]))
		{
			die_sound.play();
			player1.hit();

			pow_counter = 0;
			big_counter = 20;
			med_counter = 12;
			pow_done = false;
			ofa1_done = false;
			jet_done = false;
			medium_done = false;
			small_grey_done = false;
			big_air_done = false;

			if (small_grey_i.size() == 0 || small_grey_i[small_grey_i.size() - 1] != k) small_grey_i.push_back(k);
			explosions_m.push_back(new Mesh(pow_plane_v1, 4));
			explosions_timers.push_back(glfwGetTime());
			for (int j = 0; j < 4; j++)
				explosions_m[explosions_m.size() - 1]->getPos()[j] = (*small_grey_m)[k]->getPos()[j];
			explosions_m[explosions_m.size() - 1]->Buffer();
		}
		if (player2)
		{
			if ((((player2_m->getPos()[0][0] + player2_m->getPos()[1][0]) / 2) > (*small_grey_m)[k]->getPos()[0][0]) &&
				(((player2_m->getPos()[0][0] + player2_m->getPos()[1][0]) / 2) < (*small_grey_m)[k]->getPos()[1][0]) &&
				(((player2_m->getPos()[0][1] + player2_m->getPos()[2][1]) / 2) > (*small_grey_m)[k]->getPos()[3][1]) &&
				(((player2_m->getPos()[0][1] + player2_m->getPos()[2][1]) / 2) < (*small_grey_m)[k]->getPos()[0][1]))
			{
				player2 = false;
				if (small_grey_i.size() == 0 || small_grey_i[small_grey_i.size() - 1] != k) small_grey_i.push_back(k);
				explosions_m.push_back(new Mesh(pow_plane_v1, 4));
				explosions_timers.push_back(glfwGetTime());
				for (int j = 0; j < 4; j++)
					explosions_m[explosions_m.size() - 1]->getPos()[j] = (*small_grey_m)[k]->getPos()[j];
				explosions_m[explosions_m.size() - 1]->Buffer();
			}
		}
		for (int i = 0; i < playerFire_m.size(); i++)
		{
			if (((playerFire_m[i]->getPos()[0][0] + playerFire_m[i]->getPos()[1][0]) / 2 >(*small_grey_m)[k]->getPos()[3][0]) &&
				((playerFire_m[i]->getPos()[0][0] + playerFire_m[i]->getPos()[1][0]) / 2 < (*small_grey_m)[k]->getPos()[2][0]) &&
				(playerFire_m[i]->getPos()[0][1] > (*small_grey_m)[k]->getPos()[3][1]) &&
				(playerFire_m[i]->getPos()[0][1] < (*small_grey_m)[k]->getPos()[0][1]))
			{
				if (fire_i.size() == 0 || fire_i[fire_i.size() - 1] != i)fire_i.push_back(i);
				if (small_grey_i.size() == 0 || small_grey_i[small_grey_i.size() - 1] != k) small_grey_i.push_back(k);
				explosions_m.push_back(new Mesh(pow_plane_v1, 4));
				explosions_timers.push_back(glfwGetTime());
				for (int j = 0; j < 4; j++)
					explosions_m[explosions_m.size() - 1]->getPos()[j] = (*small_grey_m)[k]->getPos()[j];
				explosions_m[explosions_m.size() - 1]->Buffer();
			}

		}
	}
	for (int k = 0; k < (*medium_m).size(); k++)
	{
		if (!player1.getInvincible() && (((player->getPos()[0][0] + player->getPos()[1][0]) / 2) >(*medium_m)[k]->getPos()[0][0]) &&
			(((player->getPos()[0][0] + player->getPos()[1][0]) / 2) < (*medium_m)[k]->getPos()[1][0]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) > (*medium_m)[k]->getPos()[3][1]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) < (*medium_m)[k]->getPos()[0][1]))
		{
			die_sound.play();
			player1.hit();

			pow_counter = 0;
			big_counter = 20;
			med_counter = 12;
			pow_done = false;
			ofa1_done = false;
			jet_done = false;
			medium_done = false;
			small_grey_done = false;
			big_air_done = false;

			if (medium_i.size() == 0 || medium_i[medium_i.size() - 1] != k) medium_i.push_back(k);
			explosions_m.push_back(new Mesh(pow_plane_v1, 4));
			explosions_timers.push_back(glfwGetTime());
			for (int j = 0; j < 4; j++)
				explosions_m[explosions_m.size() - 1]->getPos()[j] = (*medium_m)[k]->getPos()[j];
			explosions_m[explosions_m.size() - 1]->Buffer();
		}
		if (player2)
		{
			if ((((player2_m->getPos()[0][0] + player2_m->getPos()[1][0]) / 2) >(*medium_m)[k]->getPos()[0][0]) &&
				(((player2_m->getPos()[0][0] + player2_m->getPos()[1][0]) / 2) < (*medium_m)[k]->getPos()[1][0]) &&
				(((player2_m->getPos()[0][1] + player2_m->getPos()[2][1]) / 2) > (*medium_m)[k]->getPos()[3][1]) &&
				(((player2_m->getPos()[0][1] + player2_m->getPos()[2][1]) / 2) < (*medium_m)[k]->getPos()[0][1]))
			{
				player2 = false;
				if (medium_i.size() == 0 || medium_i[medium_i.size() - 1] != k) medium_i.push_back(k);
				explosions_m.push_back(new Mesh(pow_plane_v1, 4));
				explosions_timers.push_back(glfwGetTime());
				for (int j = 0; j < 4; j++)
					explosions_m[explosions_m.size() - 1]->getPos()[j] = (*medium_m)[k]->getPos()[j];
				explosions_m[explosions_m.size() - 1]->Buffer();
			}
		}
		for (int i = 0; i < playerFire_m.size(); i++)
		{
			if (((playerFire_m[i]->getPos()[0][0] + playerFire_m[i]->getPos()[1][0]) / 2 >(*medium_m)[k]->getPos()[3][0]) &&
				((playerFire_m[i]->getPos()[0][0] + playerFire_m[i]->getPos()[1][0]) / 2 < (*medium_m)[k]->getPos()[2][0]) &&
				(playerFire_m[i]->getPos()[0][1] > (*medium_m)[k]->getPos()[3][1]) &&
				(playerFire_m[i]->getPos()[0][1] < (*medium_m)[k]->getPos()[0][1]))
			{
				
				if (fire_i.size() == 0 || fire_i[fire_i.size() - 1] != i)fire_i.push_back(i);
				if (med_counter) med_counter--;
				else
				{
					if (medium_i.size() == 0 || medium_i[medium_i.size() - 1] != k) medium_i.push_back(k);
					explosions_m.push_back(new Mesh(pow_plane_v1, 4));
					explosions_timers.push_back(glfwGetTime());
					for (int j = 0; j < 4; j++)
						explosions_m[explosions_m.size() - 1]->getPos()[j] = (*medium_m)[k]->getPos()[j];
					explosions_m[explosions_m.size() - 1]->Buffer();
				}
			}

		}
	}
	for (int k = 0; k < (*big_m).size(); k++)
	{
		if (!player1.getInvincible() && (((player->getPos()[0][0] + player->getPos()[1][0]) / 2) >(*big_m)[k]->getPos()[0][0]) &&
			(((player->getPos()[0][0] + player->getPos()[1][0]) / 2) < (*big_m)[k]->getPos()[1][0]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) > (*big_m)[k]->getPos()[3][1]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) < (*big_m)[k]->getPos()[0][1]))
		{
			die_sound.play();
			player1.hit();
			
			pow_counter = 0;
			big_counter = 20;
			med_counter = 12;
			pow_done = false;
			ofa1_done = false;
			jet_done = false;
			medium_done = false;
			small_grey_done = false;
			big_air_done = false;
			
			if (big_i.size() == 0 || big_i[big_i.size() - 1] != k) big_i.push_back(k);
			explosions_m.push_back(new Mesh(pow_plane_v1, 4));
			explosions_timers.push_back(glfwGetTime());
			for (int j = 0; j < 4; j++)
				explosions_m[explosions_m.size() - 1]->getPos()[j] = (*big_m)[k]->getPos()[j];
			explosions_m[explosions_m.size() - 1]->Buffer();
		}
		if (player2)
		{
			if ((((player2_m->getPos()[0][0] + player2_m->getPos()[1][0]) / 2) >(*big_m)[k]->getPos()[0][0]) &&
				(((player2_m->getPos()[0][0] + player2_m->getPos()[1][0]) / 2) < (*big_m)[k]->getPos()[1][0]) &&
				(((player2_m->getPos()[0][1] + player2_m->getPos()[2][1]) / 2) > (*big_m)[k]->getPos()[3][1]) &&
				(((player2_m->getPos()[0][1] + player2_m->getPos()[2][1]) / 2) < (*big_m)[k]->getPos()[0][1]))
			{
				player2 = false;
				if (big_i.size() == 0 || big_i[big_i.size() - 1] != k) big_i.push_back(k);
				explosions_m.push_back(new Mesh(pow_plane_v1, 4));
				explosions_timers.push_back(glfwGetTime());
				for (int j = 0; j < 4; j++)
					explosions_m[explosions_m.size() - 1]->getPos()[j] = (*big_m)[k]->getPos()[j];
				explosions_m[explosions_m.size() - 1]->Buffer();
			}
		}
		for (int i = 0; i < playerFire_m.size(); i++)
		{
			if (((playerFire_m[i]->getPos()[0][0] + playerFire_m[i]->getPos()[1][0]) / 2 >(*big_m)[k]->getPos()[3][0]) &&
				((playerFire_m[i]->getPos()[0][0] + playerFire_m[i]->getPos()[1][0]) / 2 < (*big_m)[k]->getPos()[2][0]) &&
				(playerFire_m[i]->getPos()[0][1] > (*big_m)[k]->getPos()[3][1]) &&
				(playerFire_m[i]->getPos()[0][1] < (*big_m)[k]->getPos()[0][1]))
			{
				if (fire_i.size() == 0 || fire_i[fire_i.size() - 1] != i)fire_i.push_back(i);
				if (big_counter) big_counter--;
				else 
				{
					if (big_i.size() == 0 || big_i[big_i.size() - 1] != k) big_i.push_back(k);
					explosions_m.push_back(new Mesh(pow_plane_v1, 4));
					explosions_timers.push_back(glfwGetTime());
					for (int j = 0; j < 4; j++)
						explosions_m[explosions_m.size() - 1]->getPos()[j] = (*big_m)[k]->getPos()[j];
					explosions_m[explosions_m.size() - 1]->Buffer();
				}
			}

		}
	}
	for (int k = 0; k < (*enemies).size(); k++)
	{
		if (!player1.getInvincible() && (((player->getPos()[0][0] + player->getPos()[1][0]) / 2) >(*enemies)[k]->getPos()[0][0]) &&
			(((player->getPos()[0][0] + player->getPos()[1][0]) / 2) < (*enemies)[k]->getPos()[1][0]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) > (*enemies)[k]->getPos()[3][1]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) < (*enemies)[k]->getPos()[0][1]))
		{
			die_sound.play();
			player1.hit();
			pow_counter = 0;
			big_counter = 20;
			med_counter = 12;
			pow_done = false;
			ofa1_done = false;
			jet_done = false;
			medium_done = false;
			small_grey_done = false;
			big_air_done = false;
			if (enemy_i.size() == 0 || enemy_i[enemy_i.size() - 1] != k) enemy_i.push_back(k);
			explosions_m.push_back(new Mesh(pow_plane_v1, 4));
			explosions_timers.push_back(glfwGetTime());
			for (int j = 0; j < 4; j++)
				explosions_m[explosions_m.size() - 1]->getPos()[j] = (*enemies)[k]->getPos()[j];
			explosions_m[explosions_m.size() - 1]->Buffer();
		}
		if (player2)
		{
			if ((((player2_m->getPos()[0][0] + player2_m->getPos()[1][0]) / 2) >(*enemies)[k]->getPos()[0][0]) &&
				(((player2_m->getPos()[0][0] + player2_m->getPos()[1][0]) / 2) < (*enemies)[k]->getPos()[1][0]) &&
				(((player2_m->getPos()[0][1] + player2_m->getPos()[2][1]) / 2) > (*enemies)[k]->getPos()[3][1]) &&
				(((player2_m->getPos()[0][1] + player2_m->getPos()[2][1]) / 2) < (*enemies)[k]->getPos()[0][1]))
			{
				player2 = false;
				if (enemy_i.size() == 0 || enemy_i[enemy_i.size() - 1] != k) enemy_i.push_back(k);
				explosions_m.push_back(new Mesh(pow_plane_v1, 4));
				explosions_timers.push_back(glfwGetTime());
				for (int j = 0; j < 4; j++)
					explosions_m[explosions_m.size() - 1]->getPos()[j] = (*enemies)[k]->getPos()[j];
				explosions_m[explosions_m.size() - 1]->Buffer();
			}
		}
		for (int i = 0; i < playerFire_m.size(); i++)
		{
			if (((playerFire_m[i]->getPos()[0][0] + playerFire_m[i]->getPos()[1][0]) / 2 >(*enemies)[k]->getPos()[3][0]) &&
				((playerFire_m[i]->getPos()[0][0] + playerFire_m[i]->getPos()[1][0]) / 2 < (*enemies)[k]->getPos()[2][0]) &&
				(playerFire_m[i]->getPos()[0][1] > (*enemies)[k]->getPos()[3][1]) &&
				(playerFire_m[i]->getPos()[0][1] < (*enemies)[k]->getPos()[0][1]))
			{
				if(fire_i.size() == 0 || fire_i[fire_i.size() - 1] != i)fire_i.push_back(i);
				if(enemy_i.size() == 0 || enemy_i[enemy_i.size() - 1] != k) enemy_i.push_back(k);
				explosions_m.push_back(new Mesh(pow_plane_v1, 4));
				explosions_timers.push_back(glfwGetTime());
				for (int j = 0; j < 4; j++)
					explosions_m[explosions_m.size() - 1]->getPos()[j] = (*enemies)[k]->getPos()[j];
				explosions_m[explosions_m.size() - 1]->Buffer();
			}

		}
	}
	for (int k = 0; k < ofa_m->size(); k++)
	{
		if (!player1.getInvincible() && (((player->getPos()[0][0] + player->getPos()[1][0]) / 2) >(*ofa_m)[k]->getPos()[0][0]) &&
			(((player->getPos()[0][0] + player->getPos()[1][0]) / 2) < (*ofa_m)[k]->getPos()[1][0]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) > (*ofa_m)[k]->getPos()[3][1]) &&
			(((player->getPos()[0][1] + player->getPos()[2][1]) / 2) < (*ofa_m)[k]->getPos()[0][1]))
		{
			die_sound.play();
			player1.hit();
			pow_counter = 0;
			big_counter = 20;
			med_counter = 12;
			pow_done = false;
			ofa1_done = false;
			jet_done = false;
			medium_done = false;
			small_grey_done = false;
			big_air_done = false;
			if (ofa_i.size() == 0 || ofa_i[ofa_i.size() - 1] != k) ofa_i.push_back(k);
			explosions_m.push_back(new Mesh(pow_plane_v1, 4));
			explosions_timers.push_back(glfwGetTime());
			for (int j = 0; j < 4; j++)
				explosions_m[explosions_m.size() - 1]->getPos()[j] = (*ofa_m)[k]->getPos()[j];
			explosions_m[explosions_m.size() - 1]->Buffer();
		}
		if (player2)
		{
			if ((((player2_m->getPos()[0][0] + player2_m->getPos()[1][0]) / 2) >(*ofa_m)[k]->getPos()[0][0]) &&
				(((player2_m->getPos()[0][0] + player2_m->getPos()[1][0]) / 2) < (*ofa_m)[k]->getPos()[1][0]) &&
				(((player2_m->getPos()[0][1] + player2_m->getPos()[2][1]) / 2) > (*ofa_m)[k]->getPos()[3][1]) &&
				(((player2_m->getPos()[0][1] + player2_m->getPos()[2][1]) / 2) < (*ofa_m)[k]->getPos()[0][1]))
			{
				player2 = false;
				if (ofa_i.size() == 0 || ofa_i[ofa_i.size() - 1] != k) ofa_i.push_back(k);
				explosions_m.push_back(new Mesh(pow_plane_v1, 4));
				explosions_timers.push_back(glfwGetTime());
				for (int j = 0; j < 4; j++)
					explosions_m[explosions_m.size() - 1]->getPos()[j] = (*enemies)[k]->getPos()[j];
				explosions_m[explosions_m.size() - 1]->Buffer();
			}
		}
		for (int i = 0; i < playerFire_m.size(); i++)
		{
			if (((playerFire_m[i]->getPos()[0][0] + playerFire_m[i]->getPos()[1][0]) / 2 >(*ofa_m)[k]->getPos()[3][0]) &&
				((playerFire_m[i]->getPos()[0][0] + playerFire_m[i]->getPos()[1][0]) / 2 < (*ofa_m)[k]->getPos()[2][0]) &&
				(playerFire_m[i]->getPos()[0][1] > (*ofa_m)[k]->getPos()[3][1]) &&
				(playerFire_m[i]->getPos()[0][1] < (*ofa_m)[k]->getPos()[0][1]))
			{
				fire_i.push_back(i);
				if (ofa_i.size() == 0 || ofa_i[ofa_i.size() - 1] != k) ofa_i.push_back(k);
				explosions_m.push_back(new Mesh(pow_plane_v1, 4));
				explosions_timers.push_back(glfwGetTime());
				for (int j = 0; j < 4; j++)
					explosions_m[explosions_m.size() - 1]->getPos()[j] = (*ofa_m)[k]->getPos()[j];
				explosions_m[explosions_m.size() - 1]->Buffer();
			}
		}

	}
	std::sort(fire_i.begin(), fire_i.end());
	std::sort(enemy_i.begin(), enemy_i.end());
	std::sort(ofa_i.begin(), ofa_i.end());
	std::sort(big_i.begin(), big_i.end());
	std::sort(medium_i.begin(), medium_i.end());
	std::sort(small_grey_i.begin(), small_grey_i.end());
	fire_i.erase(std::unique(fire_i.begin(), fire_i.end()), fire_i.end());
	int i = fire_i.size();
	while (--i >= 0)
	{
		playerFire_m[fire_i[i]]->UnBuffer();
		playerFire_m[fire_i[i]]->~Mesh();
		playerFire_m.erase(playerFire_m.begin() + fire_i[i]);
	}
	i = enemy_i.size();
	// need to fix inCircle and angle
	while (--i >= 0)
	{
		// only for pow
		for (int j = enemy_i[i]; j < 4; j++)
		{
				inCircle[j] = inCircle[j + 1];
				angle[j] = angle[j + 1];
		}
		score += base_points;
		pow_counter++;
		if (pow_counter == 5) pow_ready = true;
		(*enemies)[enemy_i[i]]->UnBuffer();
		(*enemies)[enemy_i[i]]->~Mesh();
		(*enemies).erase((*enemies).begin() + enemy_i[i]);
	}
	i = ofa_i.size();
	while (--i >= 0)
	{
		score += base_points;
		for (int j = ofa_i[i]; j < ofa_m->size() - 1; j++)
			ofa_y[j] = ofa_y[j + 1];
		(*ofa_m)[ofa_i[i]]->UnBuffer();
		(*ofa_m)[ofa_i[i]]->~Mesh();
		(*ofa_m).erase((*ofa_m).begin() + ofa_i[i]);
	}
	i = big_i.size();
	while (--i >= 0)
	{
		score += big_points;
		for (int j = big_i[i]; j < big_m->size() - 1; j++)
			big_x[j] = big_x[j + 1];
		(*big_m)[big_i[i]]->UnBuffer();
		(*big_m)[big_i[i]]->~Mesh();
		(*big_m).erase((*big_m).begin() + big_i[i]);
	}
	i = medium_i.size();
	while(--i >= 0)
	{
		score += medium_points;
		for (int j = medium_i[i]; j < medium_m->size() - 1; j++)
		{
			medium_x[j] = medium_x[j + 1];
			medium_y[j] = medium_y[j + 1];
		}
		(*medium_m)[medium_i[i]]->UnBuffer();
		(*medium_m)[medium_i[i]]->~Mesh();
		(*medium_m).erase((*medium_m).begin() + medium_i[i]);
	}
	i = small_grey_i.size();
	while (--i >= 0)
	{
		score += small_points;
		for (int j = small_grey_i[i]; j < small_grey_m->size() - 1; j++)
			small_grey_x[j] = small_grey_x[j + 1];

		(*small_grey_m)[small_grey_i[i]]->UnBuffer();
		(*small_grey_m)[small_grey_i[i]]->~Mesh();
		(*small_grey_m).erase((*small_grey_m).begin() + small_grey_i[i]);
	}
	i = jet_i.size();
	while (--i >= 0)
	{
		score += small_points;
		for (int j = jet_i[i]; j < jet_m->size() - 1; j++)
		{
			jet_angle[j] = jet_angle[j + 1];
			jet_circles[j] = jet_circles[j + 1];
			jet_options[j] = jet_options[j + 1];
			jet_x[j] = jet_x[j + 1];
			jet_y[j] = jet_y[j + 1];
		}

		(*jet_m)[jet_i[i]]->UnBuffer();
		(*jet_m)[jet_i[i]]->~Mesh();
		(*jet_m).erase((*jet_m).begin() + jet_i[i]);
	}
	i = random_circle_i.size();
	while (--i >= 0)
	{
		score += small_points;
		for (int j = random_circle_i[i]; j < random_circle_m->size() - 1; j++)
		{
			random_circle_angle[j] = random_circle_angle[j + 1];
			random_circle_inCircle[j] = random_circle_inCircle[j + 1];
			random_circle_option[j] = random_circle_option[j + 1];
			random_circle_randx[j] = random_circle_randx[j + 1];
			random_circle_x[j] = random_circle_x[j + 1];
			random_circle_y[j] = random_circle_y[j + 1];
		}

		(*random_circle_m)[random_circle_i[i]]->UnBuffer();
		(*random_circle_m)[random_circle_i[i]]->~Mesh();
		(*random_circle_m).erase((*random_circle_m).begin() + random_circle_i[i]);
	}
	fire_i.clear();
	enemy_i.clear();
	ofa_i.clear();
}