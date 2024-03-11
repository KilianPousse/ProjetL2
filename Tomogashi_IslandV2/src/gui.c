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


void initGUI(){

    GUI.hour =  NULL;
    GUI.hour = IMG_Load(IMG_GUI_HOUR);
    if( GUI.hour == NULL )
        WarningLog( "Impossible de charger la boite de l'heure" );

    GUI.dialog =  NULL;
    GUI.dialog = IMG_Load(IMG_GUI_DIALOG);
    if( GUI.dialog == NULL )
        WarningLog( "Impossible de charger la boite de dialogue" );


}

void freeGUI(){

    if( GUI.hour != NULL )
        SDL_FreeSurface( GUI.hour );

    if( GUI.dialog != NULL )
        SDL_FreeSurface( GUI.dialog );

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


