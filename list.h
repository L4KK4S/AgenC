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
    struct s_list *head_h;                       // Pointer to the head of the horizontal list
}t_list, *p_list;                                // Creation of an alias for the structure


// -------------------------- Prototypes --------------------------
p_list createEmptylistCell(int x);                   // This function creates an empty list
p_list createEmptyLevelListCell(int x);
p_list addVtabList(int levels);
void uniform_display_list (p_list list);         // This function displays the list


#endif //AGENC_LIST_H