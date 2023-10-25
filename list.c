/*
    |----------------------------------------------------------|
    |              This file contains the functions            |
    |                   used on the lists                      |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


// -------------------------- Functions --------------------------

p_list createEmptylistCell(int x) {                            // This function creates an empty list

    p_list new_list = (p_list) malloc(sizeof(t_list));     // Allocation of memory for the new list
    new_list->level = x;                                       // Initialization of the level of the list
    new_list->head_h = NULL;                                   // Initialization of the pointer to the head of the horizontal list
    new_list->next_v = addVtabList(new_list, x);                    // Initialization of the pointer to the head of the vertical list
    new_list->prev_v=NULL;

    return new_list;                                           // Return the new list
}

p_list createEmptyLevelListCell(p_list prev, int x) {                           // This function creates an empty list

    p_list new_list = (p_list) malloc(sizeof(t_list));         // Allocation of memory for the new list
    new_list->level = x;                                           // Initialization of the level of the list
    new_list->head_h = NULL;                                       // Initialization of the pointer to the head of the horizontal list
    new_list->next_v = NULL;                                       // Initialization of the pointer to the head of the vertical list
    new_list->prev_v = prev;

    return new_list;                                               // Return the new list
}

p_list addVtabList(p_list root, int levels) {                                            // This function adds a vertical tab to a cell

    if (levels>=1) {
        p_list newhead = createEmptyLevelListCell(root, levels);               // Creation of a new cell with the level x
        p_list tmp = newhead;                                               // Creation of a temporary cell to browse the list
        if (levels >= 2) {
            for (int i = 0; i < levels - 1; i++) {                          // Loop with n(=number of levels) iterations
                tmp->next_v = createEmptyLevelListCell(tmp, levels);          // Creation of a new cell with the value of the cell
                tmp = tmp->next_v;                                          // Creation of a new cell with the value of the cell
            }
        }
        return newhead;
    }
    return NULL;                                                            // Return the new head of the vertical list

}

void uniform_display_list (p_list list) {

    p_list tmp_v = list;                                                            // Set a moving variable at the level 0 list
    int level = 0;                                                                  // Create anb int variable to indicate the level
    while (tmp_v!=NULL) {                                                           // Loop which stop when all level are printed
        printf("[list head_%d @-]",level);                                          // Special printing for the head of the list
        p_cell level0cur = list->head_h;                                            // Create a cursor to compare to higher value (because the first level will be the most complete, we have to check if we have to fill higher level or not)
        p_cell tmp_h = tmp_v->head_h;                                               // Set a moving variable to go through every level

        while (level0cur!=NULL) {                                                   // Loop to go through all cell of the first level each level (and see if cell are there or not)
            if (NotInTheLevel(tmp_v->head_h, level0cur->value)) {          // Check if it has to print the cell
                for (int i = 0; i < cellLength(level0cur)+3; i++) {             // Case where cell is not on the level, then we print "-" for the length of the correspondant cell at level 0 to keep it align
                    printf("-");
                }
            } else {                                                                // Case where we have to print the cell
                printf("-->[ %d|@-]", level0cur->value);                            // Special print for the cell
                tmp_h = tmp_h->next_h;                                              // If we have printed the cell on the level we can move to the next one to continue the checking for missing cell in between
            }
            level0cur = level0cur->next_h;                                          // Move the checking cursor on the level 0

        }
        printf("-->NULL\n");                                                        // Special print to indicate the end of the level list
        tmp_v = tmp_v->next_v;                                                      // Update the level cursor
        level++;                                                                    // Update the level variable
    }
}

void display_list (p_list list) {

    p_list tmp_v = list;                                                            // Set a moving variable at the level 0 list
    int level = 0;                                                                  // Create anb int variable to indicate the level
    while (tmp_v!=NULL) {                                                           // Loop which stop when all level are printed
        printf("[list head_%d @-]",level);                                          // Special printing for the head of the list
        p_cell tmp_h = tmp_v->head_h;                                               // Set the moving pointer to the head of the level
        while (tmp_h!=NULL){
            printf("-->[ %d|@-]", tmp_h->value);                                    // Special print for the cell
            tmp_h = tmp_h->next_h;                                                  // Incrementing the moving pointer
        }
        printf("-->NULL\n");                                                        // Special print to indicate the end of the level list
        tmp_v = tmp_v->next_v;                                                      // Update the level cursor
        level++;                                                                    // Update the level variable
    }
}

void show_level(p_list list, int level) {
    p_list tmp_v = list;                                                            // Set a moving pointer which will go to the different level
    p_cell tmp_h;                                                                   // Set a moving pointer which will go through the levels

    for (int i = 0 ; i<level ; i++) {                                               // Set the moving pointer to the right level
        tmp_v=tmp_v->next_v;
    }
    tmp_h = tmp_v->head_h;                                                          // Set the moving pointer to the head of the right level
    printf("[list head_%d @-]",level);                                              // Special printing for the head of the list
    while (tmp_h!=NULL) {                                                           // Loop to print all elements from a level
        printf("-->[ %d|@-]", tmp_h->value);                                        // Special print for the cell
        tmp_h=tmp_h->next_h;
    }
    printf("-->NULL\n");                                                            // Special print to indicate the end of the level list
}
int checkListCompatibility(p_list list, int level) {
    if (level>list->level) {                                                        // Check if the level is superior than the max level of the list
        return 0;
    } else {
        return 1;
    }
}

int checkIfAlreadyInList(p_list list, int value) {
    p_cell tmp = list->head_h;                                                      // Set a moving pointer at the head of the level 0
    while (tmp!=NULL) {                                                             // Loop to check all value
        if (tmp->value==value) {                                                    // If the value is already in the list we return 1
            return 1;
        }
        tmp=tmp->next_h;
    }
    return 0;                                                                       // If not we return 0
}


// -------------------------- Tests Lists Functions --------------------------

p_list createOrderedList() {
    p_list liste = createEmptylistCell(6);
    p_cell cell1 = createEmptyCell(0, 1);
    p_cell cell2 = createEmptyCell(10, 2);
    p_cell cell3 = createEmptyCell(9, 3);
    p_cell cell4 = createEmptyCell(8, 5);
    p_cell cell5 = createEmptyCell(5, 4);
    p_cell cell6 = createEmptyCell(2, 2);
    p_cell cell7 = createEmptyCell(4, 2);
    p_cell cell8 = createEmptyCell(3, 0);
    p_cell cell9 = createEmptyCell(6, 0);
    p_cell cell10 = createEmptyCell(1, 3);
    insertCell(cell1, liste);
    insertCell(cell2, liste);
    insertCell(cell3, liste);
    insertCell(cell4, liste);
    insertCell(cell5, liste);
    insertCell(cell6, liste);
    insertCell(cell7, liste);
    insertCell(cell8, liste);
    insertCell(cell9, liste);
    insertCell(cell10, liste);
    return liste;
}

p_list createChaoticValueList() {
    p_list liste = createEmptylistCell(6);
    p_cell cell1 = createEmptyCell(-2, 1);
    p_cell cell2 = createEmptyCell(-9, 2);
    p_cell cell3 = createEmptyCell(100, 0);
    p_cell cell4 = createEmptyCell(3004, 5);
    p_cell cell5 = createEmptyCell(9, 4);
    p_cell cell6 = createEmptyCell(10, 2);
    p_cell cell7 = createEmptyCell(-23, 2);
    p_cell cell8 = createEmptyCell(7, 0);
    p_cell cell9 = createEmptyCell(5, 0);
    p_cell cell10 = createEmptyCell(102, 3);
    insertCell(cell1, liste);
    insertCell(cell2, liste);
    insertCell(cell3, liste);
    insertCell(cell4, liste);
    insertCell(cell5, liste);
    insertCell(cell6, liste);
    insertCell(cell7, liste);
    insertCell(cell8, liste);
    insertCell(cell9, liste);
    insertCell(cell10, liste);
    return liste;
}

p_list createWaveFormList() {
    p_list liste = createEmptylistCell(5);
    p_cell cell1 = createEmptyCell(2, 0);
    p_cell cell2 = createEmptyCell(4, 1);
    p_cell cell3 = createEmptyCell(6, 2);
    p_cell cell4 = createEmptyCell(8, 3);
    p_cell cell5 = createEmptyCell(10, 4);
    p_cell cell6 = createEmptyCell(12, 5);
    p_cell cell7 = createEmptyCell(14, 4);
    p_cell cell8 = createEmptyCell(16, 3);
    p_cell cell9 = createEmptyCell(18, 2);
    p_cell cell10 = createEmptyCell(20, 1);
    insertCell(cell1, liste);
    insertCell(cell2, liste);
    insertCell(cell3, liste);
    insertCell(cell4, liste);
    insertCell(cell5, liste);
    insertCell(cell6, liste);
    insertCell(cell7, liste);
    insertCell(cell8, liste);
    insertCell(cell9, liste);
    insertCell(cell10, liste);
    return liste;
}

p_list createWaveFormList2() {
    p_list liste = createEmptylistCell(5);
    p_cell cell1 = createEmptyCell(-2, 3);
    p_cell cell2 = createEmptyCell(4, 3);
    p_cell cell3 = createEmptyCell(-6, 2);
    p_cell cell4 = createEmptyCell(8, 4);
    p_cell cell5 = createEmptyCell(-10, 4);
    p_cell cell6 = createEmptyCell(12, 2);
    p_cell cell7 = createEmptyCell(-14, 1);
    p_cell cell8 = createEmptyCell(16, 5);
    p_cell cell9 = createEmptyCell(-18, 5);
    p_cell cell10 = createEmptyCell(20, 1);
    insertCell(cell1, liste);
    insertCell(cell2, liste);
    insertCell(cell3, liste);
    insertCell(cell4, liste);
    insertCell(cell5, liste);
    insertCell(cell6, liste);
    insertCell(cell7, liste);
    insertCell(cell8, liste);
    insertCell(cell9, liste);
    insertCell(cell10, liste);
    return liste;
}