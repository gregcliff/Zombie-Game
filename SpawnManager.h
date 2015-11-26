#ifndef SPAWNMANAGER_H
#define SPAWNMANAGER_H
#include <vector>
#include <queue>
#include "Spawn.h"

using namespace std;

class SpawnManager {
public:
	//SpawnConfiguration config;
	SpawnManager() {

	};

	SpawnManager(int ms) {
		setSpawnTime(ms);
	};
	vector<Spawn> spawns;
	Timer timer;
	
	void setSpawnTime(int m) {
		spawnTime = m;
		if (m < 100) spawnTime = 100;
	}
	int getSpawnTime() {
		return spawnTime;
	}
	void addToZombieQueue(int spawnId) {
		spawns.at(spawnId).queueZombie(1000);
	}

	void run() {
		if (timer.elapsed() > spawnTime) {
			timer.restart();
			addToZombieQueue(rand() % spawns.size());
		}
	}

private:
	int spawnTime = 1000;
};

#endif