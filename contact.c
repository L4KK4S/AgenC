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

    if (input[strlen(input)-2]!=' ' && strlen(input)>= 4) {                                                                        // Check if the input is not ending with a space and have the minimum require length
        while (input[i+1] != '\0') {                                                                                                     // Check all characters of the input
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
            printf("too much space\n");
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
        if (input[strlen(input)-2]==' ') {
            printf(" input -2 == space\n");
        } else {
            printf("input too short");
        }
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
            printf("found\n");
            return tmp;                                                                 // If we have find the cell we return the adress
        }
        tmp = tmp->levels[0];
    }
    printf("not existing\n");
    free(tmp);
    return NULL;                                                                        // If we haven't find the cell we return 0
}

void insertContact(p_contact_list list, p_contact new) {
    int rebuild = 1;                                                                                                                           // Set a variable to count the number of element of the different rebuild tab
    p_contact tmp = list->levels[0], rebuild_tmp;                                                                                              // Create some pointer to use as cursor
    p_contact prev = tmp;                                                                                                                      // Set the previous cursor to the tmp

    if (list->levels[0]==NULL) {                                                                                                               // Case where level is empty
        p_contact* levels = (p_contact*) malloc (4*sizeof(p_contact));                                                                          // Create a tab of 4 elements for the new cell
        for (int i  = 0 ; i<4 ; i++) {
            levels[i]=NULL;
        }
        new->levels = levels;
        for (int i = 0 ; i<4 ; i++) {                                                                                                          // Loop to set the head of each level to the cell
            list->levels[i]=new;
        }
        tmp = NULL;
        prev = NULL;
        rebuild_tmp = NULL;
        free(rebuild_tmp);
        free(tmp);
        free(prev);
        return;
    } else {                                                                                                                                    // Case the tab is not empty
        if (compareString(tmp->name, new->name)==-1) {                                                                            // Case head insertion
            p_contact* levels = (p_contact*) malloc (4*sizeof(p_contact));                                                                          // Create a tab of 4 elements for the new cell
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
            tmp = NULL;
            prev = NULL;
            rebuild_tmp = NULL;
            free(rebuild_tmp);
            free(tmp);
            free(prev);
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
                tmp = NULL;
                prev = NULL;
                rebuild_tmp = NULL;
                free(rebuild_tmp);
                free(tmp);
                free(prev);
                return;
            } else if (compareString(tmp->name, new->name) == -1 || compareString(tmp->name, new->name) == 0) {      // Case where we have to insert it in the middle (either an element already existing or not)
                p_contact* levels = (p_contact*) malloc (getMatch(prev, new)*sizeof(p_contact));                                                   // Allocating memory
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
                    tmp = NULL;
                    prev = NULL;
                    rebuild_tmp = NULL;
                    free(rebuild_tmp);
                    free(tmp);
                    free(prev);
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
                    tmp = NULL;
                    prev = NULL;
                    rebuild_tmp = NULL;
                    free(rebuild_tmp);
                    free(tmp);
                    free(prev);
                }
            }
        }
    }
}


// 3) Manipulation of Appointment Structure (related with contact)

p_appointment createAppointment (p_contact_list liste) {
    char* input = (char*) malloc(50*sizeof(char));                                // Str variable to stock the input
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
    printf("\nHow long is your new appointment {0-23}h{0-59} ?\n\n ");                  // Asking fir the length of the appointment

    do {                                                                                // Loop to ask while answer is not in the correct format or impossible
        checkFormat = checkLengthAppointmentFormat(new);
    } while (checkFormat == -1);
    checkFormat =-1;

    printf("\nWhat's the object of your appointment ( < 100 characters) ?\n\n ");       // Asking for the object of the appointment
    do {
        checkFormat = checkLengthObject(new);
    } while (checkFormat == -1);

    printf("cell before inserting in contact : ");
    testPrintAppointment(new);
    printf("\n");

    printf("Please enter a contact to assign or create :\n\n");
    do {
        input = autoCompletion(liste);
    } while (input==NULL);

    printf("input : %s\n", input);

    toAssign = searchContact(input, liste);

    // check if input is correct and transform it
    if (toAssign==NULL) {
        printf("creating contact\n");
        toAssign = createContact(input);
        insertContact(liste, toAssign);
        toAssign = searchContact(input, liste);
    }
//    printf("\n");
//    uniform_display_contact_list(liste);
//    printf("\n");
    insertAppointment(toAssign, new);
    testDisplayAppointment(toAssign);
    return new;                                                                         // Return the new appointment

}

void insertAppointment(p_contact contact, p_appointment cell) {
    p_appointment tmp = contact->head  ;
    p_appointment prev = tmp;

    if (contact->head==NULL) {
        printf("empty insertion\n");
        contact->head = cell;
        return;
    } else if (compareDate(cell, tmp) == -1) {
        printf("head insertion\n");
        cell->next = contact->head;
        contact->head = cell;
        return;
    } else {
        printf("comparison : %d\n", compareDate(cell, tmp));
        while (compareDate(cell, tmp)!=-1 && tmp->next!=NULL) {
            printf("loop\n");
            prev = tmp;
            tmp = tmp->next;
        }
        if (compareDate(cell, tmp)==-1) {
            printf("mid insertion\n");
            prev->next = cell;
            cell->next = tmp;
            return;
        } else {
            printf("end insertion\n");
            tmp->next = cell;
            return;
        }
    }
}


// 4) Display Functions

void display_contact_list (p_contact_list list) {
    for (int i = 0 ; i<list->max_levels ; i++) {                               // Loop which stop when all level are printed (<=)
        printf("[list head_%d @-]",i);                                         // Special printing for the head of the list
        p_contact tmp_h = list->levels[i];                                     // Set the moving pointer to the head of the level
        while (tmp_h!=NULL){
            printf("-->[ %s|@-]", tmp_h->name);                                // Special print for the cell
            tmp_h = tmp_h->levels[i];                                          // Incrementing the moving pointer
        }
        printf("-->NULL\n");                                                   // Special print to indicate the end of the level list
        free(tmp_h);
        return;
    }
}

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

void testDisplayAppointment (p_contact contact) {
    if (contact->head!=NULL) {
        p_appointment tmp = contact->head;
        while (tmp != NULL) {
            testPrintAppointment(tmp);
            tmp = tmp->next;
        }
        free(tmp);
    } else {
        printf("empty list\n");
    }
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
    //insertContact(new, c10);
    //uniform_display_contact_list(new);
    printf("\n\n");
    return new;

}