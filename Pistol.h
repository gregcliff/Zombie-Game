#ifndef PISTOL_H
#define PISTOL_H
#include "Weapon.h"
#include <vector>

class Pistol : Weapon {
public:
	Pistol() { 
		setClipSize(8);
		setReloadTime(1500);
		setName("Pistol");
		damage = 3;
	}
	
	virtual vector<Bullet> *fire(float playerX, float playerY, float aimX, float aimY) {
		vector<Bullet> *bullets = new vector<Bullet>();
		if (timer.elapsed() < 200 || getShotsFired() >= getClipSize() || isReloading) {
			isReadyToFire = false;
			return bullets;
		}
		isReadyToFire = true;
		timer.restart();
		Bullet bullet = Bullet(playerX, playerY, aimX, aimY, 2);
		bullets->push_back(bullet);
		incrementShotsFired();
		return bullets;
	}

	virtual void reload() {
		reloadTimer.restart();
		isReadyToFire = false;
		isReloading = true;
	}
};

#endif