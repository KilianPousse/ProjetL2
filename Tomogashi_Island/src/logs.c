/**
 * \file logs.c
 * \brief Gestions de logs
 * \details Sripte qui contient les gestions de logs
 * \author Pousse Kilian - Pierre Elona - Vallee Alban 
 * \version alpha 1.2.1
 * \date 31/01/2024
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "header.h"

/**
 * \fn void ErrorLog(char * message);
 * \brief Stop le jeu si il y a une erreur dans le programme
 * \param message est le message d'erreur à afficher dans le terminal
**/
void ErrorLog(char * message){
    printf("ERREUR: %s (%s)\n", message, SDL_GetError());

    freeMap(&map);
    FreePlayer();

    if(icon != NULL){
        SDL_FreeSurface(icon);
        icon = NULL;
    }
    
    if(renderer != NULL){
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if(window != NULL){
        SDL_DestroyWindow(window);
        window = NULL;
    }
    if(hour_Font != NULL){
        TTF_CloseFont(hour_Font);
        hour_Font = NULL;
    }

    TTF_Quit();
    SDL_Quit();
    exit(EXIT_FAILURE);
}


/**
 * \fn void WarningLog(char * message);
 * \brief Envoie un avertissement (warning)
 * \param message est le message du warning à afficher dans le terminal
**/
void WarningLog(char * message){
    printf("WARNING: %s (%s)\n", message, SDL_GetError());
}
