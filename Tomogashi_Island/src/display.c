/**
 * \file display.c
 * \brief Gestion des affichages
 * \details Scripte qui realise la gestion des affichages
 * \author Pousse Kilian - Pierre Elona - Vallee Alban 
 * \version alpha 1.2
 * \date 31/01/2024
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
#include "style.h"

void afficher_cadre(SDL_Window * window, SDL_Renderer * renderer){

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    for(int i=0; i<NB_TILE_X; i++){
        SDL_RenderDrawLine(renderer, SIZE_TILE*i, 0, SIZE_TILE*i, WINDOW_HEIGHT);
    }

    for(int i=0; i<NB_TILE_Y; i++){
        SDL_RenderDrawLine(renderer, 0, SIZE_TILE*i, WINDOW_WIDTH, SIZE_TILE*i);
    }


}

void afficher_pose_map(){

    printf("\n");

    for(int i=0; i<SIZE_MAP_Y; i++){
        for(int j=0; j<SIZE_MAP_X; j++){
            printf(" [%c]", i==map.y&&j==map.x?'X':' ');
        }
        printf("\n");
    } 

}

void displayTime(){

    time_t tps = time(NULL) - ts;
    char * hour = malloc( sizeof(char) * 10);
    sprintf( hour, "%02ld:%02ld",  (tps/60)%24, tps%60 );

    // Crée une surface de texte
    SDL_Color color = FULL_BLACK_COLOR;
    SDL_Surface* textSurface = TTF_RenderText_Solid( hour_Font , hour, color );
    free( hour );
    if (textSurface == NULL) {
        WarningLog("Erreur lors de la création de la surface de texte de l'horloge");
        return;
    }

    // Crée une texture à partir de la surface de texte
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        SDL_Log("Erreur lors de la création de la texture de l'horloge");
        SDL_FreeSurface(textSurface); // Libère la surface maintenant que la texture est créée
        return;
    }

    SDL_Rect rect = { 0, 0, 1, 1 };
    SDL_QueryTexture(textTexture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, textTexture, NULL, &rect);

    SDL_FreeSurface(textSurface); // Libère la surface maintenant que la texture est créée

}