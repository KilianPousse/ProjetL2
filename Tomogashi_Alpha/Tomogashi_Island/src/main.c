/**
 * \file main.c
 * \brief Sripte principale du jeu
 * \details Coeur principal du programme du jeu
 * \author Pousse Kilian - Pierre Elona - Vallee Alban 
 * \version alpha 1.2
 * \date 31/01/2024
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "header.h"
#include "style.h"


/**
 * \fn void ErrorLog(char * message);
 * \brief Stop le jeu si il y a une erreur dans le programme
 * \param message est le message d'erreur à afficher dans le terminal
**/
void ErrorLog(char * message){
    printf("ERREUR: %s (%s)\n", message, SDL_GetError());

    freeMap(&map);

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


int main(int argc, char ** arv){

    window = NULL;
    renderer = NULL;
    icon = NULL;

    /* Initialisation de la SDL */
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != FAILURE){
        ErrorLog("Échec de l'initialisation de la SDL");
    }


    /* Initialisation de la fenêtre du jeu */
    window = SDL_CreateWindow(
        WINDOW_NAME,                                // Nom de la fenêtre
        SDL_WINDOWPOS_CENTERED,                     // Position de la fenêtre sur l'axe x
        SDL_WINDOWPOS_CENTERED,                     // Position de la fenêtre sur l'axe y
        WINDOW_WIDTH,                               // Largeur de la fenêtre par defaut
        WINDOW_HEIGHT,                              // Hauteur de la fenêtre par defaut
        0                                           // Propriétés de la fenêtre
    );
    if( window == NULL ){
        ErrorLog("Échec de l'initialisation de la fenêtre de jeu");
    }


    /* Initialisation du rendu de la fenêtre du jeu */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
        SDL_Delay(2000);
        ErrorLog("Erreur à la création du renderer");
    }

    // Chargement de l'icône à partir d'un fichier image
    icon = IMG_Load(IMG_ICON);
    if (icon == NULL) {
        WarningLog("Impossible à charger l'icon de la fenêtre");
    }

    // Définition de l'icône de la fenêtre
    SDL_SetWindowIcon(window, icon);

    // Libération de la surface de l'icône, car elle n'est plus nécessaire après la définition de l'icône
    
    //icon = NULL;

    // Initialisation de la map
    initMap(&map);

    // Ininitalisation du joueur
    player_t player;
    player.x = SIZE_TILE*10;
    player.y = SIZE_TILE*5;
    player.dir = sud;
    player.vit = SIZE_TILE/2;

    diplayBackground();

    SDL_bool launched_program = SDL_TRUE;

    while( launched_program ){

        SDL_Event event;

        while(SDL_PollEvent(&event)) {  

				switch(event.type) { 

					// Si croix en haut a droite selectionnée
					case SDL_QUIT:
						launched_program = SDL_FALSE; 
						break; 

                    case SDL_KEYDOWN:

                        switch(event.key.keysym.sym){

                            case SDLK_UP:
                            case SDLK_z:
                                // Une touche a été relâchée
                                if( canToGo(&player, nord) ){
                                    player.y -= player.vit;
                                    player.dir = nord;
                                }
                                break;

                            case SDLK_DOWN:
                            case SDLK_s:
                                // Une touche a été relâchée
                                if( canToGo(&player, sud) ){
                                    player.y += player.vit;
                                    player.dir = sud;
                                }
                                break;

                            case SDLK_RIGHT:
                            case SDLK_d:
                                // Une touche a été relâchée
                                if( canToGo(&player, est) ){
                                    player.x += player.vit;
                                    player.dir = est;
                                }
                                break;

                            case SDLK_LEFT:
                            case SDLK_q:
                                // Une touche a été relâchée
                                if( canToGo(&player, ouest) ){
                                    player.x -= player.vit;
                                    player.dir = ouest;
                                }
                                break;
								
								
                                
					        default:			
					            break;
                        }
                    
                    default:
                        break;
				} 
                /* On fait le rendu ! */
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderClear(renderer);// Rectangle plein

                
                switch(player.dir){
                    case nord:
                        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
                        break;
                    case est:
                        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                        break;
                    case sud:
                        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
                        break;
                    case ouest:
                        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
                        break;
                }
                
                SDL_Rect rect = { player.x, player.y, SIZE_TILE, SIZE_TILE };


                

                
                switch(outWindow(player.x, player.y)){
                    case 0:
                        break;

                    case 1:
                        player.x = (NB_TILE_X-1) * SIZE_TILE;
                        map.x--;
                        diplayBackground();
                        break;

                    case 2:
                        player.y = (NB_TILE_Y-1) * SIZE_TILE;
                        map.y--;
                        diplayBackground();
                        break;

                    case 3:
                        player.x = 0;
                        diplayBackground();
                        map.x++;
                        break;

                    case 4:
                        player.y = 0;
                        diplayBackground();
                        map.y++;
                        break;
                }
                
                diplayBackground();
                
                afficher_cadre(window, renderer);
                
                SDL_RenderFillRect(renderer, &rect);

                SDL_RenderPresent(renderer);

                //afficher_pose_map();
			} 
    }

    

    freeMap(&map);
    SDL_FreeSurface(icon);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}



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


/**
 * \fn int outWindow(player_t p);
 * \brief Permet de savoir si le joueur est hors de l'ecran
 * \param p est le joueur
 * \return 0 --> est toujours dans l'ecran
 * \return 1 --> sortie par la gauche
 * \return 2 --> sortie par en haut
 * \return 3 --> sortie par la droite
 * \return 4 --> sortie par en bas
**/
int outWindow(int x, int y){

    if(x < 0)
        return 1;

    if(y < 0)
        return 2;

    if(x >= WINDOW_WIDTH)
        return 3;

    if(y >= WINDOW_HEIGHT)
        return 4;

    return 0;
}


