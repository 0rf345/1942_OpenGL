#pragma once
#include "Globals.h"
#include <vector>
#define TWO_PI 6.28318

static double randd(double low, double high) {
	return low + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (high - low)));
	//return (rand() / (double)(RAND_MAX))*abs(low - high) + low;
}


static void scrollBackGround(Vertex* background_v, Mesh* background_m)
{
	background_m->getPos()[0][1] -= offsetBG;
	background_m->getPos()[1][1] -= offsetBG;
	background_m->getPos()[2][1] -= offsetBG;
	background_m->getPos()[3][1] -= offsetBG;

	glBindBuffer(GL_ARRAY_BUFFER, background_m->getVBpos());
	glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(background_m->getPos()[0]), &background_m->getPos()[0]);
}


static void scrollBullets()
{
	if (playerFire_m.size() > 0)
	{
		for (int i = 0; i < playerFire_m.size(); i ++)
		{
			glBindBuffer(GL_ARRAY_BUFFER, playerFire_m[i]->getVBpos());

			playerFire_m[i]->getPos()[0][1] += offsetFire;
			playerFire_m[i]->getPos()[1][1] += offsetFire;
			playerFire_m[i]->getPos()[2][1] += offsetFire;
			playerFire_m[i]->getPos()[3][1] += offsetFire;

			glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(playerFire_m[i]->getPos()[0]), &playerFire_m[i]->getPos()[0]);
		}
	}
}

static void explosions(Texture** expl_t)
{
	for (int i = 0; i < explosions_m.size(); i++)
	{
		if (glfwGetTime() - explosions_timers[i] < 0.1) expl_t[0]->Bind(0);
		else if (glfwGetTime() - explosions_timers[i] < 0.2) expl_t[1]->Bind(0);
		else if (glfwGetTime() - explosions_timers[i] < 0.3) expl_t[2]->Bind(0);
		else if (glfwGetTime() - explosions_timers[i] < 0.4) expl_t[3]->Bind(0);
		else if (glfwGetTime() - explosions_timers[i] < 0.5) expl_t[4]->Bind(0);
		else if (glfwGetTime() - explosions_timers[i] < 0.6) expl_t[5]->Bind(0);
		explosions_m[i]->Draw();

		for (int k = 0; k < 4; k++) explosions_m[i]->getPos()[k][1] -= offsetBG;
		glBindBuffer(GL_ARRAY_BUFFER, explosions_m[i]->getVBpos());
		glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(explosions_m[i]->getPos()[0]), &explosions_m[i]->getPos()[0]);
	}
	int i = explosions_m.size();
	while (--i >= 0)
	{
		if (glfwGetTime() - explosions_timers[i] > 0.57)
		{
			explosions_timers.erase(explosions_timers.begin() + i);
			explosions_m[i]->UnBuffer();
			explosions_m[i]->~Mesh();
			explosions_m.erase(explosions_m.begin() + i);
		}
	}
}

static void destroyBullets()
{
	int i = playerFire_m.size();
	if (i > 0)
	{
		i--;
		while(i >= 0)//for (std::vector<Mesh*>::iterator it = playerFire_m.end(); ; it--)
		{
			if (playerFire_m[i]->getPos()[3][1] > 1.1)
			{
				playerFire_m[i]->UnBuffer();
				playerFire_m[i]->~Mesh();
				playerFire_m.erase(playerFire_m.begin() + i);
			}
			i--;
			if (i < 0) break;
		}
	}
}





