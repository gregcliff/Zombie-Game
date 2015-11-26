#ifndef SPAWN_H
#define SPAWN_H
#include <vector>
#include <queue>
#include "Zombie.h"
using namespace std;

class Spawn {
public:
	float location[2];
	queue<int> timingQueue;
	queue<Zombie> queue;
	Timer timer;

	void queueZombie(int msUntilEntry) {
		Zombie zom = Zombie(location[0], location[1]);
		queueZombie(msUntilEntry, zom);
	}

	void queueZombie(int msUntilEntry, Zombie zombie) {
		timingQueue.push(msUntilEntry);
		queue.push(zombie);
	}

	Zombie nextZombie() {
		Zombie zom = queue.front();
		queue.pop();
		timingQueue.pop();
		timer.restart();
		return zom;
	}

	void queueSuperZombie() {
		Zombie superZom = Zombie(location[0], location[1]);
		superZom.setHealth(20);
		superZom.setSpeed(4);
		superZom.setRadius(20);
		queueZombie(100, superZom);
	}

	bool isReady(vector<Zombie> zombies) {
		if (queue.size() == 0) return false;
		for (int i = 0; i < zombies.size(); i++) {
			float d = sqrtf((location[0] - zombies.at(i).getX())*(location[0] - zombies.at(i).getX())
				+ (location[1] - zombies.at(i).getY())*(location[1] - zombies.at(i).getY()));
			if (d <= 20 + zombies.at(i).getRadius()) {
				return false;
			}
		}
		if (timer.elapsed() > timingQueue.front()) {
			return true;
		}
		return false;
	}
};

#endif