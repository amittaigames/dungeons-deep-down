#include "../include/fight.h"

// Start the fight
int Fight_begin(Player* p, Monster* m) {
	printf("You began a fight with a %s!\n", m->name);
	FightI inst = {p, m, 1};

	// Loop label
	battle:

	if (inst.turn == 1) {
		Fight_turnP(inst);
	} else {
		Fight_turnM(inst);
	}

	// Swap turns and check deaths
	inst.turn = !inst.turn;
	if (inst.monster->health <= 0) {
		inst.monster->alive = 0;
		return 1;
	} else if (inst.player->health <= 0) {
		return 0;
	} else {
		goto battle;
	}
}


// Player Fighting
void Fight_turnP(FightI inst) {
	printf("\nWhat will you do?\n");
	printf("1) Fight\n");
	printf("2) Heal\n");
	printf("3) Stats\n");
	printf("> ");

	char c[32];
	fgets(c, 32, stdin);
	int opt = atoi(c);
	if (opt <= 0 || opt > 3) {
		printf("That's not a valid number!\n");
		Fight_turnP(inst);
	} else {

		// Fight
		if (opt == 1) {
			int damage = inst.player->power - inst.monster->defense;
			if (damage < 1)
				damage = 1;

			inst.monster->health -= damage;
			printf("You dealt %d damage to the %s!\n", damage, inst.monster->name);
		}

		// Heal
		if (opt == 2) {
			printf("You have %d gold, and healing costs %d.\n",
				inst.player->gold, inst.player->heal_cost);
			printf("Continue? [y/n] > ");
			char c[32];
			fgets(c, 32, stdin);
			c[strlen(c) - 1] = '\0';
			if (!strcmp(c, "yes") || !strcmp(c, "y")) {
				if (inst.player->gold >= inst.player->heal_cost) {
					Player_heal(inst.player);
					goto finish_p;
				} else {
					printf("You don't have enough gold!\n");
					Fight_turnP(inst);
				}
			} else if (!strcmp(c, "no") || !strcmp(c, "n")) {
				printf("Let's be careful out there\n");
				Fight_turnP(inst);
			} else {
				printf("I couldn't understand you\n");
				Fight_turnP(inst);
			}
		}

		// Stats
		if (opt == 3) {
			Monster* m = inst.monster;
			Player* p = inst.player;
			printf("%s: H: %d, P: %d, D: %d\n", m->name, m->health, m->power, m->defense);
			printf("You: H: %d, P: %d, D: %d\n", p->health, p->power, p->defense);
			Fight_turnP(inst);
		}
	}

	finish_p:
	return;
}

// Monster Fighting
void Fight_turnM(FightI inst) {
	int damage = inst.monster->power - inst.player->defense;
	if (damage < 1)
		damage = 1;

	inst.player->health -= damage;
	printf("The %s dealt %d damage!\n", inst.monster->name, damage);
}