#ifndef TWO_PLAYER
#define TWO_PLAYER

#include <stdbool.h>
#include <string.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../library/ui.cpp"
#include "../iGraphics.h"
#include "single_player.cpp"

int check = 0;
/*
snake1 directions
x,y=0 means static snake1
y = 1 -> up
y = -1 -> down
x = 1 -> right
x = -1 -> left
*/
char test[10] = "hi";

int direction_x1 = 0, direction_y1 = 0;

// snake1 will have total 3 life1
int life1 = 3;
// score1 increased by one after eating food
int score1 = 0;
// score1 added with bonus points
int pseudo_score1 = 0;

char life_str1[20] = "Life : 3";
char score_str1[40] = "score1 :   0";

// checks direction input queued or not
bool queue1 = false, queue2 = false;

// verifies bonus food eaten of not
// bool bonus_eaten;

// counts bonus time | total 3 seconds of time will be given
// int bonus_time = 5;

// total 3 levels
// int level = 1;

// counts status modal seconds
// int status_time = 10;
// shows in status modal
// char status_str[30] = "RESPAWNING IN FEW MOMENTS";

// highscore file
//  FILE* highscore;

int food_x1 = 16, food_y1 = 10;
// int bonus_food_x = 100, bonus_food_y = 100;

// random bonus food coordinates
// Tuple bonus_coordinate[6] = {{1, 1}, {1, 16}, {29, 1}, {29, 16}, {15, 13}, {15, 3}};

SnakeNode tail_node1;

// snake1 array
SnakeNode snake1[150] = {
	{28, 15},
	{28, 14},
	{28, 13},
	{28, 12},
	{28, 11},
	{28, 10},
	{28, 9},
	{28, 8},
};

