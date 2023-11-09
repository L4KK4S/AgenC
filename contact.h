/*
    |----------------------------------------------------------|
    |     This file contains the structures and prototype      |
    |                needed for the contacts                   |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#include "appointment.h"
#include "menu.h"

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

// 1) Simple Action functions

int compareString( char *, char *);                                 // Compare 2 string and return if the string to place has to be placed after or before
char* change_maj_to_min(char*);                                     // Change maj to min and return the result
int getMatch(p_contact, p_contact);                                 // Return the size of element to allocate memory depending on the number of matching letter
int getLevel(p_contact_list, p_contact);                            // Get the level of a contact in the list
int compareDate(p_appointment, p_appointment);                      // Compare the date of 2 appointments
char* formatString(char* input);                                    // Transform a correct unformat string to a format string
char* unformatString(char* input);                                  // Transform a correct format string to an unformat string
char* checkNameEntry(char* input);                                  // Check has the correct format (only letter and 1 space)

// 2) Manipulation of Contact Structure

p_contact_list createEmptyList();                                   // Create an empty contact List
p_contact createContact(char*);                                     // Create a new contact
p_contact searchContact(char*, p_contact_list);                     // Search a contact in a contact list
void insertContact(p_contact_list, p_contact);                      // Insert contact while keepîng the list ordered

// 3) Manipulation of Appointment Structure (related with contact)

p_appointment createAppointment (p_contact_list);                   // Create a new appointment, sort it in the appointment list and attribute it to a contact (can create contact)
void insertAppointment(p_contact, p_appointment);                   // Insert a new appointment in a chained list

// 4) Display Functions

void display_contact_list (p_contact_list list);                    // Display the list in a standard way
void uniform_display_contact_list (p_contact_list list);            // Display the list and keep cells align
void testDisplayAppointment (p_contact);


// -------------------------- Test Functions --------------------------

p_contact_list createExempleList1(int);                             // Test list
p_contact_list createExempleList2(int);                             // Exemple list from the part 3 + repetitive element


#endif //AGENC_CONTACT_H