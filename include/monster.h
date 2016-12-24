#ifndef MONSTER_H
#define MONSTER_H

#include <stdlib.h>
#include <string.h>

static char* monster_names[] = {
	"Zombie",
	"Demon",
	"Mummy",
	"Skeleton",
	"Ghost",
	"Centaur",
	"Tarantula"
};

static int monster_name_count = 7;

typedef struct _Monster {
	char* name;
	int health;
	int power;
	int defense;
	int alive;
	int h_max;
} Monster;

Monster* 	Monster_new(char* name, int health, int power, int defense);
void 		Monster_delete(Monster* self);

#endif // MONSTER_H