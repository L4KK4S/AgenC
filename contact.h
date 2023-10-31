/*
    |----------------------------------------------------------|
    |     This file contains the structures and prototype      |
    |                needed for the contacts                   |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#ifndef AGENC_CONTACT_H
#define AGENC_CONTACT_H

typedef struct s_contact_list {
    int max_levelsL;
    struct p_contact *levels;
}t_contact_list;

// -------------------------- Structures --------------------------

int compareStrings( char *a, char *b);

#endif //AGENC_CONTACT_H


