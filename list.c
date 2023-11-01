//
// Created by marya on 23/10/2023.
//

#include "list.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*void change_maj_to_min( char *s) {
   for (int i = 0; s[i] != '\0'; i++) {
       if (s[i] >= 'A' && s[i] <= 'Z') {
        s[i] = s[i] + 32; // Conversion en minuscule
        }

    }
 */
  void change_maj_to_min( char *str) {
      int i;
      for (i = 0; str[i] != '\0'; i++) {
          str[i] = tolower(str[i]);
      }
  }
int comparerString1( char *s1, char *s2) {
    int i = 0;
    int n1 = strlen(s1);
    int n2 = strlen(s2);
    change_maj_to_min(s1);
    change_maj_to_min(s2);
    while (i < n1 && i < n2 && s1[i] == s2[i]) {     // Compare characters until a mismatch is found or the end of either string is reached
        i++;
    }

    if (i < n1 && i < n2) {
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

