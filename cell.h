/*
    |----------------------------------------------------------|
    |     This file contains the structures and prototype      |
    |                needed for the cell                       |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#ifndef AGENC_FICHIER_H
#define AGENC_FICHIER_H


// -------------------------- Structures --------------------------

typedef struct s_cell{                          // Structure of a cell

    int value;                                  // Value of the cell
    struct s_cell **levels;                     // Tab stocking all of "next" values of the cell depending of the levels

}t_cell, *p_cell;                               // Creation of an alias for the structure





// -------------------------- Prototypes --------------------------

p_cell createEmptyCell(int, int);                           // Creates an empty cell with vertical tab
int cellLength(p_cell);                                     // Returns the number of characters of a cell value

#endif //AGENC_FICHIER_H