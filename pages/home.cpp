#ifndef HOME
#define HOME

#include"../library/ui.cpp"
#include"../iGraphics.h"
#include<math.h>
#include<Windows.h>


int text_x=400;
int text_y1=WINDOW_HEIGHT-120;
int text_y2=WINDOW_HEIGHT-120;

int text_direction=2;
//background music play

void bg_music()
{
   PlaySound(bg_buffer, NULL, SND_MEMORY | SND_ASYNC);
}

//animation

void title_animation()
{
    text_x = ((text_x+2) % 1000 );
    
    if(text_y1>515)
    {
        text_direction=1;
    }
     if(text_y1<495){
         text_direction=2;
    }
    text_y1 = text_y1 + pow(-1,text_direction)* 1;
    text_y2 = text_y2 - pow(-1,text_direction)* 1;
}

//desiging ui components
Ui single_btn = {
    xpos( 99,"left",&single_btn),
    ypos( 150+60,"top",&single_btn),
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
    ypos( 150+20+60+60,"top",&two_player_btn),
    60,
    300,
    "START TWO PLAYER",
    { 82 ,  3,  252},
     18,
    "center-x",
     true,
};
Ui settings = {
    xpos( 99,"left",&settings),
    ypos( 150+20+60 +80+60,"top",&settings),
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
    ypos(150+20+60+160+60,"top",&help),
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
    iText(text_x,text_y1,"S ",GLUT_BITMAP_TIMES_ROMAN_24);
    iText((text_x+60)%1000,text_y2,"N ",GLUT_BITMAP_TIMES_ROMAN_24);
    iText((text_x+60+40)%1000,text_y1,"A ",GLUT_BITMAP_TIMES_ROMAN_24);
    iText((text_x+90+80)%1000,text_y2,"K ",GLUT_BITMAP_TIMES_ROMAN_24);
    iText((text_x+120+120)%1000,text_y1,"E ",GLUT_BITMAP_TIMES_ROMAN_24);
    iText((text_x+150+160)%1000,text_y2,"_ ",GLUT_BITMAP_TIMES_ROMAN_24);
    iText((text_x+180+200)%1000,text_y1,"S ",GLUT_BITMAP_TIMES_ROMAN_24);
    iText((text_x+210+240)%1000,text_y2,"H ",GLUT_BITMAP_TIMES_ROMAN_24);
    iText((text_x+240+280)%1000,text_y1,"H ",GLUT_BITMAP_TIMES_ROMAN_24);
    render(&single_btn);
    render(&two_player_btn);
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