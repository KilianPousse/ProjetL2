/**
 * \file save.c
 * \brief S'occupe des sauvegarde
 * \details Scripte qui charge et écrit les sauvegardes
 * \author Pousse Kilian - Pierre Elona - Vallee Alban 
 * \version alpha 2.2
 * \date 15/04/2024
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

#include "hotbar.h"
#include "inventory.h"

/* Fonction pour charger une sauvegarde existante */
int LoadSave() {
    // Ouvrir le fichier de sauvegarde en lecture
    FILE *f_save = fopen(FILE_SAVE, "r");
    if (f_save == NULL) {
        // En cas d'échec, enregistrer un message d'erreur et retourner
        ErrorLog("Sauvegarde corrompue");
        return 1;
    }

    // Initialiser l'inventaire à zéro
    for (int i = 0; i < NUM_ITEMS; i++) {
        inventory.hotbar[i].id = 0;
        inventory.hotbar[i].nb = 0;
    }
    for (int i = 0; i < NB_INVENTORY_ITEM; i++) {
        inventory.pcpl[i].id = 0;
        inventory.pcpl[i].nb = 0;
    }

    // Déclaration du tampon pour stocker les lignes lues du fichier de sauvegarde
    char buffer[256];

    // Initialisation du nombre de plantes sur la ferme à zéro
    farm.n_plants = 0;

    // Parcourir le fichier de sauvegarde ligne par ligne
    while (fscanf(f_save, "%[^\n]\n", buffer) != EOF) {
        //printf("save:%s\n", buffer);

        // Traitement des différentes informations dans la sauvegarde

        // Information joueur
        if (strncmp(buffer, "player>", strlen("player>")) == 0) {
            sscanf(buffer, "player>%d:%d:%d:%d:%d",
                &(player.x),
                &(player.y),
                &(map.x),
                &(map.y),
                &(coins)
            );
            player.x *= SIZE_TILE;
            player.y *= SIZE_TILE;
        }

        // Information de temps
        if (strncmp(buffer, "time>", strlen("time>")) == 0) {
            sscanf(buffer, "time>%ld",
                &(tps_game)
            );
        }

        // Information d'agriculture
        if (strncmp(buffer, "farm>", strlen("farm>")) == 0 && farm.n_plants < NB_PLANTS_MAX) {
            sscanf(buffer, "farm>%d:%d:%d:%d:%d",
                &(farm.plants[farm.n_plants].id),
                &(farm.plants[farm.n_plants].x),
                &(farm.plants[farm.n_plants].y),
                &(farm.plants[farm.n_plants].age),
                &(farm.plants[farm.n_plants].max_age)
            );
            farm.plants[farm.n_plants].x *= SIZE_TILE;
            farm.plants[farm.n_plants].y *= SIZE_TILE;
            farm.n_plants++;
        }

        // Information de la hotbar
        if (strncmp(buffer, "hotbar>", strlen("hotbar>")) == 0) {
            sscanf(buffer, "hotbar>(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d)",
                &(inventory.hotbar[0].id), &(inventory.hotbar[0].nb),
                &(inventory.hotbar[1].id), &(inventory.hotbar[1].nb),
                &(inventory.hotbar[2].id), &(inventory.hotbar[2].nb),
                &(inventory.hotbar[3].id), &(inventory.hotbar[3].nb),
                &(inventory.hotbar[4].id), &(inventory.hotbar[4].nb),
                &(inventory.hotbar[5].id), &(inventory.hotbar[5].nb)
            );
        }

        // Information de l'inventaire
        if (strncmp(buffer, "inventory>", strlen("inventory>")) == 0) {
            sscanf(buffer, "inventory>(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d)",
                &(inventory.pcpl[0].id), &(inventory.pcpl[0].nb),
                &(inventory.pcpl[1].id), &(inventory.pcpl[1].nb),
                &(inventory.pcpl[2].id), &(inventory.pcpl[2].nb),
                &(inventory.pcpl[3].id), &(inventory.pcpl[3].nb),
                &(inventory.pcpl[4].id), &(inventory.pcpl[4].nb),
                &(inventory.pcpl[5].id), &(inventory.pcpl[5].nb),
                &(inventory.pcpl[6].id), &(inventory.pcpl[6].nb),
                &(inventory.pcpl[7].id), &(inventory.pcpl[7].nb),
                &(inventory.pcpl[8].id), &(inventory.pcpl[8].nb),
                &(inventory.pcpl[9].id), &(inventory.pcpl[9].nb),
                &(inventory.pcpl[10].id), &(inventory.pcpl[10].nb),
                &(inventory.pcpl[11].id), &(inventory.pcpl[11].nb),
                &(inventory.pcpl[12].id), &(inventory.pcpl[12].nb),
                &(inventory.pcpl[13].id), &(inventory.pcpl[13].nb),
                &(inventory.pcpl[14].id), &(inventory.pcpl[14].nb),
                &(inventory.pcpl[15].id), &(inventory.pcpl[15].nb),
                &(inventory.pcpl[16].id), &(inventory.pcpl[16].nb),
                &(inventory.pcpl[17].id), &(inventory.pcpl[17].nb)
            );
        }

        // Information du volume
        if (strncmp(buffer, "volume>", strlen("volume>")) == 0) {
            sscanf(buffer, "volume>%hhd:%hhd",
                &(volume_music),
                &(volume_sfx)
            );
        }
    }

    // Affichage des informations chargées
    for (int i = 0; i < farm.n_plants; i++)
        printf("%d>%d:%d:%d:%d:%d\n", 
            i, 
            (int)farm.plants[i].id, 
            (int)farm.plants[ i ].x,
            (int)farm.plants[ i ].y,
            (int)farm.plants[ i ].age,
            (int)farm.plants[ i ].max_age
        );


    inventory_affiche();

    inventory.i_hotbar = 0;


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
        (inventory.hotbar[ 0 ].id), (inventory.hotbar[ 0 ].nb),
        (inventory.hotbar[ 1 ].id), (inventory.hotbar[ 1 ].nb),
        (inventory.hotbar[ 2 ].id), (inventory.hotbar[ 2 ].nb),
        (inventory.hotbar[ 3 ].id), (inventory.hotbar[ 3 ].nb),
        (inventory.hotbar[ 4 ].id), (inventory.hotbar[ 4 ].nb),
        (inventory.hotbar[ 5 ].id), (inventory.hotbar[ 5 ].nb)

        );
    
    fprintf( f_save, "inventory>(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d):(%d:%d)\n",
                (inventory.pcpl[  0 ].id), (inventory.pcpl[  0 ].nb),
                (inventory.pcpl[  1 ].id), (inventory.pcpl[  1 ].nb),
                (inventory.pcpl[  2 ].id), (inventory.pcpl[  2 ].nb),
                (inventory.pcpl[  3 ].id), (inventory.pcpl[  3 ].nb),
                (inventory.pcpl[  4 ].id), (inventory.pcpl[  4 ].nb),
                (inventory.pcpl[  5 ].id), (inventory.pcpl[  5 ].nb),
                (inventory.pcpl[  6 ].id), (inventory.pcpl[  6 ].nb),
                (inventory.pcpl[  7 ].id), (inventory.pcpl[  7 ].nb),
                (inventory.pcpl[  8 ].id), (inventory.pcpl[  8 ].nb),
                (inventory.pcpl[  9 ].id), (inventory.pcpl[  9 ].nb),
                (inventory.pcpl[ 10 ].id), (inventory.pcpl[ 10 ].nb),
                (inventory.pcpl[ 11 ].id), (inventory.pcpl[ 11 ].nb),
                (inventory.pcpl[ 12 ].id), (inventory.pcpl[ 12 ].nb),
                (inventory.pcpl[ 13 ].id), (inventory.pcpl[ 13 ].nb),
                (inventory.pcpl[ 14 ].id), (inventory.pcpl[ 14 ].nb),
                (inventory.pcpl[ 15 ].id), (inventory.pcpl[ 15 ].nb),
                (inventory.pcpl[ 16 ].id), (inventory.pcpl[ 16 ].nb),
                (inventory.pcpl[ 17 ].id), (inventory.pcpl[ 17 ].nb)

            );
    fprintf( f_save, "volume>%hhd:%hhd\n",
        (volume_music),
        (volume_sfx)
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



/* Fonction pour créer une nouvelle sauvegarde */
int newSave() {
    // Ouvrir le fichier de sauvegarde
    FILE * f_save = fopen(FILE_SAVE, "w");
    if (f_save == NULL) {
        ErrorLog("Problème de sauvegarde");
        return 1;
    }

    // Ouvrir le fichier de sauvegarde par défaut
    FILE *f_default = fopen(FILE_DEFAULT_SAVE, "r");
    if (f_default == NULL) {
        fclose(f_save);
        ErrorLog("Problème de sauvegarde par défaut");
        return 1;
    }

    char c;

    // Copier le contenu du fichier de sauvegarde par défaut vers le fichier de sauvegarde
    while (fscanf(f_default, "%c", &c) != EOF) {
        fprintf(f_save, "%c", c);
    }

    // Fermer les fichiers
    fclose(f_save);
    fclose(f_default);

    return 0;
}
