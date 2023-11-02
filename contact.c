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

p_contact searchContact(char* contact) {
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

int transformName(p_contact contact) {
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
                return -1;
            }
        }
        if (space_counter != 1) {
            printf("too much space\n");
            free(input);                                                                                                                 // Memory Optimization by freeing allocated memory
            free(res);                                                                                                                   // Memory Optimization by freeing allocated memory
            free(name);                                                                                                                  // Memory Optimization by freeing allocated memory
            free(surname);                                                                                                               // Memory Optimization by freeing allocated memory
            free(temp);                                                                                                                  // Memory Optimization by freeing allocated memory
            return -1;
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
        contact->name = res;                                                                                                             // Attributing the contact to the correct variable in the structure
        free(input);                                                                                                                     // Memory Optimization by freeing allocated memory
        free(name);                                                                                                                      // Memory Optimization by freeing allocated memory
        free(surname);                                                                                                                   // Memory Optimization by freeing allocated memory
        free(temp);                                                                                                                      // Memory Optimization by freeing allocated memory
        return 0;

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
        return -1;
    }
}

p_appointment createAppointment () {
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
    toAssign = searchContact(input);
    if (toAssign!=NULL) {
        insertAppointment(toAssign->head, new);
    } else {
        createContact(input);
        insertAppointment(toAssign->head, new);
    }





    return new;                                                                         // Return the new appointment

}