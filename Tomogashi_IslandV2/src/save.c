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


    }



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

    fclose( f_save );

}