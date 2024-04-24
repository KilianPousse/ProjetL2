/**
 * \file pnj.h
 * \brief Données utilisées dans pnj.h
 * \details Stock le données utiles et utilisées dans pnj.c
 * \author Pousse Kilian - Pierre Elona - Vallee Alban 
 * \version alpha 2.2
 * \date 30/01/2024
**/


typedef struct{

    int item;
    int prix;

}trade_t;

typedef struct{

    trade_t trade[5];
    int n_trade;

}catalog_t;

void pnj_vendeur(catalog_t * catalog);
void display_trade_vente( int i_select, catalog_t * catalog);

void pnj_acheteur(catalog_t * catalog);
void display_trade_achat( int i_select, catalog_t * catalog);

