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