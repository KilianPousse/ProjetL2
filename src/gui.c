/**
 * \file gui.c
 * \brief Sripte du GUI
 * \details Gestion de l'interface utilisateur
 * \author Pousse Kilian - Pierre Elona - Vallee Alban 
 * \version alpha 2
 * \date 23/02/2024
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "header.h"
#include "struct.h"
#include "style.h"
#include "inventory.h"


void initGUI(){

    GUI.hour =  NULL;
    GUI.hour = IMG_Load(IMG_GUI_HOUR);
    if( GUI.hour == NULL )
        WarningLog( "Impossible de charger la boite de l'heure" );

    GUI.dialog =  NULL;
    GUI.dialog = IMG_Load(IMG_GUI_DIALOG);
    if( GUI.dialog == NULL )
        WarningLog( "Impossible de charger la boite de dialogue" );


    GUI.coins =  NULL;
    GUI.coins = IMG_Load(IMG_GUI_COINS);
    if( GUI.coins == NULL )
        WarningLog( "Impossible de charger la boite de l'argent" );


    GUI.inventory =  NULL;
    GUI.inventory = IMG_Load(IMG_GUI_INVENTORY);
    if( GUI.inventory == NULL )
        WarningLog( "Impossible de charger l'inventory'" );


}

void freeGUI(){

    if( GUI.hour != NULL )
        SDL_FreeSurface( GUI.hour );

    if( GUI.dialog != NULL )
        SDL_FreeSurface( GUI.dialog );

    if( GUI.coins != NULL )
        SDL_FreeSurface( GUI.coins );

    if( GUI.inventory != NULL )
        SDL_FreeSurface( GUI.inventory );

}

void GUI_print_hour(){

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, GUI.hour );
    if (texture == NULL) {
        WarningLog("Impossible de charger la texture due la boite de l'heure");
        return;
    }

    SDL_Rect rect = { 0, 0, 201, 69 };

    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);

}

void GUI_print_dialog(){

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, GUI.dialog );
    if (texture == NULL) {
        return;
    }

    SDL_Rect rect = { 350, 630, 1180, 300 };

    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);

}


int GUI_coins(){

    // Crée une texture à partir de la surface de texte
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, GUI.coins);
    if (texture == NULL) {
        WarningLog("Erreur lors de la création de la texture de l'argent boite");
        return 2;
    }
    SDL_Rect rect = { 15 , WINDOW_HEIGHT - 60, 180, 51};

    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, texture, NULL, &rect);



    if( coins > MAX_COINS )
        coins = MAX_COINS;

    char str[20];

    sprintf( str,"%03d", coins/1000);
    SDL_Color color = WHITE_COLOR;
    SDL_Surface* textSurface1 = TTF_RenderText_Solid( text_Font , str, color );
    if (textSurface1 == NULL) {
        SDL_DestroyTexture(texture);
        WarningLog("Erreur lors de la création de la surface de texte de l'argent");
        return 1;
    }

    // Crée une texture à partir de la surface de texte
    SDL_Texture* textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);
    if (textTexture1 == NULL) {
        WarningLog("Erreur lors de la création de la texture de l'argent");
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(textSurface1); // Libère la surface maintenant que la texture est créée
        return 2;
    }

    int plus = textSurface1->w;


    
    sprintf( str,"%03d", coins%1000);
    SDL_Surface* textSurface2 = TTF_RenderText_Solid( text_Font , str, color );
    if (textSurface2 == NULL) {
        SDL_DestroyTexture(texture);
        WarningLog("Erreur lors de la création de la surface de texte de l'argent");
        return 1;
    }

    // Crée une texture à partir de la surface de texte
    SDL_Texture* textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
    if (textTexture2 == NULL) {
        WarningLog("Erreur lors de la création de la texture de l'argent");
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(textSurface2); // Libère la surface maintenant que la texture est créée
        return 2;
    }



    
    rect.x += 55;
    rect.y += 8;
    SDL_QueryTexture(textTexture1, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, textTexture1, NULL, &rect);
    rect.x += plus + 8;
    SDL_QueryTexture(textTexture2, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, textTexture2, NULL, &rect);

    
    SDL_DestroyTexture(texture);

    SDL_FreeSurface(textSurface2); // Libère la surface maintenant que la texture est créée
    SDL_DestroyTexture(textTexture2);
    SDL_FreeSurface(textSurface1); // Libère la surface maintenant que la texture est créée
    SDL_DestroyTexture(textTexture1);

    return 0;

}


int displayItem_inventory(int i, int j){

    SDL_Rect destRect = { (WINDOW_WIDTH - 865)/2 + 55 + 135 * i,  (WINDOW_HEIGHT - 650)/2 + 55 +  135 * j, 80, 80};
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, items_surface[ inventory.pcpl[j * NB_HOTBAR_ITEM + i].id ] );
    if (texture == NULL) {
        return 1;
    }
    SDL_RenderCopy(renderer,texture,NULL,&destRect);

    SDL_DestroyTexture(texture);


    char nb[3];
    sprintf( nb,"%-2d", inventory.pcpl[j * NB_HOTBAR_ITEM + i].nb );
    SDL_Color color = WHITE_COLOR;
    SDL_Surface* textSurface = TTF_RenderText_Solid( text_Font , nb, color );
    if (textSurface == NULL) {
        WarningLog("Erreur lors de la création de la surface de texte du nombre d'items");
        return 2;
    }

    // Crée une texture à partir de la surface de texte
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        WarningLog("Erreur lors de la création de la texture du nombre d'items");
        SDL_FreeSurface(textSurface); // Libère la surface maintenant que la texture est créée
        return 3;
    }
    
    SDL_Rect rect = { (WINDOW_WIDTH - 860)/2 + 50 + 135 * i,  (WINDOW_HEIGHT - 645)/2 + 42 +  135 * j, 1, 1 };
    SDL_QueryTexture(textTexture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, textTexture, NULL, &rect);

    SDL_FreeSurface(textSurface); // Libère la surface maintenant que la texture est créée
    SDL_DestroyTexture(textTexture);


    return 0;
}

int displayItem_hotbar(int i){

    SDL_Rect destRect = { (WINDOW_WIDTH - 865)/2 + 55 + 135 * i,  (WINDOW_HEIGHT - 650)/2 + 510, 80, 80};
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, items_surface[ inventory.hotbar[i].id ] );
    if (texture == NULL) {
        return 1;
    }
    SDL_RenderCopy(renderer,texture,NULL,&destRect);

    SDL_DestroyTexture(texture);


    char nb[3];
    sprintf( nb,"%-2d", inventory.hotbar[i].nb );
    SDL_Color color = WHITE_COLOR;
    SDL_Surface* textSurface = TTF_RenderText_Solid( text_Font , nb, color );
    if (textSurface == NULL) {
        WarningLog("Erreur lors de la création de la surface de texte du nombre d'items");
        return 2;
    }

    // Crée une texture à partir de la surface de texte
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        WarningLog("Erreur lors de la création de la texture du nombre d'items");
        SDL_FreeSurface(textSurface); // Libère la surface maintenant que la texture est créée
        return 3;
    }
    
    SDL_Rect rect = { (WINDOW_WIDTH - 860)/2 + 50 + 135 * i,  (WINDOW_HEIGHT - 645)/2 + 497, 1, 1 };
    SDL_QueryTexture(textTexture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, textTexture, NULL, &rect);

    SDL_FreeSurface(textSurface); // Libère la surface maintenant que la texture est créée
    SDL_DestroyTexture(textTexture);


    return 0;
}



int GUI_inventory(){

     SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, GUI.inventory);
    if (texture == NULL) {
        WarningLog("Erreur lors de la création de la texture de l'inventory");
        return 2;
    }
    SDL_Rect rect = { (WINDOW_WIDTH - 865)/2 , (WINDOW_HEIGHT - 650)/2, 865, 650  };

    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, texture, NULL, &rect);


    for(int i=0; i<NB_HOTBAR_ITEM; i++){
        for(int j=0; j<NB_INVENTORY_ITEM/NB_HOTBAR_ITEM; j++){
            if( inventory.pcpl[ j * NB_HOTBAR_ITEM + i ].id !=0 &&  inventory.pcpl[j * NB_HOTBAR_ITEM + i].nb > 0 )
                displayItem_inventory(i, j);
        }
    }

    for(int i=0; i<NB_HOTBAR_ITEM; i++){
        if( inventory.hotbar[ i ].id !=0 &&  inventory.hotbar[ i ].nb > 0 )
            displayItem_hotbar(i);
    }



    SDL_DestroyTexture(texture);

    return 0;
}