static void movaOfaAirship(std::vector<Mesh*> mesh, Mesh* player1_m, Texture** texture, double* speed)
{
	float x = 0.005;
	for (int i = 0; i < mesh.size(); i++)
	{
		if ((mesh[i]->getPos()[3][1] - 0.0008 < player1_m->getPos()[0][1] && 
			mesh[i]->getPos()[3][0] + 0.2 > player1_m->getPos()[0][0]) ||
			mesh[i]->getPos()[3][1] < -0.9) speed[i] = enemy_speed;

		if(speed[i] < 0.0)texture[0]->Bind(0);
		else texture[1]->Bind(0);

		mesh[i]->getPos()[0][0] += x;
		mesh[i]->getPos()[0][1] += speed[i];
		mesh[i]->getPos()[1][0] += x;
		mesh[i]->getPos()[1][1] += speed[i];
		mesh[i]->getPos()[2][0] += x;
		mesh[i]->getPos()[2][1] += speed[i];
		mesh[i]->getPos()[3][0] += x;
		mesh[i]->getPos()[3][1] += speed[i];


		glBindBuffer(GL_ARRAY_BUFFER, mesh[i]->getVBpos());
		glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(mesh[i]->getPos()[0]), &mesh[i]->getPos()[0]);

		mesh[i]->Draw();
	}
}

static void updatePos(Mesh* mesh, double x, double y)
{
	mesh->getPos()[0][0] += x;
	mesh->getPos()[0][1] += y;
	mesh->getPos()[1][0] += x;
	mesh->getPos()[1][1] += y;
	mesh->getPos()[2][0] += x;
	mesh->getPos()[2][1] += y;
	mesh->getPos()[3][0] += x;
	mesh->getPos()[3][1] += y;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->getVBpos());
	glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(mesh->getPos()[0]), &mesh->getPos()[0]);
}

static bool circleAnimation(Mesh* airplane_m, double multiply, float loops, float* angle, int option)
{
	double x;
	double y;
	double mulx = 0.015;
	double muly = 0.011;
	static double time = glfwGetTime();

	//Doing the appropriate circle
	switch (option) {
		//Option one is circle going clockwise
	case 1: mulx = 0.015;
		muly = -0.011;
		break;
		//Option two is circle going left to right and up to down
	case 2: mulx = 0.015;
		muly = 0.011;
		break;
		//Option three is circle going anti-clockwise
	case 3: mulx = -0.015;
		muly = -0.011;
		break;
		//Option four is circle going right to left and up to down
	case 4: mulx = -0.015;
		muly = 0.011;
		break;
	default: std::cout << "Not a legal argument.\n";
		break;
	}

	if (*angle < loops*TWO_PI) {
		x = (cos(*angle))*mulx * multiply;
		y = sin(*angle) *muly * multiply;
		time = glfwGetTime();
		updatePos(airplane_m, x, y);
		*angle += 0.1;
		return true;
	}
	else {
		return false;
	}

}



static void randomCircleAnimation(std::vector<Mesh*> random_circle_m, Texture* random_circle_t, double* randx, bool* inCircle, float* x, float* y, float* angle, int* option)
{

	for (int i = 0; i < random_circle_m.size(); i++) {

		//Coming from left side of screen
		if (option[i] == 1 && y[i] == 0.0) {
			x[i] = 0.005;

			//At some random point 
			if (random_circle_m[i]->getPos()[1][0] > randx[i] || inCircle[i]) {
				inCircle[i] = circleAnimation(random_circle_m[i], 2.3, 1.24, &angle[i], option[i]);

				if (!inCircle[i]) {
					y[i] = -0.005;
				}
			}
		}
		else if (option[i] == 2 && y[i] == 0.0) {
			x[i] = 0.005;
			//At some random point 
			if (random_circle_m[i]->getPos()[1][0] > randx[i] || inCircle[i]) {
				inCircle[i] = circleAnimation(random_circle_m[i], 2.3, 0.75, &angle[i], option[i]);

				if (!inCircle[i]) {
					y[i] = -0.005;
					x[i] = -0.004;
				}
			}
		}
		//Coming from right side of screen
		else if (option[i] == 3 && y[i] == 0.0) {
			x[i] = -0.005;
			//At some random point 
			if (random_circle_m[i]->getPos()[1][0] < randx[i] || inCircle[i]) {
				inCircle[i] = circleAnimation(random_circle_m[i], 2.3, 1.25, &angle[i], option[i]);
				if (!inCircle[i]) {
					x[i] = -0.0045;
					y[i] = -0.005;
				}
			}
		}
		else if (option[i] == 4 && y[i] == 0.0) {
			//Coming from right side of screen and low
			x[i] = -0.005;
			//At some random point 
			if (random_circle_m[i]->getPos()[1][0] < randx[i] || inCircle[i]) {
				inCircle[i] = circleAnimation(random_circle_m[i], 2.7, 0.9, &angle[i], option[i]);
				if (!inCircle[i]) {
					y[i] = -0.005;
					x[i] = -0.0009;
				}
			}
		}
		else if (option[i] == 0) {
			std::cout << "Illegal argument.\n\n";
		}
		
		if (!inCircle[i]) {
			updatePos(random_circle_m[i], x[i], y[i]);
		}

		random_circle_t->Bind(0);
		random_circle_m[i]->Draw();
	}
}



