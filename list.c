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
#include "timer.h"
#include "timer.c"


// -------------------------- Functions --------------------------

p_list createEmptylistCell(int x) {                                                         // This function creates an empty list

    p_list new_list = (p_list) malloc(sizeof(t_list));                                 // Allocation of memory for the new list
    new_list->max_levels = x;                                                               // Initialization of the level of the list (Warning we define the level as the id of the last level -> mean level 6 = 7 levels)
    new_list->levels = (p_cell*) malloc ((new_list->max_levels)*sizeof(p_cell));     // Initialization of the tab stocking all level of the list with (level + 1) value because of the level 0
    return new_list;                                                                        // Return the new list
}


void uniform_display_list (p_list list) {
    p_cell level0cur;                                                           // Create a cursor to compare to higher value (because the first level will be the most complete, we have to check if we have to fill higher level or not)
    p_cell tmp_h;                                                               // Create a cursor pointer to go through each level

    for (int i = 0 ; i<list->max_levels ; i++){                                // Loop which stop when all level including the last one are printed
        printf("[list head_%d @-]",i);                                          // Special printing for the head of the list
        tmp_h = list->levels[i];                                                // Set the pointer to the head of the current level
        level0cur = list->levels[0];                                            // Reset the level 0 cursor to the first cell of the level 0

        while (level0cur!=NULL) {                                               // Loop to go through all cell of the first level each level (and see if cell are there or not)
            if (tmp_h!=level0cur || tmp_h==NULL) {                              // If the level cursor is not equal to the level 0 cursor it mean the cell aren't on the same level / or if the level cursor is NULL but there are still cell on the first level
                for (int j = 0; j < cellLength(level0cur)+3; j++) {        // Case where cell is not on the level, then we print "-" for the length of the corresponding cell at level 0 to keep it align
                    printf("-");
                }
            } else {                                                            // Case where we have to print the cell
                printf("-->[ %d|@-]", tmp_h->value);                            // Special print for the cell
                tmp_h = tmp_h->levels[i];                                       // If we have printed the cell on the level we can move to the next one to continue the checking for missing cell in between
            }
            level0cur = level0cur->levels[0];                                   // Move the checking cursor on the level 0 to the next value

        }
        printf("-->NULL\n");                                                    // Special print to indicate the end of the level list
    }
}

