#include "iGraphics.h"
#include "pages/home.cpp"
#include "library/ui.cpp"
#include "pages/single_player.cpp"
#include <string.h>
#include<time.h>
#include <stdbool.h>
#include <Windows.h>

// CONSTANTS
#define WINDOW_HEIGHT 625
#define WINDOW_WIDTH 1000

// data structures

// typedef struct
// {
// 	int x;
// 	int y;
// 	int len
// 	;
// 	int h;
// } Rect;

// /*
// snake directions
// x,y=0 means static snake
// y = 1 -> up
// y = -1 -> down
// x = 1 -> right
// x = -1 -> left
// */
// int direction_x=1;
// int direction_y=0;

// // snake array
// SnakeNode snake[150] = {{20, 15}, {20, 14}, {20, 13}, {20, 12}, {20, 11}, {20, 10},{20, 9},{20, 8},};
// // snake length ( initial length 6)
// int snake_len = 8;

// FUNCTION PROTOTYPES

// RENDERS HOMEPAGE
// void home_page();
// // RENDERS SINGLE PLAYER PAGE
// void single_player();
// // PRINTS BUTTON ACCORDING TO COORDINATES
// void button_printer(Rect btn, char text[]);
// // CHECKS MOUSE COORDINATE IS IN BOUND
// int is_clicked(int mx, int my, int x, int y, int l, int h);
// // PRINTS SNAKE
// void snake_printer();
// // UPDATES SNAKE
// void snake_update();
// // FOOD SPAWN GENERATOR
// void food_spawn();

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	// place your drawing codes here
	iClear();

	// Background Image
	iShowBMP(0, 0, "assets/bg-dark.bmp");
	if (page_state != 0)
	{
		iSetColor(82, 3, 252);
		iFilledRectangle(0, 580, 1000, 45);
	}

	// rendering page according to state
	switch (page_state)
	{
	case 0:
		home_page();
		break;
	case 1:
		single_player();
		break;
	case 2:
		iText(50, 60, "THIS IS TWO PLAYER PAGE", GLUT_BITMAP_HELVETICA_18);
		break;
	case 3:
		iText(50, 60, "THIS IS COMPUTER PAGE", GLUT_BITMAP_HELVETICA_18);
		break;
	case 4:
		iText(50, 60, "THIS IS SETTINGS PAGE", GLUT_BITMAP_HELVETICA_18);
		break;
	case 5:
		iText(50, 60, "THIS IS HELP PAGE", GLUT_BITMAP_HELVETICA_18);
		break;

	default:
		break;
	}
	// food_spawn();
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	// place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		switch (page_state)
		{
		case 0:
			home_page_control(mx, my);
			break;
		case 1:
			single_player_control(mx, my);
			break;
		case 2:
			iText(50, 60, "THIS IS TWO PLAYER PAGE", GLUT_BITMAP_HELVETICA_18);
			break;
		case 3:
			iText(50, 60, "THIS IS COMPUTER PAGE", GLUT_BITMAP_HELVETICA_18);
			break;
		case 4:
			iText(50, 60, "THIS IS SETTINGS PAGE", GLUT_BITMAP_HELVETICA_18);
			break;
		case 5:
			iText(50, 60, "THIS IS HELP PAGE", GLUT_BITMAP_HELVETICA_18);
			break;

		default:
			break;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if (key == 'p')
	{
		// do something with 'q'
		iPauseTimer(0);
		PlaySound("C:\\Users\\user\\Downloads\\bite.wav", NULL, SND_ASYNC);
	}
	if (key == 'r')
	{
		iResumeTimer(0);
		PlaySound("C:\\Users\\user\\Downloads\\game-over.wav", NULL, SND_ASYNC);
	}

	// place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
	printf("%c",key);
	switch (page_state)
		{
		case 0:
			
			break;
		case 1:
			single_player_special_control(key);
			break;
		case 2:
			iText(50, 60, "THIS IS TWO PLAYER PAGE", GLUT_BITMAP_HELVETICA_18);
			break;
		case 3:
			iText(50, 60, "THIS IS COMPUTER PAGE", GLUT_BITMAP_HELVETICA_18);
			break;
		case 4:
			iText(50, 60, "THIS IS SETTINGS PAGE", GLUT_BITMAP_HELVETICA_18);
			break;
		case 5:
			iText(50, 60, "THIS IS HELP PAGE", GLUT_BITMAP_HELVETICA_18);
			break;

		default:
			break;
		}

	
	// place your codes for other keys here
}

