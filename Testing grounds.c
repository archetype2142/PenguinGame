#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#include "UserIO.h"
#include "GameLogic.h"
#define debug

struct directions vectors[6] = { {-1, -1},{0,-2},{1,-1},{1,1},{0,2},{-1,1} };

int main(int argc, char* argv[])
{
    char *program1=argv[1], *program2=argv[2],*mapgenerator=argv[3], *filename=argv[4];
    int numbOfTests=atoi(argv[5]), sizeX, sizeY, numberOfPlayers, score1=0,score2=0, i=0, moved1=0,moved2=0, print;
    struct Floe *map=NULL;
    char buffer[100];
    struct Player *players;
    int k=numbOfTests;
    printf("print map? 1/0/n");
    scanf("%d",&print);
    while(numbOfTests>0)
    {
        sprintf(buffer,"%s %s.txt %d %d %d %d",mapgenerator,filename,20, 20,2,1); //map generator location, map name, sizex, sizey, players, pinguins
        system(buffer);
        printf("\n===================\nMAP GENERATED!\n===================\n");
        sprintf(buffer,"%s.txt",filename);
        read_file(buffer, &players,&map,&sizeX,&sizeY, &numberOfPlayers);
        while(!whatphase(players,numberOfPlayers) || IsGameOver(map,sizeX,sizeY,players,numberOfPlayers))
        {
            i++;
            sprintf(buffer,"%s.txt",filename);
            free(map);
            read_file(buffer, &players, &map, &sizeX, &sizeY, &numberOfPlayers);
            if(!whatphase(players,numberOfPlayers))
            {
                sprintf(buffer,"%s %s %d %s.txt %s.txt", program1,"phase=placement",players[0].numberOfPenguins,filename,filename);
                system(buffer);
                sprintf(buffer,"%s %s %d %s.txt %s.txt", program2,"phase=placement",players[0].numberOfPenguins,filename,filename);
                system(buffer);
            }
            else
            {
                if(IsGameOver(map,sizeX,sizeY,players,numberOfPlayers))
                    {
                        moved1=0;
                        moved2=0;
                        sprintf(buffer,"%s %s %s.txt %s.txt", program1,"phase=movement",filename,filename);
                        if(playerHasMove(players, numberOfPlayers,map,sizeX,sizeY,players[0].playerID))
                        {
                            system(buffer);
                            moved1=1;
                        }
                        else
                        {
                            printf("\nplayer %d has no move!\n",players[0].playerID);
                        }
                        sprintf(buffer,"%s.txt",filename);
                        free(map);
                        read_file(buffer, &players,&map,&sizeX,&sizeY, &numberOfPlayers);
                        sprintf(buffer,"%s %s %s.txt %s.txt", program2,"phase=movement",filename,filename);
                        if(playerHasMove(players, numberOfPlayers,map,sizeX,sizeY,players[1].playerID))
                        {
                            system(buffer);
                            moved2=1;
                        }
                        else
                        {
                            printf("\nplayer %d has no move!\n",players[1].playerID);
                        }
                        if((!moved2 && !moved1))
                            break;

                        if(print)
                        {
                        printf("\n");
                        BasicPrintMao(map,sizeX,sizeY, players,numberOfPlayers);
                        system("pause");
                        }
                        printf("score1: %d score2: %d\n",players[0].score,players[1].score);
                    }
                    else
                        break;
            }
        }
        sprintf(buffer,"%s.txt",filename);
        free(map);
        read_file(buffer, &players, &map, &sizeX, &sizeY, &numberOfPlayers);
        if(players[0].score>players[1].score)
        {
            score1++;
        }
        if(players[1].score>players[0].score)
           score2++;
        system("cls");
        printf("\n===================\nSCORE1:%d\nTHIS GAME:%d\nSCORE2:%d\nTHIS GAME:%d\n===================\n",score1,players[0].score,score2,players[1].score);
        numbOfTests--;
        printf("TESTS LEFT %d",numbOfTests);
    }
    system("cls");
    printf("\n===================\nGAME ENDED\nscore1:%d\nscore2:%d\nAVERAGE SCORE\nscore1:%f\nscore2:%f\n===================",score1,score2,(float)score1/(float)k,(float)score2/(float)k);
    system("pause");
    getchar();
    return 0;
}
