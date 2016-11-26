#include "UserIO.c"
#include "Map.h"
void write_file(char *filename, struct floe map[4][4], struct player players[4]);
char *read_file(const char *filename);