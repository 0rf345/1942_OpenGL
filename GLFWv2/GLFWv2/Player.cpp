#include "Player.h"

Player::Player(double borderL, double borderR)
{
	this->invincible = false;
	this->left_border = borderL;
	this->right_border = borderR;
	this->quadGun = false;
	this->lives = 2;
	this->loops = 3;
	this->isHit = false;
}

void Player::addLoop() { this->loops++; }
void Player::subLoop() { this->loops--; }
unsigned int Player::getLoops() { return this->loops; }
bool Player::getInvincible() { return invincible; }
bool Player::getQuadGun() { return quadGun; }
void Player::setInvincible(bool val) { invincible = val; }
void Player::setQuadGun() { quadGun = true; }
void Player::setLeftBorder(double border) { left_border = border; }
void Player::setRightBorder(double border) { right_border = border; }
double Player::getLeftBorder() { return left_border; }
double Player::getRightBorder() { return right_border; }
bool Player::getAlive() { return (bool)lives; }
void Player::hit() 
{
	if (!this->isHit)lives--;
	this->quadGun = false;
	this->isHit = true; 
}
void Player::hitReset() { this->isHit = false; }

bool Player::getHit() { return this->isHit; }

Player::~Player()
{
}
