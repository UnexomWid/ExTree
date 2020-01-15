#include "gui.h"

struct textsettingstype textInfo;
struct linesettingstype lineInfo;
struct fillsettingstype fillInfo;

int mouseX, mouseY;

double angleStartLeft = 4.5378;
double angleStartRight = 1.7453;
double angleDifference = 0.1745;
double angleMinLeft = 3.49;
double angleMaxRight = 2.79;

double offsetX = 0;
double offsetY = 0;

int minLineSize = 35;

BUTTONS button = NONE;
LANGUAGE lng = EN;
THEME globalTheme = DEFAULT;

bool leftArrow = false;
bool rightArrow = false;
bool upArrow = false;
bool downArrow = false;

float time = 10000;

buttonSettings animEvalTopText[4];
buttonSettings animEvalBottomText[4];
buttonSettings instantEvalTopText[4];
buttonSettings instantEvalBottomText[4];
buttonSettings optionsText[4];
buttonSettings aboutText[4];
buttonSettings quitText[4];
buttonSettings optionsLanguageText[4];
buttonSettings optionsBackText[4];
buttonSettings optionsThemesText[4];
buttonSettings aboutBackText[4];
buttonSettings newExp[4];

bool isInitialized = false;
bool isButtonSettingsDeclared = false;
bool isEvaluated = false;

std::string infixExpression;

BinaryTree* expressionTree = nullptr;
BinaryTree* originalTree = nullptr;
BinaryTree* unsubstitutedTree = nullptr;

