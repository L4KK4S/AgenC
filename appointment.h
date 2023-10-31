/*
    |----------------------------------------------------------|
    |     This file contains the structures and prototype      |
    |                needed for the appointments               |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#ifndef AGENC_APPOINTMENT_H
#define AGENC_APPOINTMENT_H

typedef struct s_date {
    int day;
    int month;
    int years;
}t_date;

struct s_rdv {
    int hour;
    int time;
    char* object;
    t_date date;
};

typedef struct s_rdv t_rdv, *p_rdv;

struct s_contact {
    char* name;
    struct s_contact **levels;
    p_rdv head;
};

typedef struct s_contact t_contact, *p_contact;

// -------------------------- Structures --------------------------

#endif //AGENC_APPOINTMENT_H
