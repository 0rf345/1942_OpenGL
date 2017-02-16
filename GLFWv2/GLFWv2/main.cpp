#include "Includes.h"
#define width 520
#define height 720


int main(void)
{
	Texture dead("Resources/dead.png");

	loadConfig();

	Display display(width, height);
	double start = glfwGetTime();
	unsigned int counter = 0;

	Vertex highScore_v[] = {	Vertex(glm::vec3(-0.25, 0.97, 0.0),	glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
								Vertex(glm::vec3( 0.25, 0.97, 0.0),	glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
								Vertex(glm::vec3( 0.25, 0.9, 0.0),	glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
								Vertex(glm::vec3(-0.25, 0.9, 0.0),	glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left};};
	Mesh highScore_m(highScore_v, 4);
	Texture highScore_t("Resources/high_score.png");
	highScore_m.Buffer();

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
	_sleep(10000);
	opening_m.~Mesh();
	
	Vertex mainMenu_v[] = { Vertex(glm::vec3(-1.0, 1.0, 0.0),	glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
							Vertex(glm::vec3(1.0, 1.0, 0.0),	glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
							Vertex(glm::vec3(1.0,-1.0, 0.0),	glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
							Vertex(glm::vec3(-1.0,-1.0, 0.0),	glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left};};
	Mesh mainMenu_m(mainMenu_v, 4);
	Shader mainMenu_s("Resources/basicShader");
	Texture mainMenu_t("Resources/main_menu.jpg");

	mainMenu_m.Buffer();
	highScore_t.Bind(0);
	highScore_m.Draw();
	glfwSetKeyCallback(display.getWindow(), key_callback);

	Vertex choice_v[] = {	Vertex(glm::vec3(-0.2, 0.0, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
							Vertex(glm::vec3(-0.1, 0.0, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
							Vertex(glm::vec3(-0.1,-0.125, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
							Vertex(glm::vec3(-0.2,-0.125, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left};
	Mesh choice_m(choice_v, 4);
	Shader choice_s("Resources/basicShader");
	Texture choice_t("Resources/keystone.png");
	choice_m.Buffer();
	STATE = MainMenu;
	player2 = false;
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

		highScore_t.Bind(0);
		highScore_m.Draw();
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

				std::cout << "Please input the prefered controls for player 1, one at a time, as follows:\nUP DOWN LEFT RIGHT FIRE AVOID PAUSE" << std::endl;

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
				player2 = true;
				STATE = GamePlay1;
				break;
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
	

	Vertex player1_v[] = {Vertex(glm::vec3(-(startX1), startY1, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
						  Vertex(glm::vec3( startX1, startY1, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
						  Vertex(glm::vec3( startX1, -(startY1), 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
						  Vertex(glm::vec3(-(startX1), -(startY1), 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left

	Mesh player1_m(player1_v, 4);
	Shader player1_s("Resources/basicShader");
	Texture player1_t("Resources/m_mainAircraft.png");

	Texture* player_expl[] = {	new Texture("Resources/player_expl_01.png"), new Texture("Resources/player_expl_02.png"), 
								new Texture("Resources/player_expl_03.png"), new Texture("Resources/player_expl_04.png"),
								new Texture("Resources/player_expl_05.png"), new Texture("Resources/player_expl_06.png"), };

	Vertex player2_v[] = {Vertex(glm::vec3(startX1 + 0.2, startY1, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
						  Vertex(glm::vec3(startX1 + 0.4, startY1, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
						  Vertex(glm::vec3(startX1 + 0.4, startY1 - 0.15, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
						  Vertex(glm::vec3(startX1 + 0.2, startY1 - 0.15, 0.0), glm::vec2(0.0, 0.0))};
	Mesh player2_m(player2_v, 4);
	Texture player2_t("Resources/m_secondAircraft.png");

	// Enemy planes /////////////////////////////////////////////////////////////

	Vertex ofa_plane_v[] = {
		Vertex(glm::vec3(-1.0, 1.0, 0.0), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(-0.85, 1.0, 0.0), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(-0.85, 0.9, 0.0), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(-1.0, 0.9, 0.0), glm::vec2(0.0, 0.0))
	};

	Vertex pow_plane_v[] = {
		Vertex(glm::vec3(-1.15, 0.9, 0.0), glm::vec2(0.0, 1.0)),
		Vertex(glm::vec3(-1.00, 0.9, 0.0), glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(-1.00, 0.75, 0.0), glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(-1.15, 0.75, 0.0), glm::vec2(0.0, 0.0))
	};

	Texture ofa_plane_t("Resources/small_plane00.png");
	Texture ofa_plane_t2("Resources/small_plane03.png");

	Texture** ofa_planes_t = (Texture**)malloc(2 * sizeof(Texture**));
	ofa_planes_t[0] = &ofa_plane_t;
	ofa_planes_t[1] = &ofa_plane_t2;

	std::vector<Mesh*> ofa_planes_m;
	std::vector<Mesh*> pow_planes_m;

	ofa_planes_m.push_back(new Mesh(ofa_plane_v, 4));
	//pow_planes_m.push_back(new Mesh(pow_plane_v, 4));
	
	ofa_planes_m[0]->Buffer();
	//pow_planes_m[0]->Buffer();

	double* ofa_planes_y = (double*)calloc(100, sizeof(double*));

	///////////////////////////////////////////////////
	//
	srand(time(NULL));

	std::vector<Mesh*> random_circle_m;
	Texture random_circle_t("Resources/small_plane00.png");

	float* random_circle_x = (float*)calloc(50, sizeof(float*));

	float* random_circle_y = (float*)calloc(50, sizeof(float*));

	bool* random_circles = (bool*)malloc(50 *sizeof(bool*));

	float* random_angle = (float*)malloc(50 *sizeof(float*));

	int* random_options = (int*)calloc(50, sizeof(int*));
	double* random_pos = (double*)calloc(50, sizeof(double*));

	///////////////////////////////////////////////////

	std::vector<Mesh*> jet_m;
	std::vector<Texture*> jet_t;
	//Texture jet_t("Resources/m_mainAircraft.png");

	float* jet_x = (float*)calloc(50, sizeof(float*));

	float* jet_y = (float*)calloc(50, sizeof(float*));

	bool* jet_circles = (bool*)malloc(50 * sizeof(bool*));

	float* jet_angle = (float*)malloc(50 * sizeof(float*));

	int* jet_options = (int*)calloc(50, sizeof(int*));
	//////////////////////////////////////////////////
	Texture pow_plane_t1("Resources/pow_plane_01.png");
	Texture pow_plane_t2("Resources/pow_plane_02.png");
	Texture pow_plane_t3("Resources/pow_plane_03.png");
	Texture pow_plane_t4("Resources/pow_plane_04.png");
	Texture pow_plane_t5("Resources/pow_plane_05.png");
	Texture pow_plane_t6("Resources/pow_plane_06.png");
	Texture pow_plane_t7("Resources/pow_plane_07.png");
	Texture pow_plane_t8("Resources/pow_plane_08.png");

	Texture** pow_planes_t = (Texture**)malloc(8 * sizeof(Texture**));
	pow_planes_t[0] = &pow_plane_t1;
	pow_planes_t[1] = &pow_plane_t2;
	pow_planes_t[2] = &pow_plane_t3;
	pow_planes_t[3] = &pow_plane_t4;
	pow_planes_t[4] = &pow_plane_t5;
	pow_planes_t[5] = &pow_plane_t6;
	pow_planes_t[6] = &pow_plane_t7;
	pow_planes_t[7] = &pow_plane_t8;

	float* pow_planes_angle = (float*)malloc(40);
	bool* pow_planes_circes = (bool*)malloc(10);

	//////////////////////////////////////////////////////////////////////////////
	// enemy explosion

	Texture* expl_t[] = {new Texture("Resources/enemy_expl_01.png"),
		new Texture("Resources/enemy_expl_02.png"), 
		new Texture("Resources/enemy_expl_03.png"), 
		new Texture("Resources/enemy_expl_04.png"), 
		new Texture("Resources/enemy_expl_05.png"), 
		new Texture("Resources/enemy_expl_06.png"), 
	};

	background_m.Buffer();
	player1_m.Buffer();
	player2_m.Buffer();

	bool run = true;
	_sleep(100);
	STATE = GamePlay1;

	Texture bullet_t("Resources/bullet.png");

	Texture avoid_t1("Resources/m_mainAircraftA01.png");
	Texture avoid_t2("Resources/m_mainAircraftA02.png");
	Texture avoid_t3("Resources/m_mainAircraftA03.png");
	Texture avoid_t4("Resources/m_mainAircraftA04.png");
	Texture avoid_t5("Resources/m_mainAircraftA05.png");

	/*
	double life_x = -0.93;
	double life_y = -0.9;

	Vertex life_v1[] = {
		Vertex(glm::vec3(life_x, life_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(life_x + size, life_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(life_x + size, life_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(life_x, life_y - size, 0.0), glm::vec2(0.0,0.0)),
	};

	Mesh life_m(life_v1, 4);
	life_m.Buffer();
	*/

	double sc_x = -0.93;
	double sc_y = 0.97;
	double size = 0.07;
	double offf = 0.02;
	Vertex score_v[] = { 
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)), 
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)), 
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0)) 
	};

	sc_x += size + offf;
	Vertex score_v2[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0))
	};

	sc_x += size + offf;
	Vertex score_v3[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0))
	};

	sc_x += size + offf;
	Vertex score_v4[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0))
	};

	sc_x += size + offf;
	Vertex score_v5[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0))
	};

	sc_x += size + offf;
	Vertex score_v6[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0))
	};

	std::vector<Mesh*> score_m;
	score_m.push_back(new Mesh(score_v, 4));
	score_m.push_back(new Mesh(score_v2, 4));
	score_m.push_back(new Mesh(score_v3, 4));
	score_m.push_back(new Mesh(score_v4, 4));
	score_m.push_back(new Mesh(score_v5, 4));
	score_m.push_back(new Mesh(score_v6, 4));

	for (int i = 0; i < score_m.size(); i++)
		score_m[i]->Buffer();
	
	sc_x = 0.4;
	Vertex highScore_v1[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0))
	};

	sc_x += size + offf;
	Vertex highScore_v2[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0))
	};

	sc_x += size + offf;
	Vertex highScore_v3[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0))
	};

	sc_x += size + offf;
	Vertex highScore_v4[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0))
	};

	sc_x += size + offf;
	Vertex highScore_v5[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0))
	};

	sc_x += size + offf;
	Vertex highScore_v6[] = {
		Vertex(glm::vec3(sc_x, sc_y, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(sc_x + size, sc_y - size, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(sc_x, sc_y - size, 0.0), glm::vec2(0.0,0.0))
	};

	std::vector<Mesh*> high_score_m;
	high_score_m.push_back(new Mesh(highScore_v1, 4));
	high_score_m.push_back(new Mesh(highScore_v2, 4));
	high_score_m.push_back(new Mesh(highScore_v3, 4));
	high_score_m.push_back(new Mesh(highScore_v4, 4));
	high_score_m.push_back(new Mesh(highScore_v5, 4));
	high_score_m.push_back(new Mesh(highScore_v6, 4));

	for (int i = 0; i < high_score_m.size(); i++)
		high_score_m[i]->Buffer();

	Texture* score_t[] = { 
		new Texture("Resources/num_0.png"),
		new Texture("Resources/num_1.png"),
		new Texture("Resources/num_2.png"),
		new Texture("Resources/num_3.png"),
		new Texture("Resources/num_4.png"),
		new Texture("Resources/num_5.png"),
		new Texture("Resources/num_6.png"),
		new Texture("Resources/num_7.png"),
		new Texture("Resources/num_8.png"),
		new Texture("Resources/num_9.png"),
	};

	Vertex merry[] = {Vertex(glm::vec3( 1.2, 1.0, 0.0), glm::vec2(0.0,1.0)),
					  Vertex(glm::vec3( 1.0, 1.0, 0.0), glm::vec2(1.0,1.0)),
					  Vertex(glm::vec3( 1.0, 0.8, 0.0), glm::vec2(1.0,0.0)),
					  Vertex(glm::vec3( 1.2, 0.8, 0.0), glm::vec2(0.0,0.0)) };
	Mesh merry_m(merry, 4);
	Texture merry_t("Resources/goingmerry.png");
	Texture merry_t2("Resources/goingmerry2.png");

	merry_m.Buffer();

	Texture *player_textures[] = {&player1_t, &avoid_t1, &avoid_t2, &avoid_t3, &avoid_t4, &avoid_t5};
	playerFire_v.reserve(1000);

	ofa_planes_m.clear();


	Vertex power_v[] = {
		Vertex(glm::vec3(1.2, 1.0, 0.0), glm::vec2(0.0,1.0)),
		Vertex(glm::vec3(1.0, 1.0, 0.0), glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(1.0, 0.8, 0.0), glm::vec2(1.0,0.0)),
		Vertex(glm::vec3(1.2, 0.8, 0.0), glm::vec2(0.0,0.0))
	};

	Mesh power_m(power_v, 4);
	power_m.Buffer();
	Texture* power_t[] = {
		new Texture("Resources/pow_05.png"),
		new Texture("Resources/pow_01.png"),
		new Texture("Resources/pow_03.png"),
		new Texture("Resources/pow_07.png"),
		new Texture("Resources/pow_02.png"),
		new Texture("Resources/pow_04.png"),
		new Texture("Resources/pow_06.png")
	};

	// Sound buffers, etc
	sf::SoundBuffer bg_buffer;
	if (!bg_buffer.loadFromFile("Resources/1942bg.ogg"))
	{
		std::cout << "Couldn't load 1942bg\n";
	}
	sf::Sound bg_sound;
	bg_sound.setBuffer(bg_buffer);
	bg_sound.setLoop(true);
	bg_sound.play();
	bool mpla = true;

	pow_type powerup;

	//TODO:
	std::vector<Mesh*> big_airship_m;
	double* big_airship_x = (double*)malloc(10 * sizeof(double*));
	Texture big_airship_t("Resources/large.png");

	//////////////////////
	std::vector<Mesh*> small_grey_airship_m;
	float* small_grey_airship_x = (float*)malloc(20 * sizeof(float*));
	Texture small_grey_airship_t("Resources/small_plane_grey00.png");

	////////////////////////

	std::vector<Mesh*> medium_airship_m;
	double* medium_airship_x = (double*)malloc(10 * sizeof(double*));
	double* medium_airship_y = (double*)malloc(10 * sizeof(double*));
	Texture medium_airship_t("Resources/med_dn.png");

	////////////////////////
	// for small airship?
	// x =0;
	// for big x = 0;
//	Vertex big_airship_v[] = { Vertex(glm::vec3(-0.9, -1, 0.0), glm::vec2(0.0, 1.0)),     // 0.0, 1.0  Top Left
		//Vertex(glm::vec3(-0.5, -1, 0.0), glm::vec2(1.0, 1.0)),     // 1.0, 1.0  Top Right
	//	Vertex(glm::vec3(-0.5, -1.4, 0.0), glm::vec2(1.0, 0.0)),    // 1.0, 0.0  Bottom Right
//		Vertex(glm::vec3(-0.9, -1.4, 0.0), glm::vec2(0.0, 0.0)) };  // 0.0, 0.0  Bottom Left
	// for medium
	// x = 0;
	// y = -0.002;


	glfwSetTime(0.0f);
	while (run && player1.getAlive() && background_m.getPos()[0][1] > 1)			// A stray semicolon right here cost me some time and sanity...
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);
		counter++;
		scrollBackGround(background_v, &background_m);
		if (playerFire_m.size())
		{
			scrollBullets();
			destroyBullets();
		}

		if (mpla && glfwGetTime() > 45)
		{
			mpla = !mpla;
			initiliaze_random_planes(&random_circle_m, 3, random_circle_x, random_circle_y, random_circles, random_angle,
				random_options, random_pos);
		}

		glfwPollEvents();
		InputControl(&display);

		/* Refresh rate counter   IT WILL try to match device's native refresh rate, so don't expect more than 60 on my laptop
		   when glfwSetInterval == 1 */
		if ((glfwGetTime() - start) > 1.00)
		{
			std::cout << "FPS: " << counter << std::endl;
			counter = 0; 
			start = glfwGetTime();
		}

		display.Buffer();
		glClear(GL_COLOR_BUFFER_BIT);
		
		background_t.Bind(0);
		background_m.Draw();
		
		unsigned int div = 100000;
		unsigned int score_temp = score;
		unsigned int highscore_temp = highscore;
		for (int i = 0; i < score_m.size(); i++)
		{
			if(score_temp / div == 0)score_t[0]->Bind(0);
			else if (score_temp / div == 1)score_t[1]->Bind(0);
			else if (score_temp / div == 2)score_t[2]->Bind(0);
			else if (score_temp / div == 3)score_t[3]->Bind(0);
			else if (score_temp / div == 4)score_t[4]->Bind(0);
			else if (score_temp / div == 5)score_t[5]->Bind(0);
			else if (score_temp / div == 6)score_t[6]->Bind(0);
			else if (score_temp / div == 7)score_t[7]->Bind(0);
			else if (score_temp / div == 8)score_t[8]->Bind(0);
			else if (score_temp / div == 9)score_t[9]->Bind(0);
			score_m[i]->Draw();

			if (highscore_temp / div == 0)score_t[0]->Bind(0);
			else if (highscore_temp / div == 1)score_t[1]->Bind(0);
			else if (highscore_temp / div == 2)score_t[2]->Bind(0);
			else if (highscore_temp / div == 3)score_t[3]->Bind(0);
			else if (highscore_temp / div == 4)score_t[4]->Bind(0);
			else if (highscore_temp / div == 5)score_t[5]->Bind(0);
			else if (highscore_temp / div == 6)score_t[6]->Bind(0);
			else if (highscore_temp / div == 7)score_t[7]->Bind(0);
			else if (highscore_temp / div == 8)score_t[8]->Bind(0);
			else if (highscore_temp / div == 9)score_t[9]->Bind(0);
			high_score_m[i]->Draw();

			score_temp -= div * (score_temp / div);
			highscore_temp -= div * (highscore_temp / div);
			div = div / 10;

			
		}

		//animateSmallPlanes(ofa_planes_m, &player1_m, ofa_planes_t, ofa_planes_y);

		if(pow_planes_m.size())movePowAirship(pow_planes_m, pow_planes_circes, pow_planes_t, pow_planes_angle);
		if (ofa_planes_m.size())movaOfaAirship(ofa_planes_m, &player1_m, ofa_planes_t, ofa_planes_y);
		if (random_circle_m.size()) {
			randomCircleAnimation(random_circle_m, &random_circle_t, random_pos, random_circles, random_circle_x, random_circle_y, random_angle, random_options);
			
		}
		if (jet_m.size()) {
			jetAnimation(jet_m, &player1_m, jet_t, jet_x, jet_y, jet_circles, jet_angle, jet_options);
		}
		if (big_airship_m.size())
			moveBigAirship(big_airship_m, big_airship_x, &big_airship_t);
		if (small_grey_airship_m.size()) {
			moveSmallAirship(small_grey_airship_m, &player1_m, small_grey_airship_x, &small_grey_airship_t);
		}

		if (medium_airship_m.size()) {
			moveMediumAirship(medium_airship_m, &medium_airship_t, medium_airship_x, medium_airship_y);
		}

		if (glfwGetTime() < 60.0)
		{
			merry_t.Bind(0);
			if (glfwGetTime() > 24.9) merry_t2.Bind(0);
			merry_m.Draw();

			if (glfwGetTime() > 35.4) animateMerry(&merry_m);
		} 
		
		highScore_t.Bind(0);
		highScore_m.Draw();

		updatePowerup(&power_m, pow_planes_m);

		if (pow_ready)
		{
			if (glfwGetTime() < 50) powerup_type = quad;

			power_t[powerup_type]->Bind(0);
			power_m.Draw();
			animate_Powerup(&power_m);
		}

		action(&pow_planes_m, pow_planes_angle, pow_planes_circes, &ofa_planes_m, ofa_planes_y,
			&jet_m, 2, jet_x, jet_y, jet_circles, jet_angle, jet_options, &jet_t,
			&big_airship_m, big_airship_x,
			&small_grey_airship_m, 4, small_grey_airship_x,
			&medium_airship_m, medium_airship_x, medium_airship_y);


		collision_detection(&pow_planes_m, &player1_m, &player2_m, pow_planes_circes, pow_planes_angle, &power_m, &ofa_planes_m, ofa_planes_y,
			&big_airship_m, big_airship_x, &medium_airship_m, medium_airship_x, medium_airship_y, &small_grey_airship_m, small_grey_airship_x,
			&jet_m, jet_x, jet_y, jet_circles, jet_angle, jet_options, &random_circle_m, random_pos, random_circles, random_circle_x, random_circle_y, 
			random_angle, random_options);
		explosions(expl_t);
		/* Player1 constrol */
		movePlayer(&player1_m, player_textures);
		player1_m.Draw();

		if (player2)
		{
			player2_t.Bind(0);
			player2_m.Draw();
			Player2Control(&player2_m);
		}

		if (highscore < score) highscore = score;


		bullet_t.Bind(0);
		for (int i = 0; i < playerFire_m.size(); i++)
			playerFire_m[i]->Draw();

		if (player1.getHit())
		{
			double death_t = glfwGetTime();
			bool not_done = true;
			while (not_done)
			{
				display.Buffer();
				if(glfwGetTime() - death_t < 0.1)player_expl[0]->Bind(0);
				else if (glfwGetTime() - death_t < 0.2)player_expl[1]->Bind(0);
				else if (glfwGetTime() - death_t < 0.3)player_expl[2]->Bind(0);
				else if (glfwGetTime() - death_t < 0.4)player_expl[3]->Bind(0);
				else if (glfwGetTime() - death_t < 0.5)player_expl[4]->Bind(0);
				else if (glfwGetTime() - death_t < 0.6)player_expl[5]->Bind(0);
				player1_m.Draw();
				display.Swap();
				
				if (glfwGetTime() - death_t > 0.55) not_done = false;
			}
			display.Buffer();
			std::cout << "You lost a life" << std::endl;
			//done screen
			display.Swap();
			player1.hitReset();
			for (int i = 0; i < 4; i++)
			{
				player1_m.getPos()[i] = player1_v[i].getPos()[0];
				background_m.getPos()[i] = background_v[i].getPos()[0];				
			}
			x1 = 0;
			Y1 = 0;
			ofa_planes_m.clear();
			playerFire_m.clear();
			playerFire_v.clear();
			explosions_m.clear();
			explosions_timers.clear();
			pow_planes_m.clear();
			random_circle_m.clear();
			jet_m.clear();
			pow_ready = false;
			big_airship_m.clear();
			small_grey_airship_m.clear();
			medium_airship_m.clear();
			score = 0;
			double death_timer = glfwGetTime();
			while (glfwGetTime() - death_timer < 1.5 && run)
			{
				glfwPollEvents();
			}

			glfwSetTime(0.0);
		}


		run = !display.shouldClose(); 
		display.Swap();
	}
	
	display.~Display();
	exit(EXIT_SUCCESS);
}