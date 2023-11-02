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

struct s_contact {                                                 // Structure for a contact
    char* name;                                                    // Stock the name of the contact in the correct format
    struct s_contact **levels;                                     // Stock a tab linking all next contact that have common letter
    p_appointment head;                                            // Stock the head of the appointment list
};

typedef struct s_contact t_contact, *p_contact;                   // Alias to allow using p to design the pointer to contact

typedef struct s_contact_list {                                    // Structure for a list of contacts
    int max_levels;                                               // Stock max level of the list (here it's 4 all the time)
    p_contact *levels;                                             // Stock a tab of the different head levels
}t_contact_list;

typedef struct s_contact_list t_contact_list, *p_contact_list;     // Create an alias to allow using p for designing pointer



// -------------------------- Prototypes --------------------------

p_contact_list createEmptyList();
int compareString( char *, char *);                                 // Compare 2 string and return if the string to place has to be place after or before
p_contact createContact(char*);                                     // Create a new contact
p_contact searchContact(char*, p_contact_list);                     // Search a contact in a contact list
void change_maj_to_min(char*);                                      // Transform all maj to min in a str
void insertAppointment(p_contact, p_appointment);                   // Insert a new appointment in a chained list
char* CheckNameEntry();                                             // Secure entry to attribute the name of a contact
int getMatch(p_contact, p_contact);
int getMatchtest(char* prev, char* new);
p_appointment createAppointment (p_contact_list);                   // Create a new appointment, sort it in the appointment list and attribute it to a contact (can create contact)
void insertContact(p_contact_list, p_contact);
void display_contact_list (p_contact_list list);
void uniform_display_contact_list (p_contact_list list);
int getLevel(p_contact_list list, p_contact search);

p_contact_list createExempleList1();
p_contact_list createExempleList2();


#endif //AGENC_CONTACT_H


