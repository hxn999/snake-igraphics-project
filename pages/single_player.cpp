#ifndef SINGLE_PLAYER
#define SINGLE_PLAYER

#include <stdbool.h>

#include "../library/ui.cpp"
#include "../iGraphics.h"

/*
snake directions
x,y=0 means static snake
y = 1 -> up
y = -1 -> down
x = 1 -> right
x = -1 -> left
*/
int direction_x = -1, direction_y = 0;

// snake will have total 3 life
int life = 3;
// score increased by one after eating food
int score = 0;
char score_str[16] = "Score : 0";
char life_str[15] = "Life : 3";
int heart = 3;
// sprintf(life_str,"Life : %c %c %c",heart,heart,heart);


// total 3 levels
int level = 1;

//counts status modal seconds
int status_time=10;
//shows in status modal
char status_str[30] = "RESPAWNING IN FEW MOMENTS";

int food_x=17, food_y=17;

SnakeNode tail_node;

// snake array
SnakeNode snake[150] = {
	{20, 15},
	{20, 14},
	{20, 13},
	{20, 12},
	{20, 11},
	{20, 10},
	{20, 9},
	{20, 8},
};

// obstacles
Tuple obstacle1[35] = {
	// level 2
	{6, 6},
	{6, 7},
	{6, 8},
	{6, 9},
	{6, 10},
	{6, 11},
	{6, 12},
	{6, 13},
	{6, 14},
	{26, 6},
	{26, 7},
	{26, 8},
	{26, 9},
	{26, 10},
	{26, 11},
	{26, 12},
	{26, 13},
	{26, 14},
	// level 3
	{12, 10},
	{13, 10},
	{14, 10},
	{15, 10},
	{16, 10},
	{17, 10},
	{18, 10},
	{19, 10},
	{20, 10},
	{6, 15},
	{7, 15},
	{6, 5},
	{7, 5},
	{26, 15},
	{25, 15},
	{26, 5},
	{25, 5},
};

// snake length ( initial length 6)
int snake_len = 8;

// ui styles
Ui score_ui = {
	xpos(200, "right", &score_ui),
	ypos(12, "top", &score_ui),
	20,
	120,
	score_str,
	{82, 3, 252},
	18,
	"",
	false,
};
Ui life_ui = {
	xpos(20, "right", &life_ui),
	ypos(12, "top", &life_ui),
	20,
	120,
	life_str,
	{82, 3, 252},
	18,
	"",
	false,
};

Ui status_ui = {
	xpos( 99," left",&status_ui),
	ypos( 99," bot",&status_ui),
	200,
	400,
	status_str,
	{ 82 ,  3,  252},
	 18,
	"center",
	 false,
};

void status_modal()
{
	if(status_time<8)
	{
	status_time++;
	}
	else{
		status_time=10;
		iPauseTimer(2);
		if(strcmp(status_str,"RESPAWNING IN FEW MOMENTS")!=0)
		{
			page_state=0;
			score=0;
			life=3;
			level=1;
			strcpy(status_str,"RESPAWNING IN FEW MOMENTS");
			strcpy(life_str,"Life : 3");
			strcpy(score_str,"Score : 0");
		}

	}


}


// FOOD SPAWN GENERATOR
void food_spawn()
{
	int count;
	// generating random x coordinate
	int rand_x = 1, rand_y = 2;
	do
	{
		rand_x = rand() % 33;
		count = 0;
		for (int i = 0; i < snake_len + 35; i++)
		{
			if (i > snake_len)
			{
				if (obstacle1[i].x == rand_x)
				{
					count++;
				}
			}
			else
			{
				if (snake[i].x == rand_x)
				{
					count++;
				}
			}
		}

	} while (count != 0);

	// generating random y coordinate
	do
	{
		rand_y = rand() % 19;
		count = 0;
		for (int i = 0; i < snake_len + 35; i++)
		{
			if (i > snake_len)
			{
				if (obstacle1[i].y == rand_y)
				{
					count++;
				}
			}
			else
			{
				if (snake[i].y == rand_y)
				{
					count++;
				}
			}
		}

	} while (count != 0);

	food_x = rand_x;
	food_y = rand_y;
}

// checks collision with snake head
int collide(int x, int y)
{

	int obstacle_index = 0;

	if (level == 2)
		obstacle_index = 18;
	if (level == 3)
		obstacle_index = 35;
	for (int i = 0; i < obstacle_index; i++)
	{
		if (obstacle1[i].x == x && obstacle1[i].y == y)
			return 1;
	}

	for (int i = 1; i < snake_len; i++)
	{
		if (snake[i].x == x && snake[i].y == y)
			return 1;
	}

	return 0;
}

