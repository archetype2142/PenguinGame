#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Map.h"
#include "UserIO.h"
struct directions vectors[6] = { {-1, -1},{0,-2},{1,-1},{1,1},{0,2},{-1,1} };

void randomise(int sizeX, int sizeY, struct Floe map[sizeX][sizeY] )
{
 	int x, y;
	srand(time(NULL));
	for (y = 0; y < sizeY; y++)
		for (x = ((y) % 2); x < sizeX; x += 2)
		{
			map[x][y].numbOfFish =1 + (rand()%2);
			map[x][y].whosPenguin = 0;
		}
    for (y = 0; y < sizeY; y++)
		for (x = ((y) % 2)+1; x < sizeX; x += 2)
		{
			map[x][y].numbOfFish =0;
			map[x][y].whosPenguin = 0;
		}
}

int main(int argc, char* argv[])
{
	char *filename = argv[1];
	int sizeX=atoi(argv[2]), sizeY=atoi(argv[3]), playersn=atoi(argv[4]), penguins=atoi(argv[5]), i,k;
	struct Floe map[sizeX][sizeY];
	struct Player players[playersn];
	for(i=0;i<playersn;i++)
    {
        players[i].numberOfPenguins=penguins;
        players[i].score=0;
        players[i].penguins = malloc(sizeof(struct penguin)*penguins);
        for(k=0;k<penguins;k++)
        {
            players[i].penguins[k].x = -1;
            players[i].penguins[k].y = -1;
        }
        players[i].playerID = -1;
    }
    randomise(sizeX, sizeY, map);
    write_file(filename, map, sizeX, sizeY, players,playersn);
	}
