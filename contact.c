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
        if ( strlen(cursor) == strlen(toplace)) {                                      // We check if length are the same, meaning that str would be same
            return 0;
        } else if (i < strlen(cursor)) {                                                // If i is inferior to the length of the first string, mean both string are almost same but s2 a1 as more characters
            return 1;                                                                        // In this case we want to place the string after the one with more elements
        } else {
            return -1;                                                                       // Else we place it before
        }
    }
}

p_contact createContact(char* name) {
    // Allocate memory
    // Create an empty chained list of appointment
    // Verify name
    // Convert Name to the correct format
    // Loop to search where to insert it with compare string
    // When place found check correspondance with previous and next contact
    // Allocate memory and create tab for stocking next adress at different levels
    // Link correctly the different levels
    // return the new contact
}

p_contact searchContact(char* search, p_contact_list list) {
    p_contact tmp = list->levels[0];
    while (tmp!=NULL) {
        if (compareString(tmp->name, search)==0) {
            return tmp;
        }
        tmp = tmp->levels[0];
    }
    return NULL;
}

void change_maj_to_min( char *s) {
    for (int i = 0; s[i] != '\0'; i++) {                       // Loop to go through all characters
        if (s[i] >= 'A' && s[i] <= 'Z') {                      // if the character is a majuscule
            s[i] = s[i] + 32;                                  // Convert to min
        }

    }
}

void insertAppointment(p_contact contact, p_appointment cell) {
    p_appointment tmp = contact->head, prev = tmp;                                                                                              // Create pointer to go through the list

    if (tmp==NULL) {                                                                                                                                // Case where the list is empty
        contact->head = cell;                                                                                                                       // We asign the head of the contact list
    } else if ((tmp->hour.hours > cell->hour.hours) || (tmp->hour.hours == cell->hour.hours && tmp->hour.minutes >= cell->hour.minutes)) {          // Head insertion case
        cell->next = tmp;                                                                                                                           // We asign the next of the new cell to the previous head
        contact->head = cell;                                                                                                                       // We update the head
    } else {
        while (tmp->hour.hours < cell->hour.hours && tmp->next != NULL) {                                                                           // Loop to search the hours spot to insert or the end of the list
            prev = tmp;                                                                                                                             // Move prev to last value of tmp
            tmp = tmp->next;                                                                                                                        // Update tmp
        }
        while (tmp->hour.hours == cell->hour.hours && tmp->hour.minutes < cell->hour.minutes && tmp->next != NULL) {                                // Loop to search if we arent at the end of the list the good spot for the minute
            prev = tmp;                                                                                                                             // Move prev to last value of tmp
            tmp = tmp->next;                                                                                                                        // Update tmp
        }
        if (tmp->next==NULL) {                                                                                                                      // If tmp is NULL = we're at the end of the list, we have to identify if we insert at the end or just before
            if (tmp->hour.hours < cell->hour.hours || (tmp->hour.hours == cell->hour.hours && tmp->hour.minutes < cell->hour.minutes)) {            // If the hours is superior or the hours is the same but minutes are superior wer have to insert at the end
                tmp->next = cell;
            } else if (tmp->hour.hours > cell->hour.hours || (tmp->hour.hours == cell->hour.hours && tmp->hour.minutes >= cell->hour.minutes)) {    // If the hours is inferior or the hours is the same but the minutes are inferior or equal we insert just before the end cell (between prev and tmp)
                prev->next = cell;                                                                                                                  // We update the next of the prev cell
                cell->next=tmp;                                                                                                                     // We update the next of the cell to tmp
            }
        } else {                                                                                                                                    // If we weren't at the end of the list, it means we already have found the sweet spot between prev and tmp
            prev->next = cell;                                                                                                                      // We update the next of the prev value to the cell
            cell->next = tmp;                                                                                                                       // We update the next of the cell to the tmp
        }
    }
}

