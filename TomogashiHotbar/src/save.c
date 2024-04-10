#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

#include "hotbar.h"
#include "inventary.h"


int LoadSave(  ){

    FILE * f_save = fopen( FILE_SAVE, "r" );
    if( f_save == NULL ){
        WarningLog( "Sauvegarde corrompue" );
        return 1;
    }

    for(int i=0; i<NUM_ITEMS; i++){
        inventary.hotbar[i].id = 0;
        inventary.hotbar[i].nb = 0;
    }
    for(int i=0; i<NB_INVENTARY_ITEM; i++){
        inventary.pcpl[i].id = 0;
        inventary.pcpl[i].nb = 0;
    }

    char buffer[256];

    farm.n_plants = 0;

    while( fscanf( f_save, "%[^\n]\n", buffer ) != EOF ){

        printf("save:%s\n", buffer);

        /* Information joueur */
        if( strncmp( buffer, "player>", strlen("player>") ) == 0 ){
            sscanf( buffer, "player>%d:%d:%d:%d:%d",
                &(player.x),
                &(player.y),
                &(map.x),
                &(map.y),
                &(coins)
            );
            player.x *= SIZE_TILE;
            player.y *= SIZE_TILE;
        }

        /* Information de temps */
        if( strncmp( buffer, "time>", strlen("time>") ) == 0 ){
            sscanf( buffer, "time>%ld",
                &(tps_game)
            );
        }

        /* Information d'agriculture */
        if( strncmp( buffer, "farm>", strlen("farm>") ) == 0 && farm.n_plants < NB_PLANTS_MAX){
            sscanf( buffer, "farm>%d:%d:%d:%d:%d",
                &(farm.plants[ farm.n_plants ].id),
                &(farm.plants[ farm.n_plants ].x),
                &(farm.plants[ farm.n_plants ].y),
                &(farm.plants[ farm.n_plants ].age),
                &(farm.plants[ farm.n_plants ].max_age)
            );
            farm.plants[ farm.n_plants ].x *= SIZE_TILE;
            farm.plants[ farm.n_plants ].y *= SIZE_TILE;
            farm.n_plants++;
        }

        /* Information de la hotbar */
        if( strncmp( buffer, "hotbar>", strlen("hotbar>") ) == 0 ){
            sscanf( buffer, "hotbar>(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d)",
                &(inventary.hotbar[ 0 ].id), &(inventary.hotbar[ 0 ].nb),
                &(inventary.hotbar[ 1 ].id), &(inventary.hotbar[ 1 ].nb),
                &(inventary.hotbar[ 2 ].id), &(inventary.hotbar[ 2 ].nb),
                &(inventary.hotbar[ 3 ].id), &(inventary.hotbar[ 3 ].nb),
                &(inventary.hotbar[ 4 ].id), &(inventary.hotbar[ 4 ].nb),
                &(inventary.hotbar[ 5 ].id), &(inventary.hotbar[ 5 ].nb)

            );
        }

        /* Information de l'inventaire */
        if( strncmp( buffer, "inventary>", strlen("inventary>") ) == 0 ){
            sscanf( buffer, "inventary>(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d)",
                &(inventary.pcpl[  0 ].id), &(inventary.pcpl[  0 ].nb),
                &(inventary.pcpl[  1 ].id), &(inventary.pcpl[  1 ].nb),
                &(inventary.pcpl[  2 ].id), &(inventary.pcpl[  2 ].nb),
                &(inventary.pcpl[  3 ].id), &(inventary.pcpl[  3 ].nb),
                &(inventary.pcpl[  4 ].id), &(inventary.pcpl[  4 ].nb),
                &(inventary.pcpl[  5 ].id), &(inventary.pcpl[  5 ].nb),
                &(inventary.pcpl[  6 ].id), &(inventary.pcpl[  6 ].nb),
                &(inventary.pcpl[  7 ].id), &(inventary.pcpl[  7 ].nb),
                &(inventary.pcpl[  8 ].id), &(inventary.pcpl[  8 ].nb),
                &(inventary.pcpl[  9 ].id), &(inventary.pcpl[  9 ].nb),
                &(inventary.pcpl[ 10 ].id), &(inventary.pcpl[ 10 ].nb),
                &(inventary.pcpl[ 11 ].id), &(inventary.pcpl[ 11 ].nb),
                &(inventary.pcpl[ 12 ].id), &(inventary.pcpl[ 12 ].nb),
                &(inventary.pcpl[ 13 ].id), &(inventary.pcpl[ 13 ].nb),
                &(inventary.pcpl[ 14 ].id), &(inventary.pcpl[ 14 ].nb),
                &(inventary.pcpl[ 15 ].id), &(inventary.pcpl[ 15 ].nb),
                &(inventary.pcpl[ 16 ].id), &(inventary.pcpl[ 16 ].nb),
                &(inventary.pcpl[ 17 ].id), &(inventary.pcpl[ 17 ].nb)

            );
        }

    }

    for(int i=0; i<farm.n_plants; i++)
        printf("%d>%d:%d:%d:%d:%d\n", i, (int)farm.plants[ i ].id
    , (int)farm.plants[ i ].x, (int)farm.plants[ i ].y, (int)farm.plants[ i ].age, (int)farm.plants[ i ].max_age);


    inventary_affiche();

    inventary.i_hotbar = 0;


    fclose( f_save );
    return 0;
}




