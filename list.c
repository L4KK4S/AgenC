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
    new_list->max_levels = x;                                       // Initialization of the level of the list
    new_list->levels = (p_cell*) malloc (x*sizeof(p_cell));
    return new_list;                                           // Return the new list
}


void uniform_display_list (p_list list) {
    p_cell level0cur;                                           // Create a cursor to compare to higher value (because the first level will be the most complete, we have to check if we have to fill higher level or not)
    p_cell tmp_h;     // Create anb int variable to indicate the level

    for (int i = 0 ; i<list->max_levels ; i++){                                                           // Loop which stop when all level are printed
        printf("[list head_%d @-]",i);                                          // Special printing for the head of the list
        tmp_h = list->levels[i];                                               // Set a moving variable to go through every level
        level0cur = list->levels[0];

        while (level0cur!=NULL) {                                                   // Loop to go through all cell of the first level each level (and see if cell are there or not)
            if (tmp_h!=level0cur || tmp_h==NULL) {                            // Check if it has to print the cell
                for (int j = 0; j < cellLength(level0cur)+3; j++) {            // Case where cell is not on the level, then we print "-" for the length of the correspondant cell at level 0 to keep it align
                    printf("-");
                }
            } else {                                                                // Case where we have to print the cell
                printf("-->[ %d|@-]", tmp_h->value);                            // Special print for the cell
                tmp_h = tmp_h->levels[i];                                              // If we have printed the cell on the level we can move to the next one to continue the checking for missing cell in between
            }
            level0cur = level0cur->levels[0];                                          // Move the checking cursor on the level 0

        }
        printf("-->NULL\n");                                                        // Special print to indicate the end of the level list
    }
}

void display_list (p_list list) {
    for (int i = 0 ; i<list->max_levels ; i++) {                                                           // Loop which stop when all level are printed
        printf("[list head_%d @-]",i);                                          // Special printing for the head of the list
        p_cell tmp_h = list->levels[i];                                               // Set the moving pointer to the head of the level
        while (tmp_h!=NULL){
            printf("-->[ %d|@-]", tmp_h->value);                                    // Special print for the cell
            tmp_h = tmp_h->levels[i];                                                  // Incrementing the moving pointer
        }
        printf("-->NULL\n");                                                        // Special print to indicate the end of the level list
    }
}

void show_level(p_list list, int level) {
    p_list tmp_v = list;                                                            // Set a moving pointer which will go to the different level
    p_cell tmp_h;                                                                   // Set a moving pointer which will go through the levels

    tmp_h = list->levels[level];                                                         // Set the moving pointer to the head of the right level
    printf("[list head_%d @-]",level);                                              // Special printing for the head of the list
    while (tmp_h!=NULL) {                                                           // Loop to print all elements from a level
        printf("-->[ %d|@-]", tmp_h->value);                                        // Special print for the cell
        tmp_h=tmp_h->levels[level];
    }
    printf("-->NULL\n");                                                            // Special print to indicate the end of the level list
}
int checkListCompatibility(p_list list, int level) {
    if (level>list->max_levels) {                                                        // Check if the level is superior than the max level of the list
        return 0;
    } else {
        return 1;
    }
}

int std_search(p_list list, int value) {
    p_cell tmp = list->levels[0];
    while (tmp!=NULL) {
        if (tmp->value==value) {
            return 1;
        }
        tmp=tmp->levels[0];
    }
    return 0;
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
    insertCell(cell1, liste, 1);
    insertCell(cell2, liste, 2);
    insertCell(cell3, liste, 3);
    insertCell(cell4, liste, 5);
    insertCell(cell5, liste, 4);
    insertCell(cell6, liste, 2);
    insertCell(cell7, liste, 2);
    insertCell(cell8, liste, 0);
    insertCell(cell9, liste, 0);
    insertCell(cell10, liste, 3);
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
    insertCell(cell1, liste, 1);
    insertCell(cell2, liste, 2);
    insertCell(cell3, liste, 0);
    insertCell(cell4, liste, 5);
    insertCell(cell5, liste, 4);
    insertCell(cell6, liste, 2);
    insertCell(cell7, liste, 2);
    insertCell(cell8, liste, 0);
    insertCell(cell9, liste, 0);
    insertCell(cell10, liste, 3);
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
    insertCell(cell1, liste, 0);
    insertCell(cell2, liste,1);
    insertCell(cell3, liste, 2);
    insertCell(cell4, liste, 3);
    insertCell(cell5, liste, 4);
    insertCell(cell6, liste, 5);
    insertCell(cell7, liste, 4);
    insertCell(cell8, liste, 3);
    insertCell(cell9, liste, 2);
    insertCell(cell10, liste, 1);
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
    insertCell(cell1, liste, 3);
    insertCell(cell2, liste,3);
    insertCell(cell3, liste, 2);
    insertCell(cell4, liste, 4);
    insertCell(cell5, liste, 4);
    insertCell(cell6, liste, 2);
    insertCell(cell7, liste, 1);
    insertCell(cell8, liste, 5);
    insertCell(cell9, liste, 5);
    insertCell(cell10, liste, 1);
    return liste;
}