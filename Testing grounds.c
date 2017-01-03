#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#include "UserIO.h"
#include "GameLogic.h"

struct directions vectors[6] = { {-1, -1},{0,-2},{1,-1},{1,1},{0,2},{-1,1} };
int whatphase(struct Player *players, int playerCount);
int playerHasMove(struct Player *players, int playerCount, struct Floe *map, int sizeX, int sizeY, int playerID);

int main(int argc, char* argv[])
{
    char *program1=argv[1], *program2=argv[2],*mapgenerator=argv[3], *filename=argv[4];
    int numbOfTests=atoi(argv[5]), sizeX, sizeY, numberOfPlayers, score1=0,score2=0, i=0, moved1=0,moved2=0;
    struct Floe *map=NULL;
    char buffer[100];
    struct Player *players;
    while(numbOfTests>0)
    {
        sprintf(buffer,"%s %s.txt %d %d %d %d",mapgenerator,filename,50,50,2,8); //map generator location, map name, sizex, sizey, players, pinguins
        system(buffer);
        printf("map generated!");
        sprintf(buffer,"%s.txt",filename);
        read_file(buffer, &players,&map,&sizeX,&sizeY, &numberOfPlayers);
        while(!whatphase(players,numberOfPlayers) || (playerHasMove(players, numberOfPlayers,map,sizeX,sizeY,2) && playerHasMove(players, numberOfPlayers,map,sizeX,sizeY,1)))
        {
            i++;
            sprintf(buffer,"%s.txt",filename);
            read_file(buffer, &players, &map, &sizeX, &sizeY, &numberOfPlayers);
            if(!whatphase(players,numberOfPlayers))
            {
                sprintf(buffer,"%s %s %d %s.txt %s%d.txt", program1,"phase=placement",players[0].numberOfPenguins,filename,filename,1);
                system(buffer);
                sprintf(buffer,"%s %s %d %s%d.txt %s.txt", program2,"phase=placement",players[0].numberOfPenguins,filename,1,filename);
                system(buffer);
            }
            else
            {
                if(IsGameOver(map,sizeX,sizeY,players,numberOfPlayers))
                    {
                        sprintf(buffer,"%s %s %s.txt %s%d.txt", program1,"phase=movement",filename,filename,1);
                        if(playerHasMove(players, numberOfPlayers,map,sizeX,sizeY,1))
                        {
                            system(buffer);
                            moved1=1;
                        }
                        sprintf(buffer,"%s1.txt",filename);
                        read_file(buffer, &players,&map,&sizeX,&sizeY, &numberOfPlayers);
                        sprintf(buffer,"%s %s %s%d.txt %s.txt", program2,"phase=movement",filename,1,filename);
                        if(playerHasMove(players, numberOfPlayers,map,sizeX,sizeY,2))
                        {
                            system(buffer);
                            moved2=1;
                        }
                        if(!(moved2*moved1))
                            break;
                    }
                    else
                        break;
            }
            moved1=0;
            moved2=0;
            printf("\n%d\n",i);
        }
        sprintf(buffer,"%s.txt",filename);
        read_file(buffer, &players, &map, &sizeX, &sizeY, &numberOfPlayers);
        if(players[giveIndex(1,players,numberOfPlayers)].score>players[giveIndex(2,players,numberOfPlayers)].score)
        {
            score1++;
        }
        else
        {
            score2++;
        }
        printf("score1:%d\nscore2:%d",score1,score2);
        numbOfTests--;
    }
    printf("\nGAME ENDED\nscore1:%d\nscore2:%d",score1,score2);
    getchar();
    return 0;
}
//0 means placement 1 means movement
int whatphase(struct Player *players, int playerCount)
{
    int i,k, Phase=1;
    for(i=0;i<playerCount;i++)
    {
        for(k=0;k<players[i].numberOfPenguins;k++)
        {
            if(players[i].penguins[k].y<0 || players[i].penguins[k].y<0)
            {
                Phase=0;
            }
        }
    }
    return Phase;
}

int playerHasMove(struct Player *players, int playerCount, struct Floe *map, int sizeX, int sizeY, int playerID)
{
    int k, directions=0;
        for(k=0;k<players[giveIndex(playerID,players,playerCount)].numberOfPenguins;k++)
        {
            for(directions=0;directions<6;directions++)
            {
                if(check_target_coordinates(players[giveIndex(playerID,players,playerCount)].penguins[k].x+vectors[directions].x,players[giveIndex(playerID,players,playerCount)].penguins[k].y+vectors[directions].y,map,sizeX,sizeY))
                {
                    return 1;
                }
            }
        }
    return 0;
}
