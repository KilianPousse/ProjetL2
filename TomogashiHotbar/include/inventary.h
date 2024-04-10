#include "item.h"

#define NB_INVENTARY_ITEM 18 
#define NB_HOTBAR_ITEM 6
#define MAX_ITEM_STACK 99


typedef struct{
    item_t hotbar[NB_HOTBAR_ITEM];
    item_t pcpl[NB_INVENTARY_ITEM];

    int i_hotbar;
}inventary_t;

inventary_t inventary;


item_t inventary_mainhand();
int inventary_use();
int inventary_add( item_t item );
int inventary_remove( item_t item );
int inventary_clear();
int inventary_contains_hotbar( unsigned char id, int limit );
int inventary_contains_pcpl( unsigned char id, int limit );

int inventary_canGive( item_t item );
int inventary_give( item_t * item );

void inventary_affiche(  );