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

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

    for(int n=0; n<SIZE_MAP_X*SIZE_MAP_Y; n++){
        m->background[ n ] = NULL;

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
    char img_path[255] = "assets/textures/background/";
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
    
    /*for(n=0; n<SIZE_MAP_X*SIZE_MAP_Y; n++){
            // Lire les éléments de la matrice depuis le fichier
            printf("\n< '%s' n=%d >\n", img_path, n);
            for (int j = 0; j < NB_TILE_Y; j++) {
                for (int i = 0; i < NB_TILE_X; i++) {
                    printf(" | %3d", m->map[n][i][j]);
                }
                    printf(" |\n");
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


int canToGo(player_t * p, dir_t dir){

    int exit_value = SUCCESS;

    int x = p->x;
    int y = p->y;

    switch(dir){
        case nord:
            y -= p->vit;
            break;
        
        case est:
            x += p->vit;
            break;
            
        case sud:
            y += p->vit;
            break;
        
        case ouest:
            x -= p->vit;
            break;
            
    }


    if (map.map[map.y*SIZE_MAP_X + map.x][x/SIZE_TILE][y/SIZE_TILE] < 0)
        exit_value = FAILURE;

    if (map.map[map.y*SIZE_MAP_X + map.x][(x+SIZE_TILE-1)/SIZE_TILE][y/SIZE_TILE] < 0)
        exit_value = FAILURE;

    if (map.map[map.y*SIZE_MAP_X + map.x][x/SIZE_TILE][(y+SIZE_TILE-1)/SIZE_TILE] < 0)
        exit_value = FAILURE;

    if (map.map[map.y*SIZE_MAP_X + map.x][(x+SIZE_TILE-1)/SIZE_TILE][(y+SIZE_TILE-1)/SIZE_TILE] < 0)
        exit_value = FAILURE;

    

    return exit_value;
}