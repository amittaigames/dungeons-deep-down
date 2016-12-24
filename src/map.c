#include "../include/map.h"

// Move the player with checks
void movePlayer(Player* p, int size, int dir, Room** map) {
	if (validMoveCheck(p->x, p->y, size, dir)) {
		if (dir == NORTH) {
			p->y--;
			printf("Moved north (%d/%d)\n", p->y + 1, size);
		}

		if (dir == SOUTH) {
			p->y++;
			printf("Moved south (%d/%d)\n", p->y + 1, size);
		}

		if (dir == EAST) {
			p->x++;
			printf("Moved east (%d/%d)\n", p->x + 1, size);
		}

		if (dir == WEST) {
			p->x--;
			printf("Moved west (%d/%d)\n", p->x + 1, size);
		}

		// If the room doesn't exist, make one
		if (!map[p->y * size + p->x]) {
			map[p->y * size + p->x] = Room_rand(p);
		}

		// If the room is cleared, make a new one
		if (map[p->y * size + p->x]->cleared) {
			map[p->y * size + p->x] = Room_rand(p);
		}
	} else {
		printf("You can't go that way!\n");
	}
}

// Look in a certain direction
void lookThatWay(Player* p, int size, int dir, Room** map) {
	if (validMoveCheck(p->x, p->y, size, dir)) {
		if (dir == NORTH) {
			if (!map[(p->y - 1) * size + p->x]) {
				map[(p->y - 1) * size + p->x] = Room_rand(p);
			}
			if (map[(p->y - 1) * size + p->x]->cleared) {
				map[(p->y - 1) * size + p->x] = Room_rand(p);
			}
			printRoom((p->y - 1) * size + p->x);
		}
		if (dir == SOUTH) {
			if (!map[(p->y + 1) * size + p->x]) {
				map[(p->y + 1) * size + p->x] = Room_rand(p);
			}
			if (map[(p->y + 1) * size + p->x]->cleared) {
				map[(p->y + 1) * size + p->x] = Room_rand(p);
			}
			printRoom((p->y + 1) * size + p->x);
		}
		if (dir == EAST) {
			if (!map[p->y * size + (p->x + 1)]) {
				map[p->y * size + (p->x + 1)] = Room_rand(p);
			}
			if (map[p->y * size + (p->x + 1)]->cleared) {
				map[p->y * size + (p->x + 1)] = Room_rand(p);
			}
			printRoom(p->y * size + (p->x + 1));
		}
		if (dir == WEST) {
			if (!map[p->y * size + (p->x - 1)]) {
				map[p->y * size + (p->x - 1)] = Room_rand(p);
			}
			if (map[p->y * size + (p->x - 1)]->cleared) {
				map[p->y * size + (p->x - 1)] = Room_rand(p);
			}
			printRoom(p->y * size + (p->x - 1));
		}
	} else {
		printf("You can't look any further!\n");
	}
}

// Boundary check
int validMoveCheck(int x, int y, int size, int dir) {
	if (dir == NORTH) {
		if (y == 0) {
			return 0;
		} else {
			return 1;
		}
	}

	if (dir == SOUTH) {
		if (y == size - 1) {
			return 0;
		} else {
			return 1;
		}
	}

	if (dir == EAST) {
		if (x == size - 1) {
			return 0;
		} else {
			return 1;
		}
	}

	if (dir == WEST) {
		if (x == 0) {
			return 0;
		} else {
			return 1;
		}
	}

	return 0;
}