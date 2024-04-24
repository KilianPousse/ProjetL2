#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "header.h"
#include "inventory.h"
#include "fishing.h"
#include "hotbar.h"
#include "menu.h"


long fishing_waitTime(){

    return (time_t)rand()%300+72;
}

/*
40
30
20
7
3


*/

item_t fishing_fishtype(){

    srand(time(NULL));

    item_t fish = {0, 1};

    int pct = rand()%100;

    if( pct < 40 )
        fish.id = ID_ITEM_POISSON;
    else if( pct < 70 )
        fish.id = ID_ITEM_THON;
    else if( pct < 90 )
        fish.id = ID_ITEM_POISSON_LANTERNE;
    else if( pct < 97 )
        fish.id = ID_ITEM_KOI;
    else {
        pct = rand()%100;
        if( pct < 90 )
            fish.id = ID_ITEM_REQUIN;

        else
            fish.id = ID_ITEM_POISSON_DORE;
            
    }

    return fish;
}   


void displayfisher( int * frame, SDL_Texture * idle[2], SDL_Texture * hook[2], SDL_Texture * plop, long delay ){

    SDL_Rect rect = { 35, 8*SIZE_TILE+10, 75, 50};

    if( delay <= 0 ){
        SDL_RenderCopy(renderer, plop, NULL, &rect);
    }
    else if( *frame >= 16 && *frame > 0){
        *frame = 16;
        SDL_RenderCopy(renderer, idle[ (tps_game/8)%2 ], NULL, &rect);
    }
    else if(  *frame <= 0 ){
        SDL_RenderCopy(renderer, hook[ (-(*frame)/12)%2 ], NULL, &rect);
        (*frame)++;
        if(*frame == 0)
            *frame = 100;
    }
    else{
        SDL_RenderCopy(renderer, hook[ (*frame/12)%2 ], NULL, &rect);
        (*frame)++;
    }
}

int fishing_free( SDL_Texture * idle[2], SDL_Texture * hook[2], SDL_Texture * plop ){
    for(int i=0; i<2; i++)
        SDL_DestroyTexture(idle[i]);

    for(int i=0; i<2; i++)
        SDL_DestroyTexture(hook[i]);

    SDL_DestroyTexture(plop);
}


int main_fishing(  ){

    SDL_bool launched_program = SDL_TRUE;
    long delay = fishing_waitTime();
    item_t fish = fishing_fishtype();

    int frame = 0;
    unsigned int frame_limit = 0;
    SDL_Rect rect = { 0,  0,  WINDOW_WIDTH, WINDOW_HEIGHT};

    SDL_Texture * hook[2];
    SDL_Texture * idle[2];
    SDL_Texture * plop;

    idle[0] = chargerTexture( "assets/textures/sprites/haricot/fishing_0.png", renderer);
    idle[1] = chargerTexture( "assets/textures/sprites/haricot/fishing_1.png", renderer);

    hook[0] = chargerTexture( "assets/textures/sprites/haricot/fishing_hook_0.png", renderer);
    hook[1] = chargerTexture( "assets/textures/sprites/haricot/fishing_hook_1.png", renderer);

    plop = chargerTexture( "assets/textures/sprites/haricot/fishing_plop.png", renderer);


     while( launched_program ){

        frame_limit = SDL_GetTicks() + FPS_LIMIT;
        SDL_Event event;

        while(SDL_PollEvent(&event)) {  

				switch(event.type) { 

					// Si croix en haut a droite selectionnée
					case SDL_QUIT:
						launched_program = SDL_FALSE;
                        SaveSave();
                        fishing_free(hook,idle,plop);
                        GameExit(EXIT_SUCCESS);
						break;
                    
                    case SDL_MOUSEBUTTONDOWN:
                        SDL_SetCursor( cursor_click );
                        break;
                    
                    case SDL_MOUSEBUTTONUP:
                        SDL_SetCursor( cursor );
                        break;

                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){

                            case SDLK_e:
                            case SDLK_SPACE:
                                if( frame == 16 )
                                    frame = -16;

                                if( delay < 0 ){
                                    //printf("Bravo mon pote!(id:%d//nb:%d)\n", fish.id, fish.nb);
                                    delay = 1;

                                    

                                    if( fish.nb == 1 ){
                                        inventory_give(&fish);
                                        playMusic( "assets/sound/sfx/celebration.ogg", &sfx, &channel_sfx, 0 );
                                    }
                                    
                                }

                                break;
                            
                            case SDLK_ESCAPE:
                                main_option();
                                break;

					        default:		
					            break;
                        }
                        break;
                    
                    default:
                        break;
                
				}
                
        }
            if( delay == 0 )
                playMusic( "assets/sound/sfx/plop.ogg", &sfx, &channel_sfx, 0 );

            
            if( frame == 100 ){
                fishing_free(hook,idle,plop);
                return 0;
            }

            if( delay < -24 ){
                delay = fishing_waitTime();
                fish = fishing_fishtype();
            }

            if( frame >= 16 ){
                delay--;
                


            }

        /* On fait le rendu ! */
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);// Rectangle plein
                
        displayWater();
        diplayBackground();
        //displayPlayer( tile_action );
        displayfisher( &frame, idle, hook, plop, delay );

        displayPNJ();
        displayOverlay();

        displayShadow();

        displayGUI();
        displayTime();
        displayHotbar();
        displayHotbarSelect(inventory.i_hotbar);

        SDL_RenderPresent(renderer);
        limit_fps( frame_limit );    

        tps_game++;
    }

    fishing_free(hook,idle,plop);

    return 0;
}