int SaveSave( ){

    FILE * f_save = fopen( FILE_SAVE, "w" );
    if( f_save == NULL ){
        WarningLog( "Problème de sauvegarde" );
        return 1;
    }

    fprintf( f_save, "player>%d:%d:%d:%d:%d\n",
        (player.x/SIZE_TILE),
        (player.y/SIZE_TILE),
        (map.x),
        (map.y),
        (coins)
    );


    fprintf( f_save, "time>%ld\n",
        (tps_game)
    );

    fprintf( f_save, "hotbar>(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d)\n",
        (inventary.hotbar[ 0 ].id), (inventary.hotbar[ 0 ].nb),
        (inventary.hotbar[ 1 ].id), (inventary.hotbar[ 1 ].nb),
        (inventary.hotbar[ 2 ].id), (inventary.hotbar[ 2 ].nb),
        (inventary.hotbar[ 3 ].id), (inventary.hotbar[ 3 ].nb),
        (inventary.hotbar[ 4 ].id), (inventary.hotbar[ 4 ].nb),
        (inventary.hotbar[ 5 ].id), (inventary.hotbar[ 5 ].nb)

        );
    
    fprintf( f_save, "inventary>(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d)\n",
                (inventary.pcpl[  0 ].id), (inventary.pcpl[  0 ].nb),
                (inventary.pcpl[  1 ].id), (inventary.pcpl[  1 ].nb),
                (inventary.pcpl[  2 ].id), (inventary.pcpl[  2 ].nb),
                (inventary.pcpl[  3 ].id), (inventary.pcpl[  3 ].nb),
                (inventary.pcpl[  4 ].id), (inventary.pcpl[  4 ].nb),
                (inventary.pcpl[  5 ].id), (inventary.pcpl[  5 ].nb),
                (inventary.pcpl[  6 ].id), (inventary.pcpl[  6 ].nb),
                (inventary.pcpl[  7 ].id), (inventary.pcpl[  7 ].nb),
                (inventary.pcpl[  8 ].id), (inventary.pcpl[  8 ].nb),
                (inventary.pcpl[  9 ].id), (inventary.pcpl[  9 ].nb),
                (inventary.pcpl[ 10 ].id), (inventary.pcpl[ 10 ].nb),
                (inventary.pcpl[ 11 ].id), (inventary.pcpl[ 11 ].nb),
                (inventary.pcpl[ 12 ].id), (inventary.pcpl[ 12 ].nb),
                (inventary.pcpl[ 13 ].id), (inventary.pcpl[ 13 ].nb),
                (inventary.pcpl[ 14 ].id), (inventary.pcpl[ 14 ].nb),
                (inventary.pcpl[ 15 ].id), (inventary.pcpl[ 15 ].nb),
                (inventary.pcpl[ 16 ].id), (inventary.pcpl[ 16 ].nb),
                (inventary.pcpl[ 17 ].id), (inventary.pcpl[ 17 ].nb)

            );

    for(int i=0; i<farm.n_plants; i++){
        fprintf(f_save, "farm>%d:%d:%d:%d:%d\n",
                (farm.plants[ i ].id),
                (farm.plants[ i ].x)/SIZE_TILE,
                (farm.plants[ i ].y)/SIZE_TILE,
                (farm.plants[ i ].age),
                (farm.plants[ i ].max_age)
        );
    }


    fclose( f_save );

}