#include "include/cell.h"
#include "include/graphs.h"

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
