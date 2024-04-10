
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
#include "struct.h"
#include "style.h"

void displayPlant( plant_t p ){

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, farm.texture[p.id][!(p.age>0)]);
    if (texture == NULL) {
        WarningLog("Impossible de charger la texture de la plante");
        return;
    }

    SDL_Rect rect = { p.x, p.y, SIZE_TILE , SIZE_TILE };

    // Copier la texture sur tout le rendu (pour remplir l'écran)
    //SDL_RenderFillRect(renderer, &rect);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    
    SDL_DestroyTexture(texture);

}

void displayFarm( int i_map ){

    if( i_map != IMAP_FARM )
        return;

    for(int i=0; i<farm.n_plants; i++){
        if( farm.plants[i].id != 0 )
            displayPlant( farm.plants[i] );
    }

}

int initFarmTexture(  ){

    char file_name[125];

    /* Carrot */
    for( int i=0; i<NB_STEM_PLANT; i++ ){
        sprintf(file_name, "%s/%s_%i.png", PATH_PLANT_TEXTURE, "carrot", i );
        farm.texture[ID_PLANT_CARROT][i] = IMG_Load( file_name );
        if(farm.texture[ID_PLANT_CARROT][i] == NULL)
            WarningLog("Probleme de carrot");
    }


}