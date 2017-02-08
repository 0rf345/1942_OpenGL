#include "Includes.h"
#define width 576
#define height 720


////////////////////////////////////////////////////////////
/// Play a sound
///
////////////////////////////////////////////////////////////
void playSound()
{
	// Load a sound buffer from a wav file
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("resources/canary.wav"))
		return;

	// Display sound informations
	std::cout << "Resources/canary.wav:" << std::endl;
	std::cout << " " << buffer.getDuration().asSeconds() << " seconds" << std::endl;
	std::cout << " " << buffer.getSampleRate() << " samples / sec" << std::endl;
	std::cout << " " << buffer.getChannelCount() << " channels" << std::endl;

	// Create a sound instance and play it
	sf::Sound sound(buffer);
	sound.play();

	// Loop while the sound is playing
	while (sound.getStatus() == sf::Sound::Playing)
	{
		// Leave some CPU time for other processes
		sf::sleep(sf::milliseconds(100));

		// Display the playing position
		std::cout << "\rPlaying... " << std::fixed << std::setprecision(2) << sound.getPlayingOffset().asSeconds() << " sec   ";
		std::cout << std::flush;
	}
	std::cout << std::endl << std::endl;
}


/////////////////////////////
double randd(double low, double high) {
	//std::cout <<"\n" << rand() << " " << RAND_MAX << " " << high - low << "\n";
	return low + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (high - low)));
	//return (rand() / (double)(RAND_MAX))*abs(low - high) + low;
}

