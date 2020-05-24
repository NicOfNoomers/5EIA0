#include <stdio.h>
#include <math.h>
#include "libpynq.h"

void init_display(int height, int width, int scale, pixel displaybuffer[height][width]);
void draw_display();
void clear_display();
void set_pixel(int y, int x, unsigned char r, unsigned char g, unsigned char b);


#define HEIGHT 7
#define WIDTH 6

int main (void) {
	pixel display[HEIGHT][WIDTH];
	init_display (HEIGHT, WIDTH, 20, display);

	int occupied[HEIGHT][WIDTH];
	int selection;
	int delay;
	char select;

	do
	{
		for (int i = 0; i < HEIGHT; ++i){
			for (int y = 0; y < WIDTH; ++y){
				occupied[i][y] = 0;	
			}
		}
		printf("\nWould you like an easy (3), moderate (2), or hard (1) game? ");
		scanf("\n%d", &selection);
		printf("\nGame starts in 1 second\n");	
		sleep_msec(1000);
		clear_display();
		printf("Your score is %d blocks!\n", game(occupied,30+10*selection));
		do
		{
			printf("Would you like to play again [yn]? ");
			scanf(" %c",&select);
		} while (select !='y' && select != 'n');
	} while (select == 'y');
	printf("\nBye!\n");
	return 0;
}

int game(int occupied[][WIDTH],int delay){
	int y,x = WIDTH/2;
	int counter = 0;
	do {
		// start with a new block from the top
		y = 0;
		x = WIDTH/2;
		// check that it’s not run into the bottom or another block
		while (y < HEIGHT-1 && !occupied[y+1][x]) {
			set_pixel(y,x,0,0,0); // erase the old block
			y++;
			set_pixel(y,x,255,0,255); // draw the new block
			sleep_msec(delay);
			draw_display();
			sleep_msec_buttons_pushed (50);
			if (button_states[0] > 0) { 
				// Move right
				if((x+1)<WIDTH && !occupied[y][x+1]){
					set_pixel(y,x,0,0,0);
					x++;
				}
			}
			if (button_states[3] > 0) { 
				// Move left
				if(((x-1)>=0 )&& !occupied[y][x-1]){
					set_pixel(y,x,0,0,0);
					x--;
				}
			}
		}
		set_pixel(y,x,255,0,0);
		sleep_msec(delay);
		draw_display();
		occupied[y][x] = 1;
		checkLine(occupied);
		counter++;
	} while (y > 0); // blocks reached the top
	return counter;
}

void checkLine(int occupied[][WIDTH]){
	int full = 1;
	for(int i = 0; i< WIDTH;i++)
	{
		if (occupied[HEIGHT-1][i] != 1)
		{
			full = 0;
		}
	}
	if (full)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			for (int y = HEIGHT-1; y >0 ; --y)
			{
				if (!occupied[y-1][x])
				{
					occupied[y][x] = 0;
					set_pixel(y,x,0,0,0);
					break;
				}
			}
		}
		draw_display();
	}
	
}