void defineButtonSettings() {
    // English.

    animEvalTopText[0].word = "Animated";
    animEvalTopText[0].posX = 1340;
    animEvalTopText[0].posY = 200;

    animEvalBottomText[0].word = "evaluation";
    animEvalBottomText[0].posX = 1330;
    animEvalBottomText[0].posY = 250;

    instantEvalTopText[0].word = "Instant";
    instantEvalTopText[0].posX = 1360;
    instantEvalTopText[0].posY = 330;

    instantEvalBottomText[0].word = "evaluation";
    instantEvalBottomText[0].posX = 1330;
    instantEvalBottomText[0].posY = 380;

    optionsText[0].word = "Options";
    optionsText[0].posX = 1355;
    optionsText[0].posY = 470;

    aboutText[0].word = "About";
    aboutText[0].posX = 1375;
    aboutText[0].posY = 568;

    quitText[0].word = "Quit";
    quitText[0].posX = 1390;
    quitText[0].posY = 665;

    optionsLanguageText[0].word = "Language";
    optionsLanguageText[0].posX = 1325;
    optionsLanguageText[0].posY = 220;

    optionsBackText[0].word = "Back";
    optionsBackText[0].posX = 1385;
    optionsBackText[0].posY = 665;

    optionsThemesText[0].word = "Theme";
    optionsThemesText[0].posX = 1360;
    optionsThemesText[0].posY = 425;

    aboutBackText[0].word = "Back";
    aboutBackText[0].posX = 1385;
    aboutBackText[0].posY = 665;

    newExp[0].word = "New expression";
    newExp[0].posX = 35;
    newExp[0].posY = 5;

    // Romanian.

    animEvalTopText[1].word = "Evaluare";
    animEvalTopText[1].posX = 1350;
    animEvalTopText[1].posY = 200;

    animEvalBottomText[1].word = "animata";
    animEvalBottomText[1].posX = 1355;
    animEvalBottomText[1].posY = 250;

    instantEvalTopText[1].word = "Evaluare";
    instantEvalTopText[1].posX = 1350;
    instantEvalTopText[1].posY = 330;

    instantEvalBottomText[1].word = "instanta";
    instantEvalBottomText[1].posX = 1355;
    instantEvalBottomText[1].posY = 380;

    optionsText[1].word = "Optiuni";
    optionsText[1].posX = 1360;
    optionsText[1].posY = 470;

    aboutText[1].word = "Despre";
    aboutText[1].posX = 1360;
    aboutText[1].posY = 568;

    quitText[1].word = "Iesire";
    quitText[1].posX = 1380;
    quitText[1].posY = 665;

    optionsLanguageText[1].word = "Limba";
    optionsLanguageText[1].posX = 1370;
    optionsLanguageText[1].posY = 220;

    optionsBackText[1].word = "Inapoi";
    optionsBackText[1].posX = 1370;
    optionsBackText[1].posY = 665;

    optionsThemesText[1].word = "Tema";
    optionsThemesText[1].posX = 1370;
    optionsThemesText[1].posY = 425;

    aboutBackText[1].word = "Inapoi";
    aboutBackText[1].posX = 1370;
    aboutBackText[1].posY = 665;

    newExp[1].word = "Expresie noua";
    newExp[1].posX = 40;
    newExp[1].posY = 5;

    // German.

    animEvalTopText[2].word = "Animirte";
    animEvalTopText[2].posX = 1355;
    animEvalTopText[2].posY = 200;

    animEvalBottomText[2].word = "Auswertung";
    animEvalBottomText[2].posX = 1313;
    animEvalBottomText[2].posY = 250;

    instantEvalTopText[2].word = "Direkte";
    instantEvalTopText[2].posX = 1360;
    instantEvalTopText[2].posY = 330;

    instantEvalBottomText[2].word = "Auswertung";
    instantEvalBottomText[2].posX = 1313;
    instantEvalBottomText[2].posY = 380;

    optionsText[2].word = "Optionen";
    optionsText[2].posX = 1340;
    optionsText[2].posY = 470;

    aboutText[2].word = "Uber";
    aboutText[2].posX = 1390;
    aboutText[2].posY = 568;

    quitText[2].word = "Endet";
    quitText[2].posX = 1375;
    quitText[2].posY = 665;

    optionsLanguageText[2].word = "Sprache";
    optionsLanguageText[2].posX = 1350;
    optionsLanguageText[2].posY = 220;

    optionsBackText[2].word = "Zuruck";
    optionsBackText[2].posX = 1370;
    optionsBackText[2].posY = 665;

    optionsThemesText[2].word = "Thema";
    optionsThemesText[2].posX = 1360;
    optionsThemesText[2].posY = 425;

    aboutBackText[2].word = "Zuruck";
    aboutBackText[2].posX = 1370;
    aboutBackText[2].posY = 665;

    newExp[2].word = "Neue Expression";
    newExp[2].posX = 20;
    newExp[2].posY = 5;

    // French.

    animEvalTopText[3].word = "Evaluation";
    animEvalTopText[3].posX = 1330;
    animEvalTopText[3].posY = 200;

    animEvalBottomText[3].word = "animee";
    animEvalBottomText[3].posX = 1360;
    animEvalBottomText[3].posY = 250;

    instantEvalTopText[3].word = "Evaluation";
    instantEvalTopText[3].posX = 1330;
    instantEvalTopText[3].posY = 330;

    instantEvalBottomText[3].word = "instantanee";
    instantEvalBottomText[3].posX = 1315;
    instantEvalBottomText[3].posY = 380;

    optionsText[3].word = "Options";
    optionsText[3].posX = 1355;
    optionsText[3].posY = 470;

    aboutText[3].word = "Infos";
    aboutText[3].posX = 1385;
    aboutText[3].posY = 568;

    quitText[3].word = "Quitter";
    quitText[3].posX = 1370;
    quitText[3].posY = 665;

    optionsLanguageText[3].word = "Langue";
    optionsLanguageText[3].posX = 1350;
    optionsLanguageText[3].posY = 220;

    optionsBackText[3].word = "Revenu";
    optionsBackText[3].posX = 1360;
    optionsBackText[3].posY = 665;

    optionsThemesText[3].word = "Theme";
    optionsThemesText[3].posX = 1360;
    optionsThemesText[3].posY = 425;

    aboutBackText[3].word = "Revenu";
    aboutBackText[3].posX = 1360;
    aboutBackText[3].posY = 665;

    newExp[3].word = "Nouvele expression";
    newExp[3].posX = 5;
    newExp[3].posY = 5;
}

void readInput() {
    read_input:

    char s[256];
    Log(">> ");
    std::cin.getline(s, 256);

    std::string error;
    uint errorIndex = 0;

    Queue expression = toPostfix(s, error, errorIndex);

    if(!error.empty()) {
        Log("ERROR: %s at index + %u\n\n", error.c_str(), errorIndex);
        Log("%s\n", s);

        for(uint i = 0; i < errorIndex; ++i)
            Log("_");

        Log("^\n\n");

        std::cin.clear();
        goto read_input;
    } else {
        infixExpression.assign(s);
        expressionTree = toExpressionTree(expression);

        BinaryTree* tempTree = expressionTree->copy();
        substituteConstants(tempTree);

        if(isNullOrWhitespace(getNextVariable(tempTree))) {
            evalExpressionTree(tempTree, error);

            if(!error.empty()) {
                Log("ERROR: %s\n\n", error.c_str());
                std::cin.clear();
                goto read_input;
            }
        }
    }
}

