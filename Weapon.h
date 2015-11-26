#ifndef WEAPON_H
#define WEAPON_H
#include "Bullet.h"
#include <vector>

using namespace std;

class Weapon {
public:
	Timer timer;
	Timer reloadTimer;
	virtual string getName() { return name; }
	virtual void setName(string n) { name = n; }
	virtual int getReloadTime() { return reloadTime; }
	virtual int getReloadUpdate() { 
		if (reloadTimer.elapsed() < reloadTime) {
			isReloading = true;
		}
		else isReloading = false;
		int ms = reloadTimer.elapsed() - reloadTime; 
		if (wasReloading && !isReloading) setShotsFired(0);
		wasReloading = isReloading;
		return ms;
	}
	virtual void setClipSize(int size) { clipSize = size; }
	virtual int getShotsFired() { return shotsFired; }
	virtual int getClipSize() { return clipSize; }
	virtual void setShotsFired(int s) { shotsFired = s; }
	virtual void setReloadTime(int ms) { reloadTime = ms; }
	virtual void incrementShotsFired() { shotsFired++; }
	virtual vector<Bullet> *fire(float playerX, float playerY, float aimX, float aimY) = 0;
	virtual void reload() = 0;
	virtual bool isReady() { return isReadyToFire; }
	bool isReadyToFire = true;
	bool isReloading = false;
	bool wasReloading = false;
	float damage = 1;


private:
	string name;
	int clipSize;
	int shotsFired = 0;
	int reloadTime;
};

#endif