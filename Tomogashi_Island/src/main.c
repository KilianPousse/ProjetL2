#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "header.h"
#include "style.h"



void ErrorLog(char * message, SDL_Window * window, SDL_Renderer * renderer, map_t * map){
    printf("ERREUR: %s (%s)\n", message, SDL_GetError());

    if(map != NULL)
        free(map);

    if(window != NULL)
        SDL_DestroyRenderer(renderer);

    if(renderer != NULL)
        SDL_DestroyWindow(window);

    SDL_Quit();
    exit(EXIT_FAILURE);
}



map_t * map = NULL;


int main(int argc, char ** arv){

    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Surface * icon = NULL;

    /* Initialisation de la SDL */
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != FAILURE){
        ErrorLog("Échec de l'initialisation de la SDL", NULL, NULL, NULL);
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
        ErrorLog("Échec de l'initialisation de la fenêtre de jeu", NULL, NULL, NULL);
    }


    /* Initialisation du rendu de la fenêtre du jeu */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
        ErrorLog("Erreur à la création du renderer", window, NULL, NULL);
	}

    // Chargement de l'icône à partir d'un fichier image
    icon = IMG_Load("bin/assets/icon.png");
    if (icon == NULL) {
        ErrorLog("Impossible à charger l'icon de la fenêtre", window, NULL, NULL);
    }

    // Définition de l'icône de la fenêtre
    SDL_SetWindowIcon(window, icon);

    // Libération de la surface de l'icône, car elle n'est plus nécessaire après la définition de l'icône
    SDL_FreeSurface(icon);

    int taille = 32;
    int x = 10;
    int y = 200;
    int dir = DIR_NORD;
    int vit = taille;

    // Initialisation de la map
    map = malloc(sizeof(int) * SIZE_MAP_X * SIZE_MAP_Y );


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
                                y -= vit;
                                dir = DIR_NORD;
                                break;

                            case SDLK_DOWN:
                            case SDLK_s:
                                // Une touche a été relâchée
                                y += vit;
                                dir = DIR_SUD;
                                break;

                            case SDLK_RIGHT:
                            case SDLK_d:
                                // Une touche a été relâchée
                                x += vit;
                                dir = DIR_EST;
                                break;

                            case SDLK_LEFT:
                            case SDLK_q:
                                // Une touche a été relâchée
                                x -= vit;
                                dir = DIR_OUEST;
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

                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
                SDL_Rect rect = { x, y, taille, taille };
                SDL_RenderFillRect(renderer, &rect);
                SDL_RenderPresent(renderer);
			} 
    }




    free(map);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
























/*



    A |A |
    A |A |


*/