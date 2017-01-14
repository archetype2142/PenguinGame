#include "Map.h"
#include "P9KR.h"
#include "GameLogic.h"
#include <stdlib.h>
#include <string.h>
#define DEPTH 5

struct Vector movePenguinR(int playerID, void *mapP, int sizeX, int sizeY, struct Player players[],int numberOfPlayers)
{
    struct Vector chain[DEPTH];
    recursionAlfa(mapP,sizeX,sizeY,players,numberOfPlayers,0,playerID,chain);
    return chain[0];
}

struct Point placePenguin(void *mapP, int sizeX, int sizeY, int playerID, struct Player players[], int numberOfPlayers)
{

}

int recursionAlfa(struct Floe *Map, int sizeX, int sizeY, struct Player players[], int plaayerCount, int depth, int playerID, struct Vector *chain)
{
    struct Floe *mapTMPP=NULL;
    struct Vector step;
    struct Player *playerstmp=copyplayers(players,plaayerCount);
    int direction, distanse, playerIndex=giveIndex(playerID,players,plaayerCount),i, best, newbest, flag=1;
    if(depth>DEPTH)
        return evaluate(Map,sizeX,sizeY,playerID,players,plaayerCount);
    memcpy(mapTMPP,Map,sizeof(struct Floe)*sizeX*sizeY);
    for(i=0;i<players[playerIndex].numberOfPenguins;i++)
    {
    for(direction=0;direction<6;++direction)
        {
            for(distanse=1;players[playerIndex].penguins[i].x+vectors[direction].x*distanse>=0 && players[playerIndex].penguins[i].y+vectors[direction].y*distanse>=0 &&
                players[playerIndex].penguins[i].x+vectors[direction].x*distanse<sizeX && players[playerIndex].penguins[i].y+vectors[direction].y*distanse<sizeY;distanse++)
                {
                    if(movement(players[playerIndex].penguins[i].x,
                       players[playerIndex].penguins[i].y ,
                       players[playerIndex].penguins[i].x+vectors[direction].x*distanse,
                       players[playerIndex].penguins[i].y+vectors[direction].y*distanse,
                       mapTMPP,sizeX,sizeY,playerID,playerstmp,plaayerCount))
                        {
                            step.xInitial=players[playerIndex].penguins[i].x;
                            step.yInitial=players[playerIndex].penguins[i].y;
                            step.xTarget=players[playerIndex].penguins[i].x+vectors[direction].x*distanse;
                            step.yTarget=players[playerIndex].penguins[i].y+vectors[direction].y*distanse;
                            newbest=recursionBeta(mapTMPP,sizeX,sizeY,playerstmp,plaayerCount,++depth,playerID,chain);
                            if(flag||best<newbest)
                            {
                                best=newbest;
                                flag=0;
                                chain[depth]=step;
                            }
                            memcpy(mapTMPP,Map,sizeof(struct Floe)*sizeX*sizeY);
                            playerstmp=copyplayers(players,plaayerCount);
                        }
                }
        }
    }
    return best;
}

int recursionBeta(struct Floe *Map, int sizeX, int sizeY, struct Player players[], int plaayerCount, int depth, int playerID, struct Vector *chain)
{
    struct Floe *mapTMPP=NULL;
    struct Vector step;
    struct Player *playerstmp=copyplayers(players,plaayerCount);
    int direction, distanse, playerIndex=giveIndex(playerID,players,plaayerCount),i, worst, newWorst, flag=1;//change playerIdnex
    memcpy(mapTMPP,Map,sizeof(struct Floe)*sizeX*sizeY);
    for(i=0;i<players[playerIndex].numberOfPenguins;i++)
    {
    for(direction=0;direction<6;++direction)
        {
            for(distanse=1;players[playerIndex].penguins[i].x+vectors[direction].x*distanse>=0 && players[playerIndex].penguins[i].y+vectors[direction].y*distanse>=0 &&
                players[playerIndex].penguins[i].x+vectors[direction].x*distanse<sizeX && players[playerIndex].penguins[i].y+vectors[direction].y*distanse<sizeY;distanse++)
                {
                    if(movement(players[playerIndex].penguins[i].x,
                       players[playerIndex].penguins[i].y ,
                       players[playerIndex].penguins[i].x+vectors[direction].x*distanse,
                       players[playerIndex].penguins[i].y+vectors[direction].y*distanse,
                       mapTMPP,sizeX,sizeY,playerID,playerstmp,plaayerCount))
                        {
                            step.xInitial=players[playerIndex].penguins[i].x;
                            step.yInitial=players[playerIndex].penguins[i].y;
                            step.xTarget=players[playerIndex].penguins[i].x+vectors[direction].x*distanse;
                            step.yTarget=players[playerIndex].penguins[i].y+vectors[direction].y*distanse;
                            newWorst=recursionAlfa(mapTMPP,sizeX,sizeY,playerstmp,plaayerCount,++depth,playerID,chain);
                            if(flag||worst>newWorst)
                            {
                                worst=newWorst;
                                flag=0;
                                chain[depth]=step;
                            }
                            memcpy(mapTMPP,Map,sizeof(struct Floe)*sizeX*sizeY);
                            playerstmp=copyplayers(players,plaayerCount);
                        }
                }
        }
    }
    return worst;
}
float evaluate(void *mapP, int sizeX, int sizeY, int playerID, struct Player players[], int numberOfPlayers)// needs reworking (might be fixed already XD)
{
    int direction, i,k;
    float sum=0;
    for (i = 0; i < numberOfPlayers; i++)
    {
        if (players[i].playerID == playerID)
        {
            for (k = 0; k < players[i].numberOfPenguins; k++)
            {
                if(players[i].penguins[k].x>=0 && players[i].penguins[k].y>=0)
                {
                    for (direction = 0; direction < 6; direction++)
                    {
                        sum +=(giveBranches(players[i].penguins[k].x, players[i].penguins[k].y,mapP,sizeX,sizeY)) * evaluateBranch(mapP, sizeX, sizeY, players[i].penguins[k].x, players[i].penguins[k].y, direction);
                    }
                }
            }
        }
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
                            sum -=(giveBranches(players[i].penguins[k].x, players[i].penguins[k].y,mapP,sizeX,sizeY)) * evaluateBranch(mapP, sizeX, sizeY, players[i].penguins[k].x, players[i].penguins[k].y, direction);
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
