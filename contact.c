/*
    |----------------------------------------------------------|
    |              This file contains the functions            |
    |                   used on the contacts                   |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#include "contact.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// -------------------------- Functions --------------------------

// 1) Simple Action functions

int compareString( char *cursor, char *toplace) {


    int i = 0;                                                                               //  Create an index

    while (i < strlen(cursor) && i < strlen(toplace) && cursor[i] == toplace[i]) {     // Compare characters until a mismatch is found or the end of either string is reached
        i++;
    }
    if (i < strlen(cursor) && i < strlen(toplace)) {                                   // If i was stop before the last character
        if (cursor[i] < toplace[i]) {                                                        // check is the first string was before  the second one
            return 1;
        } else {                                                                             // If not, mean that the second string has to be placed after
            return - 1;
        }
    } else {                                                                                 // If the cursor is at the end
        if ( strlen(cursor) == strlen(toplace) && cursor[strlen(cursor)-1]== toplace[strlen(toplace)-1]) {                                      // We check if length are the same, meaning that str would be same
            return 0;
        } else if (i < strlen(cursor)) {                                                  // If i is inferior to the length of the first string, mean both string are almost same but s2 a1 as more characters
            return 1;                                                                        // In this case we want to place the string after the one with more elements
        } else {
            return -1;                                                                       // Else we place it before
        }
    }
}

char* change_maj_to_min( char *s) {
    for (int i = 0; s[i] != '\0'; i++) {                       // Loop to go through all characters
        if (s[i] >= 'A' && s[i] <= 'Z') {                      // if the character is a majuscule
            s[i] = s[i] + 32;                                  // Convert to min
        }

    }
    return s;
}

int getMatch(p_contact prev, p_contact new) {

    int match = 0;                                                                                                      // Setting a variable to count the match number
    while (prev->name[match]==new->name[match] && match<3 && prev->name[match]!='\0' && new->name[match]!='\0') {       // Loop to count while 1 str is finish, or match is at it maximum value and both str are the same
        match++;
    }

    return 4-match;                                                                                                     // We return the number of level we want to create, exemple : 2 common letter = 2 levels

}

char* formatString(char* input) {
    int i = 0, space_counter = 0;
    char* name = (char*) malloc(20*sizeof(char));                                                                            // Allocate memory for the name
    char* surname = (char*) malloc(20*sizeof(char));                                                                         // Allocate memory for the surname
    char* temp = (char*) malloc(15*sizeof(char));                                                                            // Allocate memory for the temp
    char* res = (char*) malloc(20*sizeof(char));                                                                             // Allocate memory for the answer


    while (input[i]!='\0') {                                                                                                       // Loop to go through all elements
        temp[0] = input[i];                                                                                                        // Add a character to the temp
        if (input[i] == ' ') {                                                                                                     // If the character is a space we only increment the counter
            space_counter++;
        } else if (space_counter == 0) {                                                                                           // Case where we didn't pass the space, mean current character is part of the surname
            strcat(surname, temp);
        } else {                                                                                                                   // Case where we didn't pass the space, mean current character is part of the surname
            strcat (name, temp);
        }
        i++;
    }
    strcat(res, name);                                                                                                              // We create the result by adding the name first
    strcat(res, "_");                                                                                                               // We create the result by adding the underscore
    strcat(res, surname);                                                                                                           // We create the result by adding the surname
    res = change_maj_to_min(res);                                                                                                // Converting the string to small characters
    free(name);
    free(surname);
    free(temp);
    return res;
}

char* unformatString(char* input) {
    int i = 0, underscore_counter = 0;
    char* name = (char*) malloc(20*sizeof(char));                                                                            // Allocate memory for the name
    char* surname = (char*) malloc(20*sizeof(char));                                                                         // Allocate memory for the surname
    char* temp = (char*) malloc(15*sizeof(char));                                                                            // Allocate memory for the temp
    char* res = (char*) malloc(20*sizeof(char));                                                                             // Allocate memory for the answer


    while (input[i]!='\0') {                                                                                                       // Loop to go through all elements
        temp[0] = input[i];                                                                                                        // Add a character to the temp
        if (input[i] == '_') {                                                                                                     // If the character is an underscore we only increment the counter
            underscore_counter++;
        } else if (underscore_counter == 0) {                                                                                      // Case where we didn't pass the space, mean current character is part of the surname
            if (i==0) {                                                                                                            // Check if it's the first letter to put a MAJ letter
                temp[0] = temp[0]-32;
            }
            strcat(name, temp);
        } else {                                                                                                                    // Case where we didn't pass the space, mean current character is part of the surname
            if (input[i-1]=='_') {                                                                                                  // Check if the previous character was the underscore to set a capital letter to the surname
                temp[0]= temp[0]-32;
            }
            strcat (surname, temp);
        }
        i++;
    }
    strcat(res, surname);                                                                                                            // We create the result by adding the name first
    strcat(res, " ");                                                                                                                // We create the result by adding the underscore
    strcat(res, name);                                                                                                               // We create the result by adding the surname
    free(name);
    free(surname);
    free(temp);
    return res;
}

char* checkNameEntry(char* input) {
    char* name = (char*) malloc(20*sizeof(char));                                                                                  // Allocate memory for the name
    char* surname = (char*) malloc(20*sizeof(char));                                                                               // Allocate memory for the surname
    char* temp = (char*) malloc(15*sizeof(char));                                                                                  // Allocate memory for the temp
    int i = 0, space_counter=0;                                                                                                          // Set counting variable to 0

    if (input[strlen(input)-2]!=' ' && strlen(input)>= 3) {                                                                        // Check if the input is not ending with a space and have the minimum require length
        while (input[i] != '\0') {                                                                                                       // Check all characters of the input
            if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z') || input[i] == ' ' || input[i]=='-') {      // Check if the character is allowed
                if (input[i] == ' ') {                                                                                                   // If the character is a space we increment the counter
                    space_counter++;
                }
                i++;                                                                                                                     // we increment the loop
            } else {                                                                                                                     // Case where the entry contain characters not allowed
                printf("Some of the characters aren't allowed\n");
                free(name);                                                                                                              // Memory Optimization by freeing allocated memory
                free(surname);                                                                                                           // Memory Optimization by freeing allocated memory
                free(temp);                                                                                                              // Memory Optimization by freeing allocated memory
                return NULL;
            }
        }
        if (space_counter != 1) {
            printf("space counter %d\n", space_counter);
            printf("The number of space is incorrect\n");
            free(name);                                                                                                                  // Memory Optimization by freeing allocated memory
            free(surname);                                                                                                               // Memory Optimization by freeing allocated memory
            free(temp);                                                                                                                  // Memory Optimization by freeing allocated memory
            return NULL;
        }
        free(name);                                                                                                                      // Memory Optimization by freeing allocated memory
        free(surname);                                                                                                                   // Memory Optimization by freeing allocated memory
        free(temp);                                                                                                                      // Memory Optimization by freeing allocated memory
        return formatString(input);

    } else {
        printf("Input is too short\n");
        free(name);                                                                                                                     // Memory Optimization by freeing allocated memory
        free(surname);                                                                                                                  // Memory Optimization by freeing allocated memory
        free(temp);                                                                                                                     // Memory Optimization by freeing allocated memory
        return NULL;
    }
}

int getLevel(p_contact_list list, p_contact search) {
    p_contact tmp;                                                  // Create a cursor
    for (int i = 3 ; i>0 ; i--) {                                   // Loop going from the higher levels to lower level to optimize the computing time
        tmp = list->levels[i];                                      // Setting the cursor to the head of the level
        while (tmp!=NULL) {                                         // Loop to go through all level
            if (tmp == search) {                                    // Check if we found the value
                tmp = NULL;
                free(tmp);
                return i+1;                                         // We return the level +1 so we can get the right number of levels (level 3 = 4 levels)
            }
            tmp = tmp->levels[i];
        }
    }
    free(tmp);
    return 0+1;                                                     // Else we return 0+1 (0 level, but still link to 1 cell)
}

void detectZero(int x) {
    if (x < 10) {                       // If x under 10 we have to print the silent 0
        printf("0%d", x);
        return;
    } else {
        printf("%d", x);               // We just print the number
        return;
    }
}


// 2) Manipulation of Contact Structure

p_contact_list createEmptyList() {
    p_contact_list new = (p_contact_list) malloc (sizeof (t_contact_list));         // Allocating memory
    p_contact* levels = (p_contact*) malloc (4*sizeof(p_contact));                  // Allocating memory for the tab of 4 levels
    for (int i  = 0 ; i<4 ; i++) {
        levels[i]=NULL;
    }
    new->levels = levels;                                                                // Attributing the memory tab
    new->max_levels= 4;                                                                  // Setting the max level to 4
    return new;
}

p_contact createContact(char* name) {
    p_contact new = (p_contact) malloc (sizeof(t_contact));                      // Allocate memory
    new->name = name;                                                                 // Attributing name
    new->levels = NULL;                                                               // Setting level to NULL as we don't know yet how many level we need
    new->head = NULL;                                                                 // Setting the appointment list to NULL
    return new;
}

p_contact searchContact(char* search, p_contact_list list) {
    p_contact tmp = list->levels[0];                                                    // Setting a cursor at level 0 (all cells)
    while (tmp!=NULL) {                                                                 // Loop to go through all cells
        if (compareString(tmp->name, search)==0) {                        // Check if cell is the same
            return tmp;                                                                 // If we have find the cell we return the adress
        }
        tmp = tmp->levels[0];
    }
    free(tmp);
    return NULL;                                                                        // If we haven't find the cell we return 0
}

void insertContact(p_contact_list list, p_contact new) {
    int rebuild = 1;                                                                                                                           // Set a variable to count the number of element of the different rebuild tab
    p_contact tmp = list->levels[0], rebuild_tmp;                                                                                              // Create some pointer to use as cursor
    p_contact prev = tmp;                                                                                                                      // Set the previous cursor to the tmp

    if (list->levels[0]==NULL) {                                                                                                               // Case where level is empty
        p_contact* levels = (p_contact*) malloc (4*sizeof(p_contact));                                                                    // Create a tab of 4 elements for the new cell
        for (int i  = 0 ; i<4 ; i++) {
            levels[i]=NULL;
        }
        new->levels = levels;
        for (int i = 0 ; i<4 ; i++) {                                                                                                          // Loop to set the head of each level to the cell
            list->levels[i]=new;
        }
        tmp = NULL;                                                                                                                            // Avoiding to erase a pointer of the list
        prev = NULL;                                                                                                                           // Avoiding to erase a pointer of the list
        rebuild_tmp = NULL;                                                                                                                    // Avoiding to erase a pointer of the list
        free(rebuild_tmp);                                                                                                                     // Freeing unused pointer
        free(tmp);                                                                                                                             // Freeing unused variable
        free(prev);                                                                                                                            // Freeing unused variable
        return;
    } else {                                                                                                                                    // Case the tab is not empty
        if (compareString(tmp->name, new->name)==-1) {                                                                            // Case head insertion
            p_contact* levels = (p_contact*) malloc (4*sizeof(p_contact));                                                                 // Create a tab of 4 elements for the new cell
            for (int i  = 0 ; i<4 ; i++) {
                levels[i]=NULL;
            }
            new->levels = levels;
            rebuild = getMatch(new, tmp);                                                                                             // Get the size of the new tab
            p_contact* rebuild_tab = (p_contact*) malloc (rebuild*sizeof(p_contact));                                                       // Allocate the memory of the new tab
            for (int i  = 0 ; i<rebuild ; i++) {
                rebuild_tab[i]=NULL;
            }
            for (int i = 0 ; i<rebuild ; i++) {                                                                                                  // Loop to copy all common level between the new and the old tab
                rebuild_tab[i] = tmp->levels[i];                                                                                                 // Copy the old tab to the new tab
                list->levels[i] = new;                                                                                                           // Set the head of the level to the new cell
                new->levels[i] = tmp;                                                                                                            // Set the next of the cell to the old cell on the common levels
            }
            for (int i = rebuild ; i<4 ; i++) {                                                                                                  // Loop to match all level that haven't been match yet (highers levels)
                list->levels[i] = new;                                                                                                           // Set the head of the level to the new cell
                new->levels[i] = tmp->levels[i];                                                                                                 // As the old cell was the first one, it had 4 levels, so we copy the unused old next adresses from the highers levels
            }
            free(tmp->levels);                                                                                                                   // Freeing the old tab
            tmp->levels = rebuild_tab;                                                                                                           // Attributing the new tab to the tmp
            tmp = NULL;                                                                                                                          // Avoiding to erase a pointer of the list
            prev = NULL;                                                                                                                         // Avoiding to erase a pointer of the list
            rebuild_tmp = NULL;                                                                                                                  // Avoiding to erase a pointer of the list
            free(rebuild_tmp);                                                                                                                   // Freeing unused pointer
            free(tmp);                                                                                                                           // Freeing unused variable
            free(prev);                                                                                                                          // Freeing unused variable
            return;
        } else {                                                                                                                                 // Case where the cell is at the middle or at the end
            while (compareString(tmp->name, new->name) == 1 && tmp->levels[0]!=NULL) {                                             // Loop to go just after the good spot or at the end
                prev = tmp;
                tmp = tmp->levels[0];                                                                                                            // The cursor is at level 0 because we first need to place the cell to create the levels tabs of the cell and then attribute other adresses
            }
            if (compareString(tmp->name, new->name) == 1 && tmp->levels[0]==NULL) {                                                // Case where we have to place the cell at the end of the list
                p_contact* levels = (p_contact*) malloc (getMatch(tmp, new)*sizeof(p_contact));                                        // Create a tab of 4 elements for the new cell
                for (int i  = 0 ; i<getMatch(tmp, new) ; i++) {
                    levels[i]=NULL;
                }
                new->levels = levels;
                for (int i = 0 ; i<getMatch(tmp, new) ; i++) {                                                                              // Loop to match all cell that were pointing on NULL at the level of the new cell, to the new cell
                    tmp = list->levels[i];
                    while (tmp->levels[i]!=NULL) {                                                                                               // Loop to get the last element of each level and link it to the new cell
                        tmp = tmp->levels[i];
                    }
                    tmp->levels[i] = new;
                }
                tmp = NULL;                                                                                                                       // Avoiding to erase a pointer of the list
                prev = NULL;                                                                                                                      // Avoiding to erase a pointer of the list
                rebuild_tmp = NULL;                                                                                                               // Avoiding to erase a pointer of the list
                free(rebuild_tmp);                                                                                                                // Freeing unused pointer
                free(tmp);                                                                                                                        // Freeing unused variable
                free(prev);                                                                                                                       // Freeing unused variable
                return;
            } else if (compareString(tmp->name, new->name) == -1 || compareString(tmp->name, new->name) == 0) {      // Case where we have to insert it in the middle (either an element already existing or not)
                p_contact* levels = (p_contact*) malloc (getMatch(prev, new)*sizeof(p_contact));                                             // Allocating memory
                for (int i  = 0 ; i<getMatch(prev, new) ; i++) {
                    levels[i]=NULL;
                }
                new->levels = levels;
                if (getMatch(prev, new) <= getMatch(new, tmp)) {                                                                       // Case where we don't have to rebuild the cell after the new one, PROBLEM when same element, but the exception is handled
                    if (compareString(tmp->name, new->name) == 0) {                                                                // Case where it's the same element and the element is the first one
                        new->levels[0] = tmp->levels[0];                                                                                         // Manually linking the cell correctly to the first ans third cell at the level 0
                        tmp->levels[0] = new;
                    } else {                                                                                                                     // Normal case without rebuilding
                        for (int i = 0; i < getMatch(prev, new); i++) {                                                                          // We link at all level of the previous cell, all the cell that were pointing on the tmp to the new cell (which is placed before and is higher)
                            rebuild_tmp = list->levels[i];                                                                                       // We set a cursor to the head of each level
                            while (rebuild_tmp->levels[i] != tmp) {                                                                              // We find the cell that was pointing on the tmp
                                rebuild_tmp = rebuild_tmp->levels[i];
                            }
                            rebuild_tmp->levels[i] = new;                                                                                        // We relink the cell correctly
                            new->levels[i] = tmp;                                                                                                // We relink the new cell to the tmp at the current level
                        }
                    }
                    tmp = NULL;                                                                                                                  // Avoiding to erase a pointer of the list
                    prev = NULL;                                                                                                                 // Avoiding to erase a pointer of the list
                    rebuild_tmp = NULL;                                                                                                          // Avoiding to erase a pointer of the list
                    free(rebuild_tmp);                                                                                                           // Freeing unused pointer
                    free(tmp);                                                                                                                   // Freeing unused variable
                    free(prev);                                                                                                                  // Freeing unused variable
                    return;
                } else {                                                                                                                         // Case where we have to rebuild
                    p_contact* rebuild_tab = (p_contact*) malloc (getMatch(new, tmp)*sizeof(p_contact));                          // Allocate the memory
                    for (int i  = 0 ; i<getMatch(new, tmp) ; i++) {
                        rebuild_tab[i]=NULL;
                    }
                    for (int i = 0 ; i<getMatch(new, tmp) ; i++ ) {                                                                    // Loop to start rematching correctly
                        rebuild_tab[i] = tmp->levels[i];                                                                                         // Copy the common cell from the old tab to the new tab
                        new->levels[i] = tmp;                                                                                                    // Set the next to the common level of the new cell to the tmp
                    }
                    for (int i = getMatch(new, tmp) ; i < getLevel(list, tmp) ; i++) {                                         // Loop to match all the unmatch cell of the new cell and copy the unusued adress of the highers levels of the old tab
                        new->levels[i] = tmp->levels[i];                                                                                        // Copying the lefting cells from the old tab to the new tab
                    }
                    for (int i = 0 ; i<4 ; i++) {                                                                                                // Loop to go through all level and relink
                        rebuild_tmp = list->levels[i];                                                                                           // Setting a cursor to the head of each level
                        while (rebuild_tmp->levels[i]!= tmp && rebuild_tmp->levels[i]!=NULL) {                                                   // Loop to find cells that were pointing on the tmp (if they we're)
                            rebuild_tmp = rebuild_tmp->levels[i];
                        }
                        if (rebuild_tmp->levels[i]== tmp) {                                                                                      // If a cell was pointing on the tmp, we relink it to the new cell
                            rebuild_tmp->levels[i] = new;
                        }
                    }
                    free(tmp->levels);                                                                                                           // Freeing the old tab
                    tmp->levels = rebuild_tab;                                                                                                   // Attributing the new tab
                    tmp = NULL;                                                                                                                  // Avoiding to erase a pointer of the list
                    prev = NULL;                                                                                                                 // Avoiding to erase a pointer of the list
                    rebuild_tmp = NULL;                                                                                                          // Avoiding to erase a pointer of the list
                    free(rebuild_tmp);                                                                                                           // Freeing unused pointer
                    free(tmp);                                                                                                                   // Freeing unused variable
                    free(prev);                                                                                                                  // Freeing unused variable
                }
            }
        }
    }
}

int searchContact_dtc(p_contact_list list, char* search) {
    int current_level = 3;                                                                                                      // Set first level to 3 (max level)
    p_contact tmp = list->levels[current_level];                                                                                // Create a cursor
    p_contact prev = tmp;                                                                                                       // Create a prev
    while ((tmp!=NULL || current_level!=0) && (current_level!=0 || compareString(tmp->name, search) != -1)) {    // Loop to continue while it's not level 0 and NULL or level 0 and next superior
        if (tmp==NULL && current_level!=0) {                                                                                    // Check if we have to go down a level
            tmp = prev;                                                                                                         // Set the tmp to the last cell not NULL
//            printf("\n");
            current_level--;                                                                                                    // Down the level
        } else if (compareString(tmp->name, search)==0) {                                                         // Check if we have found the value
//            printf("tmp : %s, level : %d\n", tmp->name, current_level);
            tmp = NULL;
            prev = NULL;
            free(tmp);
            free(prev);
            return 1;
        } else {                                                                                                                // If we can still go fw we increment
            if (compareString(tmp->name, search)== -1 && current_level!=0) {                                      // Check if the next is superior to the search contact
//                printf("tmp : %s, level : %d\n\n", tmp->name, current_level);
                tmp = prev;                                                                                                     // If yes we down a level
                current_level--;
            } else {                                                                                                            // if not we go to the next cell
//                printf("tmp : %s, level : %d\n", tmp->name, current_level);
                prev = tmp;
                tmp = tmp->levels[current_level];
            }
        }
    }
    tmp = NULL;
    prev = NULL;
    free(tmp);
    free(prev);
    return 0;                                                                                                                   // If we haven't find the value we return 0
}

void insertContact_dtc(p_contact_list list, p_contact new) {
    int current_level = 3;                                                                                                                      // Set first level to 3 (max level)
    int rebuild = 1;                                                                                                                            // Set a variable to count the number of element of the different rebuild tab
    p_contact* temp_tab = (p_contact*) malloc (4*sizeof(p_contact));                                                                       // Create a tab to stock the prev for each level
    for (int i = 0 ; i<4 ; i++) {
        temp_tab[i]=NULL;
    }

    p_contact tmp = list->levels[current_level];                                                                                  // Create some pointer to use as cursor
    p_contact prev = tmp;                                                                                                                      // Set the previous cursor to the tmp

    if (list->levels[0]==NULL) {                                                                                                               // Case where level is empty
        p_contact* levels = (p_contact*) malloc (4*sizeof(p_contact));                                                                    // Create a tab of 4 elements for the new cell
        new->levels = levels;
        for (int i = 0 ; i<4 ; i++) {                                                                                                          // Loop to set the head of each level to the cell
            list->levels[i]=new;
        }
        tmp = NULL;                                                                                                                            // Avoiding to erase a pointer of the list
        prev = NULL;                                                                                                                           // Avoiding to erase a pointer of the list         // Freeing unused pointer
        free(tmp);                                                                                                                             // Freeing unused variable
        free(prev);                                                                                                                            // Freeing unused variable
        return;
    } else if (compareString(tmp->name, new->name)==-1) {                                                                           // Case head insertion
        tmp = list->levels[0];                                                                                                                // Set the tmp to the level 0 (before on the last level)
            p_contact *levels = (p_contact *) malloc(4 * sizeof(p_contact));                                                                 // Create a tab of 4 elements for the new cell
            for (int i = 0; i < 4; i++) {
                levels[i] = NULL;
            }
            new->levels = levels;
            rebuild = getMatch(new,tmp);                                                                                                // Get the size of the new tab
            p_contact *rebuild_tab = (p_contact *) malloc(rebuild * sizeof(p_contact));                                                       // Allocate the memory of the new tab
            for (int i = 0; i < rebuild; i++) {                                                                                                    // Forcing to NULL
                rebuild_tab[i] = NULL;
            }
            for (int i = 0; i < rebuild; i++) {                                                                                                     // Loop to copy all common level between the new and the old tab
                rebuild_tab[i] = tmp->levels[i];                                                                                                    // Copy the old tab to the new tab
                list->levels[i] = new;                                                                                                              // Set the head of the level to the new cell
                new->levels[i] = tmp;                                                                                                               // Set the next of the cell to the old cell on the common levels
            }
            for (int i = rebuild; i < 4; i++) {                                                                                                     // Loop to match all level that haven't been match yet (highers levels)
                list->levels[i] = new;                                                                                                              // Set the head of the level to the new cell
                new->levels[i] = tmp->levels[i];                                                                                                    // As the old cell was the first one, it had 4 levels, so we copy the unused old next adresses from the highers levels
            }
            free(tmp->levels);                                                                                                                      // Freeing the old tab
            tmp->levels = rebuild_tab;                                                                                                              // Attributing the new tab to the tmp
            tmp = NULL;                                                                                                                             // Avoiding to erase a pointer of the list
            prev = NULL;                                                                                                                            // Avoiding to erase a pointer of the list             // Freeing unused pointer
            free(tmp);                                                                                                                              // Freeing unused variable
            free(prev);                                                                                                                             // Freeing unused variable
            free(temp_tab);
            return;
        } else {
        while ((tmp != NULL || current_level != 0) && (current_level != 0 || compareString(tmp->name, new->name) == 1)) {             // Loop to find the spot to insert                                                                    // Loop to go through all cell  of level 0 at worst case
            if (tmp == NULL && current_level != 0) {                                                                                                // Check if we have to go down a level
                tmp = prev;                                                                                                                         // Set the tmp to the last cell not NULL
                temp_tab[current_level] = prev;                                                                                                     // Save the prev value, because we know that if we have to link a value it will be this one
                current_level--;                                                                                                                    // Down the level
            } else {                                                                                                                                // Check if we can go forward
                if (compareString(tmp->name, new->name) == -1 && current_level != 0) {                                                // Case where the next value is > and we're not at level 0
                    tmp = prev;                                                                                                                     // Set the tmp to the last cell not NULL
                    temp_tab[current_level] = prev;                                                                                                 // Save the prev value, because we know that if we have to link a value it will be this one
                    current_level--;                                                                                                                // Go down a level
                } else {                                                                                                                            // Else we just increment the cursor
                    prev = tmp;
                    tmp = tmp->levels[current_level];
                }
            }

        }

        temp_tab[current_level] = prev;                                                                                                             // Initializing the last cell of the temp tab because it hasn't been done
        if (compareString(prev->name, new->name)==1 && tmp == NULL) {                                                                   // End insertion case
            p_contact* levels = (p_contact*) malloc (getMatch(prev, new)*sizeof(p_contact));                                                   // We allocate the memory for the new tab
            new->levels = levels;                                                                                                                   // Attributing the tab
            for (int i = 0; i<getMatch(prev, new) ; i++) {                                                                                          // We relink the different next saved to the new cell
                temp_tab[i]->levels[i]=new;
            }
            tmp = NULL;
            prev = NULL;
            free(tmp);
            free(temp_tab);
            free(prev);
            return ;
        } else {                                                                                                                                    // Mid Insertion
            p_contact *levels = (p_contact *) malloc(getMatch(prev, new) * sizeof(p_contact));                                                 // We allocate the memory for the new tab
            for (int i = 0; i < getMatch(prev, new); i++) {                                                                                         // Force to NULL
                levels[i] = NULL;
            }
            new->levels = levels;                                                                                                                   // Attributing the tab
            if (getMatch(prev, new) <= getMatch(new, tmp)) {                                                                             // No rebuild case (don't have to recreate the tab of the next cell)
                for (int i = 0 ; i< getMatch(prev, new) ; i++) {                                                                                    // Loop to relink the prev next to the nex cell + the matching level of the new cell to the tmp
                    new->levels[i] = tmp;                                                                                                           // Linking the matching level of the new cell to the next (tmp)
                    temp_tab[i]->levels[i] = new;                                                                                                   // Linking prev matching level to the new cell
                }
                tmp = NULL;
                prev = NULL;
                free(tmp);
                free(prev);
                free(temp_tab);
                return ;
            } else {                                                                                                                                // Rebuild case (we have to change the adress tab of the next cell)
                p_contact *rebuild_tab = (p_contact *) malloc(getMatch(new, tmp) * sizeof(p_contact));                              // Allocate the memory
                for (int i = 0; i < getMatch(new, tmp); i++) {                                                                           // Force the tab to NULL
                    rebuild_tab[i] = NULL;
                }
                new->levels = levels;                                                                                                               // Attribute the memory
                for (int i = 0; i < getMatch(new, tmp); i++) {                                                                           // Loop to attribute all commons level
                    temp_tab[i]->levels[i] = new;                                                                                                   // Relink the prev cell saved to the new cell
                    new->levels[i] = tmp;                                                                                                           // Link common level of the new cell to the tmp
                    rebuild_tab[i] = tmp->levels[i];                                                                                                // Copy the common cell of the rebuilded cell to the new tab
                }

                for (int i = getMatch(new, tmp) ; i < getLevel(list, tmp) ; i++) {                                                 // Loop to copy missing levels byt getting the previous number of levels of the cell (A new cell cannot have more level than the one it replace)
                    temp_tab[i]->levels[i] = new;                                                                                                    // Linking the saved prev to the new cell
                    new->levels[i] = tmp->levels[i];                                                                                                 // Setting the next of the new cell to the next of the previous level of the tmp
                }
                free(tmp->levels);                                                                                                                   // Freeing the memory
                tmp->levels = rebuild_tab;                                                                                                           // Attributing the new tab of level to the tmp
                tmp = NULL;
                prev = NULL;
                free(tmp);
                free(prev);
                free(temp_tab);
                return ;
            }
        }
    }
}


// 3) Manipulation of Appointment Structure (related with contact)

p_appointment createAppointment (p_contact_list liste) {                                // VARIABLES UNFREE
    char* input = (char*) malloc(50*sizeof(char));                                 // Str variable to stock the input
    p_contact toAssign = (p_contact) malloc (sizeof(p_contact));                   // Pointer to check if the contact already exist or not
    int checkFormat = -1;                                                               // Variable to check argument are correct
    p_appointment new = createEmptyAppointment();                                       // Allocate the memory for the new appointment

    printf("What's the date of your new appointment (day/month/years) ?\n\n ");         // Asking for the date
    do {                                                                                // Loop to ask while answer is not in the correct format or impossible
        checkFormat = checkDateFormat(new);
    } while (checkFormat == -1);

    checkFormat = -1;                                                                   // Reset the check variable
    printf("\nWhen is your new appointment {0-23}h{0-59} ?\n\n ");                      // Asking for the time of the appointment
    do {                                                                                // Loop to ask while answer is not in the correct format or impossible
        checkFormat = checkHourFormat(new);
    } while (checkFormat == -1);

    checkFormat = -1;                                                                   // Reset the check variable
    printf("\nHow long is your new appointment {0-23}h{0-59} ?\n\n ");                  // Asking for the length of the appointment
    do {                                                                                // Loop to ask while answer is not in the correct format or impossible
        checkFormat = checkLengthAppointmentFormat(new);
    } while (checkFormat == -1);

    checkFormat =-1;                                                                    // Reset the check variable
    printf("\nWhat's the object of your appointment ( < 100 characters) ?\n\n ");       // Asking for the object of the appointment
    do {
        checkFormat = checkLengthObject(new);
    } while (checkFormat == -1);

    printf("Please enter a contact to assign or create :\n\n");                         // Asking for a contact input
    do {                                                                                // Loop to get an input while the format is not correct
        input = autoCompletion(liste);
    } while (input==NULL);

    toAssign = searchContact(input, liste);                                 // Search if the wanted contact exist

    if (toAssign==NULL) {                                                              // Case where we have to create a new contact
        toAssign = createContact(input);                                         // Creating the contact
        insertContact(liste, toAssign);                                       // Inserting the contact in the list
        toAssign = searchContact(input, liste);                             // Reassigning the contact to the one created
    }
    insertAppointment(toAssign, new);                                       // Inserting the appointment in the contact list
    return new;                                                                         // Return the new appointment

}

void insertAppointment(p_contact contact, p_appointment cell) {
    p_appointment tmp = contact->head  ;                                    // Set a cursor to the head of the contact list
    p_appointment prev = tmp;                                               // Set a prev cursor

    if (contact->head==NULL) {                                              // Case where the list is empty
        contact->head = cell;                                               // We set initialize the head of the list
        tmp = NULL;
        prev = NULL;
        free(tmp);
        free(prev);
        return;
    } else if (compareDate(cell, tmp) <= 0) {                              // Case we have to do an head insertion
        cell->next = contact->head;                                         // We set the next of the new head to the previous head
        contact->head = cell;                                               // We update the new head
        tmp = NULL;
        prev = NULL;
        free(tmp);
        free(prev);
        return;
    } else {
        while (compareDate(cell, tmp) > 0 && tmp->next!=NULL) {             // Loop to increment either at the end or just after the good value
            prev = tmp;
            tmp = tmp->next;
        }
        if (compareDate(cell, tmp) <= 0) {                                   // If comparerDate == -1 it means we have to insert just before the actual cell
            prev->next = cell;                                              // We update the next of the previous cell
            cell->next = tmp;                                               // We update the next of the new cell to the tmp
            tmp = NULL;
            prev = NULL;
            free(tmp);
            free(prev);
            return;
        } else {                                                            // Case where we are at the end but have to place the new cell at the end
            tmp->next = cell;                                               // We link next of the tmp to the new cell
            tmp = NULL;
            prev = NULL;
            free(tmp);
            free(prev);
            return;
        }
    }
}


// 4) Display Functions

void uniform_display_contact_list (p_contact_list list) {
    p_contact level0cur;                                                        // Create a cursor to compare to higher value (because the first level will be the most complete, we have to check if we have to fill higher level or not)
    p_contact tmp_h;                                                            // Create a cursor pointer to go through each level

    for (int i = 0 ; i<list->max_levels ; i++){                                 // Loop which stop when all level including the last one are printed
        printf("[list head_%d @-]",i);                                          // Special printing for the head of the list
        tmp_h = list->levels[i];                                                // Set the pointer to the head of the current level
        level0cur = list->levels[0];                                            // Reset the level 0 cursor to the first cell of the level 0

        while (level0cur!=NULL) {                                               // Loop to go through all cell of the first level each level (and see if cell are there or not)
            if (tmp_h!=level0cur || tmp_h==NULL) {                              // If the level cursor is not equal to the level 0 cursor it mean the cell aren't on the same level / or if the level cursor is NULL but there are still cell on the first level
                for (int j = 0; j < strlen(level0cur->name)+9; j++) {        // Case where cell is not on the level, then we print "-" for the length of the corresponding cell at level 0 to keep it align
                    printf("-");
                }
            } else {                                                            // Case where we have to print the cell
                printf("-->[ %s|@-]", tmp_h->name);                             // Special print for the cell
                tmp_h = tmp_h->levels[i];                                       // If we have printed the cell on the level we can move to the next one to continue the checking for missing cell in between
            }
            level0cur = level0cur->levels[0];                                   // Move the checking cursor on the level 0 to the next value

        }
        printf("-->NULL\n");                                                    // Special print to indicate the end of the level list
        free(level0cur);
        free(tmp_h);
    }
}

void displayContact(p_contact contact)  {
    if (contact == NULL) {                                                                                              // Case where the contact hasn't been found
        printf("Contact not found.\n");
    }

    printf("Contact: %s\n", contact->name);                                                                             // Print the contact name
    p_appointment tmp = contact->head;                                                                                  // Set the cursor to the first appointment
    p_appointment prev = tmp;                                                                                           // Set the prev to the tmp

    if (tmp == NULL) {                                                                                                  // Case where is no appointment
        printf("No appointment in this agenda\n\n");
    } else {                                                                                                            // Case where there is some appointment
        while (tmp!=NULL) {                                                                                             // Loop to go through all appointment
            if (compareDate(prev , tmp) == 1 || compareDate(prev , tmp) == -1 || prev == tmp) {                         // If the Year is different or the It's the first cell we print the year
                printf("\n=================== %d ===================\n", tmp->date.years);
            }
            if ((compareDate(prev , tmp) >= -3 && compareDate(prev , tmp) <= 3 || prev == tmp) && compareDate(prev , tmp)!=0) {  // If the date has changed, we print the date
                printf("\n");
                detectZero(tmp->date.day);                                                                           // If the number if one digit we print the silent 0
                printf("/");
                detectZero(tmp->date.month);                                                                         // If the number if one digit we print the silent 0
                printf("\n");
            }
            printf("Time : %dh", tmp->hour.hours);                                                                       // We always print the time
            detectZero(tmp->hour.minutes);                                                                           // We always print the length with the silent 0
            printf(", Length : %dh", tmp->length.hours);
            detectZero(tmp->length.minutes);                                                                         // We always print the minutes with silent 0
            printf(", Object : %s\n", tmp->object);                                                                       // We print the object
            prev = tmp;                                                                                                 // Increment the prev
            tmp = tmp -> next;                                                                                          // Increment the tmp
        }
        printf("\n");
    }
    tmp = NULL;
    prev = NULL;
    free(tmp);
    free(prev);
}

void displayAgenda(p_contact_list contactList) {            // VARIABLES UNFREE
    if (contactList == NULL) {                              // Case where the agenda is empty
        printf("Your agenda is empty.\n");
        return;
    }
    p_contact temp = contactList->levels[0];                // Set the cursor to the first contact
    while(temp != NULL){
        displayContact(temp);                       // Display the contact
        temp = temp->levels[0];                             // Increment the tmp
    }
    free(temp);
    return;
}

int removeAppointment(p_contact contact, char* objectToRemove) {
    p_appointment temp = contact->head;                                                  // Set a pointer to the first appointment of the list
    p_appointment prev = NULL ;                                                          // Set a prev to NULL

    while (temp != NULL) {                                                               // Loop to go through all cells
        if (strcmp(temp->object, objectToRemove) == 0) {                                 // Check is object is the same as the one searched
            if (prev == NULL) {                                                          // If prev == NULL, it means we remove the head
                contact->head = temp->next;                                              // We relink the list
            } else {
                prev->next = temp ->next;                                                // Relink the list if it's in middle or end
            }
            return 1;                                                                    // Return 1 if successful
        }
        prev = temp;                                                                     // Increment the prev
        temp = temp ->next;                                                              // Increment the tmp
    }
    prev = NULL;
    temp = NULL;
    free(prev);
    free(temp);                                                                         // Free the temp cell
    return 0;                                                                           // Return 0 if unsuccessful
}



// -------------------------- Tests Functions --------------------------

void createAppointmentList(p_contact contact) {
    p_appointment  a1 = createEmptyAppointment();
    a1->object = "test 1";

    a1 ->date.day = 12;
    a1->date.month = 9;
    a1->date.years = 2004;

    a1->hour.hours = 12;
    a1->hour.minutes = 12;

    a1->length.hours = 8;
    a1->length.minutes = 30;

    insertAppointment(contact, a1);
    p_appointment  a2 = createEmptyAppointment();
    a2->object = "test 2";

    a2 ->date.day = 12;
    a2->date.month = 9;
    a2->date.years = 2004;

    a2->hour.hours = 12;
    a2->hour.minutes = 0;

    a2->length.hours = 2;
    a2->length.minutes = 0;

    insertAppointment(contact, a2);
    p_appointment  a3 = createEmptyAppointment();
    a3->object = "test 3";

    a3 ->date.day = 12;
    a3->date.month = 9;
    a3->date.years = 2004;

    a3->hour.hours = 12;
    a3->hour.minutes = 12;

    a3->length.hours = 2;
    a3->length.minutes = 0;

    insertAppointment(contact, a3);
    p_appointment  a4 = createEmptyAppointment();
    a4->object = "test 4";

    a4 ->date.day = 12;
    a4->date.month = 9;
    a4->date.years = 2004;

    a4->hour.hours = 12;
    a4->hour.minutes = 12;

    a4->length.hours = 2;
    a4->length.minutes = 0;

    insertAppointment(contact, a4);
    p_appointment  a5 = createEmptyAppointment();
    a5->object = "test 5";

    a5 ->date.day = 11;
    a5->date.month = 9;
    a5->date.years = 2004;

    a5->hour.hours = 9;
    a5->hour.minutes = 15;

    a5->length.hours = 234;
    a5->length.minutes = 59;

    insertAppointment(contact, a5);
    p_appointment  a6 = createEmptyAppointment();
    a6->object = "test 6";

    a6 ->date.day = 1;
    a6->date.month = 1;
    a6->date.years = 2000;

    a6->hour.hours = 14;
    a6->hour.minutes = 12;

    a6->length.hours = 1;
    a6->length.minutes = 58;

    insertAppointment(contact, a6);
    p_appointment  a7 = createEmptyAppointment();
    a7->object = "test 7";

    a7 ->date.day = 31;
    a7->date.month = 12;
    a7->date.years = 2004;

    a7->hour.hours = 12;
    a7->hour.minutes = 12;

    a7->length.hours = 7;
    a7->length.minutes = 0;

    insertAppointment(contact, a7);
    p_appointment  a8 = createEmptyAppointment();
    a8->object = "test 8";

    a8 ->date.day = 26;
    a8->date.month = 3;
    a8->date.years = 2012;

    a8->hour.hours = 13;
    a8->hour.minutes = 11;

    a8->length.hours = 0;
    a8->length.minutes = 20;

    insertAppointment(contact, a8);

}

void testRemoveAppointment(p_contact contact) {
    removeAppointment(contact, "test 1");
    removeAppointment(contact, "test 2");
    removeAppointment(contact, "test 3");
    removeAppointment(contact, "test 4");
    removeAppointment(contact, "test 5");
    removeAppointment(contact, "test 6");
    removeAppointment(contact, "test 7");
    removeAppointment(contact, "test 8");
}

p_contact_list createExempleList1(int showstep) {
    p_contact_list new = createEmptyList();
    p_contact c1 = createContact("aaaaa");
    p_contact c2 = createContact("zzzzz");
    p_contact c3 = createContact("zzzyy");
    p_contact c4 = createContact("zaaaa");
    p_contact c5 = createContact("hhhhhh");
    p_contact c6 = createContact("hhaa");
    p_contact c7 = createContact("mmmmm");
    p_contact c8 = createContact("hma");
    insertContact(new, c1);
    if (showstep==1) {
        //uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c2);
    if (showstep==1) {
        //uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c3);
    if (showstep==1) {
        //uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c4);
    if (showstep==1) {
        //uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c5);
    if (showstep==1) {
        //uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c6);
    if (showstep==1) {
        //uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c7);
    if (showstep==1) {
        //uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c8);
    //uniform_display_contact_list(new);
    //printf("\n\n");
    return new;

}

p_contact_list  createComplexityList() {

    char* liste[1001] = { "anderson_liam", "davis_olivia", "brown_noah", "wilson_emma", "martinez_ava","taylor_lucas", "harris_isabella", "turner_mia", "thomas_sophia", "clark_ethan",
                         "johnson_amelia", "white_jackson", "scott_benjamin", "walker_harper", "lewis_aria","moore_elijah", "theo_aiden", "hall_grace", "taylor_caleb", "garcia_lily",
                         "miller_ella", "adams_samuel", "hill_abigail", "martin_sebastian", "turner_avery","davis_scarlett", "lewis_carter", "hall_chloe", "martin_zoe", "allen_grayson",
                         "harris_luna", "robinson_mason", "martinez_layla", "wilson_henry", "walker_penelope","clark_logan", "turner_victoria", "scott_evelyn", "hall_liam", "miller_nora",
                         "walker_eli", "harris_stella", "robinson_levi", "taylor_aurora", "jackson_aiden","white_mila", "turner_ezra", "robinson_camila", "davis_maverick", "smith_alice",
                         "johnson_bob", "williams_charlie", "davis_david", "anderson_eva","brown_frank", "taylor_grace", "wilson_henry", "miller_isabel", "martin_jack",
                         "lee_sophia", "harris_daniel", "martinez_olivia", "jackson_james", "taylor_emma","white_mia", "thomas_liam", "moore_ava", "davis_lucas", "garcia_aria",
                         "hernandez_ethan", "robinson_amelia", "thompson_logan", "martinez_harper", "clark_mason","rodriguez_ella", "walker_oliver", "scott_avery", "hall_lily", "adams_carter",
                         "turner_chloe", "wright_jackson", "lewis_abigail", "taylor_caleb", "brown_emily","moore_sebastian", "lewis_scarlett", "hill_gabriel", "johnson_hazel", "hall_sofia",
                         "davis_jackson", "harris_madison", "wilson_lucy", "allen_cameron", "moore_penelope",
                         "robinson_aiden", "davis_emma", "turner_zoe", "garcia_wyatt", "tremblay_marie", "gagnon_pierre", "roy_lucie", "cote_jacques", "bouchard_sylvie", "gauthier_martin", "morin_isabelle",
                         "lavoie_paul", "fortin_alice", "gagne_louis", "ouellet_josee", "pelletier_marc", "belanger_michelle", "levesque_guy",
                         "bergeron_nathalie", "leblanc_louise", "paquette_richard", "girard_lise", "simard_daniel", "boucher_claudia", "caron_stephane",
                         "beaulieu_johanne", "cloutier_pierre", "dube_julie", "poirier_robert", "fournier_chantal", "lapointe_eric", "leclerc_francine",
                         "lefebvre_jacques", "poulin_anne", "thibault_catherine", "st-pierre_patrick", "nadeau_marie", "martin_sophie", "landry_yves",
                         "martel_caroline", "bedard_alain", "grenier_denise", "lessard_denis", "bernier_luc", "richard_martine", "michaud_diane",
                         "hebert_stephan", "desjardins_jacqueline", "couture_benoit", "turcotte_michele", "lachance_pierre", "parent_julie", "blais_jacques",
                         "gosselin_chantal", "savard_francois", "proulx_louise", "beaudoin_ginette", "demers_mario", "perreault_claude", "boudreau_marie",
                         "lemieux_luc", "cyr_annette", "perron_jean", "dufour_louise", "dion_gaetan", "mercier_nancy", "bolduc_richard", "berube_celine",
                         "boisvert_ginette", "langlois_johann", "menard_suzanne", "therrien_julien", "plante_audrey", "bilodeau_guy", "blanchette_evelyne",
                         "dubois_rene", "champagne_christine", "paradis_michel", "fortier_madeleine", "arsenault_micheline", "dupuis_andre", "gaudreault_claudette",
                         "hamel_pascal", "houle_louison", "villeneuve_michele", "rousseau_gabriel", "gravel_denise", "theriault_patricia", "lemay_daniel",
                         "robert_johanne", "allard_annie", "deschenes_yvon", "giroux_jocelyne", "guay_renee", "leduc_andre", "boivin_marcel", "charbonneau_normand",
                         "lambert_chantal", "raymond_gaetan", "vachon_sylvain", "gilbert_genevieve", "audet_danielle", "jean_mario", "larouche_julie", "legault_francis",
                         "trudel_jacqueline", "fontaine_marcel", "picard_lyse", "labelle_dominique", "lacroix_pierre", "jacques_madeleine", "moreau_real", "carrier_diane",
                         "bernard_lucie", "desrosiers_claude", "goulet_sonia", "renaud_pierre", "dionne_marie", "lapierre_luc", "vaillancourt_chantal", "fillion_paul",
                         "lalonde_johanne", "tessier_eric", "bertrand_lise", "tardif_martin", "lepage_france", "gingras_sylvie", "benoit_francois", "rioux_jacques",
                         "giguere_madeleine", "drouin_guy", "harvey_jocelyne", "lauzon_patrick", "nguyen_huong", "gendron_gilles", "boutin_julie", "laflamme_richard",
                         "vallee_jocelyne", "dumont_nathalie", "breton_micheline", "pare_andre", "paquin_ginette", "robitaille_pierre", "gelinas_marie-claude",
                         "duchesne_patrick", "lussier_suzanne", "seguin_guy", "veilleux_claude", "potvin_johanne", "gervais_louise", "pepin_jacques", "laroche_marie",
                         "morissette_ghislain", "charron_nicole", "lavallee_denis", "laplante_jocelyne", "chabot_jacques", "brunet_claudette", "vezina_ginette",
                         "desrochers_sylvain", "labrecque_linda", "coulombe_luc", "tanguay_sonia", "chouinard_luc", "noel_denise", "pouliot_gaetan", "lacasse_claude",
                         "daigle_lise", "marcoux_celine", "lamontagne_pierre", "turgeon_paul", "larocque_jean", "roberge_catherine", "auger_diane", "masse_roger",
                         "pilon_madeleine", "racine_patrick", "dallaire_claudine", "emond_paul", "gregoire_diane", "beauregard_sylvain", "smith_louise", "denis_martin",
                         "lebel_lynda", "blouin_jacques", "martineau_claudette", "labbe_claude", "beauchamp_patrick", "st-onge_paul", "charette_diane", "dupont_marie",
                         "letourneau_daniel", "rodrigue_carole", "cormier_michele", "rivard_claude", "mathieu_chantal", "asselin_luc", "st-jean_francine", "plourde_pierre",
                         "thibodeau_jacques", "milot_johanne", "veilleux_richard", "grenon_ginette", "lachapelle_marc", "lizotte_marie-claude", "pare_michel", "berthiaume_martine",
                         "ross_marc", "pare_paule", "trottier_pierre", "huard_lise", "lemay_stephane", "pelletier_michele", "lamoureux_jacques", "gagne_johanne", "fiset_luc",
                         "theriault_diane", "turcotte_denis", "dion_martine", "leclerc_jean", "ranger_michele", "hamel_stephane", "ferland_claudette", "dubois_real",
                         "forest_ginette", "perrault_louis", "duguay_danielle", "bilodeau_robert", "brochu_chantal", "verreault_marc", "larose_marie", "morneau_richard",
                         "blanchet_nathalie", "boutin_stephane", "lacombe_claudette", "dupuis_sylvain", "labonte_lucie", "collin_andre", "champagne_ginette", "legare_pierre",
                         "rioux_marie-claude", "lavigne_paul", "pelletier_jacqueline", "chagnon_pierre", "vigneault_lucie", "bernier_marc", "rivest_jocelyne", "brousseau_denis",
                         "page_madeleine", "champagne_marc", "thivierge_johanne", "dion_real", "pelletier_claudette", "lemay_marc", "roussin_diane", "couture_richard",
                         "legault_louise", "lessard_gilles", "beaudry_nicole", "dufour_guy", "goulet_claudette", "bourque_jacques", "robert_luc", "perron_madeleine",
                         "provost_denis", "boulianne_pierrette", "gosselin_francois", "clement_diane", "savoie_louis", "morin_johanne", "beaudoin_michel", "marcoux_denise",
                         "carrier_stephane", "rondeau_ginette", "fontaine_denis", "bilodeau_lucie", "vincent_pierre", "lamarche_johanne", "boucher_andre", "chartrand_lise",
                         "simard_michel", "aube_marie", "lachapelle_paul", "roy_annie", "marchand_lucie", "larose_denis", "lamoureux_lucie", "morin_roger", "landry_ginette",
                         "bergeron_denis", "belanger_jacqueline", "richer_pierre", "cloutier_lucie", "beaudry_pierre", "bibeau_michele", "tanguay_gilles", "pelletier_johanne",
                         "bergeron_pierre", "roy_chantal", "leduc_daniel", "st-laurent_ginette", "sevigny_pierre", "lamontagne_claudette", "duchesne_real", "riopel_claudette",
                         "menard_jacques", "dupuis_madeleine", "gingras_luc", "roberge_louise", "duchesne_daniel", "desrosiers_ginette", "giroux_pierre", "corbeil_lucie",
                         "girard_stephane", "charbonneau_raymonde", "girard_guy", "perreault_ginette", "rochon_marc", "leduc_ginette", "fournier_pierre", "giroux_pauline",
                         "fournier_richard", "veilleux_micheline", "nadeau_michel", "martin_johanne", "lavoie_luc", "parent_lucie", "pare_jacques", "poirier_claudette",
                         "bouchard_pierre", "lefebvre_denise", "lavoie_jacques", "tremblay_claudette", "labrie_stephane", "couture_louise", "langlois_martin", "simard_louise",
                         "sylvain_micheline", "gagne_denis", "lefebvre_lise", "morin_pierre", "deschamps_denise", "lebrun_daniel", "demers_lucie", "verreault_claude",
                         "lavoie_micheline", "lemay_jocelyn", "boulet_claudette", "desrochers_daniel", "boisvert_lise", "leclerc_michel", "morin_nathalie", "girard_louis",
                         "renaud_louise", "trudeau_marc", "beauchesne_denise", "dupuis_jacques", "tremblay_johanne", "bergeron_gaetan", "leclerc_lucie", "labrie_paul",
                         "lapointe_claudette", "grenier_luc", "gagnon_martine", "belanger_sylvain", "labonte_lise", "boivin_claude", "paquette_lucie", "riopel_jacques",
                         "dion_pierrette", "beaulieu_pierre", "nadeau_chantal", "st-amand_denis", "martin_micheline", "bergeron_luc", "ouellet_claudette", "boucher_jean",
                         "desrosiers_paule", "rheault_guy", "thibodeau_ginette", "richer_luc", "laflamme_johanne", "pepin_denis", "couture_jacqueline", "ranger_diane",
                         "perron_richard", "couture_jean", "cyr_johanne", "dufour_michel", "fournier_jocelyne", "larochelle_paul", "duchesne_diane", "roy_marc",
                         "fournier_suzanne", "boucher_luc", "beauchemin_micheline", "morin_louis", "fournier_louise", "gagne_jean", "fortier_johanne", "leblanc_pierre",
                         "couture_ginette", "lorem_nicolas", "ipsum_lea", "dolor_theo", "sit_thomas", "amet_manon", "consectetur_marie", "adipiscing_kevin", "elit_alexandre", "sed_camille", "do_melissa",
                         "eiusmod_maxime", "tempor_laura", "incididunt_lucas", "ut_alexis", "labore_clement", "et_quentin", "dolore_julien", "magna_oceane", "aliqua_anais", "dolor_julie",
                         "purus_hugo", "non_pierre", "enim_pauline", "praesent_emma", "elementum_antoine", "facilisis_chloe", "convallis_florian", "a_valentin", "cras_lucie", "semper_sarah",
                         "auctor_sebastien", "neque_marine", "vitae_romain", "tempus_marion", "quam_guillaume", "quis_paul", "varius_anthony", "quam_jessica", "quisque_justine", "id_emilie",
                         "pellentesque_nathan", "diam_melanie", "volutpat_benjamin", "commodo_louis", "sed_elodie", "egestas_enzo", "egestas_jeremy", "sagittis_dylan", "orci_baptiste", "a_mathilde",
                         "scelerisque_maman", "purus_michel", "semper_clara", "eget_amandine", "lacus_vincent", "suspendisse_isabelle", "faucibus_audrey", "interdum_caroline", "posuere_leo", "lorem_philippe",
                         "ipsum_papa", "nisl_david", "rhoncus_mathieu", "mattis_corentin", "rhoncus_daniel", "urna_christophe", "neque_aurelie", "viverra_adrien", "diam_monique", "quam_nathalie",
                         "nulla_sophie", "porttitor_alain", "massa_amelie", "id_axel", "neque_damien", "aliquam_sandrine", "justo_stephanie", "donec_tom", "enim_arthur", "diam_maeva",
                         "nulla_jean", "porttitor_charlotte", "massa_frederic", "id_celine", "neque_stephane", "aliquam_claude", "justo_morgane", "enim_patrick", "diam_mathis", "vulputate_noemie",
                         "quam_claire", "nulla_eric", "porttitor_laetitia", "massa_raphael", "id_sylvie", "neque_dominique", "aliquam_martine", "justo_virginie", "enim_eva", "diam_jerome",
                         "vulputate_juliette", "quam_pascal", "nulla_loic", "porttitor_christine", "massa_romane", "id_francoise", "neque_laurent", "aliquam_olivier", "justo_papy", "enim_alicia",
                         "diam_bernard", "vulputate_clemence", "quam_maxence", "nulla_francois", "porttitor_mickael", "massa_jade", "id_remi", "neque_catherine", "aliquam_cedric", "justo_gabriel",
                         "enim_helene", "diam_jeanne", "vulputate_jonathan", "quam_lisa", "nulla_thierry", "porttitor_aurelien", "massa_christian", "id_coralie", "neque_jacqueline", "aliquam_jules",
                         "justo_andre", "enim_jordan", "diam_nicole", "vulputate_alice", "quam_chantal", "nulla_fabien", "porttitor_matheo", "massa_elise", "id_valerie", "neque_victor",
                         "aliquam_angelique", "justo_arnaud", "enim_celia", "diam_dorian", "vulputate_elisa", "quam_fanny", "nulla_gerard", "porttitor_mamie", "massa_marc", "id_simon",
                         "neque_anne", "aliquam_christelle", "justo_jacques", "enim_annie", "diam_maelys", "vulputate_margaux", "quam_alexandra", "nulla_estelle", "porttitor_ludovic", "massa_ophelie",
                         "id_samuel", "neque_veronique", "aliquam_sylvain", "justo_zoe", "enim_bruno", "diam_mamy", "vulputate_aurore", "quam_ines", "nulla_jean_pierre", "porttitor_louise",
                         "massa_tony", "id_tristan", "neque_benoit", "aliquam_cecile", "justo_erwan", "enim_laurine", "diam_matthieu", "vulputate_sandra", "quam_lena", "nulla_robert",
                         "porttitor_cindy", "massa_florence", "id_jean_claude", "neque_yann", "aliquam_bastien", "justo_laurence", "enim_mael", "diam_matteo", "vulputate_ambre", "quam_guy",
                         "nulla_cassandra", "porttitor_elisabeth", "massa_evan", "id_lola", "neque_franck", "aliquam_jennifer", "justo_maelle", "enim_remy", "diam_xavier", "vulputate_fabrice",
                         "quam_laure", "nulla_lilou", "porttitor_noah", "massa_patricia", "id_thibault", "neque_yanis", "aliquam_corinne", "justo_genevieve", "enim_michele", "diam_william",
                         "vulputate_gregory", "quam_martin", "nulla_charles", "porttitor_cloe", "massa_delphine", "id_simone", "neque_beatrice", "aliquam_ethan", "justo_kylian", "enim_rene",
                         "diam_brigitte", "vulputate_christiane", "quam_evelyne", "nulla_francis", "porttitor_gaelle", "massa_sabrina", "id_didier", "neque_dimitri", "aliquam_edouard", "justo_lou",
                         "enim_ludivine", "diam_robin", "vulputate_solene", "quam_adeline", "nulla_anna", "porttitor_emeline", "massa_herve", "id_leonie", "neque_mathias", "aliquam_bryan",
                         "justo_colette", "enim_esteban", "diam_gaetan", "vulputate_gwendoline", "quam_severine", "nulla_steven", "porttitor_denise", "massa_georges", "id_gilles", "neque_madeleine",
                         "aliquam_suzanne", "justo_elsa", "enim_valentine", "diam_yves", "vulputate_alexia", "quam_allan", "nulla_aymeric", "porttitor_christopher", "massa_claudine", "id_eloise",
                         "neque_jason", "aliquam_killian", "justo_ryan", "enim_sacha", "diam_vanessa", "vulputate_yoann", "quam_agathe", "nulla_alex", "porttitor_florent", "massa_joel",
                         "id_karine", "neque_marcel", "aliquam_roger", "justo_anaelle", "enim_bernadette", "diam_gisele", "vulputate_henri", "quam_josette", "nulla_margot", "porttitor_aline",
                         "massa_emmanuel", "id_julia", "neque_kelly", "aliquam_louane", "justo_alan", "enim_luc", "diam_magali", "vulputate_andrea", "quam_anne_marie", "nulla_antonin",
                         "porttitor_charline", "massa_melina", "id_michael", "neque_nina", "aliquam_noa", "justo_samantha", "enim_thibaut", "diam_lucile", "vulputate_nolan", "quam_olivia",
                         "nulla_yannick", "porttitor_axelle", "massa_cyril", "id_denis", "neque_laurie", "aliquam_lilian", "nicolas_lea", "theo_thomas", "manon_marie", "kevin_alexandre", "camille_melissa",
                         "maxime_laura", "lucas_alexis", "clement_quentin", "julien_oceane", "anais_julie","hugo_pierre", "pauline_emma", "antoine_chloe", "florian_valentin", "lucie_sarah",
                         "sebastien_marine", "romain_marion", "guillaume_paul", "anthony_jessica", "justine_emilie","nathan_melanie", "benjamin_louis", "elodie_enzo", "jeremy_dylan", "baptiste_mathilde",
                         "maman_michel", "clara_amandine", "vincent_isabelle", "audrey_caroline", "leo_philippe","papa_david", "mathieu_corentin", "daniel_christophe", "aurelie_adrien", "monique_nathalie",
                         "sophie_alain", "amelie_axel", "damien_sandrine", "stephanie_tom", "arthur_maeva","jean_charlotte", "frederic_celine", "stephane_claude", "morgane_patrick", "mathis_noemie",
                         "claire_eric", "laetitia_raphael", "sylvie_dominique", "martine_virginie", "eva_jerome","juliette_pascal", "loic_christine", "romane_francoise", "laurent_olivier", "papy_alicia",
                         "bernard_clemence", "maxence_francois", "mickael_jade", "remi_catherine", "cedric_gabriel","helene_jeanne", "jonathan_lisa", "thierry_aurelien", "christian_coralie", "jacqueline_jules",
                         "andre_jordan", "nicole_alice", "chantal_fabien", "matheo_elise", "valerie_victor","angelique_arnaud", "celia_dorian", "elisa_fanny", "gerard_mamie", "marc_simon",
                         "anne_christelle", "jacques_annie", "maelys_margaux", "alexandra_estelle", "ludovic_ophelie","samuel_veronique", "sylvain_zoe", "bruno_mamy", "aurore_ines", "jean_pierre_louise",
                         "tony_tristan", "benoit_cecile", "erwan_laurine", "matthieu_sandra", "lena_robert","cindy_florence", "jean_claude_yann", "bastien_laurence", "mael_matteo", "ambre_guy",
                         "cassandra_elisabeth", "evan_lola", "franck_jennifer", "maelle_remy", "xavier_fabrice","laure_lilou", "noah_patricia", "thibault_yanis", "corinne_genevieve", "michele_william",
                         "gregory_martin", "charles_cloe", "delphine_simone", "beatrice_ethan", "kylian_rene","brigitte_christiane", "evelyne_francis", "gaelle_sabrina", "didier_dimitri", "edouard_lou",
                         "ludivine_robin", "solene_adeline", "anna_emeline", "herve_leonie", "mathias_bryan","colette_esteban", "gaetan_gwendoline", "severine_steven", "denise_georges", "gilles_madeleine",
                         "suzanne_elsa", "valentine_yves", "alexia_allan", "aymeric_christopher", "claudine_eloise","jason_killian", "ryan_sacha", "vanessa_yoann", "agathe_alex", "florent_joel", "karine_marcel",
                         "roger_anaelle", "bernadette_gisele", "henri_josette", "margot_aline", "emmanuel_julia","kelly_louane", "alan_luc", "magali_andrea", "anne_marie_antonin", "charline_melina",
                         "michael_nina", "noa_samantha", "thibaut_lucile", "nolan_olivia", "yannick_axelle","cyril_denis", "laurie_lilian", "marjorie_myriam", "adam_mireille", "paulette_victoria",
                         "yvette_coline", "jean_baptiste_jimmy", "maurice_roland", "tiffany_titouan", "annick_carole","cathy_etienne", "flavie_joseph", "kilian_morgan", "odette_cynthia", "gabin_gwenaelle",
                         "jean_michel_luna", "noe_serge", "agnes_fabienne", "heloise_jean_francois", "jean_marie_josiane","marina_marius", "mateo_sabine", "therese_alison", "alizee_carla", "daniele_dorothy",
                         "lionel_lise", "salome_dany", "jean_paul_jose", "lorena_rachel", "teddy_jean_luc", "joelle_leane","lydie_matthias", "mylene_nadine", "odile_raymond", "sonia_cassandre", "clarisse_clementine",
                         "emmanuelle_gabrielle", "gaetan_lorenzo", "luca_michelle", "muriel_pascale", "carine_floriane","jacky_jeannine", "loris_maria", "melvin_renee", "tanguy_cynthia", "gaelle_sabrina",
                         "didier_dimitri", "edouard_lou"};

    startTimer();

    // Test de création
    printf("Création\n");
    for (int count = 0 ; count<100 ; count++) {
        p_contact_list newstd = createEmptyList();
        for (int i = 0; i < 1001; i++) {
            p_contact newcontact = createContact(liste[i]);
            insertContact(newstd, newcontact);
        }
        free(newstd);
    }
    stopTimer();
    displayTime();
    startTimer();
    for (int count = 0 ; count<100 ; count++) {
        p_contact_list newdtc = createEmptyList();
        for (int i = 0; i < 1001; i++) {
            p_contact newcontact = createContact(liste[i]);
            insertContact_dtc(newdtc, newcontact);
        }
        free(newdtc);
    }
    stopTimer();
    displayTime();

    // Test de recherche

    srand(542);
    p_contact_list new = createEmptyList();
    for (int i = 0; i < 998; i++) {
        p_contact newcontact = createContact(liste[i]);
        insertContact_dtc(new, newcontact);
    }

    int random;
    printf("Recherche\n");
    startTimer();
    for (int i = 0 ; i<100000 ; i++) {
        random = (int) rand();
        random %= 980;
        searchContact(liste[random], new);
    }
    stopTimer();
    displayTime();
    startTimer();
    for (int i = 0 ; i<100000 ; i++) {
        random = (int) rand();
        random %= 980;
        searchContact_dtc(new ,liste[random]);
    }
    stopTimer();
    displayTime();
    return new;





    return NULL;
}

p_contact_list createExempleList2(int showstep) {
    p_contact_list new = createEmptyList();
    p_contact c1 = createContact("flamel_stephanie");
    p_contact c2 = createContact("gallouin_alexandre");
    p_contact c3 = createContact("garnier_alexandra");
    p_contact c4 = createContact("gartner_stef");
    p_contact c5 = createContact("grandin_lia");
    p_contact c6 = createContact("gruss_stephane");
    p_contact c7 = createContact("guetta_david");
    p_contact c8 = createContact("humbert_dave");
    p_contact c9 = createContact("zerator_charlotte");
    p_contact c10 = createContact("picou_thomas");
    insertContact(new, c3);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c1);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c2);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c8);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c7);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c6);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c5);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c4);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c9);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    return new;

}

p_contact_list createExempleList3(int showstep) {
    p_contact_list new = createEmptyList();
    p_contact c1 = createContact("flamel_stephanie");
    p_contact c2 = createContact("gallouin_alexandre");
    p_contact c3 = createContact("garnier_alexandra");
    p_contact c4 = createContact("gartner_stef");
    p_contact c5 = createContact("grandin_lia");
    p_contact c6 = createContact("gruss_stephane");
    p_contact c7 = createContact("guetta_david");
    p_contact c8 = createContact("humbert_dave");
    p_contact c9 = createContact("zerator_charlotte");
    p_contact c10 = createContact("picou_thomas");
    insertContact_dtc(new, c1);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c2);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c3);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c4);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c5);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c6);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c7);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c8);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c9);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    createAppointmentList(c1);
    testRemoveAppointment(c1);
    createAppointmentList(c1);
    return new;

}




