#include "../include/room.h"

// Initialize a new room
Room* Room_new(int mcount, int gold, Player* p) {
	Room* self = (Room*)malloc(sizeof(Room));

	self->mcount = mcount;
	self->dcount = 0;
	self->gold = gold;
	self->cleared = 0;

	// Initialize all of the monsters
	for (int i = 0; i < mcount; i++) {
		char* name = monster_names[rand() % monster_name_count];
		int health = random_n(p->m_min_health, p->m_max_health);
		int power = random_n(p->m_min_power, p->m_max_power);
		int defense = random_n(p->m_min_defense, p->m_max_defense);

		self->monsters[i] = Monster_new(name, health, power, defense);
	}

	return self;
}

// Randomly create a room based on player stats
Room* Room_rand(Player* p) {
	int r_mcount = random_n(p->m_min_count, p->m_max_count);
	int r_gold = random_n(p->g_min, p->g_max);

	return Room_new(r_mcount, r_gold, p);
}

// Delete a room
void Room_delete(Room* self) {
	free(self);
}