#include <iostream>
#include <graphics.h>
#include "libs/stack.h"
#include "libs/queue.h"

using namespace std;

const int MAX_HEIGHT = getmaxheight()*9.5/10;   //871
const int MAX_WIDTH = getmaxwidth()/4;  //1594
int x,y;

enum ButtonType{
    EN,DE,RO,FR,HELP,ABOUT, ANIM_EXE, DIR_EXE
}lng;

void ClearButtons()
{
    setfillstyle(1,COLOR(0,0,0));
    bar(MAX_HEIGHT*2/3+50,0,MAX_HEIGHT,MAX_HEIGHT);
}

void DrawButtons_EN()
{
    ClearButtons();

    lng=EN;

    //setfillstyle(SLASH_FILL,COLOR(255,215,0));
    setfillstyle(HATCH_FILL,COLOR(255,215,0));

    bar(MAX_HEIGHT*2/3+50,0,MAX_HEIGHT*2/3+60,MAX_HEIGHT);
    bar(MAX_HEIGHT*2/3+50,100,MAX_HEIGHT,110);

    //setcolor(COLOR(138,43,226));  //purple theme
    setcolor(COLOR(124,252,0)); //light green theme

    settextstyle(10,0,5);
    outtextxy(MAX_HEIGHT*2/3+95,30,"ExTree");

    setlinestyle(1,0,3);
    settextstyle(10,0,3);

    //Animated evaluation button
    rectangle(MAX_HEIGHT*2/3+85,155,MAX_HEIGHT-20,235);
    outtextxy(MAX_HEIGHT*2/3+114,165,"Animated");
    outtextxy(MAX_HEIGHT*2/3+100,205,"evaluation");

    //Instant evaluation button
    rectangle(MAX_HEIGHT*2/3+85,265,MAX_HEIGHT-20,345);
    outtextxy(MAX_HEIGHT*2/3+122,275,"Instant");
    outtextxy(MAX_HEIGHT*2/3+100,310,"evaluation");

    //New expression button
    rectangle(MAX_HEIGHT*2/3+85, 375, MAX_HEIGHT-20, 455);
    outtextxy(MAX_HEIGHT*2/3+148, 390, "New");
    outtextxy(MAX_HEIGHT*2/3+102, 420, "expression");

    //About button
    rectangle(MAX_HEIGHT*2/3+85, 485, MAX_HEIGHT-20,535);
    outtextxy(MAX_HEIGHT*2/3+135,500,"About");


    //Help button
    rectangle(MAX_HEIGHT*2/3+85, 565, MAX_HEIGHT-20,615);
    outtextxy(MAX_HEIGHT*2/3+140,580,"Help");

    bar(MAX_HEIGHT*2/3+60,MAX_HEIGHT-180,MAX_HEIGHT,MAX_HEIGHT-170);
    setfillstyle(10,COLOR(143,188,143));
    bar(MAX_HEIGHT*2/3+60,MAX_HEIGHT-170,MAX_HEIGHT,MAX_HEIGHT);

    //Britan Image button
    readimagefile("assets\\images\\britan_flag.jpg",MAX_HEIGHT*2/3+95,MAX_HEIGHT-150,MAX_HEIGHT*2/3+155,MAX_HEIGHT-100);
    //Romanian Image button
    readimagefile("assets\\images\\romanian_flag.jpg",MAX_HEIGHT*2/3+185,MAX_HEIGHT-150,MAX_HEIGHT*2/3+245,MAX_HEIGHT-100);
    //German Image button
    readimagefile("assets\\images\\german_flag.jpg",MAX_HEIGHT*2/3+95,MAX_HEIGHT-75,MAX_HEIGHT*2/3+155,MAX_HEIGHT-25);
    //French Image button
    readimagefile("assets\\images\\french_flag.jpg",MAX_HEIGHT*2/3+185,MAX_HEIGHT-75,MAX_HEIGHT*2/3+245,MAX_HEIGHT-25);
}

