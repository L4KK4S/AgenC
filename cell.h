#ifndef AGENC_FICHIER_H
#define AGENC_FICHIER_H

struct s_cell{
    int value;
    struct s_cell *next_h;
    struct s_cell *next_v;
};

typedef struct s_cell t_cell, *p_cell;

#endif //AGENC_FICHIER_H
