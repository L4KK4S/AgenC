/*
    |----------------------------------------------------------|
    |     This file contains the structures and prototype      |
    |                needed for the lists                      |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#ifndef AGENC_LIST_H
#define AGENC_LIST_H
#include "cell.h"


// -------------------------- Structures --------------------------

typedef struct s_list {                          // Structure of a list
    int level;                                   // Level of the list
    struct s_list *next_v;                       // Pointer to the head of the vertical list
    struct s_list *prev_v;
    struct s_cell *head_h;                       // Pointer to the head of the horizontal list
}t_list, *p_list;                                // Creation of an alias for the structure


// -------------------------- Prototypes --------------------------

p_list createEmptylistCell(int x);                   // This function creates an empty list
p_list createEmptyLevelListCell(p_list, int x);              // Passage function to avoid creating vertical chained list at when actually creating that list
p_list addVtabList(p_list, int );                      // Function to chained a vertical list used for the different level chaines
void uniform_display_list (p_list);             // This function displays the list while keeping align
void display_list(p_list list);                      // This function displays the list by levels
void show_level(p_list list, int level);             // This function displays a specific level
int checkListCompatibility(p_list list, int level);  // Test to check if the level asked is superior to the max level list
int checkIfAlreadyInList(p_list list, int value);    // Test to check if the value is already in the list


// -------------------------- Tests lists --------------------------

p_list createOrderedList();
p_list createChaoticValueList();
p_list createWaveFormList();
p_list createWaveFormList2();


#endif //AGENC_LIST_H