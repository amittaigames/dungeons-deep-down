#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include "room.h"
#include "player.h"
#include "../main.h"

enum Directions {
	NORTH,
	SOUTH,
	EAST,
	WEST
};

void movePlayer(Player* p, int size, int dir, Room** map);
void lookThatWay(Player* p, int size, int dir, Room** map);
int validMoveCheck(int x, int y, int size, int dir);

#endif // MAP_H