/*
    |----------------------------------------------------------|
    |     This file contains the structures and prototype      |
    |                needed for the appointments               |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#ifndef AGENC_APPOINTMENT_H
#define AGENC_APPOINTMENT_H

typedef struct s_date {                                                 // Structure for a date
    int day;                                                            // Int to stock the day
    int month;                                                          // Int to stock the month
    int years;                                                          // Int to stock the years
}t_date;

typedef struct s_time {                                                 // Structure for the time
    int hours;                                                          // Int that stock the hours
    int minutes;                                                        // Int that stock the minutes
} t_time;

struct s_appointment {                                                  // Structure of an appointment
    t_time hour;                                                        // Hours of the appointment
    t_time length;                                                      // Length of the appointment
    char* object;                                                       // Object of the appointment
    t_date date;                                                        // Date of the appointment
};

typedef struct s_appointment t_appointment, *p_appointment;             // Creating an alias for pointer to structure appointment



// -------------------------- Structures --------------------------

int checkDateFormat(p_appointment new_appointment);                         // Secure entry for the date
int checkHourFormat(p_appointment new_appointment);                         // Secure entry for the time
int checkLengthAppointmentFormat(p_appointment new_appointment);            // Secure entry for the length of an appointment
p_appointment createAppointment ();                                         // Create a new appointment


#endif //AGENC_APPOINTMENT_H
