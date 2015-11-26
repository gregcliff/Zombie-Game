#ifndef PROGRESS_H
#define PROGRESS_H
#include "Player.h"

class GameProgress {
public:
	GameProgress() { };
	//Player player;
//	void setPlayer(Player nPlayer) { player = nPlayer; }
	void killedAZombie() { zombiesKilled++; }

private:
	int zombiesKilled = 0;
};

#endif