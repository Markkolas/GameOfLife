#include "include/cell.h"
#include<SDL2/SDL.h>

Cell* cell_matrix[WORLD_SIZE_H][WORLD_SIZE_W];

Cell::Cell(int initx, int inity): x{initx}, y{inity}, alive{false}{
    if(x==0 && y==0) location = CORNER_00;
    else if(x==WORLD_SIZE_W-1 && y==WORLD_SIZE_H-1) location = CORNER_AB;
    else if(x==WORLD_SIZE_W-1 && y==0) location = CORNER_A0;
    else if(x==0 && y==WORLD_SIZE_H-1) location = CORNER_0B;
    else if(x==0) location = LINE_0Y;
    else if(y==0) location = LINE_X0;
    else if(x==WORLD_SIZE_W-1) location = LINE_AY;
    else if(y==WORLD_SIZE_H-1) location = LINE_XB;
    else location = INSIDE;
}

int Cell::lookForFriends(where location){
    int n_friends;
    const int a{WORLD_SIZE_W-1}, b{WORLD_SIZE_H-1};
    //std::cout << "Im in: " << location << std::endl;
    switch(location){
    case CORNER_00:
        n_friends =
            (cell_matrix[x+1][y] -> alive) +
            (cell_matrix[x][y+1] -> alive) +
            (cell_matrix[x+1][y+1] -> alive) +
            (cell_matrix[a][y] -> alive) +
            (cell_matrix[a][y+1] -> alive) +
            (cell_matrix[a][b] -> alive) +
            (cell_matrix[x][b] -> alive) +
            (cell_matrix[x+1][b] -> alive);
        break;
    case CORNER_A0:
        n_friends =
            (cell_matrix[x-1][y] -> alive) +
            (cell_matrix[x][y+1] -> alive) +
            (cell_matrix[x-1][y+1] -> alive) +
            (cell_matrix[0][0] -> alive) +
            (cell_matrix[0][y+1] -> alive) +
            (cell_matrix[a][b] -> alive) +
            (cell_matrix[a-1][b] -> alive) +
            (cell_matrix[0][b] -> alive);
        break;
    case CORNER_0B:
        n_friends =
            (cell_matrix[x+1][y] -> alive) +
            (cell_matrix[x][y-1] -> alive) +
            (cell_matrix[x+1][y-1] -> alive) +
            (cell_matrix[0][0] -> alive) +
            (cell_matrix[x+1][0] -> alive) +
            (cell_matrix[a][b] -> alive) +
            (cell_matrix[a][b-1] -> alive) +
            (cell_matrix[a][0] -> alive);
        break;
    case CORNER_AB:
        n_friends =
            (cell_matrix[x-1][y] -> alive) +
            (cell_matrix[x][y-1] -> alive) +
            (cell_matrix[x-1][y-1] -> alive) +
            (cell_matrix[x][0] -> alive) +
            (cell_matrix[x-1][0] -> alive) +
            (cell_matrix[0][y] -> alive) +
            (cell_matrix[0][y-1] -> alive) +
            (cell_matrix[0][0] -> alive);
        break;
    case LINE_0Y:
        n_friends =
            (cell_matrix[x][y+1] -> alive) +
            (cell_matrix[x][y-1] -> alive) +
            (cell_matrix[x+1][y] -> alive) +
            (cell_matrix[x+1][y+1] -> alive) +
            (cell_matrix[x+1][y-1] -> alive) +
            (cell_matrix[a][y-1] -> alive) +
            (cell_matrix[a][y] -> alive) +
            (cell_matrix[a][y+1] -> alive);
        break;
    case LINE_X0:
        n_friends =
            (cell_matrix[x-1][y] -> alive) +
            (cell_matrix[x+1][y] -> alive) +
            (cell_matrix[x][y+1] -> alive) +
            (cell_matrix[x-1][y+1] -> alive) +
            (cell_matrix[x+1][y+1] -> alive) +
            (cell_matrix[x-1][b] -> alive) +
            (cell_matrix[x][b] -> alive) +
            (cell_matrix[x+1][b] -> alive);
        break;
    case LINE_AY:
        n_friends =
            (cell_matrix[x][y+1] -> alive) +
            (cell_matrix[x][y-1] -> alive) +
            (cell_matrix[x-1][y] -> alive) +
            (cell_matrix[x-1][y+1] -> alive) +
            (cell_matrix[x-1][y-1] -> alive) +
            (cell_matrix[0][y-1] -> alive) +
            (cell_matrix[0][y] -> alive) +
            (cell_matrix[0][y+1] -> alive);
        break;
    case LINE_XB:
        n_friends =
            (cell_matrix[x-1][y] -> alive) +
            (cell_matrix[x+1][y] -> alive) +
            (cell_matrix[x][y-1] -> alive) +
            (cell_matrix[x-1][y-1] -> alive) +
            (cell_matrix[x+1][y-1] -> alive) +
            (cell_matrix[x+1][0] -> alive) +
            (cell_matrix[x][0] -> alive) +
            (cell_matrix[x-1][0] -> alive);
        break;
    default:
        n_friends=
            (cell_matrix[x+1][y] -> alive) +
            (cell_matrix[x-1][y] -> alive) +
            (cell_matrix[x][y+1] -> alive) +
            (cell_matrix[x][y-1] -> alive) +
            (cell_matrix[x+1][y+1] -> alive) +
            (cell_matrix[x-1][y-1] -> alive) +
            (cell_matrix[x-1][y+1] -> alive) +
            (cell_matrix[x+1][y-1] -> alive);
        break;
    }

    return n_friends;
}

bool Cell::think(){
    bool want_to_live = alive;
    int friends = lookForFriends(location);
    if(alive && (friends < 2 || friends > 3))
    {
        //std::cout << "Friends: " << friends << std::endl;
        //std::cout << "I want to die!\n" << std::endl;
        want_to_live = false;
    }
    else if(friends == 3){
        //std::cout << "Friends: " << friends << std::endl;
        //std::cout << "I want to live!\n" << std::endl;
        want_to_live = true;
    }

    return want_to_live;
}
