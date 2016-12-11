#include "penguin-9000.h"
#include "Map.h"

struct vector move(int playerID, struct map map, struct player players[])
{
	struct vector best;
	struct map mapTMP = map, mapBest;
	int i, x, y, direction = 0, distanse = 0, bestvalue = 0, bestid=0;
	for (i = 0; i < sizeof(players[playerID - 1].penguins); i++)
	{
		for ( direction = 0; direction < 6; direction++)
		{
			for (distanse = 0; distanse < 100; distanse++)//create stop condition
			{
				mapTMP = makeMove(map, direction, distanse, players[playerID].penguins[i].x, players[playerID].penguins[i].y);
				if (bestvalue>evaluate(mapTMP, players[playerID].penguins[i].x, players[playerID].penguins[i].y))
				{
					mapBest=mapTMP;
					x = players[playerID].penguins[i].x;
					y = players[playerID].penguins[i].y;
					bestvalue = evaluate(mapTMP, players[playerID].penguins[i].x, players[playerID].penguins[i].y);//optimise the shit out of it!
				}
			}
		}
	}
	return convert(mapBest, x, y, players ,playerID,bestid);
}

struct map place( struct map map, int playerID)
{
	int x, y;
	int best[3];//0-x 1-y 2-value//
	for (y = 0; y < mapSize; y++)
	{
		for (x = 0; x < mapSize; x+=2)
		{
			if (y % 2 == 1 && x == 0)
			{
				x = 1;
			}
			if (map.flows[x][y].numbOfFish == 1 && map.flows[x][y].penguin == 0)
			{
				if (evaluate(map, x, y)>best[3])
				{
					best[0] = x;
					best[1] = y;
					best[2]= evaluate(map, x, y);
				}
			}
		}
	}
	if (best[2]!=0)
	{
		map.flows[best[0]][best[1]].penguin = playerID;
	}
	return map;
}

int evaluate(struct map map, int x, int y)
{
	int direction, sum=0;
	for (direction = 0; direction < 6; direction++)
	{
		sum += evaluateBranch(map, x, y, direction);
	}
	return sum;
}

int evaluateBranch(struct map map, int x, int y, int direction)
{
	int i, sum=0;
	switch (direction)
	{
	case 0:
		for (i = 1; x-i < 0&& map.flows[x - i][y - i].penguin==0&& map.flows[x - i][y - i].numbOfFish!=0; i++)
		{
			sum += map.flows[x - i][y - i].numbOfFish*map.flows[x - i][y - i].numbOfFish; //using squares so 3 fish will be much more valuable than 1 fish//
		}
		break;
	case 1:
		for (i = 1; y - 2*i < 0 && map.flows[x][y - 2 * i].penguin == 0 && map.flows[x][y - 2 * i].numbOfFish != 0; i++)
		{
			sum += map.flows[x][y - 2*i].numbOfFish*map.flows[x][y - 2*i].numbOfFish; //using squares so 3 fish will be much more valuable than 1 fish//
		}
		break;
	case 2:
		for (i = 1; x + i < mapSize && map.flows[x + i][y - i].penguin == 0 && map.flows[x + i][y - i].numbOfFish != 0; i++)
		{
			sum += map.flows[x + i][y - i].numbOfFish*map.flows[x + i][y - i].numbOfFish; //using squares so 3 fish will be much more valuable than 1 fish//
		}
		break;
	case 3:
		for (i = 1; x + i < mapSize && map.flows[x + i][y + i].penguin == 0 && map.flows[x + i][y + i].numbOfFish != 0; i++)
		{
			sum += map.flows[x + i][y + i].numbOfFish*map.flows[x + i][y + i].numbOfFish; //using squares so 3 fish will be much more valuable than 1 fish//
		}
		break;
	case 4:
		for (i = 1; y + 2*i < mapSize && map.flows[x][y + 2 * i].penguin == 0 && map.flows[x][y + 2 * i].numbOfFish != 0; i++)
		{
			sum += map.flows[x][y + 2 * i].numbOfFish*map.flows[x][y + 2 * i].numbOfFish; //using squares so 3 fish will be much more valuable than 1 fish//
		}
		break;
	case 5:
		for (i = 1; x - i > 0 && map.flows[x-i][y -i].penguin == 0 && map.flows[x - i][y - i].numbOfFish != 0; i++)
		{
			sum += map.flows[x - i][y - i].numbOfFish*map.flows[x - i][y - i].numbOfFish; //using squares so 3 fish will be much more valuable than 1 fish//
		}
		break;
	default:
		break;
	}
	return sum;
}

struct map makeMove(struct map map, int direction, int distanse, int x, int y)//do this motherfucker cos i dont wanna//
{

	return map;
}

struct vector convert(struct map map, int x, int y, struct player players[],int playerID, int penguinID)
{
	struct vector result;
	result.xInitial = x;
	result.yInitial = y;
	result.xTarget = players[playerID].penguins[penguinID].x;
	result.yTarget = players[playerID].penguins[penguinID].y;
	return result;
}