// obstacles
Tuple obstacle_1[35] = {
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

// snake1 length ( initial length 6)
int snake_len1 = 8;
int snake_len2 = 8;

// for second snake
int direction_x2 = 0, direction_y2 = 0;
// snake2 will have total 3 life2
int life2 = 3;
// score2 increased by one after eating food
int score2 = 0;
// score2 added with bonus points
int pseudo_score2 = 0;
char life_str2[20] = "Life : 3";
char score_str2[40] = "score2 :   0";

SnakeNode tail_node2;

// snake2 array
SnakeNode snake2[150] = {
	{5, 15},
	{5, 14},
	{5, 13},
	{5, 12},
	{5, 12},
	{5, 10},
	{5, 9},
	{5, 8},
};

Ui score_ui2 = {
	xpos(300, "left", &score_ui2),
	ypos(12, "top", &score_ui2),
	20,
	160,
	"score2 :   0",
	{82, 3, 252},
	18,
	"",
	false,
};

Ui life_ui2 = {
	xpos(500, "left", &life_ui2),
	ypos(12, "top", &life_ui2),
	20,
	120,
	"Life : 3",
	{82, 3, 252},
	18,
	"",
	false,
};

// ui styles
Ui score_ui1 = {
	xpos(200, "right", &score_ui1),
	ypos(12, "top", &score_ui1),
	20,
	160,
	"score1 :   0",
	{82, 3, 252},
	18,
	"",
	false,
};

Ui life_ui1 = {
	xpos(20, "right", &life_ui1),
	ypos(12, "top", &life_ui1),
	20,
	120,
	"Life : 3",
	{82, 3, 252},
	18,
	"",
	false,
};

Ui status_ui1 = {
	xpos(99, " left", &status_ui1),
	ypos(99, " bot", &status_ui1),
	200,
	400,
	status_str,
	{82, 3, 252},
	18,
	"center",
	false,
};
Ui bonus_progress_bar1 = {
	xpos(310, "left", &bonus_progress_bar1),
	ypos(15, "top", &bonus_progress_bar1),
	15,
	0,
	"",
	{255, 255, 255},
	18,
	"",
	false,
};
Ui bonus_text1 = {
	xpos(120, "left", &bonus_text1),
	ypos(12, "top", &bonus_text1),
	20,
	80,
	"",
	{82, 3, 252},
	18,
	"",
	false,
};

Ui exit_ui1 = {
	xpos(20, "left", &exit_ui1),
	ypos(12, "top", &exit_ui1),
	20,
	100,
	"<-- EXIT",
	{82, 3, 252},
	18,
	"",
	false,
};

void status_modal1()
{
	if (status_time < 8)
	{
		
		status_time++;
	}
	else
	{
		
		status_time = 10;
		iPauseTimer(10);

		// resetting all game states and redirecting to homepage
		page_state = 0;
		score1 = 0;
		pseudo_score1 = 0;
		life1 = 3;
		level = 1;
		sprintf(life_str1, "Life : 3");
		life_ui1.text = life_str1;
		sprintf(score_str1, "score1 : %3d", 0);
		score_ui1.text = score_str1;

		score2 = 0;
		pseudo_score2 = 0;
		life2 = 3;
		// level = 1;
		sprintf(life_str2, "Life : 3");
		life_ui2.text = life_str2;
		sprintf(score_str2, "score2 : %3d", 0);
		score_ui2.text = score_str2;

		for (int i = 0; i < 8; i++)
		{
			snake2[i] = {5, 15 - i};
		}

		snake_len2 = 8;
		for (int i = 0; i < 8; i++)
		{
			snake1[i] = {28, 15 - i};
		}

		snake_len1 = 8;
		// strcpy(status_str, "RESPAWNING IN FEW MOMENTS");
	}
}

// BONUS FOOD GENERATOR
void bonus_food_spawn1()
{
	int rand_coordinate = rand() % 6;

	bonus_food_x = bonus_coordinate[rand_coordinate].x;
	bonus_food_y = bonus_coordinate[rand_coordinate].y;
}

// BONUS FOOD GENERATOR
void bonus_food_timer1()
{
	if (bonus_time == 0)
	{
		bonus_food_x = 100;
		bonus_time = 5;
		bonus_food_y = 100;
		bonus_progress_bar1.w = 0;
		bonus_text1.text = "";
		iPauseTimer(8);
	}
	else
	{
		bonus_time--;
	}
}
// BONUS FOOD PROGRESS BAR
void bonus_progress_controller1()
{
	if (bonus_time == 0)
	{
		iPauseTimer(9);
	}
	else
	{
		bonus_progress_bar1.w -= 2;
	}
}

// FOOD SPAWN GENERATOR
void food_spawn1()
{
	int count;
	// generating random x coordinate
	int rand_x = 1, rand_y = 2;
	do
	{
		rand_x = rand() % 33;
		count = 0;
		for (int i = 0; i < snake_len1 + 35; i++)
		{
			if (i > snake_len1)
			{
				if (obstacle_1[i].x == rand_x)
				{
					count++;
				}
			}
			else
			{
				if (snake1[i].x == rand_x)
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
		for (int i = 0; i < snake_len1 + 35; i++)
		{
			if (i > snake_len1)
			{
				if (obstacle_1[i].y == rand_y)
				{
					count++;
				}
			}
			else
			{
				if (snake1[i].y == rand_y)
				{
					count++;
				}
			}
		}

	} while (count != 0);

	food_x1 = rand_x;
	food_y1 = rand_y;
}

// checks collision with snake1 head
int collide1(int x, int y)
{

	int obstacle_index = 0;

	if (level == 2)
		obstacle_index = 18;
	if (level == 3)
		obstacle_index = 35;
	for (int i = 0; i < obstacle_index; i++)
	{
		if (obstacle_1[i].x == x && obstacle_1[i].y == y)
			return 1;
	}

	for (int i = 1; i < snake_len1; i++)
	{
		if (snake1[i].x == x && snake1[i].y == y)
			return 1;
	}

	return 0;
}
// checks collision with snake2 head
int collide2(int x, int y)
{

	int obstacle_index = 0;

	if (level == 2)
		obstacle_index = 18;
	if (level == 3)
		obstacle_index = 35;
	for (int i = 0; i < obstacle_index; i++)
	{
		if (obstacle_1[i].x == x && obstacle_1[i].y == y)
			return 1;
	}

	for (int i = 1; i < snake_len2; i++)
	{
		if (snake2[i].x == x && snake2[i].y == y)
			return 1;
	}

	return 0;
}

// PRINTS OBSTACLE
// void obstacle_printer()

// {

// 	int obstacle_index = 0;

// 	if (level == 2)
// 		obstacle_index = 18;
// 	if (level == 3)
// 		obstacle_index = 35;

// 	for (int i = 0; i < obstacle_index; i++)
// 	{
// 		iSetColor(72, 90, 102);

// 		iFilledRectangle(obstacle_1[i].x * 30, obstacle_1[i].y * 30, 30, 30);
// 		iSetColor(32, 40, 46);
// 		iRectangle(obstacle_1[i].x * 30, obstacle_1[i].y * 30, 30, 30);
// 	}
// }

// PRINTS snake2
void snake_two_printer()
{
	// first snake
	iSetColor(255, 3, 252);
	iFilledRectangle(snake1[0].x * 30, snake1[0].y * 30, 30, 30);
	iSetColor(82, 3, 0);
	iRectangle(snake1[0].x * 30, snake1[0].y * 30, 30, 30);

	for (int i = 1; i < snake_len1; i++)
	{
		iSetColor(82, 3, 252);
		iFilledRectangle(snake1[i].x * 30, snake1[i].y * 30, 30, 30);
		iSetColor(82, 3, 0);
		iRectangle(snake1[i].x * 30, snake1[i].y * 30, 30, 30);
	}
	// second snake
	iSetColor(110, 20, 109);
	iFilledRectangle(snake2[0].x * 30, snake2[0].y * 30, 30, 30);
	iSetColor(82, 3, 0);
	iRectangle(snake2[0].x * 30, snake2[0].y * 30, 30, 30);

	for (int i = 1; i < snake_len2; i++)
	{
		iSetColor(161, 117, 255);
		iFilledRectangle(snake2[i].x * 30, snake2[i].y * 30, 30, 30);
		iSetColor(82, 3, 0);
		iRectangle(snake2[i].x * 30, snake2[i].y * 30, 30, 30);
		if(i==4)
		{
			iSetColor(161, 117, 255);
		iFilledRectangle(snake2[i].x * 30, snake2[i].y * 30, 30, 30);
		iSetColor(82, 3, 0);
		iRectangle(snake2[i].x * 30, snake2[i].y * 30, 30, 30);
		}
	}
	
}

// UPDATES snake1 POSITION
void snake_two_update1()
{
	if (pseudo_score1 >= 30)
	{
		PlaySound("assets/game-over.wav", NULL, SND_ASYNC);
		iPauseTimer(5);
		sprintf(status_str, "Plyer 2 Wins !!!");
		status_time = 0;
		iResumeTimer(10);
	}
	queue1 = false;
	// checking if the snake1 hits the border
	int head_x1 = snake1[0].x + direction_x1;
	int head_y1 = snake1[0].y + direction_y1;

	// if hits the border or itself then life1 decreases and respawns

	if (collide1(head_x1, head_y1) || (head_x1 < 0 || head_x1 > 32) || (head_y1 < 0 || head_y1 > 18))
	{
		iPauseTimer(5);
		direction_x1 = 0;
		direction_y1 = 0;
		life1--;
		printf("snake1 crashed !!\n");
		if (life1 == 0)
		{
			PlaySound("assets/game-over.wav", NULL, SND_ASYNC);
			sprintf(status_str, "Plyer 2 Wins !!!");
			status_time = 0;
			iResumeTimer(10);
		}
		// sprintf(score_str1, "score1 : %3d", 0);
		// score_ui1.text = score_str1;
		sprintf(life_str1, "Life :  %d", life1);
		life_ui1.text = life_str1;
		for (int i = 0; i < 8; i++)
		{
			snake1[i] = {21, 15 - i};
		}

		snake_len1 = 8;

		return;
	};
	// checking if snake1 eats the food
	if ((head_x1 == food_x1) && (head_y1 == food_y1))
	{
		printf("snake1 bites !\n");

		PlaySound(bite_buffer, NULL, SND_MEMORY | SND_ASYNC);
		score1++;
		pseudo_score1++;
		printf("score1 %3d\n", pseudo_score1);
		tail_node1 = snake1[snake_len1 - 1];
		sprintf(score_str1, "score1 : %3d", pseudo_score1);
		score_ui1.text = score_str1;
		if (score1 > 5)
			level = 2;
		if (score1 > 10)
			level = 3;
		if ((score1 % 4) == 0 && score1 != 0)
		{
			bonus_food_spawn1();
			iResumeTimer(8);
			bonus_progress_bar1.w = 300;
			iResumeTimer(9);
			bonus_time = 5;
			bonus_text1.text = "BONUS!";
		}

		iResumeTimer(7);
	}
	else
	{
		iPauseTimer(7);
	}

	// checking if bonus food is eaten
	if (bonus_food_x != 100)
	{
		bonus_eaten = ((head_x1 == bonus_food_x) && (head_y1 == bonus_food_y)) || ((head_x1 == (bonus_food_x + 1)) && (head_y1 == bonus_food_y)) || ((head_x1 == bonus_food_x) && (head_y1 == (bonus_food_y + 1))) || ((head_x1 == (bonus_food_x + 1)) && (head_y1 == (bonus_food_y + 1)));
		if (bonus_eaten)
		{
			PlaySound(bite_buffer, NULL, SND_MEMORY | SND_ASYNC);
			pseudo_score1 = pseudo_score1 + 3 * bonus_time;
			bonus_food_x = 100;
			bonus_food_y = 100;
			bonus_progress_bar1.w = 0;
			iPauseTimer(8);
			iPauseTimer(9);
			sprintf(score_str1, "score1 : %3d", pseudo_score1);
			score_ui1.text = score_str1;
			bonus_text1.text = "";
			bonus_time = 5;
		}
	}

	// rest of body will follow previous node
	for (int i = (snake_len1 - 1); i > 0; i--)
	{
		if (direction_x1 != 0 || direction_y1 != 0)
		{
			snake1[i].x = snake1[i - 1].x;
			snake1[i].y = snake1[i - 1].y;
		}
	}
	if ((head_x1 == food_x1) && (head_y1 == food_y1))
	{
		snake1[snake_len1] = tail_node1;

		snake_len1++;
	}

	// modifying head position
	snake1[0].x = snake1[0].x + direction_x1;
	snake1[0].y = snake1[0].y + direction_y1;
}

void snake_two_update2()
{
	if (pseudo_score2 >= 30)
	{
		PlaySound("assets/game-over.wav", NULL, SND_ASYNC);
		iPauseTimer(6);
		sprintf(status_str, "Plyer 1 Wins !!!");
		status_time = 0;
		iResumeTimer(10);
	}

	queue2 = false;
	// checking if the snake2 hits the border
	int head_x2 = snake2[0].x + direction_x2;
	int head_y2 = snake2[0].y + direction_y2;

	// if hits the border or itself then life2 decreases and respawns

	if (collide2(head_x2, head_y2) || (head_x2 < 0 || head_x2 > 32) || (head_y2 < 0 || head_y2 > 18))
	{
		iPauseTimer(6);
		direction_x2 = 0;
		direction_y2 = 0;
		// status_time = 0;
		life2--;
		printf("snake2 crashed !!\n");
		if (life2 == 0)
		{
			PlaySound("assets/game-over.wav", NULL, SND_ASYNC);
			sprintf(status_str, "Plyer 1 Wins !!!");
			status_time = 0;
			iResumeTimer(10);
		}
		// sprintf(score_str2, "score2 : %3d", 0);
		// score_ui2.text = score_str2;
		sprintf(life_str2, "Life :  %d", life2);
		life_ui2.text = life_str2;
		for (int i = 0; i < 8; i++)
		{
			snake2[i] = {5, 15 - i};
		}

		snake_len2 = 8;
		return;
	};
	// checking if snake2 eats the food
	if ((head_x2 == food_x1) && (head_y2 == food_y1))
	{
		printf("snake2 bites !\n");
		// PlaySound("assets/bite.wav", NULL, SND_ASYNC);
		PlaySound(bite_buffer, NULL, SND_MEMORY | SND_ASYNC);
		score2++;
		pseudo_score2++;
		printf("score2 %3d\n", pseudo_score2);
		tail_node2 = snake2[snake_len2 - 1];
		sprintf(score_str2, "score2 : %3d", pseudo_score2);
		score_ui2.text = score_str2;
		if (score2 > 5)
			level = 2;
		if (score2 > 10)
			level = 3;
		if ((score2 % 4) == 0 && score2 != 0)
		{
			bonus_food_spawn1();
			iResumeTimer(8);
			bonus_progress_bar1.w = 300;
			iResumeTimer(9);
			bonus_time = 5;
			bonus_text1.text = "BONUS!";
		}

		iResumeTimer(7);
	}
	else
	{
		iPauseTimer(7);
	}

	// checking if bonus food is eaten
	if (bonus_food_x != 100)
	{
		bonus_eaten = ((head_x2 == bonus_food_x) && (head_y2 == bonus_food_y)) || ((head_x2 == (bonus_food_x + 2)) && (head_y2 == bonus_food_y)) || ((head_x2 == bonus_food_x) && (head_y2 == (bonus_food_y + 2))) || ((head_x2 == (bonus_food_x + 2)) && (head_y2 == (bonus_food_y + 2)));
		if (bonus_eaten)
		{
			PlaySound(bite_buffer, NULL, SND_MEMORY | SND_ASYNC);
			pseudo_score2 = pseudo_score2 + 3 * bonus_time;
			bonus_food_x = 100;
			bonus_food_y = 100;
			bonus_progress_bar1.w = 0;
			iPauseTimer(8);
			iPauseTimer(9);
			sprintf(score_str2, "score2 : %3d", pseudo_score2);
			score_ui2.text = score_str2;
			bonus_text1.text = "";
			bonus_time = 5;
		}
	}

	// rest of body will follow previous node
	for (int i = (snake_len2 - 1); i > 0; i--)
	{
		if (direction_x2 != 0 || direction_y2 != 0)
		{
			snake2[i].x = snake2[i - 1].x;
			snake2[i].y = snake2[i - 1].y;
		}
	}
	if ((head_x2 == food_x1) && (head_y2 == food_y1))
	{
		snake2[snake_len2] = tail_node2;

		snake_len2++;
	}

	// modifying head position
	snake2[0].x = snake2[0].x + direction_x2;
	snake2[0].y = snake2[0].y + direction_y2;
}

void two_player()
{
	snake_two_printer();
	obstacle_printer();

	render(&exit_ui1);
	render(&score_ui1);
	render(&bonus_text1);
	render(&life_ui1);
	render(&life_ui2);
	render(&score_ui2);
	render(&bonus_progress_bar1);
	iShowBMP(bonus_food_x * 30, bonus_food_y * 30, "assets/bonus-food.bmp");
	iShowBMP(food_x1 * 30, food_y1 * 30, "assets/food.bmp");
	if (status_time < 8)
		render(&status_ui1);
}

void two_player_control(int mx, int my)
{
	if (click_or_hover(mx, my, exit_ui1))
	{

		page_state = 0;
		score1 = 0;
		life1 = 3;
		level = 1;
		strcpy(status_str, "RESPAWNING IN FEW MOMENTS");
		sprintf(life_str1, "Life : 3");
		life_ui1.text = life_str1;
		sprintf(score_str1, "score1 : %3d", 0);
		score_ui1.text = score_str1;
		for (int i = 0; i < 8; i++)
		{
			snake1[i] = {21, 15 - i};
		}

		snake_len1 = 8;
	}
}

void two_player_key_control(unsigned char key)
{
	if (status_time < 8)
		return;
	if (iAnimPause[6] == 1)
		iResumeTimer(6);

	if (!queue2)
	{
		queue2 = true;
		if (key == 'w')
		{
			if ((direction_x2 != 0) || ((direction_x2 == 0) && (direction_y2 == 0)))
			{
				printf("snake2 goes up\n");
				direction_y2 = 1;
				direction_x2 = 0;
			}
		}
		if (key == 's')
		{
			if ((direction_x2 != 0))
			{
				printf("snake2 goes down\n");
				direction_y2 = -1;
				direction_x2 = 0;
			}
		}
		if (key == 'd')
		{
			if ((direction_y2 != 0) || ((direction_x2 == 0) && (direction_y2 == 0)))
			{
				printf("snake2 turns right\n");
				direction_y2 = 0;
				direction_x2 = 1;
			}
		}
		if (key == 'a')
		{
			if ((direction_y2 != 0) || ((direction_x2 == 0) && (direction_y2 == 0)))
			{
				printf("snake2 turns left\n");
				direction_y2 = 0;
				direction_x2 = -1;
			}
		}
	}
}

void two_player_special_control(unsigned char key)
{
	if (status_time < 8)
		return;
	if (iAnimPause[0] == 1)
		iResumeTimer(5);

	if (!queue1)
	{
		queue1 = true;
		if (key == GLUT_KEY_END)
		{
			exit(0);
		}

		if (key == GLUT_KEY_UP)
		{
			if ((direction_x1 != 0) || ((direction_x1 == 0) && (direction_y1 == 0)))
			{
				printf("snake1 goes up\n");
				direction_y1 = 1;
				direction_x1 = 0;
			}
		}
		if (key == GLUT_KEY_DOWN)
		{
			if ((direction_x1 != 0))
			{
				printf("snake1 goes down\n");
				direction_y1 = -1;
				direction_x1 = 0;
			}
		}
		if (key == GLUT_KEY_RIGHT)
		{
			if ((direction_y1 != 0) || ((direction_x1 == 0) && (direction_y1 == 0)))
			{
				printf("snake1 turns right\n");
				direction_y1 = 0;
				direction_x1 = 1;
			}
		}
		if (key == GLUT_KEY_LEFT)
		{
			if ((direction_y1 != 0) || ((direction_x1 == 0) && (direction_y1 == 0)))
			{
				printf("snake1 turns left\n");
				direction_y1 = 0;
				direction_x1 = -1;
			}
		}
	}
}

#endif