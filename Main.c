#include <stdio.h>
#include "list.h"
#include "list.c"
int main()
{
    printf("%d\n", comparerString1("thomas", "thomas"));
    printf("%d\n", comparerString1("Thomas", "thomas"));
    printf("%d\n", comparerString1("Maryam", "thomas"));
    printf("%d\n", comparerString1("thomas", "Maryam"));
    printf("%d\n", comparerString1("thomas", "thomas2"));



    return 0;
}
