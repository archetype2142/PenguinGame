#include "Map.h"
#include <stdlib.h>

struct Floe *giveFloe(struct Map map, int x, int y)
{
    if((map.mapPointer+y*map.sizeX+x)->numbOfFish==0)
        return (map.mapPointer+y*map.sizeX+x);
    else
    {
        if(findChange(map.changelog,map.changeCount, x, y)==NULL)
        {
            return (map.mapPointer+y*map.sizeX+x);
        }
        else
        {
            return &(findChange(map.changelog,map.changeCount, x, y)->floe);
        }
    }
}

struct Box *findChange(struct Box changes[], int changeCount, int x, int y)
{
    int i;
    for(i=0;i<changeCount;i++)
    {
        if(changes[i].x==x && changes[i].y==y)
        {
            return &changes[i];
        }
    }
    return NULL;
}

void addChange(struct Map *map, struct Vector move)
{
    map->changelog[map->changeCount+1].floe.whosPenguin=map->changelog[map->changeCount].floe.whosPenguin;
    map->changelog[map->changeCount+1].floe.numbOfFish=0;
    map->changelog[map->changeCount].x=move.xInitial;
    map->changelog[map->changeCount+1].y=move.yTarget;
    map->changelog[map->changeCount+1].x=move.xTarget;
    map->changelog[map->changeCount].y=move.yInitial;
    map->changelog[map->changeCount].floe.whosPenguin=0;
    map->changelog[map->changeCount].floe.numbOfFish=0;
    map->changeCount+=2;
}

void tryPlace(struct Map *map, int x, int y, int playerID)
{
    map->changelog.x=x;
    map->changelog.y=y;
    map->changelog.floe.numbOfFish=0
    map->changeCount;

}
