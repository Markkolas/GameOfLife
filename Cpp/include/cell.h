#include "global.h"

struct Cell{ //Structs are classes in C++ (all members are public)
    //World is a rectangle with corners (0,0) (0,b) (a,0) (a,b)
    //Posible mejora: usar matriz de celdas de (N+2)x(M+2) y usar bordes de la
    //matriz como celdas del otro extremo del mundo. Me di cuenta tarde :c
    enum where {CORNER_00, CORNER_AB, CORNER_A0, CORNER_0B,
        LINE_0Y, LINE_X0, LINE_AY, LINE_XB, INSIDE};
    const int x, y;//Position of cell
    where location;

    bool alive;//State of cell

    Cell(int, int);
    bool think();
    int lookForFriends(where location);
};

extern Cell* cell_matrix[WORLD_SIZE_H][WORLD_SIZE_W];
