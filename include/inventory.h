/**
 * \file inventory.h
 * \brief Ajoue des fonctions dans inventory.c
 * \details Ajoue des fonctions qui se trouvent dans inventory.c pour pouvoir les rappeler dans d'autres parties du scripte
 * \author Pousse Kilian - Pierre Elona - Vallee Alban 
 * \version alpha 2.2
 * \date 26/03/2024
**/


#include "item.h"

#define NB_INVENTORY_ITEM 18 
#define NB_HOTBAR_ITEM 6
#define MAX_ITEM_STACK 99


typedef struct{
    item_t hotbar[NB_HOTBAR_ITEM];
    item_t pcpl[NB_INVENTORY_ITEM];

    int i_hotbar;
}inventory_t;

inventory_t inventory;


item_t inventory_mainhand();
int inventory_use();
int inventory_clear();
int inventory_contains_hotbar( unsigned int id, int limit );
int inventory_contains_pcpl( unsigned int id, int limit );
int inventory_contains( unsigned int id, int limit );

int inventory_canGive( item_t item );
int inventory_give( item_t * item );

int inventory_canRemove( item_t item );
int inventory_remove( item_t * item );

void inventory_affiche(  );

int inventory_haveItem();

int inventory_display();
