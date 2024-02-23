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


#include "header.h"
#include "struct.h"
#include "style.h"


// WIN:  gcc .\src\*.c -o .\bin\prog.exe -I C:\SDL2\include -I .\include -L C:\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf


int main(int argc, char ** arv){

    window = NULL;
    renderer = NULL;
    icon = NULL;
    hour_Font = NULL;

    /* Initialisation de la SDL */
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != FAILURE){
        ErrorLog("Échec de l'initialisation de la SDL");
    }

    /* Initialisation de la SDL_ttf */
    if(TTF_Init() != FAILURE){
        ErrorLog("Échec de l'initialisation de la SDL_ttf");
    }

    /* Initialisation de la police d'écriture */
    hour_Font = TTF_OpenFont("bin/assets/font/arial.ttf", 40);
    if (hour_Font == NULL) {
        ErrorLog("Erreur lors du chargement de la police");
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
    InitPlayer();

    printf("x:%d / y:%d\n", player.x, player.y);

    diplayBackground();

    SDL_bool launched_program = SDL_TRUE;

    SDL_Rect rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    ts = time(NULL);

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
                                if( canToGo( nord ) ){
                                    player.y -= player.vit;
                                    player.frame++;
                                    player.frame %= 23;
                                }
                                if( player.dir != nord ){
                                    player.dir = nord;
                                    player.frame = 0;
                                }
                                break;

                            case SDLK_DOWN:
                            case SDLK_s:
                                // Une touche a été relâchée
                                if( canToGo( sud ) ){
                                    player.y += player.vit;
                                    player.frame++;
                                    player.frame %= 23;
                                }
                                if( player.dir != sud ){
                                    player.dir = sud;
                                    player.frame = 0;
                                }
                                break;

                            case SDLK_RIGHT:
                            case SDLK_d:
                                // Une touche a été relâchée
                                if( canToGo( est ) ){
                                    player.x += player.vit;
                                    player.frame++;
                                    player.frame %= 23;
                                }
                                if( player.dir != est ){
                                    player.dir = est;
                                    player.frame = 0;
                                }
                                break;

                            case SDLK_LEFT:
                            case SDLK_q:
                                // Une touche a été relâchée
                                if( canToGo( ouest ) ){
                                    player.x -= player.vit;
                                    player.frame++;
                                    player.frame %= 23;
                                }
                                if( player.dir != ouest ){
                                    player.dir = ouest;
                                    //player.frame = 0;
                                }
                                break;
								
								
                                
					        default:	
                                //printf("ici\n");		
					            break;
                        }
                        break;
                    
                    default:
                        player.frame = 0;
                        break;
                
				}
        }

                //printf("player frame: %d\n", player.frame);

                /* On fait le rendu ! */
                SDL_RenderClear(renderer);// Rectangle plein

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
                
                //afficher_cadre(window, renderer);
                displayPlayer();

                
                // Active le mélange alpha pour la transparence
                
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor( renderer, 0x01, 0x00, 0x10, 0x0 );
                SDL_RenderFillRect(renderer, &rect);

                displayTime();

                SDL_RenderPresent(renderer);

                //afficher_pose_map();
			 
    }

    
    FreePlayer();
    freeMap(&map);
    SDL_FreeSurface(icon);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(hour_Font);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

