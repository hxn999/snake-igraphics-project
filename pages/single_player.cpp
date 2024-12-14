#ifndef SINGLE_PLAYER
#define SINGLE_PLAYER

#include <stdbool.h>
#include <Windows.h>
#include <stdio.h>
#include "../library/ui.cpp"
#include "../iGraphics.h"

// for storing highscore
FILE *file;
char filename[] = "highestScore.txt";
char *content;
long fileSize;
char *endptr;
long highest_score;
char new_highest_score[5];

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
// score added with bonus points
int pseudo_score = 0;

// checks direction qued or not
bool queue = false;

char life_str[15] = "Life : 3";
char score_str[40] = "Score :   0";
int heart = 3;

// verifies bonus food eaten of not
bool bonus_eaten;

// counts bonus time | total 3 seconds of time will be given
int bonus_time = 5;

// total 3 levels
int level = 1;

// counts status modal seconds
int status_time = 10;
// shows in status modal
char status_str[30] = "RESPAWNING IN FEW MOMENTS";

// highscore file
FILE *highscore;

int food_x = 17, food_y = 17;
int bonus_food_x = 100, bonus_food_y = 100;

// random bonus food coordinates
Tuple bonus_coordinate[6] = {{1, 1}, {1, 16}, {29, 1}, {29, 16}, {15, 13}, {15, 3}};

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
	160,
	"Score :   0",
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
	xpos(99, " left", &status_ui),
	ypos(99, " bot", &status_ui),
	200,
	400,
	status_str,
	{82, 3, 252},
	18,
	"center",
	false,
};
Ui bonus_progress_bar = {
	xpos(210, "left", &bonus_progress_bar),
	ypos(15, "top", &bonus_progress_bar),
	15,
	0,
	"",
	{255, 255, 255},
	18,
	"",
	false,
};
Ui bonus_text = {
	xpos(120, "left", &bonus_text),
	ypos(12, "top", &bonus_text),
	20,
	80,
	"",
	{82, 3, 252},
	18,
	"",
	false,
};

Ui exit_ui = {
	xpos(20, "left", &exit_ui),
	ypos(12, "top", &exit_ui),
	20,
	100,
	"<-- EXIT",
	{82, 3, 252},
	18,
	"",
	false,
};

void status_modal()
{
	if (status_time < 8)
	{
		status_time++;
	}
	else
	{
		status_time = 10;
		iPauseTimer(2);
		if (strcmp(status_str, "RESPAWNING IN FEW MOMENTS") != 0)
		{
			// resetting all game states and redirecting to homepage
			page_state = 0;
			score = 0;
			life = 3;
			level = 1;
			strcpy(status_str, "RESPAWNING IN FEW MOMENTS");
			strcpy(life_str, "Life : 3");
			sprintf(score_str, "Score : %3d", 0);
			score_ui.text = score_str;
		}
	}
}

// BONUS FOOD GENERATOR
void bonus_food_spawn()
{
	int rand_coordinate = rand() % 6;

	bonus_food_x = bonus_coordinate[rand_coordinate].x;
	bonus_food_y = bonus_coordinate[rand_coordinate].y;
}