int main()
{
	srand(time(0));
	// place your own initialization codes here.
	iSetTimer(100, snake_update);
	iPauseTimer(0);
	iSetTimer(100,food_spawn);
	iPauseTimer(1);
	iSetTimer(500,status_modal);
	iPauseTimer(2);
	printf("hi");

	iInitialize(WINDOW_WIDTH, WINDOW_HEIGHT, "Snake_shhhhhh");
	return 0;
}

// USER DEFINED FUNCTIONS
// PAGE FUNCTIONS

// RENDERS HOMEPAGE
// void home_page()
// {
// 	// SINGLE PLAYER
// 	Rect single_page = {(WINDOW_WIDTH / 2) - 150, 450, 300, 60};
// 	button_printer(single_page, "START SINGLE PLAYER");
// 	// TWO PLAYER
// 	Rect two_player_page = {(WINDOW_WIDTH / 2) - 150, 370, 300, 60};
// 	button_printer(two_player_page, "START TWO PLAYER");
// 	// VS COMPUTER
// 	Rect computer = {(WINDOW_WIDTH / 2) - 150, 290, 300, 60};
// 	button_printer(computer, "PLAY VS COMPUTER");
// 	// SETTINGS
// 	Rect settings = {(WINDOW_WIDTH / 2) - 150, 210, 300, 60};
// 	button_printer(settings, "SETTINGS");
// 	// HELP
// 	Rect help = {(WINDOW_WIDTH / 2) - 150, 130, 300, 60};
// 	button_printer(help, "HELP");
// }

// RENDERS SINGLE PLAYER PAGE
// void single_player()
// {
// 	snake_printer();

// }

// // UTILITIES

// // PRINTS BUTTON ACCORDING TO COORDINATES
// void button_printer(Rect btn, char text[])
// {
// 	iSetColor(82, 3, 252);
// 	iFilledRectangle(btn.x, btn.y, btn.len, btn.h);
// 	iSetColor(82, 3, 252);
// 	iFilledCircle(btn.x, btn.y + (btn.h / 2), btn.h / 2);
// 	iFilledCircle(btn.x + btn.len, btn.y + (btn.h / 2), btn.h / 2);
// 	iSetColor(255, 255, 255);
// 	iText((WINDOW_WIDTH / 2) - (btn.len / 2) - 30 + (((btn.len + 60) - strlen(text) * 11) / 2), btn.y + 25, text, GLUT_BITMAP_HELVETICA_18);
// }

// // CHECKS MOUSE COORDINATE IS IN BOUND
// int is_clicked(int mx, int my, int x, int y, int l, int h)
// {
// 	if ((x < mx && mx < (x + l)) && (y < my && (my < (y + h))))
// 		return 1;
// 	else
// 		return 0;
// }

// // PRINTS SNAKE
// void snake_printer()
// {
// 	// printing head first
// 	iSetColor(255, 3, 252);
// 	iFilledRectangle(snake[0].x * 30, snake[0].y * 30, 30, 30);
// 	iSetColor(82, 3, 0);
// 	iRectangle(snake[0].x * 30, snake[0].y * 30, 30, 30);

// 	for (int i = 1; i < snake_len; i++)
// 		{
// 			iSetColor(82, 3, 252);
// 			iFilledRectangle(snake[i].x * 30, snake[i].y * 30, 30, 30);
// 			iSetColor(82, 3, 0);
// 			iRectangle(snake[i].x * 30, snake[i].y * 30, 30, 30);
// 		}
// }

// // UPDATES SNAKE POSITION
// void snake_update()
// {
// 	// checking if the snake hits the border
// 	int head_x = snake[0].x + direction_x;
// 	int head_y = snake[0].y + direction_y;

// 	// if hits the border then snake doesnt move
// 	if(head_x<0||head_x>32) return;
// 	if(head_y<0||head_y>18) return;

// 	// rest of body will follow previous node
// 	for (int i = (snake_len-1); i > 0; i--)
// 	{
// 		if(direction_x!=0 || direction_y!=0)
// 		{
// 			snake[i].x = snake[i-1].x ;
// 			snake[i].y = snake[i-1].y;
// 		}
// 	}

// 	// modifying head position
// 	snake[0].x = snake[0].x + direction_x;
// 	snake[0].y = snake[0].y + direction_y;

// }

// // FOOD SPAWN GENERATOR
// void food_spawn(){
// 	// generating random x coordinate
// 	int rand_x = rand()%33;
// 	int rand_y = rand()%19;
// 	int count;
// 	do
// 	{
// 		count=0;
// 		/* code */
// 	} while (count!=0);

// }
