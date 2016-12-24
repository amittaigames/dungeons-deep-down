#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

typedef struct _Player {
	int x;
	int y;

	int xp;
	int l_next;
	int level;
	int gold;
	int health;
	int max_health;
	int power;
	int defense;

	int heal_cost;

	int m_min_count;
	int m_max_count;
	int m_min_health;
	int m_max_health;
	int m_min_power;
	int m_max_power;
	int m_min_defense;
	int m_max_defense;

	int g_min;
	int g_max;
} Player;

Player*		Player_new(int x, int y);
void 		Player_heal(Player* self);
void 		Player_level(Player* self);
void 		Player_delete(Player* self);

#endif // PLAYER_H