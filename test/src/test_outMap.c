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
/* Fonction qui verifie si vous êtes toujours sur la map */
int outMap(map_t m){

    /* Sortie à Gauche */
    /*

        [ ] | [ ] | [ ]
        ----+-----+----
      X [ ] | [ ] | [ ]
        ----+-----+----
        [ ] | [ ] | [ ]

    */
    if( m.x < 0 )
        return 1;

    /* Sortie en haut */
    /*
               X
        [ ] | [ ] | [ ]
        ----+-----+----
        [ ] | [ ] | [ ]
        ----+-----+----
        [ ] | [ ] | [ ]

    */
    if( m.y < 0 )
        return 2;

    /* Sortie à droite */
    /*

        [ ] | [ ] | [ ]
        ----+-----+----
        [ ] | [ ] | [ ] X
        ----+-----+----
        [ ] | [ ] | [ ]

    */
    if( m.x >= SIZE_MAP_X )
        return 3;
    
    /* Sortie en bas */
    /*

        [ ] | [ ] | [ ]
        ----+-----+----
        [ ] | [ ] | [ ]
        ----+-----+----
        [ ] | [ ] | [ ]
               X
    */
    if( m.y >= SIZE_MAP_Y )
        return 4;

    /* Pas sortie */
    /*

        [ ] | [ ] | [ ]
        ----+-----+----
        [ ] | [X] | [ ]
        ----+-----+----
        [ ] | [ ] | [ ]

    */
    return 0;
}




void outWindow_test( ){

    printf("\nSIZE_MAP_X: %d // SIZE_MAP_Y: %d\n", SIZE_MAP_X, SIZE_MAP_Y );

    map_t m_gauche;
    m_gauche.x = -1;
    m_gauche.y = 1;
    printf("\nGAUCHE:\n x:%d  y:%d\n --> %d\n", m_gauche.x, m_gauche.y, outMap( m_gauche ) );

    map_t m_haut;
    m_haut.x = 1;
    m_haut.y = -1;
    printf("\nHAUT:\n x:%d  y:%d\n --> %d\n", m_haut.x, m_haut.y, outMap( m_haut ) );

    map_t m_droite;
    m_droite.x = SIZE_MAP_X + 1;
    m_droite.y = 1;
    printf("\nDROITE:\n x:%d  y:%d\n --> %d\n", m_droite.x, m_droite.y, outMap( m_droite ) );

    map_t m_bas;
    m_bas.x = 1;
    m_bas.y = SIZE_MAP_Y + 1;
    printf("\nBAS:\n x:%d  y:%d\n --> %d\n", m_bas.x, m_bas.y, outMap( m_bas ) );

    map_t m_pas_sortie;
    m_pas_sortie.x = 1;
    m_pas_sortie.y = 1;
    printf("\nPAS_SORTIE:\n x:%d  y:%d\n --> %d\n", m_pas_sortie.x, m_pas_sortie.y, outMap( m_pas_sortie ) );

    CU_ASSERT_EQUAL( outMap( m_gauche ) , SORTIE_GAUCHE );
    CU_ASSERT_EQUAL( outMap( m_haut ) , SORTIE_HAUT );
    CU_ASSERT_EQUAL( outMap( m_droite ) , SORTIE_DROITE );
    CU_ASSERT_EQUAL( outMap( m_bas ) , SORTIE_BAS );

    CU_ASSERT_EQUAL( outMap( m_pas_sortie ) , PAS_SORTIE );

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