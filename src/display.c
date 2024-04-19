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
#include "map.h"
#include "inventory.h"

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

    char * hour = malloc( sizeof(char) * 10);
    time_t t = tps_game / FPS;
    sprintf( hour, "%02ld:%02ld",  (t/60)%24, t%60 );

    // Crée une surface de texte
    SDL_Color color = WHITE_COLOR;
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

    SDL_Rect rect = { 75, 9, 1, 1 };
    SDL_QueryTexture(textTexture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, textTexture, NULL, &rect);

    SDL_FreeSurface(textSurface); // Libère la surface maintenant que la texture est créée

    SDL_DestroyTexture(textTexture);

}




void displayShadow(){

    //time_t tps = time(NULL) - ts;
    //int x = tps;

    char alpha =  0;

    if( map.y*SIZE_MAP_X + map.x > 8 )
        return;
    
    switch( tps_game/(24*60) ){
        
        case 0: case 1: case 2: case 3:
        case 23: case 24:
            alpha = 120;
            break;
        
        case 4:
            alpha = 100;
            break;
        
        case 5:
            alpha = 80;
            break;
        
        case 6:
            alpha = 60;
            break;
        
        case 7:
            alpha = 40;
            break;
        
        case 8:
            alpha = 20;
            break;
        
        case 18:
            alpha = 20;
            break;
        
        case 19:
            alpha = 40;
            break;
        
        case 20:
            alpha = 60;
            break;
        
        case 21:
            alpha = 80;
            break;
        
        case 22:
            alpha = 100;
            break;

    }


    SDL_Rect rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    SDL_SetRenderDrawColor(renderer, 0x01, 0x01, 0x00, ((int)alpha));
    SDL_RenderFillRect(renderer, &rect);

}




void displayAction( int action ){
    
    tile_action = action;

    int i_icon = -1;
    int x, y;

    switch( action ){

        // Icon: 'exclamation.png'
        case TILE_ENTER_HOUSE:
            i_icon = 0;
            break;
        case TILE_EXIT_HOUSE:
            i_icon = 0;
            break;
        case TILE_ENTER_CAVE:
            i_icon = 0;
            break;
        case TILE_EXIT_CAVE:
            i_icon = 0;
            break;
        case TILE_FISHING:
            i_icon = 0;
            break;
        case TILE_VENDEUR_GRAINE:
            i_icon = 0;
        case TILE_ACHETEUR_PLANTE:
            i_icon = 0;
        case TILE_ACHETEUR_POISSON:
            i_icon = 0;
        case TILE_A:
            i_icon = 0;
            break;

        // Icon: 'dialogue.png'
        case TILE_PNJ:
        case TILE_CRABE:
        case TILE_PY:
        case TILE_RISETTE:
        case TILE_SERGE:
        case TILE_LIVRE_BEACH:
        case TILE_LIVRE_CAVE:
        case TILE_LIVRE_FARM:
        case TILE_LIVRE_FISHING:
        case TILE_LIVRE_FOREST:
        case TILE_LIVRE_HOUSE:
        case TILE_LIVRE_JSP:
        case TILE_LIVRE_MARKET:
        case TILE_LIVRE_SPAWN:
            i_icon = 1;
            break;

        // Farmalnd
        case TILE_FARMLAND:
            if( farmland_empty(&x, &y) ){
                switch(inventory_mainhand().id){
                    
                    case ID_ITEM_GRAINE_BLE:
                    case ID_ITEM_GRAINE_TOMATE:
                        i_icon = 2;
                        break;
                    
                    /* Aucune graine */
                    default:
                        i_icon = -1;
                        break;

                }
            }
            else{

                if( farmland_finalstage(x, y) ){

                    item_t item;
                    item = farmland_planttype(x, y);
                    
                    if( inventory_canGive( item ) ){
                        i_icon = 3;
                    }    
                    else
                        i_icon = 4;



                }

            }
            
            break;
            
        default:
            return;
            break;
    }

    if( i_icon < 0 )
        return;
    SDL_Rect rect = { player.x, player.y, SIZE_TILE/2.5, SIZE_TILE/2.5 };

    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, player.actions[ i_icon ], NULL, &rect);
}


