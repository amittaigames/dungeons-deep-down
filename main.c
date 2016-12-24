#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "include/util.h"
#include "include/room.h"
#include "include/monster.h"
#include "include/map.h"
#include "include/player.h"
#include "include/fight.h"
#include "main.h"

#define GRID_SIZE 5

Room* rooms[GRID_SIZE * GRID_SIZE];
Player* p;

int playing = 1;

// Print the help dialog
void printHelp() {
	printf("\n== Help ==\n");
	printf("info: \t\t\tPrint room information\n");
	printf("monsters: \t\tList monsters and stats\n");
	printf("look [n/s/e/w]: \tGet room information around you\n");
	printf("move [n/s/e/w]: \tMove to a room next to you\n");
	printf("player: \t\tGet your stats\n");
	printf("heal: \t\t\tHeal yourself\n");
	printf("fight [num]: \t\tFight a specified monster\n");
	printf("help: \t\t\tShow this dialog\n");
	printf("exit: \t\t\tExit the game\n");
	printf("\n");
}

// Get console input
char* getInput(char* pre) {
	printf("%s", pre);
	char* buf = (char*)malloc(32);
	fgets(buf, 32, stdin);
	buf[strlen(buf) - 1] = '\0';
	return buf;
}

// Print the stats of the monsters in the room
void printMonsters(int loc) {
	Room* room = rooms[loc];

	if (room->mcount == 0) {
		printf("There are no monsters here!\n");
		return;
	}

	printf("\n");
	for (int i = 0; i < room->mcount; i++) {
		Monster* m = room->monsters[i];
		if (m->alive) {
			printf("%d) %s: H: %d, P: %d, D:%d\n",
				i + 1, m->name, m->health, m->power, m->defense);
		} else {
			printf("%d) %s: Dead\n", i + 1, m->name);
		}
	}
	printf("\n");
}

// Print the information about the room
void printRoom(int loc) {
	Room* room = rooms[loc];
	printf("There are %d monsters defending %d gold\n",
			room->mcount, room->gold);
}

// End the game and show the score
void game_over(char* msg) {
	printf("Game Over\n");
	printf("%s\n", msg);
	printf("You reached level %d\n", p->level);
	printf("Score: %d\n", p->xp * (p->gold / 3));
}

// Parse the input from the console
void parseCommand(char** cmd) {
	int ploc = p->y * GRID_SIZE + p->x;

	// INFO
	if (!strcmp(cmd[0], "info")) {
		printRoom(ploc);
	}

	// MONSTERS
	else if (!strcmp(cmd[0], "monsters")) {
		printMonsters(ploc);
	}

	// MOVE
	else if (!strcmp(cmd[0], "move")) {
		char* dir = cmd[1];
		int ndir = -1;

		if (!strcmp(dir, "north") || !strcmp(dir, "n"))
			ndir = NORTH;
		else if (!strcmp(dir, "south") || !strcmp(dir, "s"))
			ndir = SOUTH;
		else if (!strcmp(dir, "east") || !strcmp(dir, "e"))
			ndir = EAST;
		else if (!strcmp(dir, "west") || !strcmp(dir, "w"))
			ndir = WEST;
		else
			printf("Stop that gibberish!\n");

		if (ndir != -1)
			movePlayer(p, GRID_SIZE, ndir, rooms);

		if (rooms[ploc]->mcount == 0) {
			printf("You take the %d gold from the room\n", rooms[ploc]->gold);
			p->gold += rooms[ploc]->gold;
			rooms[ploc]->cleared = 1;
		}
	}

	// LOOK
	else if (!strcmp(cmd[0], "look")) {
		char* dir = cmd[1];
		int ndir = -1;

		if (!strcmp(dir, "north") || !strcmp(dir, "n"))
			ndir = NORTH;
		else if (!strcmp(dir, "south") || !strcmp(dir, "s"))
			ndir = SOUTH;
		else if (!strcmp(dir, "east") || !strcmp(dir, "e"))
			ndir = EAST;
		else if (!strcmp(dir, "west") || !strcmp(dir, "w"))
			ndir = WEST;
		else
			printf("I don't understand crazy talk!\n");

		if (ndir != -1)
			lookThatWay(p, GRID_SIZE, ndir, rooms);
	}

	// PLAYER
	else if (!strcmp(cmd[0], "player")) {
		printf("\n");
		printf("== Player ==\n");
		printf("Health: %d/%d\t\tPower: %d\n", p->health, p->max_health, p->power);
		printf("Defense: %d\t\tGold: %d\n", p->defense, p->gold);
		printf("Exp: %d/%d\t\tLevel: %d\n", p->xp, p->l_next, p->level);
		printf("\n");
	}

	// HEAL
	else if (!strcmp(cmd[0], "heal")) {
		printf("This will cost you %d gold. Continue? [y/n]\n", p->heal_cost);
		char* in = getInput("> ");
		if (!strcmp(in, "y") || !strcmp(in, "yes")) {
			Player_heal(p);
		} else if (!strcmp(in, "n") || !strcmp(in, "no")) {
			printf("Alright, stay safe!\n");
		} else {
			printf("I don't speak that language.\n");
		}
	}

	// FIGHT
	else if (!strcmp(cmd[0], "fight")) {
		int mnum = atoi(cmd[1]);
		Monster* m = rooms[ploc]->monsters[mnum - 1];
		if (m->alive) {
			int won = Fight_begin(p, m);

			if (won) {
				int xp = m->power + m->defense + m->h_max;
				printf("You beat the %s and gained %d exp!\n", m->name, xp);
				p->xp += xp;
				rooms[ploc]->dcount++;
				Player_level(p);
			} else {
				game_over("You were killed by a monster");
			}

			if (rooms[ploc]->dcount == rooms[ploc]->mcount) {
				printf("Congrats, you cleared the room!\n");
				printf("You take the %d gold from the room\n", rooms[ploc]->gold);
				p->gold += rooms[ploc]->gold;
				rooms[ploc]->cleared = 1;
			}
		} else {
			printf("You can't fight that, it's already dead!\n");
		}
	}

	// HELP
	else if (!strcmp(cmd[0], "help")) {
		printHelp();
	}

	// EXIT
	else if (!strcmp(cmd[0], "exit")) {
		game_over("You quit the game");
		playing = 0;
	}

	else {
		printf("Enough nonsense!\n");
	}
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	printf("Dungeons Deep Down v1.0\n\n");

	// Initialize the player and middle room
	p = Player_new(GRID_SIZE / 2, GRID_SIZE / 2);
	rooms[p->y * GRID_SIZE + p->x] = Room_new(1, 100, p);

	// Game loop
	char* cmd = "~";
	while (playing) {
		cmd = getInput("> ");
		char** cmds = str_split(cmd, ' ');
		parseCommand(cmds);
	}

	// Clean up
	free(cmd);
	free(p);
	for (int i = 0; i < GRID_SIZE * GRID_SIZE; i++) {
		if (rooms[i]) {
			free(rooms[i]);
		}
	}

	return 0;
}