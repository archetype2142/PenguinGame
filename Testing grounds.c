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
    int numbOfTests=atoi(argv[5]), sizeX, sizeY, numberOfPlayers, score1=0,score2=0, i=0, moved1=0,moved2=0;
    struct Floe *map=NULL;
    char buffer[100];
    struct Player *players;
    int k=numbOfTests;
    while(numbOfTests>0)
    {
        sprintf(buffer,"%s %s.txt %d %d %d %d",mapgenerator,filename,30, 30,2,1); //map generator location, map name, sizex, sizey, players, pinguins
        system(buffer);
        printf("\n===================\nMAP GENERATED!\n===================\n");
        sprintf(buffer,"%s.txt",filename);
        read_file(buffer, &players,&map,&sizeX,&sizeY, &numberOfPlayers);
        while(!whatphase(players,numberOfPlayers) || IsGameOver(map,sizeX,sizeY,players,numberOfPlayers))
        {
            i++;
            sprintf(buffer,"%s.txt",filename);
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
                        if(playerHasMove(players, numberOfPlayers,map,sizeX,sizeY,1))
                        {
                            system(buffer);
                            moved1=1;
                        }
                        sprintf(buffer,"%s.txt",filename);
                        read_file(buffer, &players,&map,&sizeX,&sizeY, &numberOfPlayers);
                        sprintf(buffer,"%s %s %s.txt %s.txt", program2,"phase=movement",filename,filename);
                        if(playerHasMove(players, numberOfPlayers,map,sizeX,sizeY,2))
                        {
                            system(buffer);
                            moved2=1;
                        }
                        if((!moved2 && !moved1))
                            break;

                        #ifdef debug
                        printf("\n");
                        BasicPrintMao(map,sizeX,sizeY, players,numberOfPlayers);
                        system("pause");
                        #endif // debug
                    }
                    else
                        break;
            }
        }
        sprintf(buffer,"%s.txt",filename);
        read_file(buffer, &players, &map, &sizeX, &sizeY, &numberOfPlayers);
        if(players[giveIndex(1,players,numberOfPlayers)].score>players[giveIndex(2,players,numberOfPlayers)].score && players[giveIndex(2,players,numberOfPlayers)].score && players[giveIndex(1,players,numberOfPlayers)].score>players[giveIndex(2,players,numberOfPlayers)].score)
        {
            score1++;
        }
        else
        {
            if(players[giveIndex(1,players,numberOfPlayers)].score==players[giveIndex(2,players,numberOfPlayers)].score);
            else
                score2++;
        }
        system("cls");
        printf("\n===================\nSCORE1:%d\nTHIS GAME:%d\nSCORE2:%d\nTHIS GAME:%d\n===================\n",score1,players[giveIndex(1,players,numberOfPlayers)].score,score2,players[giveIndex(2,players,numberOfPlayers)].score);
        numbOfTests--;
        printf("TESTS LEFT %d",numbOfTests);
    }
    system("cls");
    printf("\n===================\nGAME ENDED\nscore1:%d\nscore2:%d\nAVERAGE SCORE\nscore1:%f\nscore2:%f\n===================",score1,score2,(float)score1/(float)k,(float)score2/(float)k);
    getchar();
    return 0;
}
