#include "Map.h"
#include "P9KR.h"

struct Vector movePenguinR(int playerID, void *mapP, int sizeX, int sizeY, struct Player players[],int numberOfPlayers)
{

}

struct Point placePenguin(void *mapP, int sizeX, int sizeY, int playerID, struct Player players[], int numberOfPlayers)
{

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
