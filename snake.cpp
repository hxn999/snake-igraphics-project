#include "iGraphics.h"
#include "pages/home.cpp"
#include "library/ui.cpp"
#include "pages/single_player.cpp"
#include "pages/two_player.cpp"
#include "pages/settings.cpp"
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>

// CONSTANTS
#define WINDOW_HEIGHT 625
#define WINDOW_WIDTH 1000


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
		two_player();
		break;
	case 3:
		iText(50, 60, "THIS IS COMPUTER PAGE", GLUT_BITMAP_HELVETICA_18);
		break;
	case 4:
		settings_page();
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
			single_player_control(mx, my);
			break;
		case 3:
			iText(50, 60, "THIS IS COMPUTER PAGE", GLUT_BITMAP_HELVETICA_18);
			break;
		case 4:
			settings_control(mx,my);
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
	// if (key == 'p')
	// {
	// 	// do something with 'q'
	// 	iPauseTimer(0);
	// 	PlaySound("assets/bite.wav", NULL, SND_ASYNC);
	// }
	// if (key == 'r')
	// {
	// 	iResumeTimer(0);
	// 	PlaySound("C:\\Users\\user\\Downloads\\game-over.wav", NULL, SND_ASYNC);
	// }

	switch (page_state)
		{
		case 0:
			
			break;
		case 1:
			single_player_key_control(key);
			break;
		case 2:
			two_player_key_control(key);
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

	switch (page_state)
		{
		case 0:
			
			break;
		case 1:
			single_player_special_control(key);
			break;
		case 2:
			two_player_special_control(key);
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
	iSetTimer(1000,bonus_food_timer);
	iPauseTimer(3);
	iSetTimer(17,bonus_progress_controller);
	iPauseTimer(4);
	iSetTimer(100, snake_two_update1);
	iPauseTimer(5);
	iSetTimer(100, snake_two_update2);
	iPauseTimer(6);
	iSetTimer(100, food_spawn1);
	iPauseTimer(7);

	iInitialize(WINDOW_WIDTH, WINDOW_HEIGHT, "Snake_shhhhhh");
	return 0;
}
