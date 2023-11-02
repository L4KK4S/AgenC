/*
    |----------------------------------------------------------|
    |     This file contains the structures and prototype      |
    |                needed for the contacts                   |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#include "appointment.h"


// -------------------------- Structures --------------------------

#ifndef AGENC_CONTACT_H
#define AGENC_CONTACT_H

typedef struct s_contact_list {                                    // Structure for a list of contacts
    int max_levelsL;                                               // Stock max level of the list (here it's 4 all the time)
    struct p_contact *levels;                                      // Stock a tab of the different head levels
}t_contact_list;

typedef struct s_contact_list t_contact_list, *p_contact_list;     // Create an alias to allow using p for designing pointer


struct s_contact {                                                 // Structure for a contact
    char* name;                                                    // Stock the name of the contact in the correct format
    struct s_contact **levels;                                     // Stock a tab linking all next contact that have common letter
    p_appointment head;                                            // Stock the head of the appointment list
};

typedef struct s_contact t_contact, *p_contact;                   // Alias to allow using p to design the pointer to contact



// -------------------------- Prototypes --------------------------

int compareStrings( char *a, char *b);
p_contact createContact(char* name);                                // Create a new contact
p_contact searchContact(char* contact);

#endif //AGENC_CONTACT_H