// PRINTS OBSTACLE
void obstacle_printer()

{

	int obstacle_index = 0;

	if (level == 2)
		obstacle_index = 18;
	if (level == 3)
		obstacle_index = 35;

	for (int i = 0; i < obstacle_index; i++)
	{
		iSetColor(72, 90, 102);

		iFilledRectangle(obstacle1[i].x * 30, obstacle1[i].y * 30, 30, 30);
		iSetColor(32, 40, 46);
		iRectangle(obstacle1[i].x * 30, obstacle1[i].y * 30, 30, 30);
	}
}

// PRINTS SNAKE
void snake_printer()
{

	// printing head first
	iSetColor(255, 3, 252);
	iFilledRectangle(snake[0].x * 30, snake[0].y * 30, 30, 30);
	iSetColor(82, 3, 0);
	iRectangle(snake[0].x * 30, snake[0].y * 30, 30, 30);

	for (int i = 1; i < snake_len; i++)
	{
		iSetColor(82, 3, 252);
		iFilledRectangle(snake[i].x * 30, snake[i].y * 30, 30, 30);
		iSetColor(82, 3, 0);
		iRectangle(snake[i].x * 30, snake[i].y * 30, 30, 30);
	}
}

// UPDATES SNAKE POSITION
void snake_update()
{

	// checking if the snake hits the border
	int head_x = snake[0].x + direction_x;
	int head_y = snake[0].y + direction_y;

	// if hits the border or itself then life decreases and respawns 


	if (collide(head_x, head_y) ||(head_x < 0 || head_x > 32) ||(head_y < 0 || head_y > 18) )
	{
		iPauseTimer(0);
		iPauseTimer(1);
		iResumeTimer(2);
		status_time=0;
		life--;
		if(life==0)
		{
			sprintf(status_str,"GAME OVER ---- SCORE : %d",score);
		}
		sprintf(life_str, "Life :  %d",life);
		for (int i = 0; i < 8; i++)
		{
			snake[i] = {21,15-i};
		}
		
		snake_len=8;
		return;
	};
	// checking if snake eats the food
	if ((head_x == food_x) && (head_y == food_y))
	{

		score++;
		tail_node = snake[snake_len - 1];
		sprintf(score_str, "Score :  %d",score);
		if (score > 5)
			level = 2;
		if (score > 10)
			level = 3;
		iResumeTimer(1);
	}
	else
	{
		iPauseTimer(1);
	}
	// rest of body will follow previous node
	for (int i = (snake_len - 1); i > 0; i--)
	{
		if (direction_x != 0 || direction_y != 0)
		{
			snake[i].x = snake[i - 1].x;
			snake[i].y = snake[i - 1].y;
		}
	}
	if ((head_x == food_x) && (head_y == food_y))
	{
		snake[snake_len] = tail_node;
		
		snake_len++;
	}

	// modifying head position
	snake[0].x = snake[0].x + direction_x;
	snake[0].y = snake[0].y + direction_y;
}

void single_player()
{
	render(&life_ui);
	render(&score_ui);
	iShowBMP(food_x * 30, food_y * 30, "C:\\Users\\user\\Desktop\\BUET\\L-1 T-1\\CSE 102\\snake-igraphics-project\\assets\\food.bmp");
	snake_printer();
	obstacle_printer();
	if(status_time<8)
	render(&status_ui);
}

void single_player_control(int mx, int my)
{
}

void single_player_special_control(unsigned char key)
{
	if(status_time<8) return;
	if(iAnimPause[0]==1) iResumeTimer(0);
	// if(iAnimPause[1]==1) iResumeTimer(1);
	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	if (key == GLUT_KEY_UP)
	{
		if (direction_x != 0)
		{
			direction_y = 1;
			direction_x = 0;
		}
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (direction_x != 0)
		{
			direction_y = -1;
			direction_x = 0;
		}
	}
	if (key == GLUT_KEY_RIGHT)
	{
		if (direction_y != 0)
		{
			direction_y = 0;
			direction_x = 1;
		}
	}
	if (key == GLUT_KEY_LEFT)
	{
		if (direction_y != 0)
		{
			direction_y = 0;
			direction_x = -1;
		}
	}
}

#endif