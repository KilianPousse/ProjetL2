#include <stdio.h>
#include <stdlib.h>

#include "header.h"
#include "item.h"

int initItem(){

    items_surface[ID_ITEM_GRAINE_BLE] = IMG_Load(PATH_ITEM_GRAINE_BLE);
    items_surface[ID_ITEM_BLE] = IMG_Load(PATH_ITEM_BLE);
    items_surface[ID_ITEM_GRAINE_TOMATE] = IMG_Load(PATH_ITEM_GRAINE_TOMATE);
    items_surface[ID_ITEM_TOMATE] = IMG_Load(PATH_ITEM_TOMATE);
    items_surface[ID_ITEM_POISSON] = IMG_Load(PATH_ITEM_POISSON);
    items_surface[ID_ITEM_THON] = IMG_Load(PATH_ITEM_THON);
    items_surface[ID_ITEM_POISSON_LANTERNE] = IMG_Load(PATH_ITEM_POISSON_LANTERNE);
    items_surface[ID_ITEM_KOI] = IMG_Load(PATH_ITEM_KOI);
    items_surface[ID_ITEM_REQUIN] = IMG_Load(PATH_ITEM_REQUIN);
    items_surface[ID_ITEM_POISSON_DORE] = IMG_Load(PATH_ITEM_POISSON_DORE);


    return 0;
}


int freeItem(){

    for(int i=0; i<NB_ITEMS; i++){
        if( items_surface[i] != NULL )
            SDL_FreeSurface(items_surface[i]);
    }

    return 0;
}