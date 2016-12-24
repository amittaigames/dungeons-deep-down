#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <string.h>

int 	str_contains(char* str, char delim);
char**	str_split(char* str, char delim);
int 	random_num(int limit);
int		random_n(int min, int max);

#endif // UTIL_H