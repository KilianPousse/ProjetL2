/**
 * \file hotbar.c
 * \brief Gestion de la hotbar
 * \details Script qui réalise l'affichage de la hotbar
 * \author Pousse Kilian - Pierre Elona - Vallee Alban 
 * \version alpha 1.2
 * \date 22/03/2024
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
#include "struct.h"
#include "style.h"
#include "hotbar.h"

 

 

 

 
void loadHotbar() {
    
    // Charge les textures d'items des fichiers 
    // A changer avec les items dynamiques
    
    hotbar = IMG_Load(IMGHOTBAR);
    hotbarSelect = IMG_Load(HOTBARSELECT);
    item[0] = IMG_Load(ITEM1);
    item[1] = IMG_Load(ITEM2);
    item[2] = IMG_Load(ITEM3);
    item[3] = IMG_Load(ITEM4);
    item[4] = IMG_Load(ITEM5);
    item[5] = IMG_Load(ITEM6);
    
}
 

void freeHotbar() {
    
    for (int i = 0; i < NUM_ITEMS; i++) {
        SDL_FreeSurface(item[i]);
    }
    
    
}





void displayHotbar(){
    
    // Copier la texture sur tout le rendu (pour remplir l'écran) 

    SDL_Rect destRect = {495, WINDOW_HEIGHT-120, 520, 100};
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, hotbar);
    if (texture == NULL) {
        WarningLog("Impossible de charger la texture de la hotbar");
        return;
    }
    SDL_RenderCopy(renderer,texture,NULL,&destRect);

    SDL_DestroyTexture(texture); 

    for (int i = 0; i < NUM_ITEMS; i++) {
        SDL_Rect destRect = {i * ITEMWIDTH, WINDOW_HEIGHT - ITEMHEIGHT , ITEMWIDTH, ITEMHEIGHT};
        displayItem(i);
        
    }

    SDL_DestroyTexture(texture);
 
}



void displayHotbarSelect(){

    // Copier la texture sur tout le rendu (pour remplir l'écran) 

    SDL_Rect destRect = {495,WINDOW_HEIGHT-120, (520/6), 100};
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, hotbarSelect);
    if (texture == NULL) {
        WarningLog("Impossible de charger la texture du select de la hotbar");
        return;
    }
    SDL_RenderCopy(renderer,texture,NULL,&destRect);

    SDL_DestroyTexture(texture);
}


 
void displayItem(int i){
    
    SDL_Rect destRect = {(i * ITEMWIDTH/3)+505,  WINDOW_HEIGHT - ITEMHEIGHT - 50 , ITEMWIDTH-200, ITEMHEIGHT};
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, item[i]);
    if (texture == NULL) {
        WarningLog("Impossible de charger la texture du background");
        return;
    }
    SDL_RenderCopy(renderer,texture,NULL,&destRect);

    SDL_DestroyTexture(texture);
    

}