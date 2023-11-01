/*
    |----------------------------------------------------------|
    |              This file contains the functions            |
    |                   used on the contacts                   |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#include "contact.h"
#include <stdlib.h>

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
