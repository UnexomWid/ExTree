#include "buttons.h"

struct textsettingstype textInfo;
struct linesettingstype lineInfo;

int mouseX, mouseY;

BUTTONS button = NONE;
LANGUAGE lng = EN;

buttonSettings animEval_1[4];
buttonSettings animEval_2[4];
buttonSettings instantEval_1[4];
buttonSettings instantEval_2[4];
buttonSettings options[4];
buttonSettings about[4];
buttonSettings quit[4];
buttonSettings options_lng[4];
buttonSettings options_back[4];

bool isInitialized = false;

void defineButtonSettings()
{
    // English.

    animEval_1[0].word = "Animated";
    animEval_1[0].posX = 1340;
    animEval_1[0].posY = 200;

    animEval_2[0].word = "evaluation";
    animEval_2[0].posX = 1330;
    animEval_2[0].posY = 250;

    instantEval_1[0].word = "Instant";
    instantEval_1[0].posX = 1360;
    instantEval_1[0].posY = 330;

    instantEval_2[0].word = "evaluation";
    instantEval_2[0].posX = 1330;
    instantEval_2[0].posY = 380;

    options[0].word = "Options";
    options[0].posX = 1355;
    options[0].posY = 470;

    about[0].word = "About";
    about[0].posX = 1375;
    about[0].posY = 568;

    quit[0].word = "Quit";
    quit[0].posX = 1390;
    quit[0].posY = 665;

    options_lng[0].word = "Language";
    options_lng[0].posX = 1325;
    options_lng[0].posY = 220;

    options_back[0].word = "Back";
    options_back[0].posX = 1385;
    options_back[0].posY = 665;

    // Romanian.

    animEval_1[1].word = "Evaluare";
    animEval_1[1].posX = 1350;
    animEval_1[1].posY = 200;

    animEval_2[1].word = "animata";
    animEval_2[1].posX = 1355;
    animEval_2[1].posY = 250;

    instantEval_1[1].word = "Evaluare";
    instantEval_1[1].posX = 1350;
    instantEval_1[1].posY = 330;

    instantEval_2[1].word = "instanta";
    instantEval_2[1].posX = 1355;
    instantEval_2[1].posY = 380;

    options[1].word = "Optiuni";
    options[1].posX = 1360;
    options[1].posY = 470;

    about[1].word = "Despre";
    about[1].posX = 1360;
    about[1].posY = 568;

    quit[1].word = "Iesire";
    quit[1].posX = 1380;
    quit[1].posY = 665;

    options_lng[1].word = "Limba";
    options_lng[1].posX = 1370;
    options_lng[1].posY = 220;

    options_back[1].word = "Inapoi";
    options_back[1].posX = 1370;
    options_back[1].posY = 665;

    // German.

    animEval_1[2].word = "Animirte";
    animEval_1[2].posX = 1355;
    animEval_1[2].posY = 200;

    animEval_2[2].word = "Auswertung";
    animEval_2[2].posX = 1313;
    animEval_2[2].posY = 250;

    instantEval_1[2].word = "Direkte";
    instantEval_1[2].posX = 1360;
    instantEval_1[2].posY = 330;

    instantEval_2[2].word = "Auswertung";
    instantEval_2[2].posX = 1313;
    instantEval_2[2].posY = 380;

    options[2].word = "Optionen";
    options[2].posX = 1340;
    options[2].posY = 470;

    about[2].word = "Uber";
    about[2].posX = 1390;
    about[2].posY = 568;

    quit[2].word = "Endet";
    quit[2].posX = 1375;
    quit[2].posY = 665;

    options_lng[2].word = "Sprache";
    options_lng[2].posX = 1350;
    options_lng[2].posY = 220;

    options_back[2].word = "Zuruck";
    options_back[2].posX = 1370;
    options_back[2].posY = 665;

    // French.

    animEval_1[3].word = "Evaluation";
    animEval_1[3].posX = 1330;
    animEval_1[3].posY = 200;

    animEval_2[3].word = "animee";
    animEval_2[3].posX = 1350;
    animEval_2[3].posY = 250;

    instantEval_1[3].word = "Evaluation";
    instantEval_1[3].posX = 1330;
    instantEval_1[3].posY = 330;

    instantEval_2[3].word = "instantanee";
    instantEval_2[3].posX = 1315;
    instantEval_2[3].posY = 380;

    options[3].word = "Options";
    options[3].posX = 1355;
    options[3].posY = 470;

    about[3].word = "Infos";
    about[3].posX = 1385;
    about[3].posY = 568;

    quit[3].word = "Quitter";
    quit[3].posX = 1370;
    quit[3].posY = 665;

    options_lng[3].word = "Langue";
    options_lng[3].posX = 1350;
    options_lng[3].posY = 220;

    options_back[3].word = "Revenu";
    options_back[3].posX = 1360;
    options_back[3].posY = 665;
}

