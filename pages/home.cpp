#ifndef HOME
#define HOME

#include"../library/ui.cpp"
#include"../iGraphics.h"

//desiging ui components
Ui single_btn = {
    xpos( 99,"left",&single_btn),
    ypos( 150,"top",&single_btn),
    60,
    300,
    "START SINGLE PLAYER",
    { 82 ,  3,  252},
     18,
    "center-x",
     true,
};
Ui two_player_btn = {
    xpos( 99,"left",&two_player_btn),
    ypos( 150+20+60,"top",&two_player_btn),
    60,
    300,
    "START TWO PLAYER",
    { 82 ,  3,  252},
     18,
    "center-x",
     true,
};
Ui computer_btn = {
    xpos( 99,"left",&computer_btn),
    ypos( 150+20+60 +80,"top",&computer_btn),
    60,
    300,
    "PLAY VS COMPUTER",
    { 82 ,  3,  252},
     18,
    "center-x",
     true,
};
Ui settings = {
    xpos( 99,"left",&settings),
    ypos( 150+20+60+160,"top",&settings),
    60,
    300,
    "SETTINGS",
    { 82 ,  3,  252},
     18,
    "center-x",
     true,
};
Ui help = {
    xpos( 99,"left",&help),
    ypos( 150+20+60+160+80,"top",&help),
    60,
    300,
    "HELP",
    { 82 ,  3,  252},
     18,
    "center-x",
     true,
};

// RENDERS HOME PAGE
void home_page()
{
    render(&single_btn);
    render(&two_player_btn);
    render(&computer_btn);
    render(&settings);
    render(&help);
}


// BUTTON CLICK CONTROLLER
void home_page_control(int mx , int my)
{
    if(click_or_hover(mx,my,single_btn))
    {
        page_state = 1;
    }
    else if(click_or_hover(mx,my,two_player_btn))
    {
        page_state = 2;
    }
    else if(click_or_hover(mx,my,computer_btn))
    {
        page_state = 3;
    }
    else if(click_or_hover(mx,my,settings))
    {
        page_state = 4;
    }
    else if(click_or_hover(mx,my,help))
    {
        page_state = 5;
    } 
}

#endif