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


int initMap(map_t * m){

    m->x = 1;
    m->y = 1;
    
    char img_overlay[255] = "";

    for(int n=0; n<SIZE_MAP_X*SIZE_MAP_Y; n++){
        m->background[ n ] = NULL;

        m->overlay[ n ] = NULL;
        sprintf(img_overlay ,"%s%d.png", PATH_BACKGROUND_OVERLAY, n);
        m->overlay[ n ] = chargerTexture(img_overlay, renderer);

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
    char img_path[255] = PATH_BACKGROUND;
    int cut = strlen(img_path);
    int n = 0;
    char c;

    while( (c = fgetc(file)) != EOF && n<SIZE_MAP_X*SIZE_MAP_Y){

        if(c == '$'){

            fscanf(file, "%s", img_name);

            strcat(img_path, img_name);
            m->background[ n ] = chargerTexture(img_path, renderer);

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




/* Fonction qui verifie si vous êtes toujours sur la map */
int outMap(map_t m){

    /* Sortie à Gauche */
    /*

        [ ] | [ ] | [ ]
        ----+-----+----
      X [ ] | [ ] | [ ]
        ----+-----+----
        [ ] | [ ] | [ ]

    */
    if( m.x < 0 )
        return 1;

    /* Sortie en haut */
    /*
               X
        [ ] | [ ] | [ ]
        ----+-----+----
        [ ] | [ ] | [ ]
        ----+-----+----
        [ ] | [ ] | [ ]

    */
    if( m.y < 0 )
        return 2;

    /* Sortie à droite */
    /*

        [ ] | [ ] | [ ]
        ----+-----+----
        [ ] | [ ] | [ ] X
        ----+-----+----
        [ ] | [ ] | [ ]

    */
    if( m.x >= SIZE_MAP_X )
        return 3;
    
    /* Sortie en bas */
    /*

        [ ] | [ ] | [ ]
        ----+-----+----
        [ ] | [ ] | [ ]
        ----+-----+----
        [ ] | [ ] | [ ]
               X
    */
    if( m.y >= SIZE_MAP_Y )
        return 4;

    /* Pas sortie */
    /*

        [ ] | [ ] | [ ]
        ----+-----+----
        [ ] | [X] | [ ]
        ----+-----+----
        [ ] | [ ] | [ ]

    */
    return 0;
}


void freeMap(map_t * m){

    for(int i=0; i<SIZE_MAP_X*SIZE_MAP_Y; i++){
        SDL_DestroyTexture(m->background[i]);
        m->background[i] = NULL;
    }

    for(int i=0; i<SIZE_MAP_X*SIZE_MAP_Y; i++){
        SDL_DestroyTexture(m->overlay[i]);
        m->background[i] = NULL;
    }

}

void diplayBackground(){

    if( map.y >= SIZE_MAP_Y || map.y < 0 || map.x >= SIZE_MAP_X || map.x < 0 )
        return;

    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, map.background[ map.y*SIZE_MAP_X + map.x ], NULL, NULL);
}

void displayOverlay(){

    if( map.y >= SIZE_MAP_Y || map.y < 0 || map.x >= SIZE_MAP_X || map.x < 0 )
        return;

    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, map.overlay[ map.y*SIZE_MAP_X + map.x ], NULL, NULL);
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
    if( 0 > tileValue(i_map, x+PLAYER_SIZE-1, y) ){
        return FAILURE;
    }

    // Test collision en bas/gauche
    if( 0 > tileValue(i_map, x, y+PLAYER_SIZE-1) ){
        return FAILURE;
    }

    // Test collision en bas/droit
    if( 0 > tileValue(i_map, x+PLAYER_SIZE-1, y+PLAYER_SIZE-1) ){
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




/* Fonction qui verifie si vous êtes toujours dans l'ecran */
int outWindow(int x, int y){

    /* Sortie à Gauche */
    if(x < 0)
        return 1;

    /* Sortie en haut */
    if(y < 0)
        return 2;
    
    /* Sortie à droite */
    if(x+SIZE_TILE-1 >= WINDOW_WIDTH)
        return 3;
    
    /* Sortie en bas */
    if(y+SIZE_TILE-1 >= WINDOW_HEIGHT)
        return 4;

    /* Pas sortie */
    return 0;
}


