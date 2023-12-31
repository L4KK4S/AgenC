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
#define LEVEL 4


// -------------------------- Structures --------------------------

typedef struct s_list {                          // Structure of a list
    int max_levels;                              // Level of the list
    struct s_cell **levels;                      // Tab stocking all "head" level of the list
}t_list, *p_list;                                // Creation of an alias for the structure




// -------------------------- Prototypes --------------------------

p_list createEmptylistCell(int x);                   // This function creates an empty list
void uniform_display_list (p_list);                  // This function displays the list while keeping align
void display_list(p_list list);                      // This function displays the list by levels
void show_level(p_list list, int level);             // This function displays a specific level
int checkListCompatibility(p_list list, int level);  // Check if the level of the cell is inferior to the level of the list
int std_search(p_list list, int value);              // Search a value in the level 0
int dtc_search(p_list list, int value);              // Search a value using the ordered level
void compareSearchMethod(int seed);
void compareSearchMethod2 (p_list testlist, int searchnumber);
int counter_dtc_search(p_list list, int value);
int counter_std_search(p_list list, int value);
int print_space(int a, int b);




// -------------------------- Tests lists --------------------------


p_list createTestList();
p_list createOrderedList();
p_list createChaoticValueList();
p_list createWaveFormList();
p_list createWaveFormList2();


void insertCell(p_cell cell, p_list list, int level);       // Insert a cell while keeping the list in order
void insertCellHead(p_cell cell, p_list list, int level);   // Insert a cell by at the head of the level
p_list createListPart2(int n);

#endif //AGENC_LIST_H