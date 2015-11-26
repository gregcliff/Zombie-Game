#ifndef PLAYER_H
#define PLAYER_H
#include "Timer.h"
#include "Level.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "MachineGun.h"
#include <vector>

using namespace std;

class Player {
public:
	Player(float startX, float endX, float startY, float endY) {
		minX = startX;
		maxX = endX;
		minY = startY;
		maxY = endY;
		weapons.push_back((Weapon *)(new Pistol()));
		weapons.push_back((Weapon *)(new Shotgun()));
		weapons.push_back((Weapon *)(new MachineGun()));
		setWeapon(0);
	};
	vector<Weapon*> weapons;
	Weapon *weapon;// = (Weapon *)(new Shotgun());
	int direction;
	float x, y, radius, aimX, aimY, minX, maxX, minY, maxY;
	float speed;
	float defaultSpeed;
	Timer timer;
	Timer fireTimer;

	void decreaseReloadTime(int ms) {
		for (int i = 0; i < weapons.size(); i++) {
			weapons.at(i)->setReloadTime(weapons.at(i)->getReloadTime() - ms);
			if (weapons.at(i)->getReloadTime() <= 200) weapons.at(i)->setReloadTime(200);
		}
	}

	void increaseWeaponDamage(float increase) {
		for (int i = 0; i < weapons.size(); i++) {
			weapons.at(i)->damage += increase;
		}
	}

	void reloadWeapon() {
		speed = defaultSpeed - 5;
		weapon->reload();
	}

	vector<Bullet> *fireWeapon() {
		fireTimer.restart();
		speed = defaultSpeed - 1;
		return weapon->fire(x, y, aimX, aimY);
	}

	void addWeapon(Weapon *newWeapon) {
		weapons.push_back(newWeapon);
	}

	void setWeapon(int weaponIndex) {
		weapon = weapons.at(weaponIndex);
	}

	void setSpeed(float s) {
		defaultSpeed = s;
		speed = s;
	}

	void setDirection(char keys[256]) {
		int numTrue = 0;
		bool a = false;
		bool s = false;
		bool d = false;
		bool w = false;
		if (keys[97]) {
			a = true;
			numTrue++;
		}
		if (keys[115]) {
			s = true;
			numTrue++;
		}
		if (keys[100]) {
			d = true;
			numTrue++;
		}
		if (keys[119]) {
			w = true;
			numTrue++;
		}
		if (numTrue > 2) {
			direction = 0;
			return;
		}
		if (a) {
			if (w) {
				direction = 8;
			}
			else if (s) {
				direction = 6;
			}
			else if (d) {
				direction = 0;
			}
			else {
				direction = 7;
			}
		}
		else if (s) {
			if (d) {
				direction = 4;
			}
			else if (w) {
				direction = 0;
			}
			else {
				direction = 5;
			}
		}
		else if (d) {
			if (w) {
				direction = 2;
			}
			else {
				direction = 3;
			}
		}
		else if (w) {
			direction = 1;
		}
		else {
			direction = 0;
		}
	}

	void updateLocation() {
		if (timer.elapsed() < 16) return;
		timer.restart();
		//if time elapsed < .0001 or something return
		switch (direction) {
		case 0: { break; }
		case 1: { y += speed; break; }
		case 2: { y += speed*.71f; x += speed*.71f; break; }
		case 3: { x += speed; break; }
		case 4: { x += speed*.71f; y -= speed*.71f; break; }
		case 5: { y -= speed; break; }
		case 6: { x -= speed*.71f; y -= speed*.71f; break; }
		case 7: { x -= speed; break; }
		case 8: { x -= speed*.71f; y += speed*.71f; break; }
		}
		if (x < minX) x = minX;
		else if (x > maxX) x = maxX;
		if (y < minY) y = minY;
		else if (y > maxY) y = maxY;
	}

	void move(vector<Zombie> &zombies, vector<Wall> &walls) {
		if (weapon->getReloadUpdate() < 0) {
			speed = defaultSpeed - 2;
		}
		else if (fireTimer.elapsed() < slowDownDuration) speed = defaultSpeed - 1;
		else speed = defaultSpeed;
		updateLocation();
		for (int i = 0; i < zombies.size(); i++) {
			float d = sqrtf((x - zombies.at(i).getX())*(x - zombies.at(i).getX())
				+ (y - zombies.at(i).getY())*(y - zombies.at(i).getY()));
			if (d <= radius + zombies.at(i).getRadius()) {
				zombies.at(i).eat();
				radius -= 1;
				if (radius == 0) radius = 1;
			}
		}
	}
	private:
		int slowDownDuration = 50;
};

#endif