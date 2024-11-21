#include"../library/ui.cpp"

//desiging ui components
Ui single_btn = {
    xpos( 99,"left",&single_btn),
    ypos( 150,"top",&single_btn),
    60,
    300,
    "SINGLE PLAYER",
    { 82 ,  3,  252},
     18,
    "center-x",
     true,
};

void home_page()
{
    render(&single_btn);
}