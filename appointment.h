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

typedef struct s_time {
    int hours;
    int minutes;
} t_time;

struct s_appointment {
    t_time hour;
    t_time time;
    char* object;
    t_date date;
};

typedef struct s_appointment t_appointment, *p_appointment;

struct s_contact {
    char* name;
    struct s_contact **levels;
    p_appointment head;
};

typedef struct s_contact t_contact, *p_contact;

// -------------------------- Structures --------------------------

int checkDateFormat(p_appointment new_appointment);
p_appointment createAppointment ();

#endif //AGENC_APPOINTMENT_H
