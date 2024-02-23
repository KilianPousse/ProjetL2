#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "header.h"
#include "struct.h"
#include "style.h"


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

    printf("ici\n");

    char * file_name = malloc( sizeof(char) * 124 );


    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(file_name, "%s/%s_%d.png", "bin/assets/textures/sprites/haricot", "back", i );
        player.sprites[0][i] = IMG_Load( file_name );
    }

    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(file_name, "%s/%s_%d.png", "bin/assets/textures/sprites/haricot", "right", i );
        player.sprites[1][i] = IMG_Load( file_name );
    }

    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(file_name, "%s/%s_%d.png", "bin/assets/textures/sprites/haricot", "forward", i );
        player.sprites[2][i] = IMG_Load( file_name );
    }

    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(file_name, "%s/%s_%d.png", "bin/assets/textures/sprites/haricot", "left", i );
        player.sprites[3][i] = IMG_Load( file_name );
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

    return SUCCESS;
}


void displayPlayer(){

    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );

    unsigned int frame = player.frame%23;

    if( 0 < frame && frame < 6 )
        frame = 1;
    else if( 6 <= frame && frame < 12 )
        frame = 0;
    else if( 12 <= frame && frame < 18 )
        frame = 2;
    else if( 18 <= frame )
        frame = 0;

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