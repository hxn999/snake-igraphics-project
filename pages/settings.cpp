#ifndef SETTINGS_PAGE
#define SETTINGS_PAGE

#include <stdbool.h>
#include <Windows.h>
#include "../library/ui.cpp"
#include "../iGraphics.h"

Ui difficulty_ui = {
    xpos( 99,"left",&difficulty_ui),
    ypos( 150,"top",&difficulty_ui),
    60,
    250,
    "SET DIFFICULTY",
    { 82 ,  3,  252},
     18,
    "center-x",
     true,
};
Ui easy = {
    xpos( 120+80,"left",&easy),
    ypos( 300,"top",&easy),
    50,
    100,
    "EASY",
    { 82 ,  3,  252},
     18,
    "",
     true,
};
Ui medium = {
    xpos(350+80,"left",&medium),
    ypos( 300,"top",&medium),
    50,
    100,
    "MEDIUM",
  {49, 141, 181},
     18,
    "",
     true,
};
Ui hard = {
    xpos(580+80,"left",&hard),
    ypos( 300,"top",&hard),
    50,
    100,
    "HARD",
    { 82 ,  3,  252},
     18,
    "",
     true,
};
// Ui difficulty_ui = {
//     xpos( 99,"left",&difficulty_ui),
//     ypos( 200,"top",&difficulty_ui),
//     60,
//     250,
//     "SET DIFFICULTY",
//     { 82 ,  3,  252},
//      18,
//     "center-x",
//      true,
// };
// Ui difficulty_ui = {
//     xpos( 99,"left",&difficulty_ui),
//     ypos( 200,"top",&difficulty_ui),
//     60,
//     250,
//     "SET DIFFICULTY",
//     { 82 ,  3,  252},
//      18,
//     "center-x",
//      true,
// };


Ui back_ui = {
	xpos(20, "left", &back_ui),
	ypos(12, "top", &back_ui),
	20,
	100,
	"<-- BACK",
	{82, 3, 252},
	18,
	"",
	false,
};






void settings_page()
{
    render(&difficulty_ui);
    render(&easy);
    render(&medium);
    render(&hard);
    render(&back_ui);
}

void settings_control(int mx , int my)
{
    if(click_or_hover(mx,my,easy))
    {
        single_snake_timer=11;
        easy.color = {49, 141, 181};
         medium.color = {82, 3, 252};
         hard.color = {82, 3, 252};
    }
    if(click_or_hover(mx,my,medium))
    {
        single_snake_timer=0;
         medium.color = {49, 141, 181};
         easy.color = {82, 3, 252};
         hard.color = {82, 3, 252};
    }
    if(click_or_hover(mx,my,hard))
    {
        single_snake_timer=12;
         hard.color = {49, 141, 181};
         medium.color = {82, 3, 252};
         easy.color = {82, 3, 252};
    }
    if(click_or_hover(mx,my,back_ui))
    {
        page_state=0;
    }
}


#endif