char* CheckNameEntry() {
    char* input = (char*) malloc(100*sizeof(char));                                                                                 // Allocate memory for the input
    char* name = (char*) malloc(100*sizeof(char));                                                                                  // Allocate memory for the name
    char* surname = (char*) malloc(100*sizeof(char));                                                                               // Allocate memory for the surname
    char* temp = (char*) malloc(100*sizeof(char));                                                                                  // Allocate memory for the temp
    char* res = (char*) malloc(100*sizeof(char));                                                                                   // Allocate memory for the answer
    printf("~> ");
    fgets(input, 100, stdin);                                                                                                            // Get the input
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
                free(input);                                                                                                             // Memory Optimization by freeing allocated memory
                free(res);                                                                                                               // Memory Optimization by freeing allocated memory
                free(name);                                                                                                              // Memory Optimization by freeing allocated memory
                free(surname);                                                                                                           // Memory Optimization by freeing allocated memory
                free(temp);                                                                                                              // Memory Optimization by freeing allocated memory
                return NULL;
            }
        }
        if (space_counter != 1) {
            printf("too much space\n");
            free(input);                                                                                                                 // Memory Optimization by freeing allocated memory
            free(res);                                                                                                                   // Memory Optimization by freeing allocated memory
            free(name);                                                                                                                  // Memory Optimization by freeing allocated memory
            free(surname);                                                                                                               // Memory Optimization by freeing allocated memory
            free(temp);                                                                                                                  // Memory Optimization by freeing allocated memory
            return NULL;
        }

        i = 0, space_counter = 0;                                                                                                        // If the entry is correct we restart the counter to analyse the differents arguments
        while (input[i+1]!='\0') {                                                                                                       // Loop to go through all elements
            temp[0] = input[i];                                                                                                          // Add a character to the temp
            if (input[i] == ' ') {                                                                                                       // If the character is a space we only increment the counter
                space_counter++;
            } else if (space_counter == 0) {                                                                                             // Case where we didn't pass the space, mean current character is part of the surname
                strcat(surname, temp);
            } else {                                                                                                                     // Case where we didn't pass the space, mean current character is part of the surname
                strcat (name, temp);
            }
            i++;
        }
        strcat(res, name);                                                                                                               // We create the result by adding the name first
        strcat(res, "_");                                                                                                                // We create the result by adding the underscore
        strcat(res, surname);                                                                                                            // We create the result by adding the surname
        change_maj_to_min(res);                                                                                                       // Converting the string to small characters
        free(input);                                                                                                                     // Memory Optimization by freeing allocated memory
        free(name);                                                                                                                      // Memory Optimization by freeing allocated memory
        free(surname);                                                                                                                   // Memory Optimization by freeing allocated memory
        free(temp);                                                                                                                      // Memory Optimization by freeing allocated memory
        return res;

    } else {
        if (input[strlen(input)-2]==' ') {
            printf(" input -2 == space\n");
        } else {
            printf("input too short");
        }
        free(input);                                                                                                                    // Memory Optimization by freeing allocated memory
        free(res);                                                                                                                      // Memory Optimization by freeing allocated memory
        free(name);                                                                                                                     // Memory Optimization by freeing allocated memory
        free(surname);                                                                                                                  // Memory Optimization by freeing allocated memory
        free(temp);                                                                                                                     // Memory Optimization by freeing allocated memory
        return NULL;
    }
}

int getMatch(p_contact prev, p_contact new) {
    int match = 0;
    while (prev->name[match]==new->name[match] && match<4 && prev->name[match]!='\0' && new->name[match]!='\0') {
        match++;
    }
    return 4-match;
}

int getMatchtest(char* prev, char* new) {
    int match = 0;
    while (prev[match]==new[match] && match<3 && prev[match]!='\0' && new[match]!='\0') {
        match++;
    }
    return 4-match;
}

p_appointment createAppointment (p_contact_list liste) {
    char* input = (char*) malloc(100*sizeof(char));                                // Str variable to stock the input
    p_contact toAssign;                                                                 // Pointer to check if the contact already exist or not
    int checkFormat = -1;                                                               // Variable to check argument are correct
    p_appointment new = (p_appointment) malloc (sizeof(p_appointment));            // Allocate the memory for the new appointment

    new->next=NULL;

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

    printf("\nWhat's the object of your appointment ( < 100 characters) ?\n\n ");       // Asking for the contact to assign the appointment
    printf("~> ");
    fgets(input, 100, stdin);
    input = NULL;
    while (input==NULL) {
        input = CheckNameEntry();
    }
    toAssign = searchContact(input, liste);
    // check if input is correct and transform it
    if (toAssign!=NULL) {
        insertAppointment(toAssign, new);
    } else {
        createContact(input);
        toAssign = searchContact(input, liste);
        insertAppointment(toAssign, new);
    }

    return new;                                                                         // Return the new appointment

}

