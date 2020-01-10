#include "buttons.h"

struct textsettingstype textInfo;
struct linesettingstype lineInfo;
struct fillsettingstype fillInfo;

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
buttonSettings options_themes[4];
buttonSettings about_back[4];
buttonSettings newExp[4];

bool isInitialized = false;
bool isButtonSettingsDeclared = false;

BinaryTree* expressionTree;

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

    options_themes[0].word = "Theme";
    options_themes[0].posX = 1360;
    options_themes[0].posY = 425;

    about_back[0].word = "Back";
    about_back[0].posX = 1385;
    about_back[0].posY = 665;

    newExp[0].word = "New expression";
    newExp[0].posX = 35;
    newExp[0].posY = 5;

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

    options_themes[1].word = "Tema";
    options_themes[1].posX = 1370;
    options_themes[1].posY = 425;

    about_back[1].word = "Inapoi";
    about_back[1].posX = 1370;
    about_back[1].posY = 665;

    newExp[1].word = "Expresie noua";
    newExp[1].posX = 40;
    newExp[1].posY = 5;

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

    options_themes[2].word = "Thema";
    options_themes[2].posX = 1360;
    options_themes[2].posY = 425;

    about_back[2].word = "Zuruck";
    about_back[2].posX = 1370;
    about_back[2].posY = 665;

    newExp[2].word = "Neue Expression";
    newExp[2].posX = 20;
    newExp[2].posY = 5;

    // French.

    animEval_1[3].word = "Evaluation";
    animEval_1[3].posX = 1330;
    animEval_1[3].posY = 200;

    animEval_2[3].word = "animee";
    animEval_2[3].posX = 1360;
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

    options_themes[3].word = "Theme";
    options_themes[3].posX = 1360;
    options_themes[3].posY = 425;

    about_back[3].word = "Revenu";
    about_back[3].posX = 1360;
    about_back[3].posY = 665;

    newExp[3].word = "Nouvele expression";
    newExp[3].posX = 5;
    newExp[3].posY = 5;
}

void readInput()
{
    char s[256];
    std::cout << ">> ";
    std::cin.clear();
    std::cin.getline(s, 256);

    std::string error;
    unsigned int errorIndex = 0;

    Queue expression = toPostfix(s, error, errorIndex);

    if(!error.empty()) {
        std::cout << "ERROR: " << error << " at index " << errorIndex << "\n\n";
        std::cout << s << '\n';

        for(unsigned int i = 0; i < errorIndex; ++i)
            std::cout << '_';

        std::cout<< '^';
    } else {
        std::cout << "\nPostfix: " << postfixToString(expression);
        std::cout << "\nTree BFS: ";

        BinaryTree* tree = toExpressionTree(expression);
        std::queue<BinaryTree*> queue;

        queue.push(tree);
        while(!queue.empty()) {
            std::cout << queue.front()->data << ' ';

            if(queue.front()->left != nullptr)
                queue.push(queue.front()->left);
            if(queue.front()->right != nullptr)
                queue.push(queue.front()->right);

            queue.pop();
        }

        double result = evalExpressionTree(tree, error);

        if(!error.empty()) {
            std::cout << "\n\nERROR: " << error << "\n\n";
        } else {
            std::cout << "\n\nResult: " << result;
        }
    }
    Log("\n");
    system("pause");
}