//std::vector<Mesh*> mesh
static void movePowAirship(std::vector<Mesh*> pow_airship_m, bool* inCircle, Texture** textures, float* angle)
{
	for (int i = 0; i < pow_airship_m.size(); i++)
	{
		//Going right and making two circles
		double x = 0.008;
		double y = 0;
		//std::cout << pow_airship_m[i]->getPos()[2][1] << std::endl;
		//Do first circle
		if ((pow_airship_m[i]->getPos()[2][0] > -0.40 || inCircle[i]) && pow_airship_m[i]->getPos()[2][0] < 0) {
			inCircle[i] = circleAnimation(pow_airship_m[i], 2.8, 1.0, &angle[i], 1);

		}
		// Do second circle
		if (pow_airship_m[i]->getPos()[2][0] > 0.5 || inCircle[i]) {
			inCircle[i] = circleAnimation(pow_airship_m[i], 2.8, 2.0, &angle[i], 1);
		}
		// Move to the right
		if (!inCircle[i]) {
			updatePos(pow_airship_m[i], x, y);

		}

		// Texture Binding
		if (angle[i] <= 0.4) textures[0]->Bind(0);
		else if (angle[i] <= 1.2) textures[1]->Bind(0);
		else if (angle[i] <= 2.0) textures[2]->Bind(0);
		else if (angle[i] <= 2.8) textures[3]->Bind(0);
		else if (angle[i] <= 3.6) textures[4]->Bind(0);
		else if (angle[i] <= 5.2) textures[5]->Bind(0);
		else if (angle[i] <= 5.6) textures[6]->Bind(0);
		else if (angle[i] <= 6.2) textures[7]->Bind(0);
		else if (angle[i] <= 6.6) textures[0]->Bind(0);
		else if (angle[i] <= 7.4) textures[1]->Bind(0);
		else if (angle[i] <= 8.2) textures[2]->Bind(0);
		else if (angle[i] <= 9.0) textures[3]->Bind(0);
		else if (angle[i] <= 9.8) textures[4]->Bind(0);
		else if (angle[i] <= 11.4) textures[5]->Bind(0);
		else if (angle[i] <= 11.8) textures[6]->Bind(0);
		else if (angle[i] <= 12.4) textures[7]->Bind(0);
		else textures[0]->Bind(0);

		pow_airship_m[i]->Draw();
	}
}



