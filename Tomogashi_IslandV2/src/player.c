#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "header.h"
#include "struct.h"
#include "style.h"
#include "map.h"


/**
 * \fn void ErrorLog(char * message);
 * \brief Stop le jeu si il y a une erreur dans le programme
 * \param message est le message d'erreur à afficher dans le terminal
**/

int InitPlayer(){

    player.x = SIZE_TILE*10;
    player.y = SIZE_TILE*5;
    player.dir = sud;
    player.vit = SIZE_TILE/6;
    player.frame = 0;


    char * file_name = malloc( sizeof(char) * 124 );


    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(file_name, "%s/%s_%d.png", PATH_SPRITE_HARICOT, "back", i );
        player.sprites[0][i] = IMG_Load( file_name );
    }

    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(file_name, "%s/%s_%d.png", PATH_SPRITE_HARICOT, "right", i );
        player.sprites[1][i] = IMG_Load( file_name );
    }

    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(file_name, "%s/%s_%d.png", PATH_SPRITE_HARICOT, "forward", i );
        player.sprites[2][i] = IMG_Load( file_name );
    }

    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(file_name, "%s/%s_%d.png", PATH_SPRITE_HARICOT, "left", i );
        player.sprites[3][i] = IMG_Load( file_name );
    }

    player.actions[0] = IMG_Load( IMG_ACTION_EXCLAMATION );
    player.actions[1] = IMG_Load( IMG_ACTION_DIALOGUE );
    player.actions[2] = NULL;
    player.actions[3] = NULL;
    player.actions[4] = NULL;

    for(int i=0; i<NB_ANIMATION; i++){
        if( player.actions[i] == NULL )
            WarningLog( "Impossible de charger une icon d'action" );
    }


    free( file_name );

    return SUCCESS;
}



int FreePlayer(){

    for(int i=0; i<4; i++){
        for(int j=0; j<NB_ANIMATION; j++){
            if( player.sprites[i][j] )
                SDL_FreeSurface( player.sprites[i][j] );
        }
    }

    for(int i=0; i<NB_ANIMATION; i++){
        if( player.actions[i] != NULL )
            SDL_FreeSurface( player.actions[i] );
    }

    return SUCCESS;
}


void displayPlayer(){

    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );

    unsigned int frame = player.frame/8;

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, player.sprites[ player.dir ][ frame ]);
    if (texture == NULL) {
        WarningLog("Impossible de charger la texture du sprite du joueur");
        return;
    }

    SDL_Rect rect = { player.x, player.y, SIZE_TILE, SIZE_TILE };

    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);

}



int action( int tile ){

    printf("<action:%3d>\n", tile);

    switch( tile ){

        case TILE_ENTER_HOUSE:
            player.x = 10*SIZE_TILE;
            player.y = 11*SIZE_TILE;
            player.dir = nord;
            map.x = 0;
            map.y = 3;
            break;

        case TILE_EXIT_HOUSE:
            player.x = 5*SIZE_TILE;
            player.y = 6*SIZE_TILE;
            player.dir = sud;
            map.x = 1;
            map.y = 1;
            break;

        case TILE_PNJ:
            dialog(DIALOG_TEST);
            break;
        
        default:
            break;

    }

    


    return tile;
}
