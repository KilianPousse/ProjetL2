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

#define SORTIE_GAUCHE   1
#define SORTIE_HAUT     2
#define SORTIE_DROITE   3
#define SORTIE_BAS      4
#define PAS_SORTIE      0



/* Fonction à tester: newSave(); */
/* Fonction qui verifie si vous êtes toujours dans l'ecran */
int outWindow(int x, int y){

    /* Sortie à Gauche */
    if(x < 0)
        return 1;

    /* Sortie en haut */
    if(y < 0)
        return 2;
    
    /* Sortie à droite */
    if(x+SIZE_TILE-1 >= WINDOW_WIDTH)
        return 3;
    
    /* Sortie en bas */
    if(y+SIZE_TILE-1 >= WINDOW_HEIGHT)
        return 4;

    /* Pas sortie */
    return 0;
}




void outWindow_test( ){

    CU_ASSERT_EQUAL( outWindow( -100, 100 ) , SORTIE_GAUCHE );
    CU_ASSERT_EQUAL( outWindow( 100, -100 ) , SORTIE_HAUT );
    CU_ASSERT_EQUAL( outWindow( WINDOW_WIDTH + 100, 100 ) , SORTIE_DROITE );
    CU_ASSERT_EQUAL( outWindow( 100, WINDOW_HEIGHT + 100 ) , SORTIE_BAS );

    CU_ASSERT_EQUAL( outWindow( 100, 100 ) , PAS_SORTIE );

}



int main(int argc, char * argv[]){

    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("outWindow Suite", NULL, NULL);
    CU_add_test(suite, "outWindow_test", outWindow_test);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}