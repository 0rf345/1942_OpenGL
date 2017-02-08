#pragma once
#include <vector>
// Main Menu Options
enum
{
	Game1,
	Game2,
	Controls
}MenuChoices;

// FSM states
enum
{
	Intro,
	MainMenu,
	ControlsConfig,
	GamePlay1,
	GamePlay2,
	Scores,
	Exit
}States;

// Global variables
static unsigned int score = 0;
static int STATE = Intro;
static int NUMOFCHOICES = 3;
static int NUMOFBUTTONS = 7;
static int CHOICE = Game1;
static bool CHOSE = false;
static int LEFT = -1;
static int RIGHT = -1;
static int UP = -1;
static int DOWN = -1;
static int FIRE = -1;
static int AVOID = -1;
static int PAUSE = -1;
static double x1 = 0.0;
static double x2 = 0.0; // For 2nd Player
static double Y1 = 0.0;
static double Y2 = 0.0; // For 2nd Player
static double move = 0.015;
static double startX1 = 0.2;
static double startY1 = 0.2;
static double offsetBG = 0.0105;
static double offsetFire = 0.05;

static std::vector<glm::vec3> PlayerFire_vec3;
static std::vector<Vertex*> playerFire_v;
static std::vector<Mesh*> playerFire_m;
static Texture playerFire_t("Resources/bullet.png");