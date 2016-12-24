#ifndef ROOM_H
#define ROOM_H

#include <stdlib.h>
#include "monster.h"
#include "player.h"
#include "util.h"

typedef struct _Room {
	int mcount;
	int dcount;
	int gold;
	Monster* monsters[8];
	int cleared;
} Room;

Room* 	Room_new(int mcount, int gold, Player* p);
Room*	Room_rand(Player* p);
void 	Room_delete(Room* self);

#endif // ROOM_H