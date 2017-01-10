#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "GameLogic.h"
#include "penguin-9000.h"
#include <math.h>

struct Vector movePenguin(int playerID, void *mapP, int sizeX, int sizeY, struct Player players[],int numberOfPlayers)
{
	struct Vector best={-1,-1,-1,-1};
	void *mapTMPP = malloc(sizeof(struct Floe)*sizeX*sizeY);
    struct Player *playerstmp=copyplayers(players,numberOfPlayers);
	int i, direction = 0, distanse = 0, playerIndex=giveIndex(playerID,players,numberOfPlayers);
	float newEvaluate, bestvalue=0;

	for (i = 0; i < players[playerIndex].numberOfPenguins; i++)//evaluating every possible move for all penguins of playerID//
	{
		for ( direction = 0; direction < 6; direction++)
		{
		    //copying the map
		    memcpy(mapTMPP,mapP,sizeof(struct Floe)*sizeX*sizeY);

			for (distanse = 1;players[playerIndex].penguins[i].x+vectors[direction].x*distanse>=0 && players[playerIndex].penguins[i].y+vectors[direction].y*distanse>=0 &&
                              players[playerIndex].penguins[i].x+vectors[direction].x*distanse<sizeX && players[playerIndex].penguins[i].y+vectors[direction].y*distanse<sizeY; distanse++)//create stop condition
                    {
			    //if a projected move is valid, evaluate it
                if(movement(players[playerIndex].penguins[i].x,players[playerIndex].penguins[i].y ,
                         players[playerIndex].penguins[i].x+vectors[direction].x*distanse,
                         players[playerIndex].penguins[i].y+vectors[direction].y*distanse,
                         mapTMPP,sizeX,sizeY,playerID,playerstmp,numberOfPlayers))
                   {
                       //evaluating projected move
                       newEvaluate=evaluate(mapTMPP, sizeX, sizeY, playerID, playerstmp,numberOfPlayers);
                       if (bestvalue<newEvaluate || best.xInitial==-1 || best.yInitial==-1 || best.xTarget==-1 || best.yTarget==-1)//new best move has been found, generating its vector//
                        {
                            //new best move found!
                            best.xInitial = players[playerIndex].penguins[i].x;
                            best.yInitial = players[playerIndex].penguins[i].y;
                            best.xTarget=players[playerIndex].penguins[i].x+vectors[direction].x*distanse;
                            best.yTarget=players[playerIndex].penguins[i].y+vectors[direction].y*distanse;
                            bestvalue = newEvaluate;
                        }
                   }
                   free(playerstmp);
                   playerstmp=copyplayers(players,numberOfPlayers);
                   memcpy(mapTMPP,mapP,sizeof(struct Floe)*sizeX*sizeY);
                   }
        }
    }
    free(mapTMPP);
	return best;
}

struct Point placePenguin(void *mapP, int sizeX, int sizeY, int playerID, struct Player players[], int numberOfPlayers)
{
    struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
	struct Floe *mapTMP = malloc(sizeof(struct Floe)*sizeX*sizeY);
	struct Player *playerstmp;
	struct Point result={-1,-1};
	int x, y;
	float best=0;
	for (y = 0; y < sizeY; y++)
	{
		for (x = 0; x < sizeX; x++)
		{
			if ((*map)[x][y].numbOfFish == 1 && (*map)[x][y].whosPenguin == 0)
			{
			    //copy the map and players
                playerstmp=copyplayers(players,numberOfPlayers);
                memcpy( mapTMP, * map, sizeof(struct Floe) * sizeX * sizeY);

                //project a move using copied data
                placement(x, y, mapTMP,sizeX,sizeY,playerID,playerstmp,numberOfPlayers);

                //evaluate projected situation
			    int newEvalueate = evaluate(mapTMP, sizeX, sizeY, playerID, playerstmp,numberOfPlayers);
				if (newEvalueate>best || result.x==-1 || result.y==-1)
				{
					result.x = x;
					result.y = y;
					best = newEvalueate;
				}
				free(playerstmp);
				free(mapTMP);
			}
		}
	}
	//releasing memory
	free(mapTMP);
	free(playerstmp);
	return result;
}

struct Player *copyplayers(struct Player players[], int playerCount)
{
    int i,k, pengI;
    struct Player *copy=malloc(sizeof(struct Player)*playerCount);
    for(i=0;i<playerCount;i++)
    {
        copy[i]=players[i];
        for(k=0;k<copy[i].numberOfPenguins;k++)
        {
            copy[i].penguins=malloc(sizeof(struct penguin)*copy[i].numberOfPenguins);
            for(pengI=0;pengI<copy[i].numberOfPenguins;pengI++)
            {
                copy[i].penguins[pengI]=players[i].penguins[pengI];
            }
        }

    }
    return copy;
}

