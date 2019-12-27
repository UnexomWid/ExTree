#ifndef BUTTONS_H_INCLUDED
#define BUTTONS_H_INCLUDED

#include <graphics.h>
#include <iostream> // Necesar pentru Log() din sectiunea de functii ajutatoare.

/// ----------------------------------------------------------------
/// Declarations for all the variables.
/// ----------------------------------------------------------------

/// The maximum height possible.
const int HEIGHT = getmaxheight();
const int WIDTH = getmaxwidth();

/// Information about the text.
extern struct textsettingstype textInfo;
extern struct linesettingstype lineInfo;

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
    NONE,ANIM_EVAL,INSTANT_EVAL,OPTIONS,ABOUT,QUIT, OPTIONS_Back,
};

/// ----------------------------------------------------------------
/// Main functions used by the program.
/// ----------------------------------------------------------------

/// This function reads the input given in the console window.
void readInput();

/// This function initializes the window with the specified theme.
void initializeWindow(THEME theme = DEFAULT);

/// This function runs the program, processing any input given by mouse.
void runProgram();

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

/// ----------------------------------------------------------------
/// Functions that ONLY draw the GUI.
/// ----------------------------------------------------------------

/// Draws all the button in the specified theme and language.
void drawAll(LANGUAGE lng = EN);

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
void Options();

/// ----------------------------------------------------------------
/// Helper functions.
/// ----------------------------------------------------------------

void Log(char* message);

/// This reset the mouseX and mouseY to -1.
void resetMouseClick();
#endif // BUTTONS_H_INCLUDED
