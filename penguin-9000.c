﻿#include "penguin-9000.h"
#include "Map.h"

struct vector move(int playerID, void *mapP, int sizeX, int sizeY, struct player players[])
{
	struct vector best;
	struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
	struct Floe mapTMP[sizeX][sizeY];
	void *mapTMPP = mapTMP;
	int i, direction = 0, distanse = 0, bestvalue = 0;
	for (i = 0; i < sizeof(players[playerID].penguins); i++)//evaluating evry possible move for all penguins of playerID//
	{
		for ( direction = 0; direction < 6; direction++)
		{
			for (distanse = 0; distanse < 100; distanse++)//create stop condition
			{
				makeMove(mapP, mapTMPP, sizeX, sizeY, direction, distanse, players[playerID].penguins[i].x, players[playerID].penguins[i].y);
				if (bestvalue<evaluate(mapTMPP, sizeX, sizeY, playerID, players))//new best move has been found, generating its vector//
				{
					findTarget(&best, players[playerID].penguins[i].x, players[playerID].penguins[i].y, distanse, direction);
					best.xInitial = players[playerID].penguins[i].x;
					best.yInitial = players[playerID].penguins[i].y;
					bestvalue = evaluate(mapTMPP, sizeX, sizeY, playerID, players);
				}
			}
		}
	}
	return best;
}

struct point place(void *mapP, int sizeX, int sizeY, int playerID, struct player players[])
{
	struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
	struct point result;
	int x, y;
	int best=0;
	for (y = 0; y < sizeY; y++)
	{
		for (x = 0; x < sizeX; x+=2)
		{
			if (y % 2 == 1 && x == 0)
			{
				x = 1;
			}
			if ((*map).flows[x][y].numbOfFish == 1 && (*map).flows[x][y].penguin == 0)
			{
				if (evaluate(mapP, sizeX, sizeY, playerID, players)>best)
				{
					result.x = x;
					result.y = y;
					best = evaluate(mapP, sizeX, sizeY, playerID, players);
				}
			}
		}
	}
	return result;
}

int evaluate(void *mapP, int sizeX, int sizeY, int playerID, struct player players[])// needs reworking 
{
	int direction, sum=0;
	for (direction = 0; direction < 6; direction++)
	{
		sum += evaluateBranch(mapP, sizeX, sizeY, x, y, direction);//fix!
	}
	return sum;
}

int evaluateBranch(void *mapP, int sizeX, int sizeY, int x, int y, int direction)//update!!
{
	struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
	int i, sum=0;
	switch (direction)
	{
	case 0:
		for (i = 1; x-i < 0&& (*map).flows[x - i][y - i].penguin==0&& (*map).flows[x - i][y - i].numbOfFish!=0; i++)
		{
			sum += (*map).flows[x - i][y - i].numbOfFish*(*map).flows[x - i][y - i].numbOfFish; //using squares so 3 fish will be much more valuable than 1 fish//
		}
		break;
	case 1:
		for (i = 1; y - 2*i < 0 && (*map).flows[x][y - 2 * i].penguin == 0 && (*map).flows[x][y - 2 * i].numbOfFish != 0; i++)
		{
			sum += (*map).flows[x][y - 2*i].numbOfFish*(*map).flows[x][y - 2*i].numbOfFish; //using squares so 3 fish will be much more valuable than 1 fish//
		}
		break;
	case 2:
		for (i = 1; x + i < sizeX && (*map).flows[x + i][y - i].penguin == 0 && (*map).flows[x + i][y - i].numbOfFish != 0; i++)
		{
			sum += (*map).flows[x + i][y - i].numbOfFish*(*map).flows[x + i][y - i].numbOfFish; //using squares so 3 fish will be much more valuable than 1 fish//
		}
		break;
	case 3:
		for (i = 1; x + i < sizeX && (*map).flows[x + i][y + i].penguin == 0 && (*map).flows[x + i][y + i].numbOfFish != 0; i++)
		{
			sum += (*map).flows[x + i][y + i].numbOfFish*(*map).flows[x + i][y + i].numbOfFish; //using squares so 3 fish will be much more valuable than 1 fish//
		}
		break;
	case 4:
		for (i = 1; y + 2*i < sizeY && (*map).flows[x][y + 2 * i].penguin == 0 && (*map).flows[x][y + 2 * i].numbOfFish != 0; i++)
		{
			sum += (*map).flows[x][y + 2 * i].numbOfFish*(*map).flows[x][y + 2 * i].numbOfFish; //using squares so 3 fish will be much more valuable than 1 fish//
		}
		break;
	case 5:
		for (i = 1; x - i > 0 && (*map).flows[x-i][y -i].penguin == 0 && (*map).flows[x - i][y - i].numbOfFish != 0; i++)
		{
			sum += (*map).flows[x - i][y - i].numbOfFish*(*map).flows[x - i][y - i].numbOfFish; //using squares so 3 fish will be much more valuable than 1 fish//
		}
		break;
	default:
		break;
	}
	return sum;
}

void makeMove(void *mapOrgP, void *mapNewP, int sizeX, int sizeY, int direction, int distanse, int x, int y)//do this motherfucker cos i dont wanna//
{

}

struct vector convert(void *mapP, int sizeX, int sizeY, int x, int y, struct player players[],int playerID, int penguinID)
{
	struct vector result;
	result.xInitial = x;
	result.yInitial = y;
	result.xTarget = players[playerID].penguins[penguinID].x;
	result.yTarget = players[playerID].penguins[penguinID].y;
	return result;
}

void findTarget(struct vector * vector, int x, int y, int distance, int direction)
{
	(*vector).xTarget = vectors[direction].x*distance;
	(*vector).yTarget = vectors[direction].y*distance;
}