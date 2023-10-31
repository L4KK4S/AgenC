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

typedef struct s_contact_list t_contact_list, *p_contact_list;

typedef struct s_contact {
    struct p_contact *levels;
    char* name;
}t_contact;

typedef struct s_contact t_contact, *p_contact;



// -------------------------- Structures --------------------------

int compareStrings( char *a, char *b);
p_contact createContact(char* name);

#endif //AGENC_CONTACT_H