void insertContact(p_contact_list list, p_contact new) {
    int leveltolink, rebuild = 1;                                                                           // Set a variable to count how many level we'll have to link
    p_contact tmp = list->levels[0], rebuild_tmp;                                                           // Set the cursor to the head of level 0
    p_contact prev = tmp;                                                                                   // Set the previous cursor to the tmp
    if (list->levels[0]==NULL) {                                                                            // Case where level is empty
        new->levels = (p_contact*) malloc (4*sizeof(p_contact));                                       // Create a tab of 4 elements for the new cell
        for (int i = 0 ; i<4 ; i++) {                                                                       // Loop to set the head of each level to the cell
            list->levels[i]=new;
        }
    } else {
        while (compareString(tmp->name, new->name) == 1 && tmp!=NULL) {                       // Loop to place the cursor either at the end or just after the right place
            prev = tmp;
            tmp = tmp->levels[0];                                                                           // Move the cursor on level 0
        }
        if (tmp == list->levels[0]) {                                                                       // Case where we have to do a head insertion
            leveltolink = 4;                                                                                // Set the level to 4
            new->levels = (p_contact *) malloc(leveltolink * sizeof(p_contact));                       // Allocate the memory for the levels tab
            new->levels[0]= tmp;                                                                            // Set the next of the new head
            list->levels[0] = new;                                                                          // Update the head
        } else {                                                                                            // Case where the cursor isn't the head
            leveltolink = getMatch(prev, new);                                                              // Use getmatch to know the size of the tab we have to create
            new->levels = (p_contact *) malloc(leveltolink * sizeof(p_contact));                       // Allocate the memory for the levels tab
            prev->levels[0] = new;                                                                          // Update the next of the previous cell
            new->levels[0] = tmp;                                                                           // Set the next of the new cell to the cursor (work even if NULL)
        }
        if (tmp!=NULL) {                                                                                    // If we had to insert the cell between two other cells
            rebuild = getMatch(new, tmp);                                                        // We set the rebuild variable to the new size of the tab of tmp cell
            p_contact* newtab = (p_contact *) malloc(rebuild * sizeof(p_contact));                     // We allocate the memory for the new tab
            for (int i = 1 ; i<rebuild ; i++) {                                                             // Loop to set all of the newtab cells
                newtab[i] = tmp->levels[i];                                                                 // We copy the adress that are on the common level
            }
            for (int i = rebuild ; i<getMatch(prev, tmp) ; i++) {                                      // Loop to rematch all unused level
                rebuild_tmp = list->levels[i];                                                              // Set a cursor to the head of the level
                while (rebuild_tmp->levels[i]!=tmp) {                                                       // Loop to rematch cell that were pointing on the deleted level of the tmp
                    rebuild_tmp = rebuild_tmp->levels[i];                                                   // While the pointer wasn't pointing on the tmp we move forward
                }
                rebuild_tmp->levels[i] = new;                                                               // Set the pointer of the level to the new cell
                new->levels[i] = tmp->levels[i];                                                            // Adress that haven't been copied are match to the new cell

            }
            free(tmp->levels);                                                                              // Free the old tab
            tmp->levels = newtab;                                                                           // Attribute the new tab
        }

        for (int i = 1; i<rebuild ; i++) {                                                                  // Loop to match other levels adresses
            tmp = list->levels[i];                                                                          // Reset the cursor to the head of the current level
            prev = tmp;                                                                                     // Reset the previous pointer
            while (compareString(tmp->name, new->name) == 1 && tmp!=NULL) {                   // Loop to place the cursor either at the end or just after the right place
                prev = tmp;
                tmp = tmp->levels[i];                                                                       // Moving the cursor on the current level
            }
            if (tmp == list->levels[i]) {                                                                   // Case where we need a head insertion
                new->levels[i]= tmp;                                                                        // Set the next of the new cell to the previous head of the level
                list->levels[i] = new;                                                                      // Set the new head of the level to the new cell
            } else {                                                                                        // Case where the cursor is just after the right place
                prev->levels[i] = new;                                                                      // Set the prev next to the new cell
                new->levels[i] = tmp;                                                                       // Set the next of the new cell to the tmp (work even if NULL)
            }
        }
    }
}