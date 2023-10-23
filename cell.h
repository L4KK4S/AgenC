#ifndef AGENC_FICHIER_H
#define AGENC_FICHIER_H

#include "list.h"

struct s_cell{
    int value;
    struct s_cell *next_h;
    struct s_cell *next_v;
};

typedef struct s_cell t_cell, *p_cell;

p_cell createEmptyLevelCell(int x);
p_cell addVtab(p_cell cell, int x);
int countCell(p_list list, p_cell first, p_cell last);
int cellLength (p_cell cell);
int isInTheLevel (p_cell head, int x);

#endif //AGENC_FICHIER_H