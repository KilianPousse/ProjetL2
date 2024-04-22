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
#include "hotbar.h"
#include "inventory.h"
#include "menu.h"



// WIN:  gcc .\src\*.c -o .\bin\prog.exe -I C:\SDL2\include -I .\include -L C:\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf




void music2fond(){
    printf("-->%d\n",  map.y*SIZE_MAP_X + map.x);

    switch( map.y*SIZE_MAP_X + map.x ){ 
        case 9:
            playMusic( "assets/sound/home.ogg", &music, &channel_music, -1 );
            break;
        case 10:
        printf("ici\n");
            playMusic( "assets/sound/cave.ogg", &music, &channel_music, -1 );
            break;
        default:
            playMusic( "assets/sound/chill.ogg", &music, &channel_music, -1 );
            break;
    }


}

int initcursor(){

    /* Initialisation du cursor */
    SDL_Surface * surface_cursor = IMG_Load( "assets/cursor.png" );
    //surface_cursor = zoomSurface( surface_cursor, 2.0 );
    cursor = SDL_CreateColorCursor( surface_cursor, 0, 0 ); 
    SDL_SetCursor(cursor);
    SDL_FreeSurface( surface_cursor );

    /* Initialisation du cursor */
    SDL_Surface * surface_cursor_select = IMG_Load( "assets/cursor_select.png" );
    //surface_cursor_select = zoomSurface( surface_cursor_select, 2.0 );
    cursor_select = SDL_CreateColorCursor( surface_cursor_select, 0, 0 ); 
    SDL_FreeSurface( surface_cursor_select );

    /* Initialisation du cursor */
    SDL_Surface * surface_cursor_click = IMG_Load( "assets/cursor_click.png" );
    //surface_cursor_click = zoomSurface( surface_cursor_click, 2.0 );
    cursor_click = SDL_CreateColorCursor( surface_cursor_click, 0, 0 ); 
    if( surface_cursor_click == NULL )
        printf("<--cursor_click NULL-->\n");
    SDL_FreeSurface( surface_cursor_click );

    if( cursor == NULL )
        printf("<cursor NULL>\n");

    if( cursor_select == NULL )
        printf("<cursor_select NULL>\n");

    if( cursor_click == NULL )
        printf("<cursor_click NULL>\n");


    return 0;
}

