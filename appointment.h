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
    struct s_appointment *next;                                         // Chained list of appointment
};

typedef struct s_appointment t_appointment, *p_appointment;             // Creating an alias for pointer to structure appointment


// -------------------------- Structures --------------------------

p_appointment createEmptyAppointment();
char* deleteLastChar(char* input);                          // Delete the last char from an input and return it
int checkDateFormat(p_appointment);                         // Secure entry for the date
int checkHourFormat(p_appointment);                         // Secure entry for the time
int checkLengthAppointmentFormat(p_appointment);            // Secure entry for the length of an appointment
int checkLengthObject(p_appointment);                       // Secure entry for the object of an appointment + delete the \n
int compareDate(p_appointment, p_appointment);              // Compare the date of 2 appointments

#endif //AGENC_APPOINTMENT_H