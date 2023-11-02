/*
    |---------------------------------------------------------------|
    |                                                               |
    |              Main program of the project: AgenC               |
    |   made by Abdel-Waheb Sakkal & Thomas Picou & Maryam Georgi   | 
    |                                                               |                   
    |---------------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include "cell.c"
#include "list.h"
#include "list.c"
#include "menu.h"
#include "menu.c"
#include "appointment.c"

// ------------------------- Main loop --------------------------

int main() {

    printf("\nWelcome to AgenC, please type a command or type help if needed :\n\n");

    //mainloop1();
    p_appointment new = createAppointment();
    printf("%d %d %d\n", new->date.day, new->date.month, new->date.years);
    printf("%dh%d\n", new->hour.hours, new->hour.minutes);
    printf("%dh%d\n", new->length.hours, new->length.minutes);
    printf("%s\n", new->object);



    return 0;
 
}
