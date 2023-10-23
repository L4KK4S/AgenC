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
    struct s_cell *next_h;                      // Pointer to the next cell horizontally
    struct s_cell *next_v;                      // Pointer to the next cell vertically
}t_cell, *p_cell;                               // Creation of an alias for the structure


// -------------------------- Prototypes --------------------------
p_cell createEmptyLevelCell(int x);
p_cell addVtab(p_cell cell, int x);
int countCell(p_list list, p_cell first, p_cell last);
int cellLength (p_cell cell);
int isInTheLevel (p_cell head, int x);

#endif //AGENC_FICHIER_H