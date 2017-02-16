#pragma once
#include <vector>
#include "Player.h"
#include <SFML\Audio.hpp>

#define enemy_speed 0.013
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
static double startX1 = 0.15;
static double startY1 = 0.1;
static double offsetBG = 0.0045;
static double offsetFire = 0.05;

static std::vector<glm::vec3> PlayerFire_vec3;
static std::vector<Vertex*> playerFire_v;
static std::vector<Mesh*> playerFire_m;
static std::vector<Mesh*> explosions_m;
static std::vector<double> explosions_timers;

static Vertex GLtempV[4];

static double avoid1time = 0.0;
static double GLtimer = 0.0;

static Player player1(1.05, 1.04);
static unsigned int highscore = 40000;
static unsigned int score = 0;

//pow
static bool pow_ready = false;
static enum pow_type {
	quad,
	kill,
	sidef,
	points,
	life,
	bullets,
	loop
};
static pow_type powerup_type;
static bool player2 = false;