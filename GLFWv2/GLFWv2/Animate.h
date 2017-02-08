#pragma once
#include "Globals.h"
#include <vector>

#define TWO_PI 6.28318

static void scrollBackGround(Vertex* background_v, Mesh* background_m)
{
	background_v[0].getPos()[0][1] -= offsetBG;
	background_v[1].getPos()[0][1] -= offsetBG;
	background_v[2].getPos()[0][1] -= offsetBG;
	background_v[3].getPos()[0][1] -= offsetBG;


	background_m->UnBuffer();
	background_m->Update(background_v);
	background_m->Buffer();
}


static void scrollBullets()
{
	// testing implementation
	if (playerFire_v.size() > 0)
	{
		for (int i = 0; i < playerFire_v.size(); i+=4)
			std::cout << playerFire_v[i]->getPos()[0][1] << std::endl;
	}
}

static void updatePos(Mesh* mesh, double x, double y)
{
	mesh->GetPos()[0][0] += x;
	mesh->GetPos()[0][1] += y;
	mesh->GetPos()[1][0] += x;
	mesh->GetPos()[1][1] += y;
	mesh->GetPos()[2][0] += x;
	mesh->GetPos()[2][1] += y;
	mesh->GetPos()[3][0] += x;
	mesh->GetPos()[3][1] += y;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->getVBpos());
	glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(mesh->GetPos()[0]), &mesh->GetPos()[0]);
}

static bool circleAnimation(Mesh* airplane_m, double multiply, double loops, int option)
{
	static float angle = 0;
	double x;
	double y;
	double mulx = 0.0;
	double muly = 0.0;

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
	static double time = glfwGetTime();
	if(angle < loops*TWO_PI) {
		x =  (cos(angle))*mulx * multiply;
		y =  (sin(angle))*muly * multiply;
		time = glfwGetTime();
		updatePos(airplane_m, x, y);

/*
		x = xcenter +(cos(angle))*radius*0.01;
		y = ycenter -(sin(angle)*radius *0.01);

		std::cout << x << " " << y << "\n";
		airplane_m->GetPos()[0][0] = x - 0.1;
		airplane_m->GetPos()[0][1] = y + 0.1;
		airplane_m->GetPos()[1][0] = x + 0.1;
		airplane_m->GetPos()[1][1] = y + 0.1;
		airplane_m->GetPos()[2][0] = x + 0.1;
		airplane_m->GetPos()[2][1] = y - 0.1;
		airplane_m->GetPos()[3][0] = x - 0.1;
		airplane_m->GetPos()[3][1] = y - 0.1;
*/
		angle += 0.1;
		return true;
	}else {
		return false;
	}

}
/*
static void destroyBullets(int elements)
{
	for (int i = elements - 1; i >= 0; i--)
		if (playerFire_v[i][3].getPos()[0][1] > 1.0)
		{
			playerFire_v.erase(playerFire_v.begin() + i);
			//playerFire_m[i].UnBuffer();
			playerFire_m.erase(playerFire_m.begin() + i);
		}
}


static void movePlayer1(Vertex* vertices, Mesh* mesh)
{
	vertices[0].getPos()[0][0] += x1;
	vertices[0].getPos()[0][1] += Y1;
	vertices[1].getPos()[0][0] += x1;
	vertices[1].getPos()[0][1] += Y1;
	vertices[2].getPos()[0][0] += x1;
	vertices[2].getPos()[0][1] += Y1;
	vertices[3].getPos()[0][0] += x1;
	vertices[3].getPos()[0][1] += Y1;
	

	
	mesh->UnBuffer();
	mesh->Update(vertices);
	mesh->Buffer();
}
*/

static void movePowAirship(Mesh* pow_airship_m) 
{
	//Going right and making two circles
	static double x = 0.008;
	static double y = 0;
	static bool inCircle = false;

	//Do first circle
	if ((pow_airship_m->GetPos()[2][0] > -0.40 || inCircle) && pow_airship_m->GetPos()[2][0] < 0) {
		inCircle = circleAnimation(pow_airship_m, 2.8 , 1.0, 1);
		
	}	
	//Do second circle
	if (pow_airship_m->GetPos()[2][0] > 0.5 || inCircle) {
		inCircle = circleAnimation(pow_airship_m, 2.8, 2.0 , 1);
	}
	//Move to the right
	if (!inCircle) {
		updatePos(pow_airship_m, x, y);

	}
}

