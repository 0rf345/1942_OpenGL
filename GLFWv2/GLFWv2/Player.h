#pragma once
class Player
{
private:
	bool invincible;
	double left_border;
	double right_border;
	bool quadGun;
	unsigned int lives;
	unsigned int loops;
	bool isHit;

public:
	Player(double borderL, double borderR);
	~Player();

	void hitReset();
	void addLoop();
	void subLoop();
	unsigned int getLoops();

	void setLeftBorder(double border);
	void setRightBorder(double border);

	double getLeftBorder();
	double getRightBorder();

	void setInvincible(bool val);
	bool getInvincible();
	
	void setQuadGun();
	bool getQuadGun();
	
	bool getAlive();

	bool getHit();
	void hit();
};

