#ifndef BULLET_H
#define BULLET_H
#include "Timer.h"
#include <cmath>

class Bullet {
public:
	Timer timer;
	Timer life;
	double started;
	int damage = 1;
	Bullet(float x, float y, float aimX, float aimY, float nLength) {
		theta = atan2f((aimY - y), (aimX - x));
		length = nLength;
		float tempLength = sqrtf((aimX - x)*(aimX - x) + (aimY - y)*(aimY - y));
		currentX = x;
		currentY = y;
		cosff = speed*cosf(theta);
		sinff = speed*sinf(theta);
		nextX = x + cosff;
		nextY = y + sinff;
		started = timer.start;
	}

	float speed = 15; //20 doesnt get detected
	double msBetweenMove = 1;

	void setDamage(int d) {
		damage = d;
	}

	void update() {
		if (timer.elapsed() < 10) return;
		timer.restart();
		float tempX = currentX;
		float tempY = currentY;
		currentX = nextX;
		currentY = nextY;
		nextX = tempX + cosff;
		nextY = tempY + sinff;
	}

	float getCurrentX() {
		return currentX;
	}

	float getCurrentY() {
		return currentY;
	}

	float getNextX() {
		return nextX;
	}

	float getNextY() {
		return nextY;
	}

	float getHitX() {
		return hitX;
	}

	float getHitY() {
		return hitY;
	}
private:
	float currentX, currentY, nextX, nextY, hitX, hitY, length, theta, cosff, sinff;

};

#endif BULLET_H