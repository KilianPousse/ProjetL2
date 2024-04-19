#include <stdio.h>
#include <CUnit/Basic.h>
#include <string.h>
#include <time.h>

#include "header.h"
#include "inventary.h"
#include "map.h"

#define NUM_ITEMS 6

player_t player_test;
map_t map_test;
int coins_test;
time_t tps_game_test;
int volume_music_test ;
int volume_sfx_test;



/* Fonction à tester: newSave(); */
/* Fonction pour charger une sauvegarde existante */
int LoadSave() {
    // Ouvrir le fichier de sauvegarde en lecture
    FILE *f_save = fopen("data/save", "r");
    if (f_save == NULL) {
        // En cas d'échec, enregistrer un message d'erreur et retourner
        printf("Sauvegarde corrompue\n");
        return 1;
    }

    // Initialiser l'inventaire à zéro
    for (int i = 0; i < NUM_ITEMS; i++) {
        inventary.hotbar[i].id = 0;
        inventary.hotbar[i].nb = 0;
    }
    for (int i = 0; i < NB_INVENTARY_ITEM; i++) {
        inventary.pcpl[i].id = 0;
        inventary.pcpl[i].nb = 0;
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
                &(inventary.hotbar[0].id), &(inventary.hotbar[0].nb),
                &(inventary.hotbar[1].id), &(inventary.hotbar[1].nb),
                &(inventary.hotbar[2].id), &(inventary.hotbar[2].nb),
                &(inventary.hotbar[3].id), &(inventary.hotbar[3].nb),
                &(inventary.hotbar[4].id), &(inventary.hotbar[4].nb),
                &(inventary.hotbar[5].id), &(inventary.hotbar[5].nb)
            );
        }

        // Information de l'inventaire
        if (strncmp(buffer, "inventary>", strlen("inventary>")) == 0) {
            sscanf(buffer, "inventary>(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d):(%hhd:%d)",
                &(inventary.pcpl[0].id), &(inventary.pcpl[0].nb),
                &(inventary.pcpl[1].id), &(inventary.pcpl[1].nb),
                &(inventary.pcpl[2].id), &(inventary.pcpl[2].nb),
                &(inventary.pcpl[3].id), &(inventary.pcpl[3].nb),
                &(inventary.pcpl[4].id), &(inventary.pcpl[4].nb),
                &(inventary.pcpl[5].id), &(inventary.pcpl[5].nb),
                &(inventary.pcpl[6].id), &(inventary.pcpl[6].nb),
                &(inventary.pcpl[7].id), &(inventary.pcpl[7].nb),
                &(inventary.pcpl[8].id), &(inventary.pcpl[8].nb),
                &(inventary.pcpl[9].id), &(inventary.pcpl[9].nb),
                &(inventary.pcpl[10].id), &(inventary.pcpl[10].nb),
                &(inventary.pcpl[11].id), &(inventary.pcpl[11].nb),
                &(inventary.pcpl[12].id), &(inventary.pcpl[12].nb),
                &(inventary.pcpl[13].id), &(inventary.pcpl[13].nb),
                &(inventary.pcpl[14].id), &(inventary.pcpl[14].nb),
                &(inventary.pcpl[15].id), &(inventary.pcpl[15].nb),
                &(inventary.pcpl[16].id), &(inventary.pcpl[16].nb),
                &(inventary.pcpl[17].id), &(inventary.pcpl[17].nb)
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

    inventary.i_hotbar = 0;


    fclose( f_save );
    return 0;
}


void LoadSave_test( ){

    CU_ASSERT_EQUAL( player.x, player_test.x );
    CU_ASSERT_EQUAL( player.y, player_test.y );

    CU_ASSERT_EQUAL( coins, coins_test );
    CU_ASSERT_EQUAL( tps_game, tps_game_test );

    CU_ASSERT_EQUAL( map.x, map_test.x );
    CU_ASSERT_EQUAL( map.y, map_test.y );

    CU_ASSERT_EQUAL( volume_music, volume_music_test );
    CU_ASSERT_EQUAL( volume_sfx, volume_sfx_test );

}



int main(int argc, char * argv[]){

    
    player_test.x = 11 * SIZE_TILE;
    player_test.y = 3 * SIZE_TILE;
    
    coins_test = 333;

    map_test.x = 1 ;
    map_test.y = 1 ;

    volume_music_test = 64;
    volume_sfx_test = 72;

    tps_game_test = 14523;

    LoadSave();

    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("LoadSave Suite", NULL, NULL);
    CU_add_test(suite, "LoadSave_test", LoadSave_test);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}