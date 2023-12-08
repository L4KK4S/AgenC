/*
    |----------------------------------------------------------|
    |     This file contains the functions about files         |
    |                                                          |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------#
#include "file.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 1000




void save_file(p_contact_list all_contact){

    // open a file for writing
    FILE *file = fopen("data.txt", "w");
    char* tmp_line;

    // check if the file was opened successfully
    if (file == NULL) {
        printf("ERROR: can't open the file\n");
        return;
    }

    // if the agenda didn't contains contact
    if (all_contact == NULL) {
        printf("ERROR: Your agenda is empty\n");
        return;
    }

    // create a tmp contact to browse the agenda
    p_contact current_contact = all_contact->levels[0];

    // browse the agenda
    while(current_contact != NULL){

        // write the name of the contact
        fprintf(file, "%s", current_contact->name);
        if (current_contact->head != NULL) {
            p_appointment tmp = current_contact->head;
            while (tmp!=NULL) {
                fprintf(file, ":%d/%d/%d/%d/%d/%d/%d/%s", tmp->date.day, tmp->date.month, tmp->date.years, tmp->hour.hours, tmp->hour.minutes, tmp->length.hours, tmp->length.minutes, tmp->object);
                tmp = tmp->next;
            }
        }

        // go to the next contact
        current_contact = current_contact->levels[0];
        fprintf(file, ";\n");
    }

    // close the file
    fclose(file);

    return;

}

p_contact_list load_file() {

    char* object = (char*) malloc(20*sizeof(char));                                                                            // Allocate memory for the name
    char* day = (char*) malloc(20*sizeof(char));                                                                         // Allocate memory for the surname
    char* month = (char*) malloc(15*sizeof(char));                                                                            // Allocate memory for the temp
    char* years = (char*) malloc(20*sizeof(char));                                                                             // Allocate memory for the answer
    char* h_hours = (char*) malloc(20*sizeof(char));
    char* m_hours = (char*) malloc(20*sizeof(char));
    char* h_length = (char*) malloc(20*sizeof(char));
    char* m_length = (char*) malloc(20*sizeof(char));
    char* temp = (char*) malloc(15*sizeof(char));



    // open the file for reading
    FILE *file = fopen("data.txt", "r");

    // check if the file was opened successfully
    if (file == NULL) {
        printf("ERROR: can't open the file\n");
        return NULL;
    }

    // array to store the readed lines
    char* lines[MAXLINES];
    char buffer[MAXLINES];

    // variable to keep track of the number of lines read
    int line_count = 0;

    // read each line and store it in the array
    while (fgets(buffer, sizeof(buffer), file) != NULL && line_count < MAXLINES) {

        // read the current line and store it in the array
        lines[line_count++] = strdup(buffer);

    }


    int letter_cursor = 0, word_cpt = 0;
    p_contact_list temp_contact_list = createEmptyList();
    char** all_names = (char**) malloc(line_count*sizeof(char*));

    for (int i = 0; i < line_count; i++) {

        char* temp_name = (char*) malloc(100*sizeof(char));

        while(lines[i][letter_cursor] != ';' && lines[i][letter_cursor] != ':') {
            temp_name[letter_cursor] = lines[i][letter_cursor];
            letter_cursor++;
        }

        all_names[word_cpt++] = temp_name;
        p_contact newcontact = createContact(all_names[i]);
        insertContact(temp_contact_list, newcontact);

        int separator_cpt = 0;
        if (lines[i][letter_cursor] == ':') {
            while (lines[i][letter_cursor] != ';') {
                if (lines[i][letter_cursor] == ':') {
                    separator_cpt = 0;
                    strcpy(day, "");
                    strcpy(month, "");
                    strcpy(years, "");
                    strcpy(h_hours, "");
                    strcpy(m_hours, "");
                    strcpy(h_length, "");
                    strcpy(m_length, "");
                    strcpy(object, "");


                } else if (lines[i][letter_cursor] == '/' ) {
                    separator_cpt ++;
                } else  {
                    switch (separator_cpt) {
                        case 0 :
                            temp[0] = lines[i][letter_cursor];
                            strcat(day, temp);
                            break;
                        case 1 :
                            temp[0] = lines[i][letter_cursor];
                            strcat(month, temp);
                            break;
                        case 2 :
                            temp[0] = lines[i][letter_cursor];
                            strcat(years, temp);
                            break;
                        case 3 :
                            temp[0] = lines[i][letter_cursor];
                            strcat(h_hours, temp);
                            break;
                        case 4 :
                            temp[0] = lines[i][letter_cursor];
                            strcat(m_hours, temp);
                            break;
                        case 5 :
                            temp[0] = lines[i][letter_cursor];
                            strcat(h_length, temp);
                            break;
                        case 6 :
                            temp[0] = lines[i][letter_cursor];
                            strcat(m_length, temp);
                            break;
                        case 7 :
                            temp[0] = lines[i][letter_cursor];
                            strcat(object, temp);
                            break;
                        default:
                            printf("error\n");
                            break;
                    }
                }

                letter_cursor++;
                if (lines[i][letter_cursor] == ':' || lines[i][letter_cursor] == ';') {
                    p_appointment new = createEmptyAppointment();
                    new->date.day = atoi(day);
                    new->date.month = atoi(month);
                    new->date.years = atoi(years);
                    new->hour.hours = atoi(h_hours);
                    new->hour.minutes = atoi(m_hours);
                    new->length.hours = atoi (h_length);
                    new->length.minutes = atoi(m_hours);
                    new->object = (char*) malloc(20*sizeof(char));
                    strcpy(new->object, object);
                    insertAppointment(newcontact, new);
                }


            }
        }
        temp_name[letter_cursor] = '\0';
        letter_cursor = 0;

    }

    // close the file
    fclose(file);


    return temp_contact_list;
}