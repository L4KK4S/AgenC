//
// Created by marya on 23/10/2023.
//

#include "list.h"
#include <stdio.h>
#include <string.h>
int compareStrings( char *a, char *b) {
    while (*a != '\0' && *b != '\0') {
        if (*a < *b) {
            return -1; //string1 is shorter than string2
        } else if (*a > *b) {
            return 1; //  string1 is greater than string2
        }
        a++;
        b++;
    }
    if (*a == '\0' && *b == '\0'){
        return 0; // Both strings are identical
    }
    if (*a == '\0') {
        return -1; //string1 is shorter than string2
    }
    else {
        return 1; // string1 is greater than string2
    }
}
int comparerString1( char *s1, char *s2) {
    int i = 0;
    int n1 = strlen(s1);
    int n2 = strlen(s2);


    while (i <= n1 && i <= n2 && s1[i] == s2[i]) {     // Compare characters until a mismatch is found or the end of either string is reached
        i++;
    }

    if (i <= n1 && i <= n2) {
        if (s1[i] < s2[i]) {
            return 1; //S1 < S2
        } else {
            return - 1; // S1> S2;
        }
    } else {
        if (n1 == n2) {
            return 0; // s1=S2
        } else if (i >= n1) {
            return 1; //s1<S2
        } else {
            return -1; // s1>S2
        }
    }
}