static void randomCircleAnimation(Mesh* random_circle_m, double randx, int option)
{
	static double x = 0.0;
	static double y = 0.0;
	static bool inCircle = false;

	//Coming from left side of screen
	if (option == 1 && y == 0.0) {
		x = 0.005;

		//At some random point 
		if (random_circle_m->GetPos()[1][0] > randx || inCircle) {
				inCircle = circleAnimation(random_circle_m, 2.3, 1.24, option);

			if (!inCircle) {
				y = -0.005;
			}
		}
	}
	else if (option == 2 && y == 0.0) {
		x = 0.005;
		//At some random point 
		if (random_circle_m->GetPos()[1][0] > randx || inCircle) {
			inCircle = circleAnimation(random_circle_m, 2.3, 0.75, option);

			if (!inCircle) {
				y = -0.005;
				x = -0.004;
			}
		}
	}
	//Coming from right side of screen
	else if (option == 3 && y == 0.0) {
		x = -0.005;
		//At some random point 
		if (random_circle_m->GetPos()[1][0] < randx || inCircle) {
			inCircle = circleAnimation(random_circle_m, 2.3, 1.25, option);
			if (!inCircle) {
				x = -0.0045;
				y = -0.005;
			}
		}
	}
	else if(option == 4 && y == 0.0){
		//Coming from right side of screen and low
		x = -0.005;
		//At some random point 
		if (random_circle_m->GetPos()[1][0] < randx || inCircle) {
			inCircle = circleAnimation(random_circle_m, 2.8, 0.9, option);
			if (!inCircle) {
				y = -0.005;
				x = -0.0009;
			}
		}
	}
	else if (option == 0) {
		std::cout << "Illegal argument.\n\n";
	}

	if (!inCircle) {
		updatePos(random_circle_m, x, y);
	}
}

static void moveBigAirship(std::vector<Mesh*> big_airship_m, double* x) {

	double y = 0.01;

	for (int i = 0; i < big_airship_m.size(); i++)
	{
		//If going really high start going left and right
		if (big_airship_m[i]->GetPos()[0][1] > 0.8) {

			y = 0.0;
			if (big_airship_m[i]->GetPos()[1][0] > 0.4 && x[i] == 0.0) {
				x[i] = -0.01;
			}
			else if (x[i] == 0.0) {
				x[i] = 0.01;
			}
			else if (big_airship_m[i]->GetPos()[1][0] > 0.8) {
				x[i] = -0.01;
			}
			else  if (big_airship_m[i]->GetPos()[0][0] < -0.8) {
				x[i] = 0.01;
			}
		}

		updatePos(big_airship_m[i], x[i], y);
	}


}


static void moveSmallAirship(Mesh* small_airship_m, Mesh* super_ace_m) 
{
	static double x = 0.0;
	static double  y = -0.008;

	//If it's at a close distance to super ace
	if (abs(abs(super_ace_m->GetPos()[0][1])-abs(small_airship_m->GetPos()[3][1]))<0.3
		&& (abs(abs(super_ace_m->GetPos()[0][0]) - abs(small_airship_m->GetPos()[3][0])) < 0.3
			|| abs(abs(super_ace_m->GetPos()[1][0]) - abs(small_airship_m->GetPos()[3][0])) < 0.3)
		&& x == 0.0	) {
		y = -0.0085;
		std::cout << "\n\n" << super_ace_m->GetPos()[0][0] << "  " << small_airship_m->GetPos()[3][0];
		std::cout << "\n\n" << super_ace_m->GetPos()[1][0] << "  " << small_airship_m->GetPos()[2][0] <<"\n";
		if (super_ace_m->GetPos()[0][0] < small_airship_m->GetPos()[3][0]
			&& super_ace_m->GetPos()[1][0] <  small_airship_m->GetPos()[2][0]) {
			
			x = -0.008;
		}
		else {
			x = 0.008;
		}
	}

	updatePos(small_airship_m, x, y);
}

