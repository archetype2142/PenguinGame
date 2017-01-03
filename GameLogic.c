#include <stdlib.h>
#include "Map.h"


int mapSize;

int sign(int n)
{
    if (n>0)
	{
		return 1;
	}
	else
	{
		if (n==0)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
}
int check_how_many_fishes(int x, int y, void *mapP, int sizeX, int sizeY)
{
    struct Floe (*map)[sizeX][sizeY]= (struct Floe(*)[sizeX][sizeY]) mapP;
	return (*map)[x][y].numbOfFish;
}

int check_penguin(int x, int y, void *mapP, int sizeX, int sizeY)
{
	struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
	return (*map)[x][y].whosPenguin;
}

int check_valid_move(int x1, int y1, int x2, int y2, void *mapP, int sizeX, int sizeY)
{
	int pathClear = 1;
	int y, x = 0;
	// checking fields above or below current field
	if ((x2 - x1) == 0 && (y2 - y1) % 2 == 0)
	{
		for (y = y1; y == y2; y += sign(y2 - y1) * 2)
		{
			if (y < 0 || y > mapSize || check_penguin(x1, y, mapP, sizeX, sizeY) != 0 || check_how_many_fishes(x, y, mapP, sizeX, sizeY) == 0)
			{
				pathClear = 0;
				break;
			}
		}
	}
	else {
		if (abs(x2 - x1) != abs(y2 - y1))
		{
			pathClear = 0;
		}
		else {
			// checking fields on diaognals
			for (x = x1, y = y1; x == x2; x += sign(x2 - x1), y == sign(y2 - y1))
			{
				if (y < 0 || x < 0 || x > mapSize || y > mapSize || check_penguin(x, y, mapP, sizeX, sizeY) != 0 || check_how_many_fishes(x, y, mapP, sizeX, sizeY) == 0)
				{
					pathClear = 0;
					break;
				}
			}
		}
	}
	return pathClear;
}

int check_target_coordinates(int x, int y, void *mapP, int sizeX, int sizeY)
{
	struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
	if (x>=0 && y >=0 && x<sizeX && y<sizeY && (*map)[x][y].whosPenguin == 0 && (*map)[x][y].numbOfFish != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_coordinates(int x, int y, void *mapP, int sizeX, int sizeY, int playerId)
{
	struct Floe (*map)[sizeX][sizeY]= (struct Floe(*)[sizeX][sizeY]) mapP;
	if ((*map)[x][y].whosPenguin == playerId)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void place_penguin(int x, int y, int playerID, void *mapP, int sizeX, int sizeY)
{
	struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
	(*map)[x][y].whosPenguin = playerID;
}

int giveIndex(int playerID, struct Player players[], int playerCount)
{
	int i;
	for (i = 0; i < playerCount; i++)
		if (players[i].playerID == playerID)
			return i;
    return -1;
}

void checkIfPlaying(int playerID, struct Player *players, int playerCount)
{
    int i, freePlace, isPlaying=0;
    for(i=playerCount;i>=0;i--)
    {
        if(players[i].playerID==-1)
        {
            freePlace=i;
        }
        if(players[i].playerID==playerID)
        {
            isPlaying=1;
        }
    }
    if(isPlaying==0)
    {
        players[freePlace].playerID=playerID;
    }
}

int IsGameOver(void *mapP, int sizeX, int sizeY, int playerID, struct Player players[],int playerCount)
{
    int i,k, directions=0, movePossible=0;
	for(i=0;i<playerCount;i++)
    {
        for(k=0;k<players[i].numberOfPenguins;k++)
        {
            for(directions=0;directions<6;directions++)
            {
                if(check_target_coordinates(players[i].penguins[k].x+vectors[directions].x,players[i].penguins[k].y+vectors[directions].y,mapP,sizeX,sizeY))
                {
                    movePossible=1;
                }
            }
        }

    }
    return movePossible;
}
