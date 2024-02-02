#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "header.h"
#include "style.h"

int initMap(char * path){

    map->size_x = SIZE_MAP_X;
    map->size_y = SIZE_MAP_Y;

    FILE * file = fopen(path, "r");
    if( file == NULL )
        return FAILURE;

    int i = 0;
    int j = 0;
    
    for (i = 0; i < SIZE_MAP_Y; i++) {
        for (j = 0; j < SIZE_MAP_X; j++) {
            if (fscanf(file, "%d:", &(map->map[j][i])) != 1)
                printf("ERREUR\n");
        }
    }


    for(i=0; i<SIZE_MAP_Y; i++){
        for(j=0; j<SIZE_MAP_X; j++)
            printf("%3d|", map->map[j][i]);

        printf("\n");
    }

    free(file);

    return SUCCESS;
}





int displayMap(SDL_Renderer * renderer){
    
    int x = 30;
    int y = x;

    int i = 0;
    int j = 0;

    /*printf("x:%d   y:%d\n", map->size_x, map->size_y);

    for(i=0; i<map->size_y; i++){
        for(j=0; j<map->size_x; j++)
            printf("%3d|", map->map[j][i]);

        printf("\n");
    }*/

    for(i=0; i<SIZE_MAP_Y; i++){
        for(j=0; j<SIZE_MAP_X; j++){

            printf("%5d|\n", map->map[j][i]);

            switch(map->map[j][i]){
        
                case 1:
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                    break;
                
                case 2:
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
                    break;

                default:
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
                    break;
        
            }

            printf("i:%d  j:%d  val:%d\n", i, j, map->map[j][i]);
            SDL_Rect rect = { x*i, y*j, x, y };
            SDL_RenderFillRect(renderer, &rect);
        }
        printf("\n");
    }

    

    return SUCCESS;
}