#ifndef ZOMBIE_H
#define ZOMBIE_H
#pragma once

#include <vector>
#include "Timer.h"

using namespace std;

class Zombie
{
public:
	Zombie(float newX, float newY);
	void setLocation(float newX, float newY);
	void move(float newX, float newY, float pRadius, vector<Zombie> &zombies);
	void setX(float newX) { x = newX; }
	void setY(float newY) { y = newY; }
	void setSpawn(int spawn) { spawnPoint = spawn; }
	void setRadius(float r) { radius = r; }
	void setSpeed(float s) { speed = s; }
	void setHealth(int h) { health = h; }
	float getX() { return x; }
	float getY() { return y; }
	float getRadius() { return radius; }
	float getSpeed() { return speed; }
	int getSpawn() { return spawnPoint; }
	int health = 3;
	Timer timer;
	Timer feedingTimer;
	void eat() { feedingTimer.restart(); }
	~Zombie();

private:
	int spawnPoint;
	float x, y, radius, speed;
};

#endif ZOMBIE_H