void initializeWindow(THEME theme)
{
    if(!isButtonSettingsDeclared)
    {
        isButtonSettingsDeclared = true;
        defineButtonSettings();
    }
    if(!isInitialized)
    {
        initwindow(WIDTH,HEIGHT,"ExTree");
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
        // moveTree(); --------------------------------------------------------------------DE IMPLEMENTAT
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
            Log("Options was pressed!");
            button = OPTIONS;
            Options();

        }
        if(isAboutPressed(mouseX,mouseY) && button != ABOUT)
        {
            Log("About was pressed!");
            button = ABOUT;
            About();
        }
        if(isQuitPressed(mouseX,mouseY) && button != QUIT)
        {
            Log("Quit was pressed!");
            button = QUIT;
            closegraph();
        }
        if(isNewExpPressed(mouseX,mouseY))
        {
            closegraph(CURRENT_WINDOW);
            isInitialized = false;
            readInput();
            initializeWindow();
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

bool isNewExpPressed(int X, int Y){
    return (X>=0 && X<=420) && (Y>=0 && Y<=60);
}


void drawAll(LANGUAGE lng)
{
    gettextsettings(&textInfo);
    getlinesettings(&lineInfo);

    drawSquares();
    drawTree();
    drawNewExp();
    drawTitle();
    drawAnimEval();
    drawInstantEval();
    drawOptions();
    drawAbout();
    drawQuit();
}

void drawTree()
{
    setfillstyle(SOLID_FILL,getbkcolor());
    bar(0,65,1260,HEIGHT);
    settextstyle(textInfo.font,textInfo.direction,2);
//    char* t = "Testul";
//    char* t1 = "Test2";
//    char* t2 = "Un test mult mai lung";
//    int var = textwidth(t);
//    int var1 = textwidth(t1);
//    int var2 = textwidth(t2);
//    rectangle(600 - var/2,100, 610+ var/2,130);
//    outtextxy(600 - var/2 + 5, 105, t);
//    line(600,130,610 + var/2,150);


    //drawNode(expressionTree, 0,600);
}
void drawNode(BinaryTree* tree, int contor, int topCenter)
{
    if(tree == nullptr) return;
    int w;
    char * temp;
    strcpy(temp, tree->data.c_str());
    w = textwidth(temp);

    rectangle(topCenter,100 + contor*50,topCenter + 10 + w, 130 + contor*50);
    outtextxy(topCenter + 5, 105 + contor*50, temp);
    line()

    if(temp == "neg")
    {

    }
    else
    {

    }
}

void drawNewExp()
{
    setfillstyle(SOLID_FILL,getbkcolor());
    bar(0,0,420,60);
    line(0,60,420,60);
    line(420,60,420,0);
    settextstyle(textInfo.font,textInfo.direction,5);
    outtextxy(newExp[lng].posX,newExp[lng].posY,newExp[lng].word);
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

    // This draws the "Themes" title.
    outtextxy(options_themes[lng].posX,options_themes[lng].posY,options_themes[lng].word);

    // This draws all button themes.
    settextstyle(textInfo.font,textInfo.direction,3);
    rectangle(1355,485,1520,520);
    outtextxy(1390,490,"DEFAULT");
    rectangle(1355,530,1520,565);
    outtextxy(1370,535,"GREEN_BLUE");
    rectangle(1355,575,1520,610);
    outtextxy(1410,580,"PINKY");

    while(button != OPTIONS_Back)
    {
        getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
        if(mouseX >= 1355 && mouseX <= 1520 && mouseY >= 485 && mouseY <= 520 && button != OPTIONS_Default)
        {
            button = OPTIONS_Default;
            initializeWindow(DEFAULT);
            resetMouseClick();
            break;
        }
        if(mouseX >= 1355 && mouseX <= 1520 && mouseY >= 530 && mouseY <= 565 && button != OPTIONS_Green_Blue)
        {
            button = OPTIONS_Green_Blue;
            initializeWindow(GREEN_BLUE);
            resetMouseClick();
            break;
        }
        if(mouseX >= 1355 && mouseX <= 1520 && mouseY >= 575 && mouseY <= 610 && button != OPTIONS_Pinky)
        {
            button = OPTIONS_Pinky;
            initializeWindow(PINKY);
            resetMouseClick();
            break;
        }
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
            Log("Back from Options was pressed!");
            button = OPTIONS_Back;

            setfillstyle(SOLID_FILL,getbkcolor());
            bar(1275,155,WIDTH,HEIGHT);

            drawNewExp();
            drawAnimEval();
            drawInstantEval();
            drawOptions();
            drawAbout();
            drawQuit();
            resetMouseClick();
        }

    }
}

void About()
{
    setfillstyle(SOLID_FILL,getbkcolor());
    bar(1275,155,WIDTH,HEIGHT);

    // This draws the "Back" button.
    rectangle(1310,645,1570,725);
    outtextxy(about_back[lng].posX,about_back[lng].posY,about_back[lng].word);

    // This draws the link rectangle.
    rectangle(1310,250,1570,320);
    outtextxy(1390,265,"LINK");

    while(button != ABOUT_Back)
    {
        getmouseclick(WM_LBUTTONDOWN,mouseX, mouseY);
        if(mouseX >= 1310 && mouseX <=1570 && mouseY >= 250 && mouseY <= 320 /*&& linkPressed == false*/)
        {
            ShellExecute(HWND_DESKTOP, "open", "https://github.com/UnexomWid/ExTree", NULL, NULL, SW_SHOWDEFAULT);
            //linkPressed = true;
        }
        if(mouseX >= 1310 && mouseX <=1570 && mouseY >= 645 && mouseY <= 725 && button != ABOUT_Back)
        {
            Log("Back from About was pressed!");
            button = ABOUT_Back;

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
