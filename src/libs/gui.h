#ifndef BUTTONS_H_INCLUDED
#define BUTTONS_H_INCLUDED

#include <graphics.h>
#include <stdarg.h> // For the Log() function.
#include <string>   // For the stod() function.
#include <iostream> // Necesar pentru Log() din sectiunea de functii ajutatoare.
#include <windows.h>

#include "tree.h"
#include "queue.h"
#include "expression_parser.h"

/// ----------------------------------------------------------------
/// Declarations for all the variables.
/// ----------------------------------------------------------------

/// The maximum height and width possible.
const int HEIGHT = getmaxheight();
const int WIDTH = getmaxwidth();

/// Information about the text, line and fill settings.
extern struct textsettingstype textInfo;
extern struct linesettingstype lineInfo;
extern struct fillsettingstype fillInfo;

/// Extern binary tree.
extern BinaryTree* expressionTree;

/// A struct containing the information about each button, based on the selected language.
struct buttonSettings{
    /// The word translated.
    char* word;

    /// The x coordinate of the word.
    int posX;

    /// The y coordinate of the word.
    int posY;
};

/// ----------------------------------------------------------------
/// Declarations for all the enums.
/// ----------------------------------------------------------------

/// Different types of themes available.
enum THEME{
    DEFAULT,GREEN_BLUE,PINKY
};

/// All the languages available.
enum LANGUAGE{
    EN,RO,DE,FR
};

/// All buttons available.
enum BUTTONS{
    NONE,ANIM_EVAL,INSTANT_EVAL,OPTIONS,ABOUT,QUIT, OPTIONS_Back, OPTIONS_Default, OPTIONS_Green_Blue, OPTIONS_Pinky, ABOUT_Back, ARROW
};

/// ----------------------------------------------------------------
/// Main functions used by the program.
/// ----------------------------------------------------------------

/// This function reads the variables from the console windows.
void readVariables();

/// This function reads the input given in the console window.
void readInput();

/// This function initializes the window with the specified theme.
void initializeWindow(THEME theme = DEFAULT);

/// This function runs the program, processing any input given by mouse.
void runProgram();

/// Evaluates using animation.
void animEval();

/// Evaluates an expression tree using animation.
double evalExpressionTreeAnimated(BinaryTree* &tree);

/// Evaluates instantly.
void instantEval();

/// ----------------------------------------------------------------
/// Functions that verify whether something is true or not.
/// ----------------------------------------------------------------

/// Returns whether or not the "Animated evaluation" button was pressed.
bool isAnimEvalPressed(int X, int Y);

/// Returns whether or not the "Instant evaluation" button was pressed.
bool isInstantEvalPressed(int X, int Y);

/// Returns whether or not the "Options" button was pressed.
bool isOptionsPressed(int X, int Y);

/// Returns whether or not the "About" button was pressed.
bool isAboutPressed(int X, int Y);

/// Returns whether or not the "Quit" button was pressed.
bool isQuitPressed(int X, int Y);

/// Returns whether or not the "New expression" button was pressed.
bool isNewExpPressed(int X, int Y);

/// Returns whether or not the "Arrow" button was pressed.
bool isArrowPressed(int X,int Y);

/// ----------------------------------------------------------------
/// Functions that ONLY draw the GUI.
/// ----------------------------------------------------------------

/// Draws all the button in the specified theme and language.
void drawAll(LANGUAGE lng = EN);

/// Draws the new expression button.
void drawNewExp();

/// Draws the reverse arrow.
void drawArrow();

/// Draws the tree.
void drawTree();

/// Draws a particular node.
void drawNode(BinaryTree* tree, int x, int y, int lineSize, double angleLeft, double angleRight);

/// Draws the title.
void drawTitle();

/// Draws the squares.
void drawSquares();

/// Draws the animated evaluation button.
void drawAnimEval();

/// Draws the instant evaluation button.
void drawInstantEval();

/// Draws the options button.
void drawOptions();

/// Draws the about button.
void drawAbout();

/// Draws the quit button.
void drawQuit();

/// Draws the Options GUI when this button is pressed.
void options();

/// Draws the About GUI when this button is pressed.
void about();

/// ----------------------------------------------------------------
/// Helper functions.
/// ----------------------------------------------------------------

void Log(const char* format, ...);

/// Draws a line at a specific angle. The angle starts from 12 o'clock and goes clockwise.
void angle(int x, int y, double a, int &V, int &W, int lineSize);

/// This reset the mouseX and mouseY to -1.
void resetMouseClick();
#endif // BUTTONS_H_INCLUDED
