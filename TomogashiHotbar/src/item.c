#include <stdio.h>
#include <stdlib.h>

#include "header.h"
#include "item.h"

int initItem(){

    items_surface[ID_ITEM_GRAINE_BLE] = IMG_Load(PATH_ITEM_GRAINE_BLE);
    items_surface[ID_ITEM_BLE] = IMG_Load(PATH_ITEM_BLE);
    items_surface[ID_ITEM_GRAINE_TOMATE] = IMG_Load(PATH_ITEM_GRAINE_TOMATE);
    items_surface[ID_ITEM_TOMATE] = IMG_Load(PATH_ITEM_TOMATE);


    return 0;
}


int freeItem(){

    for(int i=0; i<NB_ITEMS; i++){
        if( items_surface[i] != NULL )
            SDL_FreeSurface(items_surface[i]);
    }

    return 0;
}