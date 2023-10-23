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
p_cell createEmptyCell(int x);                  // This function creates an empty cell
void addVtab(p_cell cell, int x);

#endif //AGENC_FICHIER_H