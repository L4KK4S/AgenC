#include <stdio.h>
#include "list.h"
#include "cell.h"

int main()
{
    printf("hello world\n");
    p_cell c1 = createEmptyCell(4, 5);
    printf("la cellule a une longueur de : %d", cellLength(c1));
    return 0;
}
