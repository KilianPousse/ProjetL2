
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
#include "struct.h"
#include "style.h"
#include "item.h"

void displayPlant( plant_t p ){

    SDL_Rect rect = { p.x, p.y, SIZE_TILE , SIZE_TILE };

    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, farm.texture[p.id][p.age], NULL, &rect);

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

    /* Blé */
    for( int i=0; i<NB_STEM_PLANT; i++ ){
        sprintf(file_name, "%s/%s_%i.png", PATH_PLANT_TEXTURE, "ble", i );
        farm.texture[ID_PLANT_BLE][i] = chargerTexture( file_name, renderer );
        if(farm.texture[ID_PLANT_BLE][i] == NULL)
            WarningLog("Probleme de blé"); 
    }

    /* Tomate */
    for( int i=0; i<NB_STEM_PLANT; i++ ){
        sprintf(file_name, "%s/%s_%i.png", PATH_PLANT_TEXTURE, "tomate", i );
        farm.texture[ID_PLANT_TOMATE][i] = chargerTexture( file_name, renderer );
        if(farm.texture[ID_PLANT_TOMATE][i] == NULL)
            WarningLog("Probleme de tomate"); 
    }



}

void freeFarm(){

    for(int i=0; i<NB_PLANTS_MAX; i++){
        for(int j=0; j<NB_STEM_PLANT; j++)
            SDL_DestroyTexture(farm.texture[i][j]);
    }


}

int farmland_empty(int * x, int * y){

    *x = player.x;
    *y = player.y;


    switch( player.dir ){

        case nord:
            *x += SIZE_TILE/3.5;
            *y -= SIZE_TILE/3.5;
            break;

        case est:
            *x += (3*SIZE_TILE)/3.5;
            *y += SIZE_TILE/3.5;
            break;

        case sud:
            *x += SIZE_TILE/3.5;
            *y += (3*SIZE_TILE)/3.5;
            break;

        case ouest:
            *x -= SIZE_TILE/3.5;
            *y += SIZE_TILE/3.5;
            break;

        default:
            break;
    }

    *x -= *x % 60; 
    *y -= *y % 60;

    for(int i=0; i<farm.n_plants; i++){

        if( farm.plants[i].x == *x && farm.plants[i].y == *y )
            return 0;

    }
    

    return 1;
}


int farmland_finalstage(int x, int y){

    for(int i=0; i<farm.n_plants; i++){

        if( farm.plants[i].x == x && farm.plants[i].y == y ){
                return ( farm.plants[i].max_age <= farm.plants[i].age );
        }

    }

    return 0;
}

item_t farmland_planttype(int x, int y){

    int id = 0;

    for(int i=0; i<farm.n_plants; i++){

        if( farm.plants[i].x == x && farm.plants[i].y == y ){
                id = farm.plants[i].id;
        }

    }

    item_t item = {0, 0};
    switch(id){

        case ID_PLANT_BLE:
            item.id = ID_ITEM_BLE;
            item.nb = 2;
            break;

        case ID_PLANT_TOMATE:
            item.id = ID_ITEM_TOMATE;
            item.nb = 2;
            break;



    }


    return item;
}

int farmland_remove(int x, int y){

    for(int i=0; i<farm.n_plants; i++){

        if( farm.plants[i].x == x && farm.plants[i].y == y ){
            i++;    
            for(; i<farm.n_plants; i++){
                farm.plants[i-1] = farm.plants[i];
            }

            (farm.n_plants)--;
            


            return 0;
        }

    }



    return 1;
}