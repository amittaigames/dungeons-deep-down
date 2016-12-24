#include "../include/monster.h"

// New monster
Monster* Monster_new(char* name, int health, int power, int defense) {
	Monster* self = (Monster*)malloc(sizeof(Monster));

	self->name = strdup(name);
	self->health = health;
	self->power = power;
	self->defense = defense;
	self->alive = 1;
	self->h_max = health;

	return self;
}

// Delete monster
void Monster_delete(Monster* self) {
	free(self->name);
	free(self);
}