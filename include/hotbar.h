/**
 * \file hotbar.h
 * \brief Variables utilisées dans scripte de la hotbar.c 
 * \details Création des variables qqui seront utilisée dans la hotbar.c
 * \author Pousse Kilian - Pierre Elona - Vallee Alban 
 * \version alpha 1.2
 * \date 24/02/2024
**/2024
**/
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/**
 * \def NUM_ITEMS
 * \brief Nombre d'éléments dans la hotbar
 */
#define NUM_ITEMS 6

/**
 * \def ITEMWIDTH
 * \brief Largeur d'un élément de la hotbar
 */
#define ITEMWIDTH WINDOW_WIDTH / NUM_ITEMS

/**
 * \def ITEMHEIGHT
 * \brief Hauteur d'un élément de la hotbar
 */
#define ITEMHEIGHT WINDOW_HEIGHT / 20 // Taille de la hotbar

/**
 * \var SDL_Surface* item[NUM_ITEMS]
 * \brief Tableau des surfaces des éléments de la hotbar
 */
SDL_Surface* item[NUM_ITEMS]; 

/**
 * \var SDL_Surface* hotbar
 * \brief Surface de la hotbar
 */
SDL_Surface* hotbar;

/**
 * \var SDL_Surface* hotbarSelect
 * \brief Surface de la sélection dans la hotbar
 */
SDL_Surface* hotbarSelect;

/**
 * \fn void loadHotbar()
 * \brief Charge les ressources de la hotbar
 */
void loadHotbar();

/**
 * \fn void displayHotbar()
 * \brief Affiche la hotbar
 */
void displayHotbar();

/**
 * \fn void displayHotbarSelect()
 * \brief Affiche la sélection dans la hotbar
 */
void displayHotbarSelect();

/**
 * \fn void freeHotbar()
 * \brief Libère les ressources de la hotbar
 */
void freeHotbar();

/**
 * \fn void displayItem()
 * \brief Affiche les éléments de la hotbar
 */
void displayItem();

