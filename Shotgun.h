#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "Weapon.h"
#include <vector>

using namespace std;

class Shotgun : Weapon{
public:
	Shotgun() {
		setClipSize(6);
		setReloadTime(500);
		setName("Shotgun");
	}

	virtual int getReloadUpdate() {
		if (reloadTimer.elapsed() < getReloadTime() && wasReloading) {
			isReloading = true;
		}
		if(getShotsFired() == 0)
			isReloading = false;
		int ms = reloadTimer.elapsed() - getReloadTime();
		if (wasReloading && isReloading && ms > 0) {
			reloadTimer.restart();
			setShotsFired(getShotsFired() - 1);
		}
		wasReloading = isReloading;
		return ms;
	}

	virtual vector<Bullet> *fire(float playerX, float playerY, float aimX, float aimY) {
		vector<Bullet> *bullets = new vector<Bullet>();
		if (timer.elapsed() < 800 || getShotsFired() >= getClipSize()) {
			isReadyToFire = false;
			return bullets;
		}

		isReadyToFire = true;
		wasReloading = false;
		float theta = atan2f((aimY - playerY), (aimX - playerX));
		float vx = playerX + cosf(theta);
		float vy = playerY + sinf(theta);
		timer.restart();
		for (int i = 0; i < 5; i++) {
			float random, rTheta;
			random = ((float)(rand() % 20) / 100);
			if (rand() % 2 == 0) {
				random = -random;
			}
			rTheta = theta + random;
			Bullet bullet = Bullet(playerX, playerY, playerX+cosf(rTheta), playerY+sinf(rTheta), 1);
			bullets->push_back(bullet);
		}
		incrementShotsFired();
		isReloading = false;
		return bullets;
	}

	virtual void reload() {
		reloadTimer.restart();
		isReadyToFire = false;
		isReloading = true;
	}

};

#endif