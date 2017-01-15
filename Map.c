#include "Map.h"
#include "GameLogic.h"
#include <stdlib.h>

struct Floe *giveFloe(struct Map *map, int x, int y)
{
    struct Box *ptr;
    if((map->mapPointer+y+map->sizeX*x)->numbOfFish==0)
        return (map->mapPointer+y+map->sizeX*x);
    else
    {
        ptr=findChange(map->changelog,map->changeCount, x, y);
        if(ptr==NULL)
        {
            return (map->mapPointer+y+map->sizeX*x);
        }
        else
        {
            return &(ptr->floe);
        }
    }
}

struct Box *findChange(struct Box changes[], int changeCount, int x, int y)
{
    int i;
    struct Box *result=NULL;
    for(i=0;i<changeCount;i++)
    {
        if(changes[i].x==x && changes[i].y==y)
        {
            result = &changes[i];
        }
    }
    return result;
}

int addChange(struct Map *map, struct Vector move, int penguinIndex)
{
    if(check_valid_move(move.xInitial,move.yInitial,move.xTarget,move.yTarget,map->mapPointer,map->sizeX,map->sizeY))
    {
        map->changelog[map->changeCount+1].floe.whosPenguin=map->changelog[map->changeCount].floe.whosPenguin;
        map->changelog[map->changeCount+1].floe.numbOfFish=0;
        map->changelog[map->changeCount+1].penguinIndex=penguinIndex;
        map->changelog[map->changeCount].penguinIndex=-1;
        map->changelog[map->changeCount].x=move.xInitial;
        map->changelog[map->changeCount+1].y=move.yTarget;
        map->changelog[map->changeCount+1].x=move.xTarget;
        map->changelog[map->changeCount].y=move.yInitial;
        map->changelog[map->changeCount].floe.whosPenguin=0;
        map->scores[giveIndex(map->changelog[map->changeCount+1].floe.whosPenguin,map->players,map->playerCount)]+=giveFloe(map,move.xTarget,move.yTarget)->numbOfFish;
        map->changelog[map->changeCount].floe.numbOfFish=0;
        map->changeCount+=2;
        return 1;
    }
    else
        return 0;
}

void tryPlace(struct Map *map, int x, int y, int playerID)
{
    int i;
    map->changelog[map->changeCount].x=x;
    map->changelog[map->changeCount].y=y;
    map->changelog[map->changeCount].floe.numbOfFish=0;
    map->changeCount++;
    map->scores[giveIndex(playerID,map->players,map->playerCount)]++;
    for(i=0;i<map->players[0].numberOfPenguins;i++)
    {
        if(map->players[giveIndex(playerID,map->players,map->playerCount)].penguins[i].x<0 && map->players[giveIndex(playerID,map->players,map->playerCount)].penguins[i].y<0)
        {
            map->players[giveIndex(playerID,map->players,map->playerCount)].penguins[i].x=x;
            map->players[giveIndex(playerID,map->players,map->playerCount)].penguins[i].y=y;
            break;
        }
    }
}

struct penguin givePenguin(struct Map *map, int playerID, int penguinIndex)
{
    struct penguin result=map->players[giveIndex(playerID,map->players,map->playerCount)].penguins[penguinIndex];
    int i;
    for(i=map->changeCount;i>=0;i--)
    {
        if(map->changelog[i].floe.whosPenguin==playerID && map->changelog[i].penguinIndex==penguinIndex)
        {
            result.x = map->changelog[i].x;
            result.y = map->changelog[i].y;
        }
    }

    return result;
}


int giveScore(int playerID, struct Map *map)
{
    int playerIndex=giveIndex(playerID,map->players,map->playerCount);
    return map->players[playerIndex].score+map->scores[playerIndex];
}
