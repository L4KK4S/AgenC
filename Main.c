#include <stdio.h>
#include "list.h"
#include "list.c"
#include <stdlib.h>
#include <string.h>
int main()
{
   // printf("%d\n", comparerString1("thomas", "thomas"));
    printf("%d\n", comparerString1("Thomas", "thomas"));
    //printf("%d\n", comparerString1("Maryam", "thomas"));
    //printf("%d\n", comparerString1("thomas", "Maryam"));
    //printf("%d\n", comparerString1("thomas", "thomas2"));
    char *string2 = malloc(30); // Chaîne dynamique

    strcpy(string2, "Autre Chaine De Test");
    change_maj_to_min(string2);

    return 0;
}
