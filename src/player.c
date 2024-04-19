#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "header.h"
#include "struct.h"
#include "style.h"
#include "map.h"
#include "inventory.h"
#include "fishing.h"


#include "pnj.h"


int InitPlayer(){

    player.x = PLAYER_SIZE*10;
    player.y = PLAYER_SIZE*5;
    player.dir = sud;
    player.vit = SIZE_TILE/6;
    player.frame = 0;


    char * file_name = malloc( sizeof(char) * 124 );


    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(file_name, "%s/%s_%d.png", PATH_SPRITE_HARICOT, "back", i );
        player.sprites[0][i] = chargerTexture( file_name, renderer );
    }

    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(file_name, "%s/%s_%d.png", PATH_SPRITE_HARICOT, "right", i );
        player.sprites[1][i] = chargerTexture( file_name, renderer );
    }

    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(file_name, "%s/%s_%d.png", PATH_SPRITE_HARICOT, "forward", i );
        player.sprites[2][i] = chargerTexture( file_name, renderer );
    }

    for(int i=0; i<NB_ANIMATION; i++){
        sprintf(file_name, "%s/%s_%d.png", PATH_SPRITE_HARICOT, "left", i );
        player.sprites[3][i] = chargerTexture( file_name, renderer );
    }

    player.actions[0] = chargerTexture( IMG_ACTION_EXCLAMATION, renderer );
    player.actions[1] = chargerTexture( IMG_ACTION_DIALOGUE, renderer );
    player.actions[2] = chargerTexture( IMG_ACTION_PLANT, renderer );
    player.actions[3] = chargerTexture( IMG_ACTION_HARVEST, renderer );
    player.actions[4] = chargerTexture( IMG_ACTION_FULL_INVENTORY, renderer );

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
                SDL_DestroyTexture( player.sprites[i][j] );
        }
    }

    for(int i=0; i<NB_ANIMATION; i++){
        if( player.actions[i] != NULL )
            SDL_DestroyTexture( player.actions[i] );
    }

    return SUCCESS;
}

void displayPlayer(){

    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );

    unsigned int frame = player.frame/8;

    SDL_Rect rect = { player.x, player.y, PLAYER_SIZE , PLAYER_SIZE };

    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, player.sprites[ player.dir ][ frame ], NULL, &rect);

}


