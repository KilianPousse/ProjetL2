#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"


int LoadSave(  ){

    FILE * f_save = fopen( FILE_SAVE, "r" );
    if( f_save == NULL ){
        WarningLog( "Sauvegarde corrompue" );
        return 1;
    }

    char buffer[256];

    farm.n_plants = 0;

    while( fscanf( f_save, "%[^\n]\n", buffer ) != EOF ){

        /* Information joueur */
        if( strncmp( buffer, "player>", strlen("player>") ) == 0 ){
            sscanf( buffer, "player>%d:%d:%d:%d",
                &(player.x),
                &(player.y),
                &(map.x),
                &(map.y)
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
            sscanf( buffer, "farm>%d:%d:%d:%ld",
                &(farm.plants[ farm.n_plants ].id),
                &(farm.plants[ farm.n_plants ].x),
                &(farm.plants[ farm.n_plants ].y),
                &(farm.plants[ farm.n_plants ].age)
            );
            farm.n_plants++;
        }

    }

    for(int i=0; i<farm.n_plants; i++)
        printf("%d>%d:%d:%d:%d\n", i, (int)farm.plants[ i ].id
    , (int)farm.plants[ i ].x, (int)farm.plants[ i ].y, (int)farm.plants[ i ].age);



    fclose( f_save );
    return 0;
}




int SaveSave( ){

    FILE * f_save = fopen( FILE_SAVE, "w" );
    if( f_save == NULL ){
        WarningLog( "Problème de sauvegarde" );
        return 1;
    }

    fprintf( f_save, "player>%d:%d:%d:%d\n",
        (player.x/SIZE_TILE),
        (player.y/SIZE_TILE),
        (map.x),
        (map.y)
    );


    fprintf( f_save, "time>%ld\n",
        (tps_game)
    );

    for(int i=0; i<farm.n_plants; i++){
        fprintf(f_save, "farm>%d:%d:%d:%ld\n",
                (farm.plants[ i ].id),
                (farm.plants[ i ].x),
                (farm.plants[ i ].y),
                (farm.plants[ i ].age)
        );
    }

    fclose( f_save );

}