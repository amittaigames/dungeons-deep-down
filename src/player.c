#include "../include/player.h"

// Initialize a new player
Player*	Player_new(int x, int y) {
	Player* self = (Player*)malloc(sizeof(Player));

	self->x = x;
	self->y = y;

	self->xp = 0;
	self->l_next = 30;
	self->level = 1;
	self->gold = 0;
	self->health = 20;
	self->max_health = 20;
	self->power = 4;
	self->defense = 3;

	self->heal_cost = 20;

	self->m_min_count = 0;
	self->m_max_count = 8;
	self->m_min_health = 5;
	self->m_max_health = 20;
	self->m_min_power = 1;
	self->m_max_power = 4;
	self->m_min_defense = 0;
	self->m_max_defense = 3;

	self->g_min = 10;
	self->g_max = 50;

	return self;
}

// Heal the player
void Player_heal(Player* self) {
	if (self->gold >= self->heal_cost) {
		self->health = self->max_health;
		self->gold -= self->heal_cost;
		printf("You have been healed\n");
	} else {
		printf("You don't have enough gold to heal!\n");
	}
}

// Check the level status of the player
void Player_level(Player* self) {
	// Level up on first level
	if (self->level == 1) {
		self->level++;
		printf("Level up! Now at level %d\n", self->level);

		self->max_health = 25;
		self->health += 5;
		self->power += 2;
		self->defense += 1;

		self->heal_cost = 25;
		self->m_min_health = 7;
		self->m_max_health = 23;
		self->m_min_power = 2;
		self->m_max_power = 6;
		self->m_min_defense = 2;
		self->m_max_defense = 5;
		self->g_min = 15;
		self->g_max = 55;
		return;
	}

	// Check every level after 1
	if (self->xp >= self->l_next) {
		self->level++;
		printf("Level up! Now at level %d\n", self->level);
		self->l_next += self->level * 6;

		int h = random_n(3, 7);
		self->max_health += h;
		self->health += h;
		self->power += random_n(2, 5);
		self->defense += random_n(1, 3);

		self->heal_cost += 5;
		self->m_min_health += random_n(1, 4);
		self->m_max_health += random_n(1, 4);
		self->m_min_power += random_n(1, 3);
		self->m_max_power += random_n(1, 3);
		self->m_min_defense += random_n(0, 3);
		self->m_max_defense += random_n(0, 3);
		self->g_min += random_n(4, 10);
		self->g_max += random_n(5, 11);

		Player_level(self); // Double check
	}

}

void Player_delete(Player* self) {
	free(self);
}