void display_list (p_list list) {
    for (int i = 0 ; i<list->max_levels ; i++) {                               // Loop which stop when all level are printed (<=)
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
    p_cell tmp_h;                                                                   // Set a moving pointer which will go through the levels

    tmp_h = list->levels[level];                                                    // Set the moving pointer to the head of the current level
    printf("[list head_%d @-]",level);                                              // Special printing for the head of the list
    while (tmp_h!=NULL) {                                                           // Loop to print all elements from a level
        printf("-->[ %d|@-]", tmp_h->value);                                        // Special print for the cell
        tmp_h=tmp_h->levels[level];                                                 // Incrementing the level cursor
    }
    printf("-->NULL\n");                                                            // Special print to indicate the end of the level list
}
int checkListCompatibility(p_list list, int level) {
    if (level>list->max_levels || level<=0) {                                                   // Check if the level is superior than the max level of the list
        return 0;
    } else {
        return 1;
    }
}

int std_search(p_list list, int value) {
    startTimer();
    int operation = 0;                                                              // Set a variable to count the number of operation
    p_cell tmp = list->levels[0];                                                   // Set the level cursor to the first cell of the level 0
    while (tmp!=NULL) {                                                             // Loop to go through every element
        operation++;                                                                // Increment the number of operations
        if (tmp->value==value) {                                                    // If we find the value we return 1
            printf("%d operations effectued\n", operation);
            stopTimer();
            displayTime();
            return 1;
        }
        tmp=tmp->levels[0];                                                         // Incrementing the level cursor
    }
    printf("%d operations effectued\n", operation);
    stopTimer();
    displayTime();
    return 0;                                                                       // If we haven't found anything at the end of the loop we return 0
}

int counter_std_search(p_list list, int value) {
    int operation = 0;                                                              // Set a variable to count the number of operation
    p_cell tmp = list->levels[0];                                                   // Set the level cursor to the first cell of the level 0
    while (tmp!=NULL) {                                                             // Loop to go through every element
        operation++;                                                                // Increment the number of operations
        if (tmp->value==value) {                                                    // If we find the value we return 1
            return operation;
        }
        tmp=tmp->levels[0];                                                         // Incrementing the level cursor
    }
    return operation;                                                                       // If we haven't found anything at the end of the loop we return 0
}

int dtc_search(p_list list, int value) {
    startTimer();

    int operation = 0;                                                              // Initialize a counter for the differents operations
    int current_level = list->max_levels;                                           // Set a variable to decrement the current level
    p_cell tmp = list->levels[current_level];                                       // Set the cursor to the head of the last level

    while (tmp==NULL) {                                                             // Loop to downgrade every empty level
        current_level--;                                                            // Decrement the current level variable
        operation++;                                                                // Count an operation
        tmp = list->levels[current_level];                                          // Move the cursor to the inferior level
    }

    while (tmp->value > value && current_level>0) {                                 // Loop to downgrade the level why the first value is superior than what we're searching
        current_level--;                                                            // Decrement the current level variable
        operation++;                                                                // Increment the operation counter
        tmp = list->levels[current_level];                                          // Move the cursor to the inferior level
    }
    if (current_level==0) {                                                         // If every value at every level were superior, it means the searched value is not in the tab
        printf("%d operations effectued\n", operation);
        stopTimer();
        displayTime();
        return 0;

    }

    if (tmp->value == value) {                                                      // As we won't check the current value everytime, then we check is the first value is the one searched for
        printf("%d operations effectued\n", operation);
        stopTimer();
        displayTime();
        return 1;
    }
    while (current_level!=0 || tmp!=NULL) {                                         // Loop to go through in the worst case to the level 0 and last value
        if (tmp->levels[current_level] != NULL) {                                   // We check if the next level is not NULL to avoid crash because we've tried to compare it
            if (tmp->levels[current_level]->value == value) {                       // If the next value is the searched value we return 1
                printf("%d operations effectued\n", operation);
                stopTimer();
                displayTime();
                return 1;
            } else if (tmp->levels[current_level]->value > value){                  // If the next value is not the one searched for
                if (current_level==0) {                                             // Case where the next value is superior but the level is 0, we can't go lower so the value is not in the tab
                    printf("%d operations effectued\n", operation);
                    stopTimer();
                    displayTime();
                    return 0;
                } else {                                                            // Case where we can go lower, so we try to see if the value in on lower level
                    current_level--;                                                // So we decrement the current level
                    operation++;                                                    // And we increment the number of operation
                }
            } else {                                                                // Case where the next value is not NULL and inferior to what we're searching
                tmp = tmp->levels[current_level];                                   // Move of the cursor to the next value on the level
                operation++;                                                        // We increment the operation
            }
        } else if (value > tmp->value && current_level==0) {                        // Value is superior than the last value at last level of the list
            printf("%d operations effectued\n", operation);
            stopTimer();
            displayTime();
            return 0;
        } else {                                                                    // Case where there is no next value on higher level and we need to drop down till level 0 or level with next value
            current_level--;                                                        // We decrement the current level variable
            operation++;                                                            // We increment the operation counter
        }
    }                                                                               // Case already treated in the previous if to optimize condition, should never be used
    stopTimer();
    displayTime();
    return 0;
}

int counter_dtc_search(p_list list, int value) {
    int operation = 0;                                                              // Initialize a counter for the differents operations
    int current_level = list->max_levels;                                           // Set a variable to decrement the current level
    p_cell tmp = list->levels[current_level];                                       // Set the cursor to the head of the last level

    while (tmp==NULL) {                                                             // Loop to downgrade every empty level
        current_level--;                                                            // Decrement the current level variable
        operation++;                                                                // Count an operation
        tmp = list->levels[current_level];                                          // Move the cursor to the inferior level
    }

    while (tmp->value > value && current_level>0) {                                 // Loop to downgrade the level why the first value is superior than what we're searching
        current_level--;                                                            // Decrement the current level variable
        operation++;                                                                // Increment the operation counter
        tmp = list->levels[current_level];                                          // Move the cursor to the inferior level
    }
    if (current_level==0) {                                                         // If every value at every level were superior, it means the searched value is not in the tab
        return operation;
    }

    if (tmp->value == value) {                                                      // As we won't check the current value everytime, then we check is the first value is the one searched for
        return operation;
    }
    while (current_level!=0 || tmp!=NULL) {                                         // Loop to go through in the worst case to the level 0 and last value
        if (tmp->levels[current_level] != NULL) {                                   // We check if the next level is not NULL to avoid crash because we've tried to compare it
            if (tmp->levels[current_level]->value == value) {                       // If the next value is the searched value we return 1
                return operation;
            } else if (tmp->levels[current_level]->value > value){                  // If the next value is not the one searched for
                if (current_level==0) {                                             // Case where the next value is superior but the level is 0, we can't go lower so the value is not in the tab
                    return operation;
                } else {                                                            // Case where we can go lower, so we try to see if the value in on lower level
                    current_level--;                                                // So we decrement the current level
                    operation++;                                                    // And we increment the number of operation
                }
            } else {                                                                // Case where the next value is not NULL and inferior to what we're searching
                tmp = tmp->levels[current_level];                                   // Move of the cursor to the next value on the level
                operation++;                                                        // We increment the operation
            }
        } else if (value > tmp->value && current_level==0) {                        // Value is superior than the last value at last level of the list
            return operation;
        } else {                                                                    // Case where there is no next value on higher level and we need to drop down till level 0 or level with next value
            current_level--;                                                        // We decrement the current level variable
            operation++;                                                            // We increment the operation counter
        }
    }                                                                               // Case already treated in the previous if to optimize condition, should never be used
    return operation;
}

int print_space(int a, int b) {
    int countA = 0;
    int countB = 0;
    while (a>10) {
        countA++;
        a/=10;
    }
    while (b>10) {
        countB++;
        b/=10;
    }
    return countA-countB-1;

}

void compareSearchMethod(int seed) {
    srand(seed);
    p_list testlist = createListPart2(15);
    int** results = (int**) malloc (100*sizeof(int*));
    results[0] = (int*) malloc (3*sizeof(int));
    results[0][0]=rand()%250;
    for (int i = 1 ; i<100 ; i++) {
        results[i] = (int*) malloc (3*sizeof(int));
        results[i][0] = results[i-1][0] + (rand()%3500);
    }
    for (int i = 0 ; i<100 ; i++) {
        results[i][1] = counter_std_search(testlist, results[i][0]);
        results[i][2] = counter_dtc_search(testlist, results[i][0]);
    }
    printf("tirage      : ");
    for (int i = 0 ; i<100 ; i++) {
        printf ("%d\t", results[i][0]);
    }
    printf("\nstandard    : ");
    for (int i = 0 ; i<100 ; i++) {
        printf ("%d\t", results[i][1]);
    }
    printf("\ndichotomous : ");
    for (int i = 0 ; i<100 ; i++) {
        for (int space = 0 ; space< print_space(results[i][1], results[i][3]) ; space++) {
            printf(" ");
        }
        printf ("%d\t", results[i][2]);
    }
    printf("\n\n");
}



int compareStrings( char *a, char *b) {
    while (*a != '\0' && *b != '\0') {
        if (*a < *b) {
            return -1; //string1 is shorter than string2
        } else if (*a > *b) {
            return 1; //  string1 is greater than string2
        }
        a++;
        b++;
    }
    if (*a == '\0' && *b == '\0'){
        return 0; // Both strings are identical
    }
    if (*a == '\0') {
        return -1; //string1 is shorter than string2
    }
    else {
        return 1; // string1 is greater than string2
        }
}




// -------------------------- Tests Lists Functions --------------------------

p_list createTestList() {
    p_list liste = createEmptylistCell(5);
    p_cell cell1 = createEmptyCell(4, 4);
    p_cell cell2 = createEmptyCell(3, 2);
    p_cell cell3 = createEmptyCell(2, 3);
    p_cell cell4 = createEmptyCell(1, 3);
    p_cell cell5 = createEmptyCell(11, 1);
    insertCell(cell1, liste, 4);
    insertCell(cell2, liste, 2);
    insertCell(cell3, liste, 3);
    insertCell(cell4,liste,  3);
    insertCell(cell5, liste, 1);
    return liste;
}

p_list createOrderedList() {
    p_list liste = createEmptylistCell(5);
    p_cell cell1 = createEmptyCell(0, 1);
    p_cell cell2 = createEmptyCell(10, 2);
    p_cell cell3 = createEmptyCell(9, 3);
    p_cell cell4 = createEmptyCell(8, 5);
    p_cell cell5 = createEmptyCell(5, 4);
    p_cell cell6 = createEmptyCell(2, 2);
    p_cell cell7 = createEmptyCell(4, 2);
    p_cell cell8 = createEmptyCell(3, 1);
    p_cell cell9 = createEmptyCell(6, 1);
    p_cell cell10 = createEmptyCell(1, 3);
    insertCell(cell1, liste, 1);
    insertCell(cell2, liste, 2);
    insertCell(cell3, liste, 3);
    insertCell(cell4, liste, 5);
    insertCell(cell5, liste, 4);
    insertCell(cell6, liste, 2);
    insertCell(cell7, liste, 2);
    insertCell(cell8, liste, 1);
    insertCell(cell9, liste, 1);
    insertCell(cell10, liste, 3);
    return liste;
}

p_list createChaoticValueList() {
    p_list liste = createEmptylistCell(5);
    p_cell cell1 = createEmptyCell(-2, 1);
    p_cell cell2 = createEmptyCell(-9, 2);
    p_cell cell3 = createEmptyCell(100, 1);
    p_cell cell4 = createEmptyCell(3004, 5);
    p_cell cell5 = createEmptyCell(9, 4);
    p_cell cell6 = createEmptyCell(10, 2);
    p_cell cell7 = createEmptyCell(-23, 2);
    p_cell cell8 = createEmptyCell(7, 1);
    p_cell cell9 = createEmptyCell(5, 1);
    p_cell cell10 = createEmptyCell(102, 3);
    insertCell(cell1, liste, 1);
    insertCell(cell2, liste, 2);
    insertCell(cell3, liste, 1);
    insertCell(cell4, liste, 5);
    insertCell(cell5, liste, 4);
    insertCell(cell6, liste, 2);
    insertCell(cell7, liste, 2);
    insertCell(cell8, liste, 1);
    insertCell(cell9, liste, 1);
    insertCell(cell10, liste, 3);
    return liste;
}

p_list createWaveFormList() {
    p_list liste = createEmptylistCell(5);
    p_cell cell1 = createEmptyCell(2, 1);
    p_cell cell2 = createEmptyCell(4, 1);
    p_cell cell3 = createEmptyCell(6, 2);
    p_cell cell4 = createEmptyCell(8, 3);
    p_cell cell5 = createEmptyCell(10, 4);
    p_cell cell6 = createEmptyCell(12, 5);
    p_cell cell7 = createEmptyCell(14, 4);
    p_cell cell8 = createEmptyCell(16, 3);
    p_cell cell9 = createEmptyCell(18, 2);
    p_cell cell10 = createEmptyCell(20, 1);
    insertCell(cell1, liste, 1);
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