int action( int tile ){

    printf("<action:%3d>\n", tile);
    int x, y;
    catalog_t catalog;

    switch( tile ){
        case TILE_ENTER_HOUSE:
            player.x = 10*SIZE_TILE;
            player.y = 11*SIZE_TILE;
            player.dir = nord;
            map.x = 0;
            map.y = 3;
            music2fond();
            break;

        case TILE_EXIT_HOUSE:
            player.x = 13*SIZE_TILE;
            player.y = 8*SIZE_TILE;
            player.dir = sud;
            map.x = 1;
            map.y = 1;
            music2fond();
            break;

        case TILE_ENTER_CAVE :
            player.x =22*SIZE_TILE;
            player.y = 12*SIZE_TILE;
            player.dir = ouest;
            map.x = 1;
            map.y = 3;
            music2fond();
            break; 

        case TILE_EXIT_CAVE :
            player.x = 5*SIZE_TILE;
            player.y = 9*SIZE_TILE;
            player.dir = sud;
            map.x = 0;
            map.y = 2;
            music2fond();
            break; 
        

        case TILE_PNJ:
            dialog(DIALOG_TEST);
            break;

        case TILE_CRABE:
            dialog("data/dialog/crabe");
            break;

        case TILE_PY:
            dialog("data/dialog/py");
            break;

        case TILE_RISETTE:
            dialog("data/dialog/risette");
            break;

        case TILE_SERGE:
            dialog("data/dialog/serge");
            break;

        case TILE_LIVRE_SPAWN:
            dialog("data/dialog/spawn");
            break;

        case TILE_LIVRE_HOUSE:
            dialog("data/dialog/house");
            break;

        case TILE_LIVRE_MARKET:
            dialog("data/dialog/market");
            break;

        case TILE_LIVRE_FOREST:
            dialog("data/dialog/forest");
            break;

        case TILE_LIVRE_FISHING:
            dialog("data/dialog/fishing");
            break;

        case TILE_LIVRE_FARM:
            dialog("data/dialog/farm");
            break;

        case TILE_LIVRE_BEACH:
            dialog("data/dialog/beach");
            break;

        case TILE_LIVRE_CAVE:
            dialog("data/dialog/cave");
            break;

        case TILE_LIVRE_JSP:
            dialog("data/dialog/jsp");
            break;
        
        case TILE_VENDEUR_GRAINE:
            catalog.trade[0].item = ID_ITEM_GRAINE_BLE; 
            catalog.trade[0].prix = 2; 

            catalog.trade[1].item = ID_ITEM_GRAINE_TOMATE; 
            catalog.trade[1].prix = 6;  

            catalog.trade[2].item = ID_ITEM_GRAINE_TOMATE; 
            catalog.trade[2].prix = 6;

            catalog.trade[3].item = ID_ITEM_GRAINE_TOMATE; 
            catalog.trade[3].prix = 6;

            catalog.trade[4].item = ID_ITEM_GRAINE_TOMATE; 
            catalog.trade[4].prix = 6;

            catalog.n_trade = 5;
            pnj_vendeur(&catalog);
            break;
        
        case TILE_ACHETEUR_PLANTE:
            catalog.trade[0].item = ID_ITEM_BLE; 
            catalog.trade[0].prix = 3; 

            catalog.trade[1].item = ID_ITEM_TOMATE; 
            catalog.trade[1].prix = 8; 

            catalog.trade[2].item = ID_ITEM_BLE; 
            catalog.trade[2].prix = 3; 

            catalog.trade[3].item = ID_ITEM_TOMATE; 
            catalog.trade[3].prix = 8; 

            catalog.trade[4].item = ID_ITEM_TOMATE; 
            catalog.trade[4].prix = 8; 

            catalog.n_trade = 5;
            pnj_acheteur(&catalog);
            break;

        case TILE_ACHETEUR_POISSON:
            catalog.trade[0].item = ID_ITEM_POISSON; 
            catalog.trade[0].prix = 25; 

            catalog.trade[1].item = ID_ITEM_THON; 
            catalog.trade[1].prix = 50; 

            catalog.trade[2].item = ID_ITEM_POISSON_LANTERNE; 
            catalog.trade[2].prix = 75; 

            catalog.trade[3].item = ID_ITEM_KOI; 
            catalog.trade[3].prix = 100; 

            catalog.trade[4].item = ID_ITEM_REQUIN; 
            catalog.trade[4].prix = 200; 

            catalog.n_trade = 5;
            pnj_acheteur(&catalog);
            break;


        /* Sur une plantation */
        case TILE_FARMLAND:
            /* Si vide et graine dans la main --> planter */
            if( farmland_empty( &x, &y) ){
                int id_plant = 0;
                int max_age = 0;
                switch(inventory_mainhand().id){

                    /* Graine de blé */
                    case ID_ITEM_GRAINE_BLE:

                        id_plant = ID_PLANT_BLE;
                        max_age = 2;
                        break;

                    /* Graine de tomate */
                    case ID_ITEM_GRAINE_TOMATE:
                        id_plant = ID_PLANT_TOMATE;
                        max_age = 3;
                        break;
                    
                    /* Aucune graine */
                    default:
                        return tile;
                        break;

                }

                farm.plants[ farm.n_plants ].id = id_plant;
                farm.plants[ farm.n_plants ].x = x;
                farm.plants[ farm.n_plants ].y = y;
                farm.plants[ farm.n_plants ].age = 0;
                farm.plants[ farm.n_plants ].max_age = max_age;
                (farm.n_plants)++;
                inventory_use();

                for(int i=0; i<farm.n_plants; i++){
                    printf("%d> x:%d y:%d age:%d max:%d id:%d\n", i, farm.plants[ i ].x, farm.plants[ i ].y, farm.plants[ i ].age, farm.plants[ i ].max_age, farm.plants[ i ].id);
                }

            }
            else{
                /* Si plante fin d'avoir poussée */
                if( farmland_finalstage(x, y) ){

                    item_t item;
                    item = farmland_planttype(x, y);
                    
                    if( inventory_canGive( item ) ){
                        inventory_give( &item );
                        //inventory_affiche();
                        farmland_remove(x, y);
                    }     



                }



            }
            break;
        
        case TILE_FISHING:
            player.x = 60;
            player.y = 8*SIZE_TILE+10;
            player.dir = ouest;
            main_fishing();
            break;
        
        default:
            break;

    }

    


    return tile;
}