float evaluate(void *mapP, int sizeX, int sizeY, int playerID, struct Player players[], int numberOfPlayers)// needs reworking (might be fixed already XD)
{
	int direction, i,k;
	float sum=0;
	for (i = 0; i < numberOfPlayers; i++)
	{
	    //counting value of a move, from friendly penguins (increace the value)
		if (players[i].playerID == playerID)
		{
			for (k = 0; k < players[i].numberOfPenguins; k++)
			{
                if(players[i].penguins[k].x>=0 && players[i].penguins[k].y>=0)
                {
                    for (direction = 0; direction < 6; direction++)
                    {
                        sum +=pow(check_how_many_fishes(players[i].penguins[k].x,players[i].penguins[k].y,mapP,sizeX,sizeY),2)* evaluateBranch(mapP, sizeX, sizeY, players[i].penguins[k].x, players[i].penguins[k].y, direction)/ giveAgression(players,numberOfPlayers,mapP,sizeX,sizeY,playerID);
                    }
                }
			}
		}
		//counting value of a move, from enemy penguins (decrease the value)
		else
		{
            if (players[i].playerID != playerID && players[i].playerID>0)
            {
                for (k = 0; k < players[i].numberOfPenguins; k++)
                {
                    if(players[i].penguins[k].x>=0 && players[i].penguins[k].y>=0)
                    {
                        for (direction = 0; direction < 6; direction++)
                        {
                            sum -=pow(check_how_many_fishes(players[i].penguins[k].x,players[i].penguins[k].y,mapP,sizeX,sizeY),2)* giveAgression(players,numberOfPlayers,mapP,sizeX,sizeY,playerID) * evaluateBranch(mapP, sizeX, sizeY, players[i].penguins[k].x, players[i].penguins[k].y, direction);
                        }
                    }
                }
            }
		}
	}
	return sum;
}

float evaluateBranch(void *mapP, int sizeX, int sizeY, int x, int y, int direction)
{
	struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
	int i;
	float sum=0;
	for(i=1; x+i*vectors[direction].x<sizeX && y+i*vectors[direction].y<sizeY && x+i*vectors[direction].x>=0 && y+i*vectors[direction].y>=0 && (*map)[x + i*vectors[direction].x][y + i*vectors[direction].y].numbOfFish!=0 && (*map)[x + i*vectors[direction].x][y + i*vectors[direction].y].whosPenguin==0; i++)
    {
        sum+=((*map)[x + i*vectors[direction].x][y + i*vectors[direction].y].numbOfFish);
    }
	return sum;
}


struct Vector convert(void *mapP, int sizeX, int sizeY, int x, int y, struct Player players[],int playerID, int penguinID)
{
	struct Vector result;
	result.xInitial = x;
	result.yInitial = y;
	result.xTarget = players[playerID].penguins[penguinID].x;
	result.yTarget = players[playerID].penguins[penguinID].y;
	return result;
}

void findTarget(struct Vector * Vector, int x, int y, int distance, int direction)
{
	(*Vector).xTarget = x+vectors[direction].x*distance;
	(*Vector).yTarget = y+vectors[direction].y*distance;
}

float giveAgression(struct Player players[], int PlayerCount, struct Floe *mapp, int sizeX, int sizeY, int playerID)
{
    float aggresion;
    int numOfFloes=0, x,y, enemyScore=0;
   	struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapp;

   	//counting number of Floes still in the game
   	for(y=0;y<sizeY;y++)
    {
        for(x=0;x<sizeX;x++)
            if((*map)[x][y].numbOfFish>0)
        {
            numOfFloes++;
        }
    }

    //counting everyone else's score
    for(x=0;x<PlayerCount;x++)
    {
        if(players[x].playerID!=playerID)
        {
            enemyScore+=players[x].score;
        }
    }
    //calculating the aggresion factor
    aggresion = ((float) players[giveIndex(playerID,players,PlayerCount)].score/ (float) enemyScore)/numOfFloes*sizeX*sizeY/2;
    return aggresion;
}
int giveBranches(int x, int y, struct Floe *mapp, int sizeX, int sizeY)
{
    struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapp;
    int i, branches;
    for(i=0;i<6;i++)
    {
        if(y+vectors[i].y>=0 && y+vectors[i].y<sizeY && x+vectors[i].x>=0 && x+vectors[i].x<sizeX && (*map)[x+vectors[i].x][y+vectors[i].y].numbOfFish!=0 && (*map)[x+vectors[i].x][y+vectors[i].y].whosPenguin==0)
            branches++;
    }
    return branches;
}
