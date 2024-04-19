#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
#include "style.h"
#include "struct.h"
#include "menu.h"

/*Définiton variable globale*/

#define SCREEN_HEIGHT 480
#define SCREEN_WIDGHT 640
#define TAILLE 4
SDL_Event evenement;

void menu_destruction(bouton_t * bouton, SDL_Texture * texture, nuages_t nuage, nuages_t nuagea,nuages_t nuageb,nuages_t nuagec,logo_t logo){
        /*Destruction fenetre*/
    for(int j = 0; j < TAILLE ; j++){
        SDL_DestroyTexture(bouton[j].image);
        SDL_DestroyTexture(bouton[j].clique);
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(nuage.image[0]);
    SDL_DestroyTexture(nuage.image[1]);

    SDL_DestroyTexture(nuagea.image[0]);
    SDL_DestroyTexture(nuagea.image[1]);

    SDL_DestroyTexture(nuageb.image[0]);
    SDL_DestroyTexture(nuageb.image[1]);

    SDL_DestroyTexture(nuagec.image[0]);
    SDL_DestroyTexture(nuagec.image[1]);
    for(int i = 0; i< 6;i++){
        SDL_DestroyTexture(logo.image[i]);
    }
}

/*Structure stockée dans struct.h*/




/*En SDL obligé de mettre une fonction à argument variable*/
int menu_main(int argc, char * argv[]){
    printf("ici\n");
    playMusic( "assets/sound/menu.ogg", music, &channel_music, -1 );

    SDL_Texture * fond = chargerTexture(IMG_FOND, renderer);
    if(fond == NULL){
        printf("PAS FOND\n");
    }
    SDL_Rect rectangle= {0,0,100,100};

    /*Chargement image logo*/
    logo_t logo;
    logo.image[0]=chargerTexture(IMG_L1,renderer);
    logo.image[1]=chargerTexture(IMG_L2,renderer);
    logo.image[2]=chargerTexture(IMG_L3,renderer);
    logo.image[3]=chargerTexture(IMG_L4,renderer);
    logo.image[4]=chargerTexture(IMG_L5,renderer);
    logo.image[5]=chargerTexture(IMG_L6,renderer);
    logo.image[6]=chargerTexture(IMG_L7,renderer);




    /*Définiton de plusieurs nuages*/
    nuages_t nuage;
    nuage.image[0]=chargerTexture(IMG_NUAGE_1,renderer);
    nuage.image[1]=chargerTexture(IMG_NUAGE_2,renderer);
    
    nuages_t nuagea;
    nuagea.image[0]=chargerTexture(IMG_NUAGE_1,renderer);
    nuagea.image[1]=chargerTexture(IMG_NUAGE_2,renderer);

    nuages_t nuageb;
    nuageb.image[0]=chargerTexture(IMG_NUAGE_1,renderer);
    nuageb.image[1]=chargerTexture(IMG_NUAGE_2,renderer);

    nuages_t nuagec;
    nuagec.image[0]=chargerTexture(IMG_NUAGE_1,renderer);
    nuagec.image[1]=chargerTexture(IMG_NUAGE_2,renderer);


    /*Définition des boutons*/

    bouton_t menu[TAILLE];
    menu[0].texte = "jouer";
    menu[1].texte = "nouvelle partie";
    menu[2].texte = "parametre";
    menu[3].texte = "quitter";

    /*Chargement des images*/
    menu[0].image = chargerTexture(IMG_BOUTON_PLAY,renderer);
    menu[0].clique = chargerTexture(IMG_BOUTON_PLAY_CLIQUE,renderer);
    menu[1].image = chargerTexture(IMG_BOUTON_NEW,renderer);
    menu[1].clique = chargerTexture(IMG_BOUTON_NEW_CLIQUE,renderer);
    menu[2].image = chargerTexture(IMG_BOUTON_SET,renderer);
    menu[2].clique = chargerTexture(IMG_BOUTON_SET_CLIQUE,renderer);
    menu[3].image = chargerTexture(IMG_BOUTON_QUIT,renderer);
    menu[3].clique = chargerTexture(IMG_BOUTON_QUIT_CLIQUE,renderer);

    /*Calcul des postitions et des rectangles => pour savoir ou l'utilisateur clique*/
    int mrec = 100;
    int espace = 10;
    int totalheight = (mrec + espace)*TAILLE; 
    int y = (SCREEN_HEIGHT - totalheight) / 2 + 300; /*On ajouter pour centrer sur l'ecran*/
    int i;
    for(i = 0; i < TAILLE; i++){
        menu[i].rectangle.x = (SCREEN_WIDGHT + espace);
        menu[i].rectangle.y = y + (mrec + espace) * i; 
        menu[i].rectangle.w = 200;
        menu[i].rectangle.h = mrec;
    }
    int quitter = 0;
    int mousex,mousey;
    /*chargement rectangle pour nuage*/
    nuage.rectangle.x = 50;
    nuage.rectangle.y = 250;
    nuage.rectangle.w = 300;
    nuage.rectangle.h = 300;
    
    nuagea.rectangle.x = 250;
    nuagea.rectangle.y = 50;
    nuagea.rectangle.w = 300;
    nuagea.rectangle.h = 300;
    
    nuageb.rectangle.x = 710;
    nuageb.rectangle.y = 450;
    nuageb.rectangle.w = 300;
    nuageb.rectangle.h = 300;
    
    nuagec.rectangle.x = 1000;
    nuagec.rectangle.y = 100;
    nuagec.rectangle.w = 300;
    nuagec.rectangle.h = 300;

    /*Chargement rectangle pour logo*/
    logo.rectangle.x = 600;
    logo.rectangle.y = 20;
    logo.rectangle.w = 300;
    logo.rectangle.h = 300;


    /*Définition mouvement des nuages*/
    int frame = 0;
    int limite = 0;
    while(!quitter){
        
        limite = SDL_GetTicks()+FPS_LIMIT;

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
            
             /*On récupère les coordonnées de la souris*/
            int i;
            for(i = 0; i < 4; i++){
                if(SDL_PointInRect(&(SDL_Point){mousex,mousey},&menu[i].rectangle)){
                    printf("Cliquer sur %s (%d)\n",menu[i].texte, i);
                    if( i == 2 ){
                        mousex = 0;
                        mousey = 0;
                        printf("ici0\n");
                        main_option();
                        printf("ici10\n");
                    }
                    else{
                        quitter = 1;
                        menu_destruction(menu, fond,nuage,nuagea,nuageb,nuagec,logo);
                        return i;
                    }
                }
            }


            /*trou carré qui descen morceau echelle linge lit fontaine livre*/
        
        }
    
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, fond, NULL, NULL);
        SDL_RenderCopy(renderer, nuage.image[(frame/20)%2], NULL, &nuage.rectangle);/*on augmente le nombre en fonction de la vitesse d'animation qu'on veut*/
        SDL_RenderCopy(renderer, nuagea.image[(frame/20)%2], NULL, &nuagea.rectangle);
        SDL_RenderCopy(renderer, nuageb.image[(frame/20)%2], NULL, &nuageb.rectangle);
        SDL_RenderCopy(renderer, nuagec.image[(frame/20)%2], NULL, &nuagec.rectangle);
        SDL_RenderCopy(renderer, logo.image[(frame/30)%6], NULL, &logo.rectangle);
        
        /*renderer des items*/
        for(i = 0;i<4;i++){
            SDL_RenderCopy(renderer, menu[i].image, NULL, &(menu[i].rectangle)); /*Rectangle*/
                /*Si on clique alors*/
                if(SDL_PointInRect(&(SDL_Point){mousex,mousey},&menu[i].rectangle)){

                    SDL_RenderCopy(renderer, menu[i].clique, NULL, &(menu[i].rectangle)); /*Rectangle*/
                    
                    
                }

        frame++;
        }
        SDL_RenderPresent(renderer);
        limit_fps(limite);
    }

    /*musique*/
    /*Gestion musique SDL MIXER*/
    menu_destruction(menu, fond,nuage,nuagea,nuageb,nuagec,logo);
    return 0;
    
}
