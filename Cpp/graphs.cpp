#include<SDL2/SDL.h>
#include "include/graphs.h"
#include "include/cell.h"

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
