#include <stdio.h>
read_file();/* TODO */
placement(){
	scanf("%i %i", &x, &y);
	if (check_coordinates(x,y) && check_how_many_fishes(x,y) == 1 && !check_pengiun(x,y)){
			place_penguin(x,y);
	}
	
}	
movement(){
	scanf("%i %i %i %i", &x1, &y1, &x2, &y2); /* x1,y1 are coordinates of a penguin user wants to move, x2,y2 are target coordinates*/
	check_coordinates();
	check_pengiun();
	check_target_coordinates();
	check_valid_move();
	
	}
write_file();
int check_valid_move(int x1, int y1, int x2, int y2)
{
	int pathClear=1;
	if((x2-x1)==0&&(y2-y1)%2==0) /* checking fields above or below current field*/
	{
		for(int y=y1;y==y2;y+=sign(y2-y1)*2)
		{
			if(y<0||y>mapSize||check_penguin(x1,y)!=0||check_how_many_fishes(x1,y)==0)
			{
				pathClear=0
				break;
			}
		}
	}
	else
	{
		if(abs(x2-x1)!=abs(y2-y1)
		   {
			   pathClear=0
		   }
		   else
		   {
			for(int x=x1, y=y1;x==x2;x+=sign(x2-x1),y==sign(y2-y1))/* checking fields on diaognals*/
			{
			if(y<0||x<0||x>mapSize||y>mapSize||check_penguin(x,y)!=0||check_how_many_fishes(x,y)==0)
				{
					pathClear=0
					break;
				}
			}
		   }

		}
	}
	return pathClear;
	
}


int main(){
	/* declare structures and some variables */
	
	read_file();
	if (phase==placement){
		placement();
		
	} else {
		movement();
	}
	write_file();
	return 0;
	
}
