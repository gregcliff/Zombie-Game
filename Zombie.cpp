#include "Zombie.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

Zombie::Zombie(float newX, float newY)
{
	setLocation(newX, newY);
	radius = 10;
	speed = 2;//steps per second
}

void Zombie::setLocation(float newX, float newY) {
	x = newX;
	y = newY;
}

void Zombie::move(float gotoX, float gotoY, float pRadius, vector<Zombie> &zombies) {
	if (timer.elapsed() < 16 || feedingTimer.elapsed() < 3000) return;
	timer.restart();
	float vx = (gotoX - x);// *speed / (float)msElapsed;
	float vy = (gotoY - y);// *speed / (float)msElapsed;
	float length = sqrtf((vx*vx) + (vy*vy));
	vx = vx * speed / length;
	vy = vy * speed / length;
	float nx = x + vx;
	float ny = y + vy;

	for (int i = 0; i < zombies.size(); i++) {
		if (zombies.at(i).getX() == x && zombies.at(i).getY() == y) continue;
		float d = sqrtf((nx - zombies.at(i).getX())*(nx - zombies.at(i).getX()) 
			+ (ny - zombies.at(i).getY())*(ny - zombies.at(i).getY()));
		if (d <= radius + zombies.at(i).getRadius()) {
			if (radius > zombies.at(i).getRadius()) {
				zombies.erase(zombies.begin() + i);
			}
			else {
				return;
			}
		}
	}
	setLocation(nx, ny);
}

Zombie::~Zombie()
{

}
