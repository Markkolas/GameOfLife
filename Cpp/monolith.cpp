#include<SDL2/SDL.h>
#include<iostream>

const int SCREEN_H = 680;
const int SCREEN_W = 680;
const int SCREEN_CELL_SIZE_H = 10; //pixels
const int SCREEN_CELL_SIZE_W = 10;
const int WORLD_SIZE_H = SCREEN_H/SCREEN_CELL_SIZE_H;
const int WORLD_SIZE_W = SCREEN_W/SCREEN_CELL_SIZE_W;

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

void renderCellsWindow(SDL_Texture* texture, SDL_Renderer* renderer){
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int i = 0; i < WORLD_SIZE_H; i++){
        for(int j = 0; j < WORLD_SIZE_W; j++){
            if(cell_matrix[i][j] -> alive)
                //std::cout << cell_matrix[i][j] -> alive << std::endl;
                SDL_RenderDrawPoint(renderer, i, j);
        }
    }

    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void nextState(){
    bool nextCellStates[WORLD_SIZE_H][WORLD_SIZE_W];
    for(int i = 0; i < WORLD_SIZE_H; i++)
        for(int j = 0; j < WORLD_SIZE_W; j++){
            //std::cout << "x: " << i << "y: " << j << std::endl;
            nextCellStates[i][j] = cell_matrix[i][j] -> think();
        }

    for(int i = 0; i < WORLD_SIZE_H; i++)
        for(int j = 0; j < WORLD_SIZE_W; j++)
            cell_matrix[i][j] -> alive = nextCellStates[i][j];
}

int main(){
    SDL_Event e;
    SDL_Window* window = SDL_CreateWindow("Game of Life",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_W, SCREEN_H, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    //Texture of cells. Each pixel is a cell.
    SDL_Texture* world_texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_RGBA8888,
                                             SDL_TEXTUREACCESS_TARGET,
                                             WORLD_SIZE_H,
                                             WORLD_SIZE_W);

    //Populate the world with cells
    for(int i = 0; i < WORLD_SIZE_H; i++){
        for(int j = 0; j < WORLD_SIZE_W; j++){
            cell_matrix[i][j] = new Cell(i,j); //goes on heap
        }
    }

    SDL_Init(SDL_INIT_EVERYTHING);

    bool run = false;
    int ms_delay = 100;
    while(1){//main loop
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_TOUCH_MOUSEID){
                if(e.button.button == SDL_BUTTON_LEFT){
                    int x = e.button.x;
                    int y = e.button.y;
                    //std::cout << "x: " << x << " y: " << y << std::endl;
                    cell_matrix[x/SCREEN_CELL_SIZE_W][y/SCREEN_CELL_SIZE_H] -> alive = true;
                }
                else if (e.button.button == SDL_BUTTON_RIGHT){
                    int x = e.button.x;
                    int y = e.button.y;
                    //std::cout << "x: " << x << " y: " << y << std::endl;
                    cell_matrix[x/SCREEN_CELL_SIZE_W][y/SCREEN_CELL_SIZE_H] -> alive = false;
                }

                renderCellsWindow(world_texture, renderer);
            }
            if(e.type == SDL_KEYDOWN)
                switch(e.key.keysym.sym){
                case SDLK_SPACE: run = !run; break;
                case SDLK_PLUS: if(ms_delay < 1000) ms_delay += 10; break;
                case SDLK_MINUS: if(ms_delay > 0) ms_delay -= 10; break;
                default: break;
                }
            if(e.type == SDL_QUIT) std::exit(0);
        }

        if(run){
            nextState();
            renderCellsWindow(world_texture, renderer);
        }

        SDL_Delay(ms_delay);
    }
    return 0;
}