void initializeWindow(THEME theme) {
    globalTheme = theme;
    Beep(3000,100);
    if(!isButtonSettingsDeclared) {
        isButtonSettingsDeclared = true;
        defineButtonSettings();
    }
    if(!isInitialized) {
        initwindow(WIDTH,HEIGHT,"ExTree");
        isEvaluated = false;
        isInitialized = true;
    }
    switch(theme) {
    case DEFAULT: {
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
    case GREEN_BLUE: {
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
    case PINKY: {
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

void runProgram() {
    while(button != QUIT) {
        getmouseclick(WM_LBUTTONDOWN,mouseX,mouseY);

        if(GetAsyncKeyState(VK_LEFT) && leftArrow == false && !isEvaluated) {
            leftArrow = true;
            offsetX -= TREE_SPEED;
            initializeWindow(globalTheme);
        }
        else if(GetAsyncKeyState(VK_RIGHT) && rightArrow == false && !isEvaluated) {
                rightArrow = true;
                offsetX += TREE_SPEED;
                initializeWindow(globalTheme);
            }
            else if(GetAsyncKeyState(VK_DOWN) && downArrow == false && !isEvaluated) {
                    downArrow = true;
                    offsetY += TREE_SPEED;
                    initializeWindow(globalTheme);
                }
                else if(GetAsyncKeyState(VK_UP) && upArrow == false && !isEvaluated) {
                        upArrow = true;
                        offsetY -= TREE_SPEED;
                        initializeWindow(globalTheme);
                    }
                    else if(time <= 0){
                            time = 100000;
                            upArrow = false;
                            downArrow = false;
                            leftArrow = false;
                            rightArrow = false;
                        }
                        else
                            time -=TIME_SPEED;

        if(isAnimEvalPressed(mouseX,mouseY) && button != ANIM_EVAL) {
            button = ANIM_EVAL;

            if(!isNullOrWhitespace(getNextVariable(expressionTree))) {
                if(originalTree != nullptr)
                    unsubstitutedTree = originalTree->copy();
                else unsubstitutedTree = expressionTree->copy();

                button = NONE;
                closegraph(CURRENT_WINDOW);
                isInitialized = false;

                readVariables();

                initializeWindow(globalTheme);
            } else {
                originalTree = expressionTree->copy();
                substituteConstants(expressionTree);
                isEvaluated = true;
                animEval();
            }
        }
        if(isInstantEvalPressed(mouseX,mouseY) && button != INSTANT_EVAL && !isEvaluated) {
            button = INSTANT_EVAL;

            if(!isNullOrWhitespace(getNextVariable(expressionTree))) {
                if(originalTree != nullptr)
                    unsubstitutedTree = originalTree->copy();
                else unsubstitutedTree = expressionTree->copy();

                button = NONE;
                closegraph(CURRENT_WINDOW);
                isInitialized = false;

                readVariables();

                initializeWindow(globalTheme);
            } else {
                originalTree = expressionTree->copy();
                substituteConstants(expressionTree);
                isEvaluated = true;
                instantEval();
            }
        }
        if(isOptionsPressed(mouseX,mouseY) && button != OPTIONS) {
            button = OPTIONS;
            options();
        }
        if(isAboutPressed(mouseX,mouseY) && button != ABOUT) {
            button = ABOUT;
            about();
        }
        if(isQuitPressed(mouseX,mouseY) && button != QUIT) {
            button = QUIT;
            for(int i=2000;i>37;i-=100)
            {
                Beep(i,1+ i/20);
                delay(10);
            }
            closegraph();
        }
        if(isNewExpPressed(mouseX,mouseY)) {
            Beep(3000,200);
            button = NONE;
            closegraph(CURRENT_WINDOW);
            isInitialized = false;

            if(unsubstitutedTree != nullptr) {
                Log("Do you want to change the variables? (Y/N)\n");

                char c[256];
                std::cin.getline(c, 256);
                while(c[0] != 'Y' && c[0] != 'y' && c[0] != 'N' && c[0] != 'n')
                    std::cin.getline(c, 256);

                if(c[0] == 'N' || c[0] == 'n') {
                    expressionTree = nullptr;
                    originalTree = nullptr;
                    unsubstitutedTree = nullptr;

                    readInput();
                } else {
                    readVariables();
                }
            } else {
                expressionTree = nullptr;
                originalTree = nullptr;

                readInput();
            }

            initializeWindow();
        }
        if(isArrowPressed(mouseX,mouseY) && isEvaluated) {
            Beep(3000,100);
            button = ARROW;
            isEvaluated = false;
            offsetX = 0;
            offsetY = 0;

            if(originalTree != nullptr) {
                expressionTree = originalTree->copy();
                originalTree = nullptr;
            }
            else
                expressionTree = unsubstitutedTree->copy();

            drawTree();
        }
    }
}

void readVariables() {
    readVariablesLoop:

    Log("\n%s\n\n", infixExpression.c_str());

    originalTree = unsubstitutedTree->copy();
    std::string var = getNextVariable(originalTree);

    while(!isNullOrWhitespace(var)) {
        variableLoop:

        Log("%s = ", var.c_str());

        char buffer[256];
        double value;
        std::cin.getline(buffer, 256);

        try {
            value = std::stod(buffer);
        } catch(std::exception &e) {
            goto variableLoop;
        }

        substitute(originalTree, var, value);
        var = getNextVariable(originalTree);
    }

    std::string err;
    BinaryTree* tempTree = originalTree->copy();
    substituteConstants(tempTree);

    evalExpressionTree(tempTree, err);

    if(!err.empty()) {
        Log("\nERROR: %s\n\n", err.c_str());
        goto readVariablesLoop;
    }

    expressionTree = originalTree->copy();
}

void animEval() {
    setfillstyle(SOLID_FILL,getbkcolor());
    bar(0,0,1260,HEIGHT);
    drawNewExp();
    drawArrow();
    if(globalTheme == DEFAULT)
        setlinestyle(SOLID_LINE,0,1);
    else
        if(globalTheme == GREEN_BLUE)
            setlinestyle(DOTTED_LINE,0,1);
        else
            if(globalTheme == PINKY)
                setlinestyle(DASHED_LINE,0,1);
    settextstyle(textInfo.font,textInfo.direction,2);

    Beep(3000,100);
    offsetX = 0;
    offsetY = 0;

    drawTree();

    evalExpressionTreeAnimated(expressionTree);
}

double evalExpressionTreeAnimated(BinaryTree* &tree) {
    if(tree == nullptr)
        return 0;

    if(tree->left == nullptr && tree->right == nullptr)
        return stod(tree->data);

    if(isBinaryOperator(tree->data)) {
        if(tree->right != nullptr) {
            std::string error;
            double left = evalExpressionTreeAnimated(tree->left);
            double right = evalExpressionTreeAnimated(tree->right);

            delay(ANIMATION_DELAY);
            tree->data = toString(evalBinaryOperator(tree->data, left, right, error));

            delete tree->left;
            delete tree->right;

            tree->left = nullptr;
            tree->right = nullptr;

            drawAll();
            Beep(2000, 100);

            return stod(tree->data);
        }
    }
    if(isUnaryOperator(tree->data)) {
        std::string error;
        double left = evalExpressionTreeAnimated(tree->left);

        delay(ANIMATION_DELAY);
        tree->data = toString(evalUnaryOperator(tree->data, left, error));

        delete tree->left;

        tree->left = nullptr;

        drawAll();
        Beep(2000, 100);

        return stod(tree->data);
    }
    if(isBinaryFunction(tree->data)) {
        if(tree->right != nullptr) {
            std::string error;
            double left = evalExpressionTreeAnimated(tree->left);
            double right = evalExpressionTreeAnimated(tree->right);

            delay(ANIMATION_DELAY);
            tree->data = toString(evalBinaryFunction(tree->data, left, right, error));

            delete tree->left;
            delete tree->right;

            tree->left = nullptr;
            tree->right = nullptr;

            drawAll();
            Beep(2000, 100);

            return stod(tree->data);
        }
    }
    if(isUnaryFunction(tree->data)) {
        std::string error;
        double left = evalExpressionTreeAnimated(tree->left);

        delay(ANIMATION_DELAY);
        tree->data = toString(evalUnaryFunction(tree->data, left, error));

        delete tree->left;

        tree->left = nullptr;

        drawAll();
        Beep(2000, 100);

        return stod(tree->data);
    }

    return 0;
}

void instantEval() {
    setfillstyle(SOLID_FILL,getbkcolor());
    bar(0,0,1260,HEIGHT);
    drawNewExp();
    drawArrow();
    if(globalTheme == DEFAULT)
        setlinestyle(SOLID_LINE,0,1);
    else
        if(globalTheme == GREEN_BLUE)
            setlinestyle(DOTTED_LINE,0,1);
        else
            if(globalTheme == PINKY)
                setlinestyle(DASHED_LINE,0,1);
    settextstyle(textInfo.font,textInfo.direction,2);

    Beep(3000,100);

    std::string error;
    std::string result = toString(evalExpressionTree(expressionTree,error));
    int textW;

    char* temp = (char*) malloc(256 * sizeof(char));
    strcpy(temp, result.c_str());
    textW = textwidth(temp);

    rectangle(600 - textW/2, 100, 610 + textW/2,130);
    outtextxy(605 - textW/2, 105, temp);
    free(temp);
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

bool isArrowPressed(int X, int Y){
    return X>1200 && X<1265 && Y>=0 && Y<65;
}

void drawAll(LANGUAGE lng) {
    gettextsettings(&textInfo);
    getlinesettings(&lineInfo);

    drawTree();
    drawSquares();
    drawArrow();
    drawNewExp();
    drawTitle();
    drawAnimEval();
    drawInstantEval();
    drawOptions();
    drawAbout();
    drawQuit();
}

void drawTree() {
    setfillstyle(SOLID_FILL,getbkcolor());
    bar(0,65,1270,HEIGHT);
    settextstyle(textInfo.font,textInfo.direction,2);

    if(globalTheme == DEFAULT)
        setlinestyle(SOLID_LINE,0,1);
    else
        if(globalTheme == GREEN_BLUE)
            setlinestyle(DOTTED_LINE,0,1);
        else
            if(globalTheme == PINKY)
                setlinestyle(DASHED_LINE,0,1);

    drawNode(expressionTree, 600 + offsetX,100 + offsetY, LINE_LENGTH, angleStartLeft, angleStartRight);
}

void drawNode(BinaryTree* tree, int x, int y, int lineSize, double angleLeft, double angleRight) {
    if(tree == nullptr || tree == NULL) return;

    int textW;
    char * temp = (char*) malloc(256 * sizeof(char));

    if(tree->data != "neg"){
        strcpy(temp, tree->data.c_str());
        textW = textwidth(temp);
    }
    else {
        strcpy(temp,"-");
        textW = textwidth("-");
    }

    int V,W;
    if(tree->right == nullptr) {
        rectangle(x - textW/2 + offsetX, y + offsetY, x + textW/2 + 10 + offsetX, y + 30 + offsetY);
        outtextxy(x - textW/2 + 5  + offsetX, y + 5 + offsetY, temp);
        if(tree->left != nullptr) {
            angle(x + offsetX,y+30 + offsetY,PI,V,W, 30);
            drawNode(tree->left,V,W,lineSize, angleLeft, angleRight);
        }
    }
    else {
        rectangle(x - textW/2 + offsetX, y + offsetY, x + textW/2 + 10 + offsetX, y + 30 + offsetY);
        outtextxy(x - textW/2 + 5 + offsetX, y + 5 + offsetY, temp);
        if(tree->left != nullptr) {
            angle(x + offsetX,y+30 + offsetY,angleLeft,V,W, lineSize);

            drawNode(tree->left,V,W,
                     lineSize > minLineSize ? lineSize * 7/10 : minLineSize,
                     angleLeft - angleDifference > angleMinLeft ? angleLeft - angleDifference : angleMinLeft,
                     angleRight + angleDifference < angleMaxRight ? angleRight + angleDifference : angleMaxRight);
        }
        if(tree->right != nullptr) {
            angle(x + offsetX,y+30 + offsetY,angleRight,V,W, lineSize);

            drawNode(tree->right,V,W,
                     lineSize > minLineSize ? lineSize * 7/10 : minLineSize,
                     angleLeft - angleDifference > angleMinLeft ? angleLeft - angleDifference : angleMinLeft,
                     angleRight + angleDifference < angleMaxRight ? angleRight + angleDifference : angleMaxRight);
        }
    }
    free(temp);
}

void drawNewExp() {
    setfillstyle(SOLID_FILL,getbkcolor());
    bar(0,0,420,60);
    line(0,60,420,60);
    line(420,60,420,0);
    settextstyle(textInfo.font,textInfo.direction,5);
    outtextxy(newExp[lng].posX,newExp[lng].posY,newExp[lng].word);
}

void drawArrow() {
    readimagefile("assets\\images\\arrow.jpg",1200,0,1265,65);
}

void drawSquares() {
    if(globalTheme == DEFAULT) {
        bar(1270,0,WIDTH,HEIGHT);
        setfillstyle(SOLID_FILL,WHITE);
    }
    else if(globalTheme == GREEN_BLUE) {
            bar(1270,0,WIDTH,HEIGHT);
            setfillstyle(SOLID_FILL,COLOR(0,205,205));
        }
        else if(globalTheme == PINKY) {
                bar(1270,0,WIDTH,HEIGHT);
                setfillstyle(BKSLASH_FILL,COLOR(96, 15, 143));
            }
    bar(1270,0,1275,HEIGHT);
    bar(1270,150,WIDTH,155);
}

void drawTitle() {
    settextstyle(textInfo.font,textInfo.direction,8);
    outtextxy(1325,40,"ExTree");
}

void drawAnimEval() {
    setlinestyle(lineInfo.linestyle,lineInfo.upattern,2);
    rectangle(1310,190,1570,305);

    settextstyle(textInfo.font,textInfo.direction,5);
    outtextxy(animEvalTopText[lng].posX,animEvalTopText[lng].posY,animEvalTopText[lng].word);
    outtextxy(animEvalBottomText[lng].posX,animEvalBottomText[lng].posY,animEvalBottomText[lng].word);
}

void drawInstantEval() {
    setlinestyle(lineInfo.linestyle,lineInfo.upattern,2);
    rectangle(1310,320,1570,435);

    settextstyle(textInfo.font,textInfo.direction,5);
    outtextxy(instantEvalTopText[lng].posX,instantEvalTopText[lng].posY,instantEvalTopText[lng].word);
    outtextxy(instantEvalBottomText[lng].posX,instantEvalBottomText[lng].posY,instantEvalBottomText[lng].word);
}

void drawOptions() {
    setlinestyle(lineInfo.linestyle,lineInfo.upattern,2);
    rectangle(1310,450,1570,535);

    settextstyle(textInfo.font,textInfo.direction,5);
    outtextxy(optionsText[lng].posX,optionsText[lng].posY,optionsText[lng].word);
}

void drawAbout() {
    setlinestyle(lineInfo.linestyle,lineInfo.upattern,2);
    rectangle(1310,550,1570,630);

    settextstyle(textInfo.font,textInfo.direction,5);
    outtextxy(aboutText[lng].posX,aboutText[lng].posY,aboutText[lng].word);
}

void drawQuit() {
    setlinestyle(lineInfo.linestyle,lineInfo.upattern,2);
    rectangle(1310,645,1570,725);

    settextstyle(textInfo.font,textInfo.direction,5);
    outtextxy(quitText[lng].posX,quitText[lng].posY,quitText[lng].word);
}


void options() {
    setfillstyle(SOLID_FILL,getbkcolor());
    bar(1275,155,WIDTH,HEIGHT);

    Beep(3000,100);

    setlinestyle(lineInfo.linestyle,lineInfo.upattern,2);

    settextstyle(textInfo.font,textInfo.direction,5);
    outtextxy(optionsLanguageText[lng].posX,optionsLanguageText[lng].posY,optionsLanguageText[lng].word);

    readimagefile("assets\\images\\britan_flag.jpg",1345,280,1420,330);
    rectangle(1345,280,1420,330);
    readimagefile("assets\\images\\romanian_flag.jpg",1445,280,1520,330);
    rectangle(1445,280,1520,330);
    readimagefile("assets\\images\\german_flag.jpg",1345,350,1420,400);
    rectangle(1345,350,1420,400);
    readimagefile("assets\\images\\french_flag.jpg",1445,350,1520,400);
    rectangle(1445,350,1520,400);


    rectangle(1310,645,1570,725);
    outtextxy(optionsBackText[lng].posX,optionsBackText[lng].posY,optionsBackText[lng].word);

    outtextxy(optionsThemesText[lng].posX,optionsThemesText[lng].posY,optionsThemesText[lng].word);

    settextstyle(textInfo.font,textInfo.direction,3);
    rectangle(1355,485,1520,520);
    outtextxy(1390,490,"DEFAULT");
    rectangle(1355,530,1520,565);
    outtextxy(1370,535,"GREEN_BLUE");
    rectangle(1355,575,1520,610);
    outtextxy(1410,580,"PINKY");

    while(button != OPTIONS_Back) {
        getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
        if(mouseX >= 1355 && mouseX <= 1520 && mouseY >= 485 && mouseY <= 520 && globalTheme != DEFAULT) {
            button = OPTIONS_Default;

            isEvaluated = false;
            if(originalTree != nullptr) {
                expressionTree = originalTree->copy();
                originalTree = nullptr;
            }
            else
                if(unsubstitutedTree != nullptr)
                    expressionTree = unsubstitutedTree->copy();

            initializeWindow(DEFAULT);
            resetMouseClick();
            break;
        }
        if(mouseX >= 1355 && mouseX <= 1520 && mouseY >= 530 && mouseY <= 565 && globalTheme != GREEN_BLUE) {
            button = OPTIONS_Green_Blue;

            isEvaluated = false;
            if(originalTree != nullptr) {
                expressionTree = originalTree->copy();
                originalTree = nullptr;
            }
            else
                if(unsubstitutedTree != nullptr)
                    expressionTree = unsubstitutedTree->copy();

            initializeWindow(GREEN_BLUE);
            resetMouseClick();
            break;
        }
        if(mouseX >= 1355 && mouseX <= 1520 && mouseY >= 575 && mouseY <= 610 && globalTheme != PINKY) {
            button = OPTIONS_Pinky;

            isEvaluated = false;
            if(originalTree != nullptr) {
                expressionTree = originalTree->copy();
                originalTree = nullptr;
            }
            else
                if(unsubstitutedTree != nullptr)
                    expressionTree = unsubstitutedTree->copy();

            initializeWindow(PINKY);
            resetMouseClick();
            break;
        }
        if(mouseX >= 1345 && mouseX <= 1420 && mouseY >= 280 && mouseY <= 330 && lng != EN) {
            lng = EN;
            Beep(3000,100);
            Beep(3000,100);
        }
        if(mouseX >= 1445 && mouseX <=1520 && mouseY >= 280 && mouseY <= 330 && lng != RO) {
            lng = RO;
            Beep(3000,100);
            Beep(3000,100);
        }
        if(mouseX >= 1345 && mouseX <=1420 && mouseY >= 350 && mouseY <= 400 && lng != DE) {
            lng = DE;
            Beep(3000,100);
            Beep(3000,100);
        }
        if(mouseX >= 1445 && mouseX <=1520 && mouseY >= 350 && mouseY <= 400 && lng != FR) {
            lng = FR;
            Beep(3000,100);
            Beep(3000,100);
        }
        if(mouseX >= 1310 && mouseX <=1570 && mouseY >= 645 && mouseY <= 725 && button != OPTIONS_Back) {
            button = OPTIONS_Back;

            Beep(3000,100);

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

void about() {
    setfillstyle(SOLID_FILL,getbkcolor());
    bar(1275,155,WIDTH,HEIGHT);

    Beep(3000,100);

    rectangle(1310,645,1570,725);
    outtextxy(aboutBackText[lng].posX,aboutBackText[lng].posY,aboutBackText[lng].word);

    rectangle(1310,250,1570,320);
    outtextxy(1390,265,"GitHub");

    while(button != ABOUT_Back) {
        getmouseclick(WM_LBUTTONDOWN,mouseX, mouseY);
        if(mouseX >= 1310 && mouseX <=1570 && mouseY >= 250 && mouseY <= 320)
            ShellExecute(HWND_DESKTOP, "open", "https://github.com/UnexomWid/ExTree", NULL, NULL, SW_SHOWDEFAULT);
        if(mouseX >= 1310 && mouseX <=1570 && mouseY >= 645 && mouseY <= 725 && button != ABOUT_Back) {
            button = ABOUT_Back;

            Beep(3000,100);

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

void Log(const char* format, ...) {
    va_list va;
    va_start(va, format);

    vprintf(format, va);

    va_end(va);
}

void angle(int x, int y, double a, int &V, int &W, int lineSize) {
    int v;
    int w;
    v = sin(a) * lineSize;
    w = (-1) * cos(a) * lineSize;
    line(x, y, x+v, y+w);
    V = v + x - offsetX;
    W = w + y - offsetY;
}

void resetMouseClick() {
    mouseX = mouseY = -1;
}
