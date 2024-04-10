#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "header.h"
#include "struct.h"
#include "style.h"
#include "hotbar.h"

#include "inventary.h"


item_t inventary_mainhand(  ){
    return inventary.hotbar[inventary.i_hotbar];
}

int inventary_use(  ){

    if( inventary.hotbar[inventary.i_hotbar].nb <= 0 )
        return 1;

    if( inventary.hotbar[inventary.i_hotbar].nb == 1 ){
        inventary.hotbar[inventary.i_hotbar].id = 0;
    }

    (inventary.hotbar[inventary.i_hotbar].nb)--;
    return 0;
}

int inventary_contains_hotbar( unsigned char id, int limit ){

    int j = 0;

    for(int i=0; i<NUM_ITEMS; i++){
        if( inventary.hotbar[ i ].id == id ){
            j++;
            if( j == limit )
                return i;
        }
    }

    return -1;
}

int inventary_contains_pcpl( unsigned char id, int limit ){

    int j = 0;

    for(int i=0; i<NB_INVENTARY_ITEM; i++){
        if( inventary.pcpl[ i ].id == id ){
            j++;
            if( j == limit )
                return i;
        }
    }

    return -1;
}


void inventary_affiche(  ){


    for(int i=0; i<NB_INVENTARY_ITEM; i++){
        if(i%NUM_ITEMS == 0)
            printf("\n");
        printf(" [id:%02d|nb:%02d]", inventary.pcpl[i].id, inventary.pcpl[i].nb );
    }
    printf("\n");


    printf("-------------------------------------------------------------------------------------\n");

    for(int i=0; i<NB_HOTBAR_ITEM; i++){
        printf(" [id:%02d|nb:%02d]", inventary.hotbar[i].id, inventary.hotbar[i].nb );
    }
    printf("\n");


}


int inventary_clear(){

    for(int i=0; i<NB_HOTBAR_ITEM; i++){
        inventary.hotbar[i].nb = 0;
        inventary.hotbar[i].id = 0;
    }

    for(int i=0; i<NB_INVENTARY_ITEM; i++){
        inventary.pcpl[i].nb = 0;
        inventary.pcpl[i].id = 0;
    }

    return 0;
}

int inventary_canGive( item_t item ){

    int nb = item.nb;

    for( int i=0; i<NB_HOTBAR_ITEM; i++ ){
        //printf("/hotbar:[id:%d|nb:%d]  -- item[id:%d|nb:%d]/\n", inventary.hotbar[i].id, inventary.hotbar[i].nb, item.id, item.nb);
        if( inventary.hotbar[i].nb <= 0 && inventary.hotbar[i].id == 0)
            return 1;
        
        if( inventary.hotbar[i].id == item.id  ){
            nb = (inventary.hotbar[i].nb + nb) - MAX_ITEM_STACK;

            if( nb <= 0 )
                return 2;
        }


    }

    for( int i=0; i<NB_INVENTARY_ITEM; i++ ){
        //printf("/iventary:[id:%d|nb:%d]  -- item[id:%d|nb:%d]/\n", inventary.pcpl[i].id, inventary.pcpl[i].nb, item.id, item.nb);
        if( inventary.pcpl[i].nb <= 0 && inventary.pcpl[i].id == 0 )
            return 1;
        
        if( inventary.pcpl[i].id == item.id  ){
            nb = (inventary.pcpl[i].nb + nb) - MAX_ITEM_STACK;

            if( nb <= 0 )
                return 2;
        }


    }


    return 0;
}

int inventary_give( item_t * item ){

    if( item->nb > MAX_ITEM_STACK )
        item->nb = MAX_ITEM_STACK;

    int i_hotbar = -1;
    int i_pcpl = -1;

    for(int i=0; i<NB_HOTBAR_ITEM; i++){

        if( i_hotbar < 0 && inventary.hotbar[i].nb <= 0 && inventary.hotbar[i].id == 0 )
            i_hotbar = i;

        if( inventary.hotbar[i].id == item->id  ){
            inventary.hotbar[i].nb += item->nb;
            item->nb = inventary.hotbar[i].nb - MAX_ITEM_STACK;
            if( inventary.hotbar[i].nb > MAX_ITEM_STACK )
                inventary.hotbar[i].nb = MAX_ITEM_STACK;

            if( item->nb <= 0 )
                return 0;
        }

    }

    for(int i=0; i<NB_INVENTARY_ITEM; i++){

        if( i_hotbar < 0 && i_pcpl < 0 && inventary.pcpl[i].nb <= 0 && inventary.pcpl[i].id == 0 )
            i_pcpl = i;

        if( inventary.pcpl[i].id == item->id  ){
            inventary.pcpl[i].nb += item->nb;
            item->nb = inventary.hotbar[i].nb - MAX_ITEM_STACK;
            if( inventary.pcpl[i].nb > MAX_ITEM_STACK )
                inventary.pcpl[i].nb = MAX_ITEM_STACK;

            if( item->nb <= 0 )
                return 0;
        }

    }

    if( item->nb > 0 ){

        if( i_hotbar >= 0 ){
            inventary.hotbar[i_hotbar] = *item;
            return 0;
        }

        if( i_pcpl >= 0 ){
            inventary.pcpl[i_pcpl] = *item;
            return 0;
        }

    }

    return 1;
}