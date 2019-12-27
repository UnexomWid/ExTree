#include <iostream> // Inclus deja in "button.h"
#include "libs/buttons.h"
#include "libs/stack.h"
#include "libs/queue.h"
#include "libs/tree.h"

using namespace std;

int main()
{
    /* First read from the console then open the window*/

    readInput(); // De implementat.

    initializeWindow(PINKY);

    runProgram();
    return 0;
}