static void jetAnimation(Mesh* jet_m, Mesh* super_ace_m) {
	static double x = 0.0;
	static double y = 0.0;
	static bool inCircle = false;
	static int option = 0;
	
	//Does a curve before attacking
	if (jet_m->GetPos()[0][0] == -1 || (inCircle && option == 1)) {
		option = 1;
		inCircle = circleAnimation(jet_m, 4, 0.25, 1);

	}
	else if (jet_m->GetPos()[0][0] == 1 || (inCircle && option == 3)) {
		option = 3;
		inCircle = circleAnimation(jet_m, 4, 0.25, 3);
	}

	//Goes downward and ready to attack
	if (!inCircle && y == 0.0) {
		y = -0.005;
	}
	//Attack
	else if(abs(abs(super_ace_m->GetPos()[0][1]) - abs(jet_m->GetPos()[3][1]))<0.4 && x == 0.0){

		if (super_ace_m->GetPos()[0][0] < jet_m->GetPos()[3][0]
			&& super_ace_m->GetPos()[1][0] <  jet_m->GetPos()[2][0]) {

			x = -0.005;
		}
		else {
			x = 0.005;
		}
	}
	updatePos(jet_m, x, y);
}

static void moveMediumAirship(std::vector<Mesh*> medium_airship_m, double* x, double* y) 
{
	//static double x = 0;
	//static double y = -0.002;
	for (int i = 0; i < medium_airship_m.size(); i++)
	{
		//Start going right on x axis 
		if (medium_airship_m[i]->GetPos()[2][1] < 0.3 && x[i] == 0.0 && y[i] > -0.0024) {
			std::cout << "first case \n";
			x[i] = 0.001;
			y[i] = -0.0015;
		}
		//Going completely straight and right
		else if (medium_airship_m[i]->GetPos()[2][1] < 0.10 && y[i] != 0.0 && y[i] != -0.0025) {
			std::cout << "second case \n";
			x[i] = 0.002;
			y[i] = 0;
		}
		//Making the circle
		else if (medium_airship_m[i]->GetPos()[2][0] > 0.50 && y[i] != 0.002 && x[i] > 0.0) {
			std::cout << "third case \n";
			y[i] = 0.002;

		}//Going left now
		else if (medium_airship_m[i]->GetPos()[1][1] > 0.70 && y[i] == 0.002 && x[i] != -0.0025) {
			std::cout << "fourth case \n";
			x[i] = -0.0025;
		}
		//Going straight and left now
		else if (medium_airship_m[i]->GetPos()[1][1] > 0.85 && y[i] > 0.0 && y[i] != 0.0) {
			std::cout << "fifth case \n";
			y[i] = 0;
		}
		//Closing off circle
		else if (medium_airship_m[i]->GetPos()[3][0] < -0.70 && y[i] == 0.0 && x[i] < 0.0) {
			std::cout << "sixth case \n";
			y[i] = -0.0025;
		}//Closing off circle, going downwards
		else if (medium_airship_m[i]->GetPos()[3][0] < -0.85 && x[i] < 0.0 && x[i] != 0.0) {
			std::cout << "seventh case \n";
			x[i] = 0;
		}

		medium_airship_m[i]->GetPos()[0][0] += x[i];
		medium_airship_m[i]->GetPos()[0][1] += y[i];
		medium_airship_m[i]->GetPos()[1][0] += x[i];
		medium_airship_m[i]->GetPos()[1][1] += y[i];
		medium_airship_m[i]->GetPos()[2][0] += x[i];
		medium_airship_m[i]->GetPos()[2][1] += y[i];
		medium_airship_m[i]->GetPos()[3][0] += x[i];
		medium_airship_m[i]->GetPos()[3][1] += y[i];

		glBindBuffer(GL_ARRAY_BUFFER, medium_airship_m[i]->getVBpos());
		glBufferSubData(GL_ARRAY_BUFFER, NULL, 4 * sizeof(medium_airship_m[i]->GetPos()[0]), &medium_airship_m[i]->GetPos()[0]);
	}
}