// BONUS FOOD GENERATOR
void bonus_food_timer()
{
	if (bonus_time == 0)
	{
		bonus_food_x = 100;
		bonus_time = 5;
		bonus_food_y = 100;
		bonus_progress_bar.w = 0;
		bonus_text.text = "";
		iPauseTimer(3);
	}
	else
	{
		bonus_time--;
	}
}
// BONUS FOOD PROGRESS BAR
void bonus_progress_controller()
{
	if (bonus_time == 0)
	{
		iPauseTimer(4);
	}
	else
	{
		bonus_progress_bar.w -= 2;
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
	queue = false;

	// checking if the snake hits the border
	int head_x = snake[0].x + direction_x;
	int head_y = snake[0].y + direction_y;

	// if hits the border or itself then life decreases and respawns

	if (collide(head_x, head_y) || (head_x < 0 || head_x > 32) || (head_y < 0 || head_y > 18))
	{
		iPauseTimer(single_snake_timer);
		iPauseTimer(1);
		iResumeTimer(2);
		status_time = 0;
		life--;
		printf("snake crashed !!\n");

		// game ends here
		if (life == 0)
		{
			PlaySound("assets/game-over.wav",NULL,SND_ASYNC);
			// Open the file in read mode
			file = fopen(filename, "r");

			// Find the file size
			fseek(file, 0, SEEK_END);
			fileSize = ftell(file);
			rewind(file);

			// Allocate memory for the file content
			content = (char *)malloc(fileSize + 1);

			// Read the file into the buffer
			fread(content, 1, fileSize, file);
			content[fileSize] = '\0'; // Null-terminate the string

			highest_score = strtol(content, &endptr, 10);

			if (pseudo_score >= highest_score)
			{
				sprintf(status_str, "HIGHEST SCORE :  %3d !!", pseudo_score);
				free(content);
				fclose(file);

				file = fopen(filename, "w");

				sprintf(new_highest_score, "%d", pseudo_score);
				// Write the new content to the file
				fprintf(file, "%s", new_highest_score);

				// Close the file
				fclose(file);
			}
			else
			{
				sprintf(status_str, "SCORE :  %3d | HIGHEST SCORE :  %3ld", pseudo_score, highest_score);
				free(content);
				fclose(file);
			}

			// Free allocated memory and close the file
		}
		// sprintf(score_str, "Score : %3d", 0);
		// score_ui.text = score_str;
		sprintf(life_str, "Life :  %d", life);
		for (int i = 0; i < 8; i++)
		{
			snake[i] = {21, 15 - i};
		}

		snake_len = 8;

		return;
	};
	// checking if snake eats the food
	if ((head_x == food_x) && (head_y == food_y))
	{
		printf("snake bites !\n");

		PlaySound(bite_buffer, NULL,SND_MEMORY | SND_ASYNC);
		score++;
		pseudo_score++;
		printf("score %3d\n", pseudo_score);
		tail_node = snake[snake_len - 1];
		sprintf(score_str, "Score : %3d", pseudo_score);
		score_ui.text = score_str;
		if (score > 5)
			level = 2;
		if (score > 10)
			level = 3;
		if ((score % 4) == 0 && score != 0)
		{
			bonus_food_spawn();
			iResumeTimer(3);
			bonus_progress_bar.w = 300;
			iResumeTimer(4);
			bonus_time = 5;
			bonus_text.text = "BONUS!";
		}

		iResumeTimer(1);
	}
	else
	{
		iPauseTimer(1);
	}

	// checking if bonus food is eaten
	if (bonus_food_x != 100)
	{
		bonus_eaten = ((head_x == bonus_food_x) && (head_y == bonus_food_y)) || ((head_x == (bonus_food_x + 1)) && (head_y == bonus_food_y)) || ((head_x == bonus_food_x) && (head_y == (bonus_food_y + 1))) || ((head_x == (bonus_food_x + 1)) && (head_y == (bonus_food_y + 1)));
		if (bonus_eaten)
		{
			PlaySound(bite_buffer, NULL,SND_MEMORY | SND_ASYNC);
			pseudo_score = pseudo_score + 3 * bonus_time;
			bonus_food_x = 100;
			bonus_food_y = 100;
			bonus_progress_bar.w = 0;
			iPauseTimer(3);
			iPauseTimer(4);
			sprintf(score_str, "Score : %3d", pseudo_score);
			score_ui.text = score_str;
			bonus_text.text = "";
			bonus_time = 5;
		}
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
	render(&exit_ui);
	render(&score_ui);
	render(&bonus_text);
	render(&bonus_progress_bar);
	iShowBMP(food_x * 30, food_y * 30, "C:\\Users\\user\\Desktop\\BUET\\L-1 T-1\\CSE 102\\snake-igraphics-project\\assets\\food.bmp");
	iShowBMP(bonus_food_x * 30, bonus_food_y * 30, "C:\\Users\\user\\Desktop\\BUET\\L-1 T-1\\CSE 102\\snake-igraphics-project\\assets\\bonus-food.bmp");
	snake_printer();
	obstacle_printer();
	if (status_time < 8)
		render(&status_ui);
}

void single_player_control(int mx, int my)
{
	if (click_or_hover(mx, my, exit_ui))
	{

		page_state = 0;
		score = 0;
		pseudo_score = 0;
		life = 3;
		level = 1;
		strcpy(status_str, "RESPAWNING IN FEW MOMENTS");
		strcpy(life_str, "Life : 3");
		sprintf(score_str, "Score : %3d", 0);
		score_ui.text = score_str;
		for (int i = 0; i < 8; i++)
		{
			snake[i] = {21, 15 - i};
		}

		snake_len = 8;
		iPauseTimer(single_snake_timer);
	}
}

void single_player_key_control(unsigned char key)
{
}

void single_player_special_control(unsigned char key)
{
	if (status_time < 8)
		return;
	if (iAnimPause[0] == 1)
		iResumeTimer(single_snake_timer);

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}

	if (!queue)
	{

		queue = true;

		if (key == GLUT_KEY_UP)
		{
			if (direction_x != 0)
			{
				printf("snake goes up\n");
				direction_y = 1;
				direction_x = 0;
			}
		}
		if (key == GLUT_KEY_DOWN)
		{
			if (direction_x != 0)
			{
				printf("snake goes down\n");
				direction_y = -1;
				direction_x = 0;
			}
		}
		if (key == GLUT_KEY_RIGHT)
		{
			if (direction_y != 0)
			{
				printf("snake turns right\n");
				direction_y = 0;
				direction_x = 1;
			}
		}
		if (key == GLUT_KEY_LEFT)
		{
			if (direction_y != 0)
			{
				printf("snake turns left\n");
				direction_y = 0;
				direction_x = -1;
			}
		}
	}
}

#endif