void displayGUI(){

    GUI_print_hour();
    GUI_coins();

}



SDL_Surface * zoomSurface(SDL_Surface* originalSurface, double zoomFactor) {
    if (originalSurface == NULL || zoomFactor <= 0) {
        return NULL;
    }

    // Calcul des nouvelles dimensions
    int newWidth = (int)(originalSurface->w * zoomFactor);
    int newHeight = (int)(originalSurface->h * zoomFactor);

    // Création d'une nouvelle surface pour le zoom
    SDL_Surface* zoomedSurface = SDL_CreateRGBSurfaceWithFormat(0, newWidth, newHeight, originalSurface->format->BitsPerPixel, originalSurface->format->format);
    if (zoomedSurface == NULL) {
        SDL_Log("Unable to create zoomed surface: %s", SDL_GetError());
        return NULL;
    }

    // Redimensionnement avec prise en compte de la transparence
    if (SDL_BlitScaled(originalSurface, NULL, zoomedSurface, NULL) != 0) {
        SDL_Log("Unable to scale surface: %s", SDL_GetError());
        SDL_FreeSurface(zoomedSurface);
        return NULL;
    }

    return zoomedSurface;
}



int initPNJ(  ){

    SDL_Surface * surface;
    char path[120];

    /* PNJ: Risette */
    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(path, "assets/textures/sprites/%s/idle_%d.png", "risette", i);
        pnj_sprites[ID_PNJ_RISETTE].texture[i] = chargerTexture( path, renderer );
    }

    /* PNJ: Py */
    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(path, "assets/textures/sprites/%s/idle_%d.png", "py", i);
        pnj_sprites[ID_PNJ_PY].texture[i] =  chargerTexture( path, renderer );
    }

    /* PNJ: Crabe */
    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(path, "assets/textures/sprites/%s/idle_%d.png", "crabe", i);
        pnj_sprites[ID_PNJ_CRABE].texture[i] =  chargerTexture( path, renderer );
    }

    /* PNJ: Zebi */
    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(path, "assets/textures/sprites/%s/idle_%d.png", "zebi", i);
        pnj_sprites[ID_PNJ_ZEBI].texture[i] =  chargerTexture( path, renderer );
    }

    /* PNJ: Ken */
    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(path, "assets/textures/sprites/%s/idle_%d.png", "ken", i);
        pnj_sprites[ID_PNJ_KEN].texture[i] =  chargerTexture( path, renderer );
    }

    /* PNJ: Brocoli */
    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(path, "assets/textures/sprites/%s/idle_%d.png", "brocoli", i);
        pnj_sprites[ID_PNJ_BROCOLI].texture[i] =  chargerTexture( path, renderer );
    }

    /* PNJ: Serge */
    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(path, "assets/textures/sprites/%s/idle_%d.png", "serge", i);
        pnj_sprites[ID_PNJ_SERGE].texture[i] =  chargerTexture( path, renderer );
    }


    return 0;
}

int freePNJ( ){

    for(int i=0; i<NB_PNJ; i++){
        for(int j=0; j<NB_ANIMATION; j++){
            if( pnj_sprites[i].texture[j] != NULL )
                SDL_DestroyTexture( pnj_sprites[i].texture[j] );
        }
    }

    return 0;

}