void DrawButtons_RO()
{
    ClearButtons();
    lng=RO;

    //setfillstyle(SLASH_FILL,COLOR(255,215,0));
    setfillstyle(HATCH_FILL,COLOR(255,215,0));

    bar(MAX_HEIGHT*2/3+50,0,MAX_HEIGHT*2/3+60,MAX_HEIGHT);
    bar(MAX_HEIGHT*2/3+50,100,MAX_HEIGHT,110);

    //setcolor(COLOR(138,43,226));  //purple theme
    setcolor(COLOR(124,252,0)); //light green theme

    settextstyle(10,0,5);
    outtextxy(MAX_HEIGHT*2/3+95,30,"ExTree");

    setlinestyle(1,0,3);
    settextstyle(10,0,3);

    //Animated evaluation button
    rectangle(MAX_HEIGHT*2/3+85,155,MAX_HEIGHT-20,235);
    outtextxy(MAX_HEIGHT*2/3+114,165,"Evaluare");
    outtextxy(MAX_HEIGHT*2/3+122,205,"animata");

    //Instant evaluation button
    rectangle(MAX_HEIGHT*2/3+85,265,MAX_HEIGHT-20,345);
    outtextxy(MAX_HEIGHT*2/3+120,275,"Evaluare");
    outtextxy(MAX_HEIGHT*2/3+120,310,"instanta");

    //New expression button
    rectangle(MAX_HEIGHT*2/3+85, 375, MAX_HEIGHT-20, 455);
    outtextxy(MAX_HEIGHT*2/3+120, 390, "Expresie");
    outtextxy(MAX_HEIGHT*2/3+145, 420, "noua");

    //About button
    rectangle(MAX_HEIGHT*2/3+85, 485, MAX_HEIGHT-20,535);
    outtextxy(MAX_HEIGHT*2/3+130,500,"Despre");


    //Help button
    rectangle(MAX_HEIGHT*2/3+85, 565, MAX_HEIGHT-20,615);
    outtextxy(MAX_HEIGHT*2/3+130,580,"Ajutor");

    bar(MAX_HEIGHT*2/3+60,MAX_HEIGHT-180,MAX_HEIGHT,MAX_HEIGHT-170);
    setfillstyle(10,COLOR(143,188,143));
    bar(MAX_HEIGHT*2/3+60,MAX_HEIGHT-170,MAX_HEIGHT,MAX_HEIGHT);

    //Britan Image button
    readimagefile("assets\\images\\britan_flag.jpg",MAX_HEIGHT*2/3+95,MAX_HEIGHT-150,MAX_HEIGHT*2/3+155,MAX_HEIGHT-100);
    //Romanian Image button
    readimagefile("assets\\images\\romanian_flag.jpg",MAX_HEIGHT*2/3+185,MAX_HEIGHT-150,MAX_HEIGHT*2/3+245,MAX_HEIGHT-100);
    //German Image button
    readimagefile("assets\\images\\german_flag.jpg",MAX_HEIGHT*2/3+95,MAX_HEIGHT-75,MAX_HEIGHT*2/3+155,MAX_HEIGHT-25);
    //French Image button
    readimagefile("assets\\images\\french_flag.jpg",MAX_HEIGHT*2/3+185,MAX_HEIGHT-75,MAX_HEIGHT*2/3+245,MAX_HEIGHT-25);
}

void DrawButtons_DE()
{
    ClearButtons();
    lng=DE;

    //setfillstyle(SLASH_FILL,COLOR(255,215,0));
    setfillstyle(HATCH_FILL,COLOR(255,215,0));

    bar(MAX_HEIGHT*2/3+50,0,MAX_HEIGHT*2/3+60,MAX_HEIGHT);
    bar(MAX_HEIGHT*2/3+50,100,MAX_HEIGHT,110);

    //setcolor(COLOR(138,43,226));  //purple theme
    setcolor(COLOR(124,252,0)); //light green theme

    settextstyle(10,0,5);
    outtextxy(MAX_HEIGHT*2/3+95,30,"ExTree");

    setlinestyle(1,0,3);
    settextstyle(10,0,3);

    //Animated evaluation button
    rectangle(MAX_HEIGHT*2/3+85,155,MAX_HEIGHT-20,235);
    outtextxy(MAX_HEIGHT*2/3+120,165,"Animirte");
    outtextxy(MAX_HEIGHT*2/3+105,200,"Auswertung");

    //Instant evaluation button
    rectangle(MAX_HEIGHT*2/3+85,265,MAX_HEIGHT-20,345);
    outtextxy(MAX_HEIGHT*2/3+122,275,"Direkte");
    outtextxy(MAX_HEIGHT*2/3+105,310,"Auswertung");

    //New expression button
    rectangle(MAX_HEIGHT*2/3+85, 375, MAX_HEIGHT-20, 455);
    outtextxy(MAX_HEIGHT*2/3+145, 390, "Neue");
    outtextxy(MAX_HEIGHT*2/3+103, 420, "Expression");

    //About button
    rectangle(MAX_HEIGHT*2/3+85, 485, MAX_HEIGHT-20,535);
    outtextxy(MAX_HEIGHT*2/3+115,500,"Uber das");


    //Help button
    rectangle(MAX_HEIGHT*2/3+85, 565, MAX_HEIGHT-20,615);
    outtextxy(MAX_HEIGHT*2/3+140,580,"Hilfe");

    bar(MAX_HEIGHT*2/3+60,MAX_HEIGHT-180,MAX_HEIGHT,MAX_HEIGHT-170);
    setfillstyle(10,COLOR(143,188,143));
    bar(MAX_HEIGHT*2/3+60,MAX_HEIGHT-170,MAX_HEIGHT,MAX_HEIGHT);

    //Britan Image button
    readimagefile("assets\\images\\britan_flag.jpg",MAX_HEIGHT*2/3+95,MAX_HEIGHT-150,MAX_HEIGHT*2/3+155,MAX_HEIGHT-100);
    //Romanian Image button
    readimagefile("assets\\images\\romanian_flag.jpg",MAX_HEIGHT*2/3+185,MAX_HEIGHT-150,MAX_HEIGHT*2/3+245,MAX_HEIGHT-100);
    //German Image button
    readimagefile("assets\\images\\german_flag.jpg",MAX_HEIGHT*2/3+95,MAX_HEIGHT-75,MAX_HEIGHT*2/3+155,MAX_HEIGHT-25);
    //French Image button
    readimagefile("assets\\images\\french_flag.jpg",MAX_HEIGHT*2/3+185,MAX_HEIGHT-75,MAX_HEIGHT*2/3+245,MAX_HEIGHT-25);
}