int main(int argc, char ** arv){

    window = NULL;
    renderer = NULL;
    icon = NULL;
    hour_Font = NULL;

    srand(time(NULL));

    /* Initialisation de la SDL */
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != FAILURE){
        ErrorLog("Échec de l'initialisation de la SDL");
    }

    /* Initialisation de la SDL_ttf */
    if(TTF_Init() != FAILURE){
        ErrorLog("Échec de l'initialisation de la SDL_ttf");
    }

    /* Initialisation de SDL_mixer */
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        ErrorLog("Erreur lors de l'initialisation de SDL_mixer");
    }
    volume_music = 64;
    volume_sfx = 64;

    /* Initialisation de la police d'écriture */
    hour_Font = TTF_OpenFont(FONT_HOUR, 50);
    if (hour_Font == NULL) {
        ErrorLog("Erreur lors du chargement de la police");
    }

    /* Initialisation de la police d'écriture */
    text_Font = TTF_OpenFont(FONT_HOUR, 35);
    if (text_Font == NULL) {
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

    // Chargement du fichier audio
    //Mix_VolumeChunk(music, volume_music);
    //Mix_VolumeChunk(sfx, volume_sfx);

    // Chargement du fichier audio
    //sfx = Mix_LoadWAV("assets/sound/mozart.ogg");


    // Chargement de l'icône à partir d'un fichier image
    icon = IMG_Load(IMG_ICON);
    if (icon == NULL) {
        WarningLog("Impossible à charger l'icon de la fenêtre");
    }

    // Définition de l'icône de la fenêtre
    SDL_SetWindowIcon(window, icon);

    initcursor();

    switch( menu_main() ){

        case 1:
            printf("\n<<<<< NEW GAME >>>>>\n");
            newSave();
            break;
        
        case 3:
            GameExit(0);
            break;

        default:
            break;
    }
    
    tps_game = 0;

    initFarmTexture( );    

    // Initialisation de la map
    initMap(&map);

    // Ininitalisation du joueur
    InitPlayer();

    initItem();
    loadHotbar();

    initPNJ();
    
    LoadSave();

    // Ininitalisation des interfaces de jeu
    initGUI();

    initWater();
    initBateau();

    diplayBackground();
    Mix_Pause(channel_music);
    SDL_CloseAudio();

    music2fond();
    

    SDL_bool launched_program = SDL_TRUE;
    unsigned int frame_limit = 0;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


    // Lecture du fichier audio
    //Mix_PlayChannel(0, music, -1); // -1 indique de jouer en boucle

    // Lecture du fichier audio
    //Mix_PlayChannel(1, sfx, -1); // -1 indique de jouer en boucle
    // Modification du volume du canal


    while( launched_program ){

        SDL_Event event;
        frame_limit = SDL_GetTicks() + FPS_LIMIT;

        while(SDL_PollEvent(&event)) {  

                tile_action = tileAction();

				switch(event.type) { 

					// Si croix en haut a droite selectionnée
					case SDL_QUIT:
						launched_program = SDL_FALSE; 
			
						break; 

                    case SDL_KEYDOWN:

                        switch(event.key.keysym.sym){

                            case SDLK_l:

                                for(int i=0; i<farm.n_plants; i++){
                                    printf("%d> x:%d y:%d age:%d max:%d id:%d\n", i, farm.plants[ i ].x, farm.plants[ i ].y, farm.plants[ i ].age, farm.plants[ i ].max_age, farm.plants[ i ].id);
                                }
                                break;

                            case SDLK_p:
                                tps_game+=24*10;
                                printf("p\n");
                                break;

                            case SDLK_m:
                                tps_game-=24*10;
                                printf("m\n");
                                break;


                            case SDLK_UP:
                            case SDLK_z:
                                // Une touche a été relâchée
                                if( canToGo( nord ) ){
                                    player.y -= player.vit;
                                    player.frame++;
                                    player.frame %= 32;
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
                                    player.frame %= 32;
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
                                    player.frame %= 32;
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
                                    player.frame %= 32;
                                }
                                if( player.dir != ouest ){
                                    player.dir = ouest;
                                    //player.frame = 0;
                                }
                                break;

                            case SDLK_e:
                            case SDLK_SPACE:
                                // Une touche a été relâchée
                                action( tile_action );
                                break;

							case SDLK_1:
                                inventory.i_hotbar = 0;
                                break;   

                            case SDLK_2:
                                inventory.i_hotbar = 1;
                                break;   

                            case SDLK_3:
                                inventory.i_hotbar = 2;
                                break;   

                            case SDLK_4:
                                inventory.i_hotbar = 3;
                                break;   

                            case SDLK_5:
                                inventory.i_hotbar = 4;
                                break;   

                            case SDLK_6:
                                inventory.i_hotbar = 5;
                                break;   

                            case SDLK_i:
                                inventory_display();
                                break;
                            
                            case SDLK_ESCAPE:
                                main_option();
                                break;
 
					        default:		
					            break;
                        }
                        break;
                    
                    case SDL_MOUSEBUTTONDOWN:
                        SDL_SetCursor( cursor_click );
                        break;
                    
                    case SDL_MOUSEBUTTONUP:
                        SDL_SetCursor( cursor );
                        break;
                    
                    default:
                        player.frame = 0;
                        break;
                
				}
                //afficher_pose_map();

                /*int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                printf("<MOUSE x:%d y:%d >\n", mouseX, mouseY);*/
                
        }

                //printf("player frame: %d\n", player.frame);
                /* On fait le rendu ! */
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
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
                
                displayWater();
                diplayBackground();
                displayFarm( map.y*SIZE_MAP_X + map.x );
                
                //afficher_cadre(window, renderer);
                displayPlayer( tile_action );
                displayPNJ();
                displayBateau();

                displayOverlay();
                
                

                displayShadow();


                displayGUI();
                displayHotbar();
                displayHotbarSelect(inventory.i_hotbar);
                
            


                displayTime();
                displayAction( tile_action );

                SDL_RenderPresent(renderer);
                limit_fps( frame_limit );

                /* Passage au jour suivant */
                if( tps_game > TIME_MAX_DAY ){
                    tps_game = 0;
                }

                /* Croissance des plantes */
                if( ((tps_game) % (6*FPS*60)) == 0 ){
                    for(int i=0; i<farm.n_plants ; i++){
                        if(farm.plants[i].age < farm.plants[i].max_age)
                            (farm.plants[i].age)++;
                    }
                }
                
                

                tps_game++;

                
			 
    }

    SaveSave( );

    GameExit( EXIT_SUCCESS );

    return EXIT_SUCCESS;
}


void limit_fps( unsigned int limit ){

    unsigned int ticks = SDL_GetTicks();

    if( limit < ticks ){
        return;
    }

    else if( ticks > ticks + FPS_LIMIT ){
        SDL_Delay( FPS_LIMIT );
    }

    else{
        SDL_Delay( limit - ticks );
    }

}


int tileAction(){

    int x = player.x;
    int y = player.y;


    switch( player.dir ){

        case nord:
            x += SIZE_TILE/3.5;
            y -= SIZE_TILE/3.5;
            break;

        case est:
            x += (3*SIZE_TILE)/3.5;
            y += SIZE_TILE/3.5;
            break;

        case sud:
            x += SIZE_TILE/3.5;
            y += (3*SIZE_TILE)/3.5;
            break;

        case ouest:
            x -= SIZE_TILE/3.5;
            y += SIZE_TILE/3.5;
            break;

        default:
            break;
    }

    /*SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawPoint(renderer, x, y);*/

    
    if( outWindow(x, y) )
        return -1;

    return tileValue( map.y*SIZE_MAP_X + map.x, x, y );
}
