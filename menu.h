/*
    |----------------------------------------------------------|
    |     This file contains the structures and prototype      |
    |                needed for the menu                       |
    |----------------------------------------------------------|
*/

// -------------------------- Includes --------------------------

#ifndef AGENC_MENU_H
#define AGENC_MENU_H


// -------------------------- Prototypes --------------------------

int get_inputs (char* input);                           // Match an input to a known function
int arguments(char *input, int index, int* args);       // Check if there is the good number of argument and return them in an int tab
int get_option(char* input);                            // Match an input to a known option

#endif //AGENC_MENU_H
