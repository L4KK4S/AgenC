/*
    |----------------------------------------------------------|
    |     This file contains the structures and prototype      |
    |                needed for the menu                       |
    |----------------------------------------------------------|
*/

// -------------------------- Includes --------------------------

#ifndef AGENC_MENU_H
#define AGENC_MENU_H
#include "list.h"
#include "contact.h"
// -------------------------- Prototypes --------------------------

int get_inputs_part12  (char* input);                           // Match an input to a known function
int arguments_part12 (char *input, int index, int* args);       // Check if there is the good number of argument and return them in an int tab
int get_option_part12 (char* input);                            // Match an input to a known option
int matchingString(char* ref, char* new);               // Check to see if the new string is contain in the ref string
char** getCompletion(char* input, p_contact_list list); // Get the matching result to use for autocompletion
char* autoCompletion(p_contact_list);                   // Function to autocomplete the string input
void mainloop1();                                       // Part 1 and 2 menu

int get_inputs_part3 (char* input);
char *get_argument_part3(int function, char *input);
#endif //AGENC_MENU_H