int displayPNJ( ){

    int i_map = map.y*SIZE_MAP_X + map.x;
    int i, j;
    SDL_Rect rect = {0, 0, PLAYER_SIZE, PLAYER_SIZE};
    int frame = (tps_game/12)%NB_ANIMATION;

    for (j = 0; j < NB_TILE_Y; j++) {
        for (i = 0; i < NB_TILE_X; i++) {
            rect.x = i*SIZE_TILE + 5;
            rect.y = j*SIZE_TILE + 5;

            switch(map.map[i_map][i][j]){

                case TILE_VENDEUR_GRAINE:
                    SDL_RenderCopy(renderer, pnj_sprites[ID_PNJ_ZEBI].texture[ frame ], NULL, &rect);
                    break;

                case TILE_ACHETEUR_PLANTE:
                    SDL_RenderCopy(renderer, pnj_sprites[ID_PNJ_KEN].texture[ frame ], NULL, &rect);
                    break;

                case TILE_ACHETEUR_POISSON:
                    SDL_RenderCopy(renderer, pnj_sprites[ID_PNJ_BROCOLI].texture[ frame ], NULL, &rect);
                    break;

                case TILE_CRABE:
                    SDL_RenderCopy(renderer, pnj_sprites[ID_PNJ_CRABE].texture[ frame ], NULL, &rect);
                    break;

                case TILE_PY:
                    SDL_RenderCopy(renderer, pnj_sprites[ID_PNJ_PY].texture[ frame ], NULL, &rect);
                    break; 

                case TILE_RISETTE:
                    SDL_RenderCopy(renderer, pnj_sprites[ID_PNJ_RISETTE].texture[ frame ], NULL, &rect);
                    break; 

                case TILE_SERGE:
                    SDL_RenderCopy(renderer, pnj_sprites[ID_PNJ_SERGE].texture[ frame ], NULL, &rect);
                    break; 


                default:
                    break;


            }





        }

    }



    return 0;
}



/*Permet de cherger une image*/
SDL_Texture * chargerTexture (char * chemin, SDL_Renderer * renderer){
    SDL_Surface * surface = IMG_Load(chemin);
    if(!surface){
        printf("L'image n'as pas pu être chargée(%s)\n", chemin);
        return NULL;
    }
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    return texture;
}



int displayWater(){
 
    int frame = (tps_game/12)%NB_SPRITES_WATER;

    SDL_RenderCopy( renderer, water[frame], NULL, NULL );

    return 0;
}

int initWater(){

    SDL_Surface * surface[NB_SPRITES_WATER];
    SDL_Surface * temp;
    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
    
    SDL_Rect rect = { 0, 0, SIZE_TILE, SIZE_TILE };

    char name[120];

    for(int k=0; k<NB_SPRITES_WATER; k++){

        sprintf(name, "assets/textures/background/water_%d.png", k); 
        temp = IMG_Load( name );
        if(temp == NULL) printf("[ERREUR]: IMG_Load(%s)\n", name);
        surface[k] = SDL_CreateRGBSurfaceWithFormat(0, SIZE_TILE, SIZE_TILE, temp->format->BitsPerPixel, temp->format->format);
        if(surface[k] == NULL) printf("[ERREUR]: SDL_CreateRGBSurfaceWithFormat(%s)\n", name);
        SDL_BlitScaled(temp, NULL, surface[k], NULL);
        if(surface[k] == NULL) printf("[ERREUR]: SDL_BlitScaled(%s)\n", name);

        for(int i=0; i<NB_TILE_X; i++){
            for(int j=0; j<NB_TILE_Y; j++ ){
                rect.x = i*SIZE_TILE;
                rect.y = j*SIZE_TILE;
                SDL_BlitSurface(surface[k], NULL, windowSurface, &rect);
            }
        }
        rect.x = 0;
        rect.y = 0;
        water[k] = SDL_CreateTextureFromSurface(renderer, windowSurface);
    }

    for(int i=0; i<NB_ANIMATION; i++)
        SDL_FreeSurface(surface[i]);
    
    SDL_FreeSurface(windowSurface);
    SDL_FreeSurface(temp);

}

int freeWater(){

    for(int i=0; i<NB_SPRITES_WATER; i++)
        SDL_DestroyTexture(water[i]);

}


int initBateau(){

    bateau[0] = chargerTexture("assets/textures/sprites/bateau/idle_0.png", renderer);
    bateau[1] = chargerTexture("assets/textures/sprites/bateau/idle_1.png", renderer);
    bateau[2] = chargerTexture("assets/textures/sprites/bateau/idle_2.png", renderer);
    bateau[3] = chargerTexture("assets/textures/sprites/bateau/idle_3.png", renderer);

}


int displayBateau(){

    if( map.y*SIZE_MAP_X + map.x != 2 )
        return 0;

    SDL_Rect rect = { 1400, 300, 100, 100 };

    int frame = (tps_game/12)%NB_ANIMATION;

    SDL_RenderCopy( renderer, bateau[frame], NULL, &rect );


}


int freeBateau(){

    for(int i=0; i<NB_ANIMATION; i++)
        SDL_DestroyTexture(water[i]);

}