static void jetAnimation(std::vector<Mesh*> jet_m, Mesh* super_ace_m, std::vector<Texture*> jet_t, float* x, float* y, bool* inCircle, float* angle, int* option) {

	//For each jet do
	for (int i = 0; i < jet_m.size(); i++) {

		//Does a curve before attacking
		if (jet_m[i]->getPos()[0][0] == -1 || (inCircle[i] && option[i] == 1)) {
			option[i] = 1;
			inCircle[i] = circleAnimation(jet_m[i], 2, 0.25, &angle[i], 1);

		}
		else if (jet_m[i]->getPos()[0][0] == 1 || (inCircle[i] && option[i] == 3)) {
			option[i] = 3;
			inCircle[i] = circleAnimation(jet_m[i], 2, 0.25, &angle[i], 3);
		}

		//Goes downward and ready to attack
		if (!inCircle[i] && y[i] == 0.0) {
			y[i] = -0.005;
		}
		//Attack
		else if (abs(abs(super_ace_m->getPos()[0][1]) - abs(jet_m[i]->getPos()[3][1])) < 0.4 && x[i] == 0.0) {

			if (super_ace_m->getPos()[0][0] < jet_m[i]->getPos()[3][0]
				&& super_ace_m->getPos()[1][0] < jet_m[i]->getPos()[2][0]) {

				x[i] = -0.005;
			}
			else {
				x[i] = 0.005;
			}
		}
		updatePos(jet_m[i], x[i], y[i]);



		// Texture Binding
		if (angle[i] <= 0.7) jet_t[0]->Bind(0);
		else if (angle[i] <= 1.56) jet_t[1]->Bind(0);
		else if (angle[i] <= 2.0) { jet_t[2]->Bind(0); angle[i] = 3.0;  }
		else if (angle[i] == 3.0) {
			jet_t[3]->Bind(0); 
			angle[i] = 4.0;
		}
		else if (angle[i] == 4.0) {
			jet_t[4]->Bind(0);
			angle[i] = 5.0;
		}
		else if (angle[i] == 5.0) {
			jet_t[5]->Bind(0);
			angle[i] = 6.0;
		}
		else if (angle[i] == 6.0) {
			jet_t[4]->Bind(0);
			angle[i] = 3.0;
		}

		jet_m[i]->Draw();
	}
}


static void movePlayer(Mesh* player1_m, Texture** textures)
{
	if (avoid1time == 0.0)
	{
		player1.setInvincible(false);
		textures[0]->Bind(0);
	}
	else
	{
		if (glfwGetTime() - GLtimer >= 0.1)
		{
			if (avoid1time < 0.4) avoid1time = 0.0;
			else avoid1time -= 0.1;
			GLtimer = glfwGetTime();
		}

		if (avoid1time > 1.6) textures[1]->Bind(0);
		else if (avoid1time > 1.2) textures[2]->Bind(0);
		else if (avoid1time > 1.0) textures[3]->Bind(0);
		else if (avoid1time > 0.4) textures[4]->Bind(0);
		else textures[5]->Bind(0);
	}

	player1_m->getPos()[0][0] = -startX1 + x1;
	player1_m->getPos()[0][1] =  startY1 + Y1;
	player1_m->getPos()[1][0] =  startX1 + x1;
	player1_m->getPos()[1][1] =  startY1 + Y1;
	player1_m->getPos()[2][0] =  startX1 + x1;
	player1_m->getPos()[2][1] = -startY1 + Y1;
	player1_m->getPos()[3][0] = -startX1 + x1;
	player1_m->getPos()[3][1] = -startY1 + Y1;
	
	glBindBuffer(GL_ARRAY_BUFFER, player1_m->getVBpos());
	glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(player1_m->getPos()[0]), &player1_m->getPos()[0]);
}

static void animate_Powerup(Mesh* pow_m)
{
	pow_m->getPos()[0][1] -= offsetBG;
	pow_m->getPos()[1][1] -= offsetBG;
	pow_m->getPos()[2][1] -= offsetBG;
	pow_m->getPos()[3][1] -= offsetBG;
	glBindBuffer(GL_ARRAY_BUFFER, pow_m->getVBpos());
	glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(pow_m->getPos()[0]), &pow_m->getPos()[0]);
}

static void updatePowerup(Mesh* power_m, std::vector<Mesh*> pow_m)
{
	if (pow_m.size())
	{
		for (int i = 0; i < 4; i++)
		{
			power_m->getPos()[i][0] = pow_m[0]->getPos()[i][0];
			power_m->getPos()[i][1] = pow_m[0]->getPos()[i][1];
		}
		glBindBuffer(GL_ARRAY_BUFFER, power_m->getVBpos());
		glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(power_m->getPos()[0]), &power_m->getPos()[0]);
	}
}