void DrawButtons_FR()
{
    ClearButtons();
    lng=FR;

    //setfillstyle(SLASH_FILL,COLOR(255,215,0));
    setfillstyle(HATCH_FILL,COLOR(255,215,0));

    bar(MAX_HEIGHT*2/3+50,0,MAX_HEIGHT*2/3+60,MAX_HEIGHT);
    bar(MAX_HEIGHT*2/3+50,100,MAX_HEIGHT,110);

    //setcolor(COLOR(138,43,226));  //purple theme
    setcolor(COLOR(124,252,0)); //light green theme

    settextstyle(10,0,5);
    outtextxy(MAX_HEIGHT*2/3+95,30,"ExTree");

    setlinestyle(1,0,3);
    settextstyle(10,0,3);

    //Animated evaluation button
    rectangle(MAX_HEIGHT*2/3+85,155,MAX_HEIGHT-20,235);
    outtextxy(MAX_HEIGHT*2/3+105,165,"Evaluation");
    outtextxy(MAX_HEIGHT*2/3+130,200,"animee");

    //Instant evaluation button
    rectangle(MAX_HEIGHT*2/3+85,265,MAX_HEIGHT-20,345);
    outtextxy(MAX_HEIGHT*2/3+105,275,"Evaluation");
    outtextxy(MAX_HEIGHT*2/3+125,310,"directe");

    //New expression button
    rectangle(MAX_HEIGHT*2/3+85, 375, MAX_HEIGHT-20, 455);
    outtextxy(MAX_HEIGHT*2/3+120, 390, "Nouvelle");
    outtextxy(MAX_HEIGHT*2/3+103, 420, "expression");

    //About button
    rectangle(MAX_HEIGHT*2/3+85, 485, MAX_HEIGHT-20,535);
    outtextxy(MAX_HEIGHT*2/3+150,500,"Sur");


    //Help button
    rectangle(MAX_HEIGHT*2/3+85, 565, MAX_HEIGHT-20,615);
    outtextxy(MAX_HEIGHT*2/3+145,580,"Aide");

    bar(MAX_HEIGHT*2/3+60,MAX_HEIGHT-180,MAX_HEIGHT,MAX_HEIGHT-170);
    setfillstyle(10,COLOR(143,188,143));
    bar(MAX_HEIGHT*2/3+60,MAX_HEIGHT-170,MAX_HEIGHT,MAX_HEIGHT);

    //Britan Image button
    readimagefile("assets\\images\\britan_flag.jpg",MAX_HEIGHT*2/3+95,MAX_HEIGHT-150,MAX_HEIGHT*2/3+155,MAX_HEIGHT-100);
    //Romanian Image button
    readimagefile("assets\\images\\romanian_flag.jpg",MAX_HEIGHT*2/3+185,MAX_HEIGHT-150,MAX_HEIGHT*2/3+245,MAX_HEIGHT-100);
    //German Image button
    readimagefile("assets\\images\\german_flag.jpg",MAX_HEIGHT*2/3+95,MAX_HEIGHT-75,MAX_HEIGHT*2/3+155,MAX_HEIGHT-25);
    //French Image button
    readimagefile("assets\\images\\french_flag.jpg",MAX_HEIGHT*2/3+185,MAX_HEIGHT-75,MAX_HEIGHT*2/3+245,MAX_HEIGHT-25);
}

void SetLanguage()
{
    if(x>=MAX_HEIGHT*2/3+95 && x<=MAX_HEIGHT*2/3+155 && y>=MAX_HEIGHT-150 && y<=MAX_HEIGHT-100 && lng!=EN)
    {
        DrawButtons_EN();
        return;
    }
    if(x>=MAX_HEIGHT*2/3+95 && x<=MAX_HEIGHT*2/3+155 && y>=MAX_HEIGHT-75 && y<=MAX_HEIGHT-25 && lng!=DE)
    {
        DrawButtons_DE();
        return;
    }
    if(x>=MAX_HEIGHT*2/3+185 && x<=MAX_HEIGHT*2/3+245 && y>=MAX_HEIGHT-150 && y<=MAX_HEIGHT-100 && lng!=RO)
    {
        DrawButtons_RO();
        return;
    }
    if(x>=MAX_HEIGHT*2/3+185 && x<=MAX_HEIGHT*2/3+245 && y>=MAX_HEIGHT-75 && y<=MAX_HEIGHT-25 && lng!=FR)
    {
        DrawButtons_FR();
        return;
    }
}

int main()
{
    /* First read from the console then open the window*/

    initwindow(MAX_HEIGHT,MAX_HEIGHT,"ExTree",MAX_WIDTH);
    DrawButtons_RO();
    while(1)
    {
        getmouseclick(WM_LBUTTONDOWN,x,y);
        SetLanguage();
    }
    getch();



    return 0;
}
