/*
    |----------------------------------------------------------|
    |     This file contains the structures and prototype      |
    |                needed for the cell                       |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#ifndef AGENC_FICHIER_H
#define AGENC_FICHIER_H
#include "list.h"


// -------------------------- Structures --------------------------

typedef struct s_cell{                          // Structure of a cell

    int value;                                  // Value of the cell
    struct s_cell **levels;                     // Tab stocking all of "next" values of the cell depending of the levels

}t_cell, *p_cell;                               // Creation of an alias for the structure


// -------------------------- Prototypes --------------------------

p_cell createEmptyCell(int, int);                           // Creates an empty cell with vertical tab
int cellLength(p_cell);                                     // Returns the number of characters of a cell value
void insertCell(p_cell cell, p_list list, int level);       // Insert a cell while keeping the list in order
void insertCellHead(p_cell cell, p_list list, int level);   // Insert a cell by at the head of the level
p_list createListPart2(int n);
int get_level(p_cell cell);

#endif //AGENC_FICHIER_H