int main(void)
{
	loadConfig();

	Display display(width, height);
	double start = glfwGetTime();
	unsigned int counter = 0;
	
	Vertex opening_v[] = {	Vertex(glm::vec3(-1.0, 1.0, 0.0),	glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
							Vertex(glm::vec3( 1.0, 1.0, 0.0),	glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
							Vertex(glm::vec3( 1.0,-1.0, 0.0),	glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
							Vertex(glm::vec3(-1.0,-1.0, 0.0),	glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left};
	Mesh opening_m(opening_v, 4);
	Shader opening_s("Resources/basicShader");
	Texture opening_t("Resources/opening.jpg");

	opening_m.Buffer();
	display.Buffer();
	opening_s.Bind();
	opening_t.Bind(0);
	opening_m.Draw();
	display.Swap();
	_sleep(1000);
	opening_m.~Mesh();
	
	Vertex mainMenu_v[] = { Vertex(glm::vec3(-1.0, 1.0, 0.0),	glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
							Vertex(glm::vec3(1.0, 1.0, 0.0),	glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
							Vertex(glm::vec3(1.0,-1.0, 0.0),	glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
							Vertex(glm::vec3(-1.0,-1.0, 0.0),	glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left};};
	Mesh mainMenu_m(mainMenu_v, 4);
	Shader mainMenu_s("Resources/basicShader");
	Texture mainMenu_t("Resources/main_menu.jpg");

	mainMenu_m.Buffer();
	glfwSetKeyCallback(display.getWindow(), key_callback);

	std::cout << FIRE << std::endl;
	Vertex choice_v[] = {	Vertex(glm::vec3(-0.2, 0.0, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
							Vertex(glm::vec3(-0.1, 0.0, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
							Vertex(glm::vec3(-0.1,-0.125, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
							Vertex(glm::vec3(-0.2,-0.125, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left};
	Mesh choice_m(choice_v, 4);
	Shader choice_s("Resources/basicShader");
	Texture choice_t("Resources/keystone.png");
	choice_m.Buffer();
	STATE = MainMenu;
	std::vector<Mesh*> bp_m;

	//////////////////////////////////////////
	srand((time(NULL)));
	while (1)
	{

		


		glViewport(0, 0, 1000, 9300);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);

		display.Buffer();
		glClear(GL_COLOR_BUFFER_BIT);

		mainMenu_s.Bind();
		mainMenu_t.Bind(0);
		mainMenu_m.Draw();
		choice_s.Bind();
		choice_t.Bind(0);
		choice_m.Draw();
		display.Swap();
		glfwPollEvents();

		choice_m.UnBuffer();
		if (CHOICE == Game1)
		{
			Vertex choice_v2[] = {	Vertex(glm::vec3(-0.2,-0.02, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
									Vertex(glm::vec3(-0.1,-0.02, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
									Vertex(glm::vec3(-0.1,-0.12, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
									Vertex(glm::vec3(-0.2,-0.12, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left};
			choice_m.Update(choice_v2);
		}
		else if (CHOICE == Game2)
		{
			Vertex choice_v2[] = {	Vertex(glm::vec3(-0.2,-0.15, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
									Vertex(glm::vec3(-0.1,-0.15, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
									Vertex(glm::vec3(-0.1,-0.25, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
									Vertex(glm::vec3(-0.2,-0.25, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left};
			choice_m.Update(choice_v2);
		}
		else
		{
			Vertex choice_v2[] = {	Vertex(glm::vec3(-0.2,-0.28, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
									Vertex(glm::vec3(-0.1,-0.28, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
									Vertex(glm::vec3(-0.1,-0.38, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
									Vertex(glm::vec3(-0.2,-0.38, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left};
			choice_m.Update(choice_v2);
		}
		choice_m.Buffer();

		if ((display).shouldClose()) exit(EXIT_SUCCESS);
		if (CHOSE)
			if (CHOICE == Game1) break;
			else if (CHOICE == Controls)
			{
				STATE = ControlsConfig;
				deInitializeControls();
				_sleep(100);
				while (UP == 0 || DOWN == 0 || LEFT == 0 || RIGHT == 0 || FIRE == 0 || AVOID == 0 || PAUSE == 0) 
				{
					std::cout << UP << " " << DOWN << " " << LEFT << " " << RIGHT << " " << FIRE << " " << AVOID << " " << PAUSE << std::endl;
				
					_sleep(100);
					glfwWaitEvents();
					if(display.shouldClose()) return 1;
				}
				saveControls();
				STATE = GamePlay1;
				break;
			}
			else
			{
				std::cout << "System will now exit this feature is not present yet" << std::endl;
				_sleep(3000);
				exit(EXIT_SUCCESS);
			}
	}
	mainMenu_m.~Mesh();
	
	
	Vertex background_v[] = { Vertex(glm::vec3(-1.0, 40.0, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
						  Vertex(glm::vec3( 1.0, 40.0, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
						  Vertex(glm::vec3( 1.0,-1.0, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
						  Vertex(glm::vec3(-1.0,-1.0, 0.0), glm::vec2(0.0, 0.0)) };

	Mesh background_m(background_v, 4);
	Shader background_s("Resources/basicShader");
	Texture background_t("Resources/terrain01.bmp");
	
	double sc_x = -0.8;
	double sc_y = 0.9;
	double size = 0.1;
	double score_off = 0.005;
	Vertex score_v[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0)),
	};

	sc_x += size;
	Vertex score_v2[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0)),
	};

	sc_x += size;
	Vertex score_v3[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0)),
	};

	sc_x += size;
	Vertex score_v4[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0)),
	};

	sc_x += size;
	Vertex score_v5[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,1.0)),
	};

	std::vector<Mesh*> score_m;
	score_m.push_back(new Mesh(score_v, 4));
	score_m.push_back(new Mesh(score_v2, 4));
	score_m.push_back(new Mesh(score_v3, 4));
	score_m.push_back(new Mesh(score_v4, 4));
	score_m.push_back(new Mesh(score_v5, 4));

	for (int i = 0; i < score_m.size(); i++)
		score_m[i]->Buffer();

	Texture* score_t[] = {new Texture("Resources/num_0.png"), new Texture("Resources/num_1.png"),
		new Texture("Resources/num_2.png"), new Texture("Resources/num_3.png"), new Texture("Resources/num_4.png"),
		new Texture("Resources/num_5.png"), new Texture("Resources/num_6.png"), new Texture("Resources/num_7.png"),
		new Texture("Resources/num_8.png"), new Texture("Resources/num_9.png"),
	};
		

	Vertex player1_v[] = {Vertex(glm::vec3(-(startX1), startY1, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
						  Vertex(glm::vec3( startX1, startY1, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
						  Vertex(glm::vec3( startX1, -(startY1), 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
						  Vertex(glm::vec3(-(startX1), -(startY1), 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left

	Mesh player1_m(player1_v, 4);
	Shader player1_s("Resources/basicShader");
	Texture player1_t("Resources/m_mainAircraft.png");

	/////////////////////////////////////////////

	Vertex big_airship_v[] = { Vertex(glm::vec3(-0.9, -1, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
		Vertex(glm::vec3(-0.5, -1, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
		Vertex(glm::vec3(-0.5, -1.4, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
		Vertex(glm::vec3(-0.9, -1.4, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left

	Mesh big_airship_m(big_airship_v, 4);
	Texture big_airship_t("Resources/m_mainAircraft.png");
	//big_airship_m.Buffer();
	bp_m.push_back(new Mesh(big_airship_v, 4));
	bp_m[0]->Buffer();
	double* bp_x = (double*)malloc(100 * sizeof(double*));
	bp_x[0] = 0.0;

	/////////////////////////////////////////////

	Vertex medium_airship_v[] = { Vertex(glm::vec3(-0.9, 1.0, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
		Vertex(glm::vec3(-0.5, 1.0, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
		Vertex(glm::vec3(-0.5, 0.58, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
		Vertex(glm::vec3(-0.9, 0.58, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left

	Mesh medium_airship_m(medium_airship_v, 4);
	Texture medium_airship_t("Resources/m_mainAircraft.png");
	medium_airship_m.Buffer();

	/////////////////////////////////////////////
	Vertex pow_airship_v[] = { Vertex(glm::vec3(-1.0, 0.9, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
		Vertex(glm::vec3(-0.9, 0.9, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
		Vertex(glm::vec3(-0.9, 0.8, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
		Vertex(glm::vec3(-1.0, 0.8, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left

	Mesh pow_airship_m(pow_airship_v, 4);
	Texture pow_airship_t("Resources/m_mainAircraft.png");
	pow_airship_m.Buffer();

	////////////////////////////////////////////////

	double randy = randd(-0.9, 0.9);
	double randx = rand() % 2;
	double randxm;
	if (randx == 0) {
		randx--;
		randxm = randx + 0.1;
	}
	else {
		randxm = randx - 0.1;
	}
	std::cout << randy << "\n\n";
		Vertex random_circle_v[] = { Vertex(glm::vec3(randx, randy, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
			Vertex(glm::vec3(randxm, randy, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
			Vertex(glm::vec3(randxm, randy - 0.1, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
			Vertex(glm::vec3(randx, randy - 0.1, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left


	Mesh random_circle_m(random_circle_v, 4);
	Texture random_circle_t("Resources/m_mainAircraft.png");
	random_circle_m.Buffer();
	///////////////////////////////////////////////////////////
	double randx_small = randd(-0.9, 0.9);


		Vertex small_airship_v[] = { Vertex(glm::vec3(randx_small, 1.0, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
		Vertex(glm::vec3(randx_small + 0.1, 1.0, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
		Vertex(glm::vec3(randx_small + 0.1,  0.9, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
		Vertex(glm::vec3(randx_small, 0.9, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left

		Mesh small_airship_m(small_airship_v, 4);
		Texture small_airship_t("Resources/m_mainAircraft.png");
		small_airship_m.Buffer();

	///////////////////////////////////////////////////////////
		Vertex jet_v[] = { Vertex(glm::vec3(randx, 0.6, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
			Vertex(glm::vec3(randxm, 0.6, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
			Vertex(glm::vec3(randxm, 0.5, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
			Vertex(glm::vec3(randx, 0.5, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left

		Mesh jet_m(jet_v, 4);
		Texture jet_t("Resources/m_mainAircraft.png");
		jet_m.Buffer();


	background_m.Buffer();
	player1_m.Buffer();

	bool run = true;
	_sleep(100);
	STATE = GamePlay1;
	

	Vertex bullet_v[] = {	Vertex(glm::vec3(-0.025, -1.0, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
							Vertex(glm::vec3( 0.025, -1.0, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
							Vertex(glm::vec3( 0.025, -1.05, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
							Vertex(glm::vec3(-0.025, -1.05, 0.0), glm::vec2(0.0, 0.0))  // 0.0, 0.0  Bottom Left
	};

	Mesh bullet_m(bullet_v, 4);
	Shader bullet_s("Resources/basicShader");
	Texture bullet_t("Resources/bullet.png");
	bullet_m.Buffer();

	std::vector<Mesh*> med_m;
	med_m.push_back(&medium_airship_m);
	med_m[0]->Buffer();
	double* med_x = (double*)malloc(100 * sizeof(double*));
	double* med_y = (double*)malloc(100 * sizeof(double*));
	med_x[0] = 0;
	med_y[0] = -0.002;

	playerFire_v.reserve(1000);
	glfwSetTime(0.0f);

	///////////////////////////////////////////////////////
	double random;
	int option = 0;
	///////////////////////////////////////////////////////

	while (run)			// A stray semicolon right here cost me some time and sanity...
	{
		glViewport(0, 0, 1000, 9300);

		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);
		counter++;
		display.Buffer();
		glClear(GL_COLOR_BUFFER_BIT);
		
		background_s.Bind();
		background_t.Bind(0);
		background_m.Draw();


		//player1_s.Bind();		// we do no use different shaders, so we could eliminate this
		player1_t.Bind(0);
		player1_m.Draw();

		/////////////////
		moveMediumAirship(med_m, med_x, med_y);
		medium_airship_t.Bind(0);
		med_m[0]->Draw();
		//moveMediumAirship(&medium_airship_m);

		/////////////////
		//movePowAirship(&pow_airship_m);
		//pow_airship_t.Bind(0);
		//pow_airship_m.Draw();

		////////////////////////////////////////////
		
		if (random_circle_m.GetPos()[0][0] < 0 && option == 0) {
			random = randd(-0.65, 0.5);
			//Left and low side of screen
			if (random_circle_m.GetPos()[0][1] < -0.4) {
				option = 2;
			}
			else {
			//Left and high side of screen
				option = 1;
			}
		}
		else if(option == 0){
			random = randd(-0.5, 0.65);
			//Right and low side of screen
			if (random_circle_m.GetPos()[0][1] < -0.4) {
				option = 4;
			}
			else {
				//Right and high side of screen
				option = 3;
			}
		}
		//randomCircleAnimation(&random_circle_m, random, option);

		//random_circle_t.Bind(0);
		//random_circle_m.Draw();


		///////////////////////////////////////////////////////////

		//moveSmallAirship(&small_airship_m, &player1_m);
/*
		small_airship_t.Bind(0);
		small_airship_m.Draw();*/

		/////////////////////////////////////////////////////////////

		//jetAnimation(&jet_m, &player1_m);
		//jet_t.Bind(0);
		//jet_m.Draw();

		////////////////////////////////////////////////////////////

		moveBigAirship(bp_m, bp_x);
		big_airship_t.Bind(0);
		bp_m[0]->Draw();

		///////////////////////////////////////////////////////////////

		//bullet_s.Bind();
		bullet_t.Bind(0);
		bullet_m.Draw();

		playerFire_t.Bind(0);
		for (int i = 0; i < playerFire_m.size(); i++)
			playerFire_m[i]->Draw();

		display.Swap();
		glfwPollEvents();

		bullet_v[0].getPos()[0][1] += 0.05;
		bullet_v[1].getPos()[0][1] += 0.05;
		bullet_v[2].getPos()[0][1] += 0.05;
		bullet_v[3].getPos()[0][1] += 0.05;


		
		bullet_m.UnBuffer();
		bullet_m.Update(bullet_v);
		bullet_m.Buffer();

		scrollBackGround(background_v, &background_m);
		scrollBullets();

		InputControl(&display);
		
		/* Player1 constrol */
		Vertex verticesNew[] = {	Vertex(glm::vec3(-startX1 + x1, startY1 + Y1, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
								Vertex(glm::vec3(startX1 + x1, startY1 + Y1, 0.0), glm::vec2(1.0, 1.0)),		// 1.0, 1.0  Top Right
								Vertex(glm::vec3(startX1 + x1, -(startY1) + Y1, 0.0), glm::vec2(1.0, 0.0)),		// 1.0, 0.0  Bottom Right
								Vertex(glm::vec3(-(startX1) + x1, -(startY1) + Y1, 0.0), glm::vec2(0.0, 0.0)) };// 0.0, 0.0  Bottom Left

		player1_m.UnBuffer();
		player1_m.Update(verticesNew);
		player1_m.Buffer();



		unsigned int div = 100000;
		for (int i = 0; i < score_m.size(); i++)
		{
			if (score % div == 0)player1_t.Bind(0); //score_t[0]->Bind(0);
			else if (score % div == 1)score_t[1]->Bind(0);
			else if (score % div == 2)score_t[2]->Bind(0);
			else if (score % div == 3)score_t[3]->Bind(0);
			else if (score % div == 4)score_t[4]->Bind(0);
			else if (score % div == 5)score_t[5]->Bind(0);
			else if (score % div == 6)score_t[6]->Bind(0);
			else if (score % div == 7)score_t[7]->Bind(0);
			else if (score % div == 8)score_t[8]->Bind(0);
			else if (score % div == 9)score_t[9]->Bind(0);
			else player1_t.Bind(0);
			//std::cout << score << std::endl;
			div = div / 10;
			score_m[i]->Draw();
		}


		// An fps counter, it seems weird that we only get 60fps, maybe look into it
		if ((glfwGetTime() - start) > 1.00)
		{
			std::cout << "FPS: " << counter << std::endl;
			counter = 0;
			start = glfwGetTime();
		}
		run = !display.shouldClose(); // no idea why inverted boolean...
	}
	display.~Display();
	exit(EXIT_SUCCESS);
}