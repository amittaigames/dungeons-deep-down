#include "../include/util.h"

// See how many times a string contains a character
int str_contains(char* str, char delim) {
	int count = 0;
	int len = strlen(str);

	for (int i = 0; i < len; i++) {
		if (str[i] == delim) {
			count++;
		}
	}

	return count;
}

// Split a string (taken from vextools)
char** str_split(char* str, char delim) {
	int length = strlen(str);
	int size = str_contains(str, delim) + 1;
	char** split = (char**)malloc((size + 1) * sizeof(char*));

	int it = 0;
	int currentSize = 0;
	for (int i = 0; i < size; i++) {
		for (int j = it; j <= length; j++) {
			if (str[it] == delim || str[it] == '\0') {
				split[i] = (char*)malloc(sizeof(char) * currentSize);
				for (int k = 0; k < currentSize; k++) {
					split[i][k] = str[(it - currentSize) + k];
				}
				it++;
				currentSize = 0;
				break;
			} else {
				it++;
				currentSize++;
			}
		}
	}

	split[size] = NULL;

	return split;
}

// Random number between 0 and limit
int random_num(int limit) {
	int divisor = RAND_MAX / (limit + 1);
	int val;

	do {
		val = rand() / divisor;
	} while (val > limit);

	return val;
}

// An easier way to get a random number between min and max
int	random_n(int min, int max) {
	return random_num(max - min) + min;
}