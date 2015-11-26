#ifndef MACHINE_GUN_H
#define MACHINE_GUN_H
#include "Weapon.h"
using namespace std;

class MachineGun :Weapon {
public:
	MachineGun() {
		setClipSize(30);
		setReloadTime(3000);
		setName("Machine Gun");
		damage = 1.5;
	}

	virtual vector<Bullet> *fire(float playerX, float playerY, float aimX, float aimY) {
		vector<Bullet> *bullets = new vector<Bullet>();
		if (timer.elapsed() < 80 || getShotsFired() >= getClipSize() || isReloading) {
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