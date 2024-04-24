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
#include "hotbar.h"
#include "inventory.h"

/**
 * \fn void ErrorLog(char * message);
 * \brief Stop le jeu si il y a une erreur dans le programme
 * \param message est le message d'erreur à afficher dans le terminal
**/
void ErrorLog(char * message){
    fprintf(stderr, "[ERREUR]: %s (%s)\n", message, SDL_GetError());

    
    GameExit(EXIT_FAILURE);
}


/**
 * \fn void WarningLog(char * message);
 * \brief Envoie un avertissement (warning)
 * \param message est le message du warning à afficher dans le terminal
**/
void WarningLog(char * message){
    fprintf(stderr, "[WARNING]: %s (%s)\n", message, SDL_GetError());
}

void GameExit( int exit_value ){

    freeMap(&map);
    FreePlayer();
    freeGUI();
    freeHotbar();
    freeItem();
    freePNJ();
    freeFarm();
    freeWater();
    freeBateau();
    
    Mix_FreeChunk(music);
    Mix_FreeChunk(sfx);
    
    if(icon != NULL){
        SDL_FreeSurface(icon);
        icon = NULL;
    }
    if(cursor != NULL){
        SDL_FreeCursor(cursor);
        cursor = NULL;
    }
    if(cursor_select != NULL){
        SDL_FreeCursor(cursor_select);
        cursor = NULL;
    }
    if(cursor_click != NULL){
        SDL_FreeCursor(cursor_click);
        cursor = NULL;
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
    if(text_Font != NULL){
        TTF_CloseFont(text_Font);
        hour_Font = NULL;
    }

    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    

    exit( exit_value );

}

int playMusic(char* path, Mix_Chunk** chunk, int* channel, int loop) {
    
    Mix_Pause( *channel );
    
    *chunk = Mix_LoadWAV(path);
    if (*chunk == NULL) {
        fprintf(stderr, "Impossible de charger la musique (%s)\n", path);
        return 1;
    }

    // Ouvrir le canal audio
    *channel = Mix_PlayChannel(-1, *chunk, loop);
    if (*channel == -1) {
        fprintf(stderr, "Impossible de jouer la musique (%s)\n", Mix_GetError());
        return 1;
    }

    return 0;
}