static void animateMerry(Mesh* merry_m)
{
	double timing = 0;
	if (glfwGetTime() < 32.9 + timing)
	{
		merry_m->getPos()[0][0] -= 0.01;
		merry_m->getPos()[0][1] -= offsetBG;
		merry_m->getPos()[1][0] -= 0.01;
		merry_m->getPos()[1][1] -= offsetBG;
		merry_m->getPos()[2][0] -= 0.01;
		merry_m->getPos()[2][1] -= offsetBG;
		merry_m->getPos()[3][0] -= 0.01;
		merry_m->getPos()[3][1] -= offsetBG;
	}
	else if (glfwGetTime() < 34.0 + timing)
	{
		merry_m->getPos()[0][0] -= 0.007;
		merry_m->getPos()[0][1] -= offsetBG + 0.008;
		merry_m->getPos()[1][0] -= 0.007;
		merry_m->getPos()[1][1] -= offsetBG + 0.008;
		merry_m->getPos()[2][0] -= 0.007;
		merry_m->getPos()[2][1] -= offsetBG + 0.008;
		merry_m->getPos()[3][0] -= 0.007;
		merry_m->getPos()[3][1] -= offsetBG + 0.008;
	}
	else if (glfwGetTime() < 34.2 + timing)
	{
		merry_m->getPos()[0][1] -= offsetBG + 0.008;
		merry_m->getPos()[1][1] -= offsetBG + 0.008;
		merry_m->getPos()[2][1] -= offsetBG + 0.008;
		merry_m->getPos()[3][1] -= offsetBG + 0.008;
	}
	else if (glfwGetTime() < 34.85 + timing)
	{
		merry_m->getPos()[0][0] -= 0.012;
		merry_m->getPos()[0][1] -= offsetBG + 0.0076;
		merry_m->getPos()[1][0] -= 0.012;
		merry_m->getPos()[1][1] -= offsetBG + 0.0076;
		merry_m->getPos()[2][0] -= 0.012;
		merry_m->getPos()[2][1] -= offsetBG + 0.0076;
		merry_m->getPos()[3][0] -= 0.012;
		merry_m->getPos()[3][1] -= offsetBG + 0.0076;
	}
	else if (glfwGetTime() < 35.0 + timing)
	{
		merry_m->getPos()[0][1] -= offsetBG + 0.0082;
		merry_m->getPos()[1][1] -= offsetBG + 0.0082;
		merry_m->getPos()[2][1] -= offsetBG + 0.0082;
		merry_m->getPos()[3][1] -= offsetBG + 0.0082;
	}
	else
	{
		merry_m->getPos()[0][1] -= offsetBG + 0.008;
		merry_m->getPos()[0][0] += 0.01;
		merry_m->getPos()[1][1] -= offsetBG + 0.008;
		merry_m->getPos()[1][0] += 0.01;
		merry_m->getPos()[2][1] -= offsetBG + 0.008;
		merry_m->getPos()[2][0] += 0.01;
		merry_m->getPos()[3][1] -= offsetBG + 0.008;
		merry_m->getPos()[3][0] += 0.01;
	}
	glBindBuffer(GL_ARRAY_BUFFER, merry_m->getVBpos());
	glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(merry_m->getPos()[0]), &merry_m->getPos()[0]);

}

static void moveSmallAirship(std::vector<Mesh*> small_airship_m, Mesh* super_ace_m, float* x, Texture* small_airship_t)
{
	for (int i = 0; i < small_airship_m.size(); i++)
	{
		float  y = -0.007;

		//If it's at a close distance to super ace
		if (abs(abs(super_ace_m->getPos()[0][1]) - abs(small_airship_m[i]->getPos()[3][1])) < 0.3
			&& (abs(abs(super_ace_m->getPos()[0][0]) - abs(small_airship_m[i]->getPos()[3][0])) < 0.3
				|| abs(abs(super_ace_m->getPos()[1][0]) - abs(small_airship_m[i]->getPos()[3][0])) < 0.3)
			&& x[i] == 0.0) {
			y = -0.0085;
			//std::cout << "\n\n" << super_ace_m->getPos()[0][0] << "  " << small_airship_m->getPos()[3][0];
			//std::cout << "\n\n" << super_ace_m->getPos()[1][0] << "  " << small_airship_m->getPos()[2][0] << "\n";
			if (super_ace_m->getPos()[0][0] < small_airship_m[i]->getPos()[3][0]
				&& super_ace_m->getPos()[1][0] < small_airship_m[i]->getPos()[2][0]) {

				x[i] = -0.007;
			}
			else {
				x[i] = 0.007;
			}
		}
		small_airship_t->Bind(0);
		small_airship_m[i]->Draw();
		updatePos(small_airship_m[i], x[i], y);
	}
}