void readInput()
{
    // De implementat.
}

void initializeWindow(THEME theme)  // Trebuie sa mai faci celelalte doua teme.
{
    if(!isInitialized)
    {
        initwindow(WIDTH,HEIGHT,"ExTree");
        defineButtonSettings();
        isInitialized = true;
    }
    switch(theme)
    {
    case DEFAULT:
        {
            // Sets the background to a specified color.
            setfillstyle(SOLID_FILL,BLUE);
            setbkcolor(BLUE);
            bar(0,0,WIDTH,HEIGHT);

            // Sets the text style and color
            setcolor(WHITE);
            settextstyle(SANS_SERIF_FONT,0,5);

            // Sets the fill settings.
            setfillstyle(SOLID_FILL,WHITE);

            // Sets the line settings.
            setlinestyle(SOLID_LINE,0,1);

            drawAll();
            break;
        }
    case GREEN_BLUE:
        {
            setfillstyle(SOLID_FILL,COLOR(0,51,0));
            setbkcolor(COLOR(0,51,0));
            bar(0,0,WIDTH,HEIGHT);

            setcolor(COLOR(0,205,205));
            settextstyle(SANS_SERIF_FONT,0,5);

            setfillstyle(SOLID_FILL,COLOR(0,205,205));

            setlinestyle(DOTTED_LINE,0,1);

            drawAll();
            break;
        }
    case PINKY:
        {
            setfillstyle(SOLID_FILL,COLOR(255,79,167));
            setbkcolor(COLOR(255,79,167));
            bar(0,0,WIDTH,HEIGHT);

            setcolor(COLOR(96, 15, 143));
            settextstyle(SANS_SERIF_FONT,0,5);

            setfillstyle(BKSLASH_FILL,COLOR(96, 15, 143));

            setlinestyle(DASHED_LINE,0,1);

            drawAll();
            break;
        }
    }
}

void runProgram()
{
    while(button != QUIT)
    {
        getmouseclick(WM_LBUTTONDOWN,mouseX,mouseY);
        if(isAnimEvalPressed(mouseX,mouseY) && button != ANIM_EVAL)
        {
            // Call AnimEval();
            Log("Animated evaluation was pressed!");
            button = ANIM_EVAL;
        }
        if(isInstantEvalPressed(mouseX,mouseY) && button != INSTANT_EVAL)
        {
            // Call InstantEval();
            Log("Instant evaluation was pressed!");
            button = INSTANT_EVAL;
        }
        if(isOptionsPressed(mouseX,mouseY) && button != OPTIONS)
        {
            // Call Options();
            Log("Options was pressed!");
            button = OPTIONS;
            Options();

        }
        if(isAboutPressed(mouseX,mouseY) && button != ABOUT)
        {
            // Call About();
            Log("About was pressed!");
            button = ABOUT;
        }
        if(isQuitPressed(mouseX,mouseY) && button != QUIT)
        {
            button = QUIT;
            Log("Quit was pressed!");
            closegraph();
        }
    }

}



bool isAnimEvalPressed(int X, int Y){
    return ((X>=1310 && X<=1570) && (Y>=190 && Y<=305));
}

bool isInstantEvalPressed(int X, int Y){
    return (X >= 1310 && X <= 1570) && (Y >= 320 && Y <= 435);
}

bool isOptionsPressed(int X, int Y){
    return (X >= 1310 && X <= 1570) && (Y >=450 && Y <= 535);
}

bool isAboutPressed(int X, int Y){
    return (X >= 1310 && X <= 1570) && (Y >=550 && Y <= 630);
}

bool isQuitPressed(int X, int Y){
    return (X >= 1310 && X <= 1570) && (Y >=645 && Y <= 725);
}



void drawAll(LANGUAGE lng)
{
    gettextsettings(&textInfo);
    getlinesettings(&lineInfo);

    drawSquares();
    drawTitle();
    drawAnimEval();
    drawInstantEval();
    drawOptions();
    drawAbout();
    drawQuit();
}

