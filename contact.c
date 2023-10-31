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

int getmatch(char* name) {
    return 0;
}

p_contact createContact(char* name) {
    p_contact new = (p_contact) malloc (sizeof(p_contact));
    new->levels = (p_contact*) malloc (getmatch(name)*sizeof(p_contact));
    new->name = name;
    return new;
}