static void moveBigAirship(std::vector<Mesh*> big_airship_m, double* x, Texture* big_t) {

	for (int i = 0; i < big_airship_m.size(); i++)
	{
		double y = 0.005;
		//If going really high start going left and right
		if (big_airship_m[i]->getPos()[0][1] > 0.8) {

			y = 0.0;
			if (big_airship_m[i]->getPos()[1][0] > 0.4 && x[i] == 0.0) {
				x[i] = -0.005;
			}
			else if (x[i] == 0.0) {
				x[i] = 0.005;
			}
			else if (big_airship_m[i]->getPos()[1][0] > 0.8) {
				x[i] = -0.005;
			}
			else  if (big_airship_m[i]->getPos()[0][0] < -0.8) {
				x[i] = 0.005;
			}
		}
		big_t->Bind(0);
		big_airship_m[i]->Draw();
		updatePos(big_airship_m[i], x[i], y);
	}
}

static void moveMediumAirship(std::vector<Mesh*> medium_airship_m, Texture* medium_airship_t, double* x, double* y)
{
	for (int i = 0; i < medium_airship_m.size(); i++)
	{
		//Start going right on x axis 
		if (medium_airship_m[i]->getPos()[2][1] < 0.3 && x[i] == 0.0 && y[i] > -0.0024) {
			std::cout << "first case \n";
			x[i] = 0.001;
			y[i] = -0.0015;
		}
		//Going completely straight and right
		else if (medium_airship_m[i]->getPos()[2][1] < 0.10 && y[i] != 0.0 && y[i] != -0.0025) {
			std::cout << "second case \n";
			x[i] = 0.002;
			y[i] = 0;
		}
		//Making the circle
		else if (medium_airship_m[i]->getPos()[2][0] > 0.50 && y[i] != 0.002 && x[i] > 0.0) {
			std::cout << "third case \n";
			y[i] = 0.002;

		}//Going left now
		else if (medium_airship_m[i]->getPos()[1][1] > 0.70 && y[i] == 0.002 && x[i] != -0.0025) {
			std::cout << "fourth case \n";
			x[i] = -0.0025;
		}
		//Going straight and left now
		else if (medium_airship_m[i]->getPos()[1][1] > 0.85 && y[i] > 0.0 && y[i] != 0.0) {
			std::cout << "fifth case \n";
			y[i] = 0;
		}
		//Closing off circle
		else if (medium_airship_m[i]->getPos()[3][0] < -0.70 && y[i] == 0.0 && x[i] < 0.0) {
			std::cout << "sixth case \n";
			y[i] = -0.0025;
		}//Closing off circle, going downwards
		else if (medium_airship_m[i]->getPos()[3][0] < -0.85 && x[i] < 0.0 && x[i] != 0.0) {
			std::cout << "seventh case \n";
			x[i] = 0;
		}

		medium_airship_t->Bind(0);
		medium_airship_m[i]->Draw();

		medium_airship_m[i]->getPos()[0][0] += x[i];
		medium_airship_m[i]->getPos()[0][1] += y[i];
		medium_airship_m[i]->getPos()[1][0] += x[i];
		medium_airship_m[i]->getPos()[1][1] += y[i];
		medium_airship_m[i]->getPos()[2][0] += x[i];
		medium_airship_m[i]->getPos()[2][1] += y[i];
		medium_airship_m[i]->getPos()[3][0] += x[i];
		medium_airship_m[i]->getPos()[3][1] += y[i];

		glBindBuffer(GL_ARRAY_BUFFER, medium_airship_m[i]->getVBpos());
		glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(medium_airship_m[i]->getPos()[0]), &medium_airship_m[i]->getPos()[0]);
	}
}


