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
#include "inventory.h"

 

 

 

 
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

    SDL_Rect destRect = {498, WINDOW_HEIGHT-120, 520, 95};
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

 

void displayHotbarSelect(int i){

    // Copier la texture sur tout le rendu (pour remplir l'écran) 

    float cases = (86 * i) + 2.5;
    SDL_Rect destRect = {498+cases,WINDOW_HEIGHT-120, (520/6), 95};
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, hotbarSelect);
    if (texture == NULL) {
        WarningLog("Impossible de charger la texture du select de la hotbar");
        return;
    }
    SDL_RenderCopy(renderer,texture,NULL,&destRect);

    SDL_DestroyTexture(texture);
}


 
void displayItem(int i){
    
    SDL_Rect destRect = {(i * ITEMWIDTH/3)+510,  WINDOW_HEIGHT - ITEMHEIGHT - 60 , 60, 60};
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, items_surface[ inventory.hotbar[i].id ] );
    if (texture == NULL) {
        return;
    }
    SDL_RenderCopy(renderer,texture,NULL,&destRect);

    SDL_DestroyTexture(texture);
    
    char nb[3];
    sprintf( nb,"%d", inventory.hotbar[i].nb );
    SDL_Color color = WHITE_COLOR;
    SDL_Surface* textSurface = TTF_RenderText_Solid( text_Font , nb, color );
    if (textSurface == NULL) {
        WarningLog("Erreur lors de la création de la surface de texte du nombre d'items");
        return;
    }

    // Crée une texture à partir de la surface de texte
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        WarningLog("Erreur lors de la création de la texture du nombre d'items");
        SDL_FreeSurface(textSurface); // Libère la surface maintenant que la texture est créée
        return;
    }
    
    SDL_Rect rect = { 498 + 46 - (textSurface->w/2)  + (86 * i),  WINDOW_HEIGHT - ITEMHEIGHT - 12, 1, 1 };
    SDL_QueryTexture(textTexture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, textTexture, NULL, &rect);

    SDL_FreeSurface(textSurface); // Libère la surface maintenant que la texture est créée
    SDL_DestroyTexture(textTexture);



}
