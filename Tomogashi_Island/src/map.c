/**
 * \file map.c
 * \brief Sripte de la gestion de la map
 * \details Ensemble des fonctions qui utilise la map
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

/**
 * \fn int initMap(map_t * m);
 * \brief Permet d'initialiser la map
 * \param m est la map du jeu à initialiser
**/
int initMap(map_t * m){

    m->x = 1;
    m->y = 1;
    
    char img_overlay[255] = "";

    for(int n=0; n<SIZE_MAP_X*SIZE_MAP_Y; n++){
        m->background[ n ] = NULL;

        m->overlay[ n ] = NULL;
        sprintf(img_overlay ,"bin/assets/textures/background/overlay_%d.png", n);
        m->overlay[ n ] = IMG_Load(img_overlay);

        if( m->overlay[ n ] == NULL )
            WarningLog("Impossible de charger un overlay");

        for(int i=0; i<NB_TILE_X; i++){
            for(int j=0; j<NB_TILE_Y; j++){
                    m->map[n][i][j] = -1;
            }
        }
    }

    FILE * file = fopen(MAIN_MAP, "r");
    /*if(file == NULL){
        ErrorLog("Impossible de charger la map");
    }*/

    char img_name[24];
    char img_path[255] = "bin/assets/textures/background/";
    int cut = strlen(img_path);
    int n = 0;
    char c;

    while( (c = fgetc(file)) != EOF && n<SIZE_MAP_X*SIZE_MAP_Y){

        if(c == '$'){

            fscanf(file, "%s", img_name);

            strcat(img_path, img_name);
            m->background[ n ] = IMG_Load(img_path);

            

            if(m->background[ n ] == NULL)
                WarningLog("Impossible de charger un background");

            // Lire les éléments de la matrice depuis le fichier
            for (int j = 0; j < NB_TILE_Y; j++) {
                for (int i = 0; i < NB_TILE_X; i++) {
                    fscanf(file, "%d", &(m->map[n][i][j]));
                }
            }

            n++;
            img_path[cut] = '\0';
            img_name[0] = '\0';
        }

    }
    
    // Affichage de la map dans le terminal
    /*for(n=0; n<SIZE_MAP_X*SIZE_MAP_Y; n++){
            // Lire les éléments de la matrice depuis le fichier
            printf("\n< '%s' n=%d >\n", img_path, n);
            for (int j = 0; j < NB_TILE_Y; j++) {
                for (int i = 0; i < NB_TILE_X; i++) {
                    printf("|%2d", m->map[n][i][j]);
                }
                    printf("|\n");
            }
    }*/

    



    fclose(file);

    return SUCCESS;
}



/**
 * \fn int outMap(map_t m);
 * \brief Permet de savoir si le joueur est hors de la map
 * \param m est la map du jeu
 * \return 0 --> est toujours dans la map
 * \return 1 --> sortie par la gauche
 * \return 2 --> sortie par en haut
 * \return 3 --> sortie par la droite
 * \return 4 --> sortie par en bas
**/
int outMap(map_t m){

    if( m.x < 0 )
        return 1;

    if( m.y < 0 )
        return 2;

    if( m.x >= SIZE_MAP_X )
        return 3;

    if( m.x >= SIZE_MAP_Y )
        return 4;

    return 0;
}


void freeMap(map_t * m){

    for(int i=0; i<SIZE_MAP_X*SIZE_MAP_Y; i++){
        SDL_FreeSurface(m->background[i]);
        m->background[i] = NULL;
    }

    for(int i=0; i<SIZE_MAP_X*SIZE_MAP_Y; i++){
        SDL_FreeSurface(m->overlay[i]);
        m->background[i] = NULL;
    }

}

void diplayBackground(){

    if( map.y >= SIZE_MAP_Y || map.y < 0 || map.x >= SIZE_MAP_X || map.x < 0 )
        return;

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, map.background[ map.y*SIZE_MAP_X + map.x ]);
    if (texture == NULL) {
        WarningLog("Impossible de charger la texture du background");
        return;
    }

    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_DestroyTexture(texture);




}

void displayOverlay(){

    if( map.y >= SIZE_MAP_Y || map.y < 0 || map.x >= SIZE_MAP_X || map.x < 0 )
        return;

    SDL_Texture * overlay = SDL_CreateTextureFromSurface(renderer, map.overlay[ map.y*SIZE_MAP_X + map.x ]);
    if (overlay == NULL) {
        return;
    }

    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, overlay, NULL, NULL);

    SDL_DestroyTexture(overlay);
}


int canToGo( dir_t dir){

    int exit_value = SUCCESS;

    int x = player.x;
    int y = player.y;

    int i_map = map.y*SIZE_MAP_X + map.x;

    // Calcul la nouvelle position du joueur
    switch(dir){
        // S'il part vers le nord
        case nord:
            y -= player.vit;
            break;
        
        // S'il part vers le est
        case est:
            x += player.vit;
            break;
            
        // S'il part vers le sud
        case sud:
            y += player.vit;
            break;
        
        // S'il part vers l'ouest
        case ouest:
            x -= player.vit;
            break;
            
    }

    switch( outWindow(x, y) ){
        case 0:
            break;

        // Sortie vers l'ouest
        case 1:
            x = WINDOW_WIDTH - SIZE_TILE;
            i_map--;
            break;

        // Sortie vers le nord
        case 2:
            y = WINDOW_HEIGHT - SIZE_TILE ;
            i_map -= SIZE_MAP_Y;
            break;

        // Sortie vers l'est
        case 3:
            i_map++;
            x = 0;
            break;

        // Sortie vers le sud
        case 4:
            y = 1;
            i_map += SIZE_MAP_Y;
            break;
    }


    // Test collision en haut/gauche
    if( 0 > tileValue(i_map, x, y) ){
        return FAILURE;
    }

    // Test collision en haut/droit
    if( 0 > tileValue(i_map, x+SIZE_TILE-1, y) ){
        return FAILURE;
    }

    // Test collision en bas/gauche
    if( 0 > tileValue(i_map, x, y+SIZE_TILE-1) ){
        return FAILURE;
    }

    // Test collision en bas/droit
    if( 0 > tileValue(i_map, x+SIZE_TILE-1, y+SIZE_TILE-1) ){
        return FAILURE;
    }


    return exit_value;
}
/*

  |  |  |
--+--+--+--
  |  |  |
--+--+--+--
  |  |  | 



*/



// Retourne la valeur de le tuile en 'x'.'y' de la map 'i_map'
int tileValue(int i_map, int x, int y){

    return map.map[ i_map ][ (x)/SIZE_TILE ][ (y)/SIZE_TILE ];

}




/**
 * \fn int outWindow(x, y);
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

    if(x+SIZE_TILE-1 >= WINDOW_WIDTH)
        return 3;

    if(y+SIZE_TILE-1 >= WINDOW_HEIGHT)
        return 4;

    return 0;
}


