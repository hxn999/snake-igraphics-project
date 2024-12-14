#ifndef UI_LIBRARY
#define UI_LIBRARY

#include <string.h>
#include <stdbool.h>
#include <Windows.h>
#include "../iGraphics.h"

#define WINDOW_HEIGHT 625
#define WINDOW_WIDTH 1000

int single_snake_timer = 0 // 11 for easy // 12 for hard
    ,
    two_snake_timer1 = 5, two_snake_timer2 = 6;

// bg_music initialization variable
int fileSize_bg = 400 * 1024;
char *bg_buffer;
const char *bg_file_path = "assets/bg-music.wav";

// bg_music initialization variable
int fileSize_click = 50 * 1024;
char *click_buffer;
const char *click_file_path = "assets/click.wav";

// bg_music initialization variable
int fileSize_bite = 60 * 1024;
char *bite_buffer;
const char *bite_file_path = "assets/bite.wav";


/*
page_state = 0 ->  home page
page_state = 1 ->  single player page
page_state = 2 ->  two player page
page_state = 3 ->  vs computer page
page_state = 4 ->  settings page
page_state = 5 ->  help page
*/
int page_state = 0;

// controlls snake speed difficulty=1 is the highest 2, is medium and 3 is low
int difficulty = 3;

// snake position
typedef struct
{
    int x;
    int y;
} SnakeNode;

typedef struct
{
    int x;
    int y;
} Tuple;

typedef struct
{
    int r;
    int g;
    int b;
} Rgb;

/*
position x , y , height, width, text , RGB color , font_size , position , border_radius
*/
typedef struct
{
    int x;
    int y;
    int h;
    int w;
    char *text;
    Rgb color;
    int font_size;
    char *position;
    bool border_radius;
} Ui;

int xpos(int x, char pos[], Ui *ui)
{

    if (strcmp(pos, "right") == 0)
    {
        x = WINDOW_WIDTH - x - ui->w;
        if (ui->border_radius)
            x = x - ui->h / 2;
    }
    if (ui->border_radius && strcmp(pos, "right") != 0)
        x = x + ui->h / 2;

    ui->x = x;
    return x;
}
int ypos(int y, char pos[], Ui *ui)
{

    if (strcmp(pos, "top") == 0)
        y = WINDOW_HEIGHT - y - ui->h;

    ui->y = y;
    return y;
}

/*
RENDERS USER INTERFACE IN WINDOW
TAKES Ui STRUCT AS INPUT
*/
void render(Ui *ui)
{
    // background color
    iSetColor(ui->color.r, ui->color.g, ui->color.b);

    // calculating coordinates
    int x = ui->x, y = ui->y;

    // rendering rectangle
    if (strcmp("center", ui->position) == 0)
    {
        x = (WINDOW_WIDTH / 2) - ((ui->w) / 2);
        y = (WINDOW_HEIGHT / 2) - ((ui->h) / 2);
        ui->x = x;
        ui->y = y;
        iFilledRectangle(x, y, ui->w, ui->h);
    }
    else if (strcmp("center-x", ui->position) == 0)
    {
        x = (WINDOW_WIDTH / 2) - ((ui->w) / 2);
        ui->x = x;
        iFilledRectangle(x, y, ui->w, ui->h);
    }
    else if (strcmp("center-y", ui->position) == 0)
    {
        y = (WINDOW_HEIGHT / 2) - ((ui->h) / 2);
        ui->y = y;
        iFilledRectangle(x, y, ui->w, ui->h);
    }
    else
    {

        iFilledRectangle(x, y, ui->w, ui->h);
    }

    iSetColor(ui->color.r, ui->color.g, ui->color.b);

    // rendering border radius
    if (ui->border_radius)
    {

        iFilledCircle(x, y + ((ui->h) / 2), (ui->h) / 2);
        iFilledCircle(x + ui->w, y + (ui->h) / 2, (ui->h) / 2);
    }

    // rendering font
    iSetColor(255, 255, 255);

    if (ui->font_size == 18)
    {
        int font_x = x + (((ui->w) - strlen(ui->text) * 11) / 2);
        int font_y = y + (((ui->h) - 14) / 2);
        iText(font_x, font_y, ui->text, GLUT_BITMAP_HELVETICA_18);
    }
    else
    {
        int font_x = x + (((ui->w) - strlen(ui->text) * 7) / 2);
        int font_y = y + (((ui->h) - 10) / 2);
        iText(font_x, font_y, ui->text, GLUT_BITMAP_HELVETICA_12);
    }
}

int click_or_hover(int mx, int my, Ui ui, int sound = 1)
{
    if ((ui.x < mx && mx < (ui.x + ui.w)) && (ui.y < my && (my < (ui.y + ui.h))))
    {
        if (sound)
            PlaySound(click_buffer, NULL, SND_MEMORY | SND_ASYNC);
        return 1;
    }
    else
    {
        return 0;
    }
}



void copySubstring(char *source, int start, int end, char *destination)
{

    int length = strlen(source);
    if (start < 0 || end >= length || start > end)
    {
        printf("Invalid indices.\n");
        destination[0] = '\0';
        return;
    }

    int i, j = 0;
    for (i = start; i <= end; i++)
    {
        destination[j++] = source[i];
    }

    destination[j] = '\0';
}




#endif // UI_LIBRARY