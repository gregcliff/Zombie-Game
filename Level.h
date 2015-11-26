#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <queue>
#include "SpawnManager.h"
using namespace std;

class Wall {
public:
	float sx, sy, ex, ey;
};

class Level {
public:
	Timer timer;
	//GameProgress game;
	float startXBound, endXBound, startYBound, endYBound;
	vector<Wall> walls;
	Level() { 
	};

	void addSpawn(float spawnX, float spawnY) {
		Spawn spawn;
		spawn.location[0] = spawnX;
		spawn.location[1] = spawnY;
		manager.spawns.push_back(spawn);
	};

	Spawn& getSpawn(int spawnId) {
		return manager.spawns.at(spawnId);
	}

	int getManagerSpawnTime() {
		return manager.getSpawnTime();
	}
	void setManagerSpawnTime(int ms) {
		manager.setSpawnTime(ms);
	}

	int spawnCount() { return manager.spawns.size(); }

	void checkEnvironment() {
		manager.run();
	}

	Wall &getWall(int index) {
		return walls.at(index);
	}

	void init() {
		Wall wall1;
		wall1.sx = startXBound;
		wall1.sy = startXBound + 40;
		wall1.ex = startYBound + 10;
		wall1.ey = endYBound - 40;
		Wall wall2;
		wall2.sx = startXBound + 40;
		wall2.sy = endYBound - 20;
		wall2.ex = endXBound - 40;
		wall2.ey = endYBound;
		Wall wall3;
		wall3.sx = endXBound - 10;
		wall3.sy = startYBound + 40;
		wall3.ex = endXBound;
		wall3.ey = endYBound - 40;
		Wall wall4;
		wall4.sx = startXBound + 40;
		wall4.sy = startYBound;
		wall4.ex = endXBound - 40;
		wall4.ey = startYBound + 10;
		walls.push_back(wall1);
		walls.push_back(wall2);
		walls.push_back(wall3);
		walls.push_back(wall4);
	};

	~Level() {};

private:
	SpawnManager manager;
	float *rects;
};

#endif // !LEVEL_H
