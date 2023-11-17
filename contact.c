/*
    |----------------------------------------------------------|
    |              This file contains the functions            |
    |                   used on the contacts                   |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#include "contact.h"
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
        if (compareString(prev->name, new->name)==1 && tmp==NULL) {                                                                   // End insertion case
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
        printf("Contact non trouvé.\n");
    }

    printf("Contact: %s\n", contact->name);                                                                             // Print the contact name
    p_appointment tmp = contact->head;                                                                                  // Set the cursor to the first appointment
    p_appointment prev = tmp;                                                                                           // Set the prev to the tmp

    if (tmp == NULL) {                                                                                                  // Case where is no appointment
        printf("No appointment in this agenda\n\n");
    } else {                                                                                                            // Case where there is some appointment
        while (tmp!=NULL) {                                                                                             // Loop to go through all appointment
            if (compareDate(prev , tmp) == 1 || compareDate(prev , tmp) == -1 || prev == tmp) {                         // If the Year is different or the It's the first cell we print the year
                printf("======== %d ========\n", tmp->date.years);
            }
            if (compareDate(prev , tmp) >= -3 && compareDate(prev , tmp) <= 3 || prev == tmp) {                         // If the date has changed, we print the date
                printf("\n");
                detectZero(tmp->date.day);                                                                           // If the number if one digit we print the silent 0
                printf("/");
                detectZero(tmp->date.month);                                                                         // If the number if one digit we print the silent 0
                printf("\n");
            }
            printf("Time : %d", tmp->hour.hours);                                                                       // We always print the time
            printf("h");
            detectZero(tmp->hour.minutes);                                                                           // We always print the length with the silent 0
            printf(", Length : %d", tmp->length.hours);
            printf("h");
            detectZero(tmp->length.minutes);                                                                         // We always print the minutes with silent 0
            printf(", Object : %s", tmp->object);                                                                       // We print the object
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

}

int removeAppointment(p_contact contact, char* objectToRemove) {                         // VARIABLES UNFREE
    if (contact == NULL || objectToRemove == NULL) {                                     // If there wasn't any object to remove or contact
        return 0;
    }

    p_appointment temp = contact->head;                                                  // Set a pointer to the first appointment of the list
    p_appointment prev = NULL ;                                                          // Set a prev to NULL

    while (temp != NULL) {                                                               // Loop to go through all cells
        if (strcmp(temp->object, objectToRemove) == 0) {                                 // Check is object is the same as the one searched
            if (prev == NULL) {                                                          // If prev == NULL, it means we remove the head
                contact->head = temp->next;                                              // We relink the list
            } else {
                prev->next = temp ->next;                                                // Relink the list if it's in middle or end
            }
            free(temp->object);                                                          // Free the object
            free(temp);                                                                  // Free the removed cell
            return 1;                                                                    // Return 1 if successful
        }

        prev = temp;                                                                     // Increment the prev
        temp = temp ->next;                                                              // Increment the tmp
    }

    return 0;                                                                           // Return 0 if unsuccessful
}



// -------------------------- Tests Functions --------------------------


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
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c2);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c3);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c4);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c5);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c6);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c7);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact(new, c8);
    uniform_display_contact_list(new);
    printf("\n\n");
    return new;

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
    insertContact_dtc(new, c3);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c2);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c8);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c7);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c6);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c5);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c4);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    insertContact_dtc(new, c9);
    if (showstep==1) {
        uniform_display_contact_list(new);
        printf("\n\n");
    }
    return new;

}