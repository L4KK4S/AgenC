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
    struct s_cell *next_h;                      // Pointer to the next cell horizontally
    struct s_cell *next_v;                      // Pointer to the next cell vertically
    struct s_cell *prev_v;                      // Pointer to the prev cell vertically

}t_cell, *p_cell;                               // Creation of an alias for the structure


// -------------------------- Prototypes --------------------------

p_cell createEmptyCell(int, int);               // Creates an empty cell with vertical tab
p_cell createEmptyLevelCell(p_cell, int);               // Creates an empty cell without vertical tab
p_cell addVtabCell(p_cell prev, int levels);                   // Adds a vertical tab to a cell
int cellLength(p_cell);                         // Returns the number of characters of a cell value
int NotInTheLevel(p_cell, int);                 // Checks if a value is in the level
void displayCell(p_cell);                       // Display a cell
void insertCell(p_cell cell, p_list list);      // Insert a cell while keeping the list in order

#endif //AGENC_FICHIER_H