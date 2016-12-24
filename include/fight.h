#ifndef FIGHT_H
#define FIGHT_H

#include <stdio.h>
#include "player.h"
#include "monster.h"

typedef struct _FightI {
	Player* player;
	Monster* monster;
	int turn;
} FightI;

int Fight_begin(Player* p, Monster* m);
void Fight_turnP(FightI inst);
void Fight_turnM(FightI inst);

#endif // FIGHT_H