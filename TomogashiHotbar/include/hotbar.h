/**
 * \file header.h
 * \brief Entete principale du projet
 * \details C'est ici qu'on retrouvera les initialisations des variables globals, struct, enum, fonctions, ...
 * \author Pousse Kilian - Pierre Elona - Vallee Alban 
 * \version alpha 1.2
 * \date 31/01/2024
**/
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



#define NUM_ITEMS 6

#define ITEMWIDTH WINDOW_WIDTH / NUM_ITEMS
#define ITEMHEIGHT WINDOW_HEIGHT / 20 // Taille de la hotbar



SDL_Surface* item[NUM_ITEMS];
SDL_Surface* hotbar;
SDL_Surface* hotbarSelect;

void loadHotbar();

void displayHotbar();

void displayHotbarSelect();

void freeHotbar();

void displayItem();