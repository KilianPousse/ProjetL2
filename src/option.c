/**
* \file option.c
* \brief Option du jeu 
* \details Permet d'afficher les options et de mettre le jeu en pause
* \author Pousse Kilian - Pierre Elona - Vallee Alban 
* \version alpha 1.4
* \date 15/04/2024
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
#include "style.h"
#include "menu.h"


#define SCREEN_HEIGHT 480
#define SCREEN_WIDGHT 640
#define TAILLE 3
SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;
SDL_Event evenement;

void option_destruction(bouton_t * bouton, SDL_Texture * texture){
        /*Destruction fenetre*/
    for(int j = 0; j < TAILLE ; j++){
        SDL_DestroyTexture(bouton[j].image);
        SDL_DestroyTexture(bouton[j].clique);
    }
    
}




int main_option(){

    SDL_Texture * fond = chargerTexture(IMG_SET,renderer);

    /*Définition de l'image du menu*/
    bouton_t set;
    set.image = chargerTexture(PUSH_MENU,renderer);
    set.clique = chargerTexture(PUSH_MENU,renderer);
    set.texte = "setting";
    set.rectangle.x = 500;
    set.rectangle.y = 100;
    set.rectangle.w = 600;
    set.rectangle.h = 800;
    


    /*Définiton des boutons*/
    bouton_t param[3];
    param[0].texte = "jouer";
    param[0].image = chargerTexture(IMG_PLAY,renderer);
    param[0].clique = chargerTexture(PUSH_PLAY,renderer);
    param[1].texte = "quit";
    param[1].image = chargerTexture(IMG_QUIT,renderer);
    param[1].clique = chargerTexture(PUSH_QUIT,renderer);
    param[2].texte = "save";
    param[2].image = chargerTexture(IMG_SAVE,renderer);
    param[2].clique = chargerTexture(PUSH_SAVE,renderer);

    /*On défini la taille des rectangle*/
    int mrec = 100;
    int espace = 10;
    int totalheight = (mrec + espace)*TAILLE; 
    int y = (SCREEN_HEIGHT - totalheight) / 2 + 300; /*On ajouter pour centrer sur l'ecran*/
    int i;
    for(i = 0; i < TAILLE; i++){
        param[i].rectangle.x = (SCREEN_WIDGHT + espace) + 50;
        param[i].rectangle.y = y + (mrec + espace) * i; 
        param[i].rectangle.w = 200;
        param[i].rectangle.h = mrec;
    }
   
    int quitter = 0;
    while(!quitter){
        int mousex;
        int mousey;
        while(SDL_PollEvent(&evenement) != 0){
            if(evenement.type == SDL_QUIT){
                quitter = 1;
                GameExit(1);
            }
            else if(evenement.type == SDL_MOUSEBUTTONUP){
                SDL_SetCursor( cursor );
            }
            else if(evenement.type == SDL_MOUSEBUTTONDOWN){
                SDL_SetCursor( cursor_click );
                SDL_GetMouseState(&mousex,&mousey);
            }
            else if( evenement.type == SDL_KEYDOWN ){
                if( evenement.key.keysym.sym == SDLK_ESCAPE ){
                    option_destruction(param,fond);
                    return 0;
                }
            }
            
             /*On récupère les coordonnées de la souris*/
            int i;
            for(i = 0; i < 4; i++){
                if(SDL_PointInRect(&(SDL_Point){mousex,mousey},&param[i].rectangle)){
                    printf("Cliquer sur %s\n",param[i].texte);
                    quitter = 1;
                    if(i == 1){
                        option_destruction(param, fond);
                        GameExit(0);
                    }
                    if(i == 2){
                        SaveSave();
                    }
                    if(i == 0){
                        option_destruction(param,fond);
                        return 1;
                    }
                    break;  
                }
            }     
        }
    
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,fond,NULL,NULL);
        SDL_RenderCopy(renderer,set.image,NULL,&set.rectangle);/*on augmente le nombre en fonction de la vitesse d'animation qu'on veut*/
        
        /*renderer des items*/
        for(i = 0;i<3;i++){
        //printf("x:%d / y:%d / w:%d / h:%d \n",param[i].rectangle.x,param[i].rectangle.y,param[i].rectangle.w ,param[i].rectangle.h );
            SDL_RenderCopy(renderer, param[i].image, NULL, &(param[i].rectangle)); /*Rectangle*/
                /*Si on clique alors*/
                if(SDL_PointInRect(&(SDL_Point){mousex,mousey},&param[i].rectangle)){
                    SDL_RenderCopy(renderer, param[i].clique, NULL, &(param[i].rectangle)); /*Rectangle*/
                    
                    
                }
        }
        printf("ici10\n");
        SDL_RenderPresent(renderer);
        

    }
    option_destruction(param,fond);
    return 0;
   /*Image fond flou/noir*/
    /*Option son SDL MIXER*/
    /*Option résolutoin => à venir*/
    /*Option quitter*/

}