void drawSquares()
{
    bar(1270,0,1275,HEIGHT);
    bar(1270,150,WIDTH,155);
}

void drawTitle()
{
    settextstyle(textInfo.font,textInfo.direction,8);
    outtextxy(1325,40,"ExTree");
}

void drawAnimEval()
{
    setlinestyle(lineInfo.linestyle,lineInfo.upattern,2);
    rectangle(1310,190,1570,305);

    settextstyle(textInfo.font,textInfo.direction,5);
    outtextxy(animEval_1[lng].posX,animEval_1[lng].posY,animEval_1[lng].word);
    outtextxy(animEval_2[lng].posX,animEval_2[lng].posY,animEval_2[lng].word);
}

void drawInstantEval()
{
    setlinestyle(lineInfo.linestyle,lineInfo.upattern,2);
    rectangle(1310,320,1570,435);

    settextstyle(textInfo.font,textInfo.direction,5);
    outtextxy(instantEval_1[lng].posX,instantEval_1[lng].posY,instantEval_1[lng].word);
    outtextxy(instantEval_2[lng].posX,instantEval_2[lng].posY,instantEval_2[lng].word);
}

void drawOptions()
{
    setlinestyle(lineInfo.linestyle,lineInfo.upattern,2);
    rectangle(1310,450,1570,535);

    settextstyle(textInfo.font,textInfo.direction,5);
    outtextxy(options[lng].posX,options[lng].posY,options[lng].word);
}

void drawAbout()
{
    setlinestyle(lineInfo.linestyle,lineInfo.upattern,2);
    rectangle(1310,550,1570,630);

    settextstyle(textInfo.font,textInfo.direction,5);
    outtextxy(about[lng].posX,about[lng].posY,about[lng].word);
}

void drawQuit()
{
    setlinestyle(lineInfo.linestyle,lineInfo.upattern,2);
    rectangle(1310,645,1570,725);

    settextstyle(textInfo.font,textInfo.direction,5);
    outtextxy(quit[lng].posX,quit[lng].posY,quit[lng].word);
}


void Options()
{
    setfillstyle(SOLID_FILL,getbkcolor());
    bar(1275,155,WIDTH,HEIGHT);

    // This draws the "Language" title and icons.

    setlinestyle(lineInfo.linestyle,lineInfo.upattern,2);

    settextstyle(textInfo.font,textInfo.direction,5);
    outtextxy(options_lng[lng].posX,options_lng[lng].posY,options_lng[lng].word);

    readimagefile("assets\\images\\britan_flag.jpg",1345,280,1420,330);
    rectangle(1345,280,1420,330);
    readimagefile("assets\\images\\romanian_flag.jpg",1445,280,1520,330);
    rectangle(1445,280,1520,330);
    readimagefile("assets\\images\\german_flag.jpg",1345,350,1420,400);
    rectangle(1345,350,1420,400);
    readimagefile("assets\\images\\french_flag.jpg",1445,350,1520,400);
    rectangle(1445,350,1520,400);


    // This draws the "Back" button.
    rectangle(1310,645,1570,725);
    outtextxy(options_back[lng].posX,options_back[lng].posY,options_back[lng].word);

    while(button != OPTIONS_Back)
    {
        getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
        if(mouseX >= 1345 && mouseX <= 1420 && mouseY >= 280 && mouseY <= 330 && lng != EN)
        {
            lng = EN;
        }
        if(mouseX >= 1445 && mouseX <=1520 && mouseY >= 280 && mouseY <= 330 && lng != RO)
        {
            lng = RO;
        }
        if(mouseX >= 1345 && mouseX <=1420 && mouseY >= 350 && mouseY <= 400 && lng != DE)
        {
            lng = DE;
        }
        if(mouseX >= 1445 && mouseX <=1520 && mouseY >= 350 && mouseY <= 400 && lng != FR)
        {
            lng = FR;
        }
        if(mouseX >= 1310 && mouseX <=1570 && mouseY >= 645 && mouseY <= 725 && button != OPTIONS_Back)
        {
            Log("Back was pressed!");
            button = OPTIONS_Back;

            setfillstyle(SOLID_FILL,getbkcolor());
            bar(1275,155,WIDTH,HEIGHT);

            drawAnimEval();
            drawInstantEval();
            drawOptions();
            drawAbout();
            drawQuit();
            resetMouseClick();
        }

    }
}


void Log(char* message)
{
    std::cout<<message<<std::endl;
}

void resetMouseClick()
{
    mouseX = mouseY = -1;
}