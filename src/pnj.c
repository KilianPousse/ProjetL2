/**
 * \file pnj.c
 * \brief Gère les PNJ
 * \details Scripte qui gènere les PNJ charge les textures et les fait bouger
 * \author Pousse Kilian - Pierre Elona - Vallee Alban 
 * \version alpha 2.2
 * \date 10/04/2024
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "header.h"
#include "map.h"
#include "style.h"
#include "inventory.h"

#include "pnj.h"

SDL_Surface * trade_box;
SDL_Surface * trade_cell;
SDL_Surface * trade_cell_select;

void pnj_vendeur(catalog_t * catalog){

    trade_box = IMG_Load(GUI_TRADE_BOX);
    trade_cell = IMG_Load(GUI_TRADE_CELL);
    trade_cell_select = IMG_Load(GUI_TRADE_CELL_SELECT);

    SDL_Surface * surface;
    SDL_Texture * texture;
    SDL_Color color = WHITE_COLOR;
    char str[20];

    SDL_Rect rect_nb_select = { (WINDOW_WIDTH - 865)/2 + 530, (WINDOW_HEIGHT - 650)/2 + 410, 1, 1  };
    SDL_Rect rect_prix = { (WINDOW_WIDTH - 865)/2 + 540, (WINDOW_HEIGHT - 650)/2 + 230, 1, 1  };

    SDL_Rect rect_plus = { (WINDOW_WIDTH - 865)/2 + 510, (WINDOW_HEIGHT - 650)/2 + 325, 90, 75  };
    SDL_Rect rect_moins = { (WINDOW_WIDTH - 865)/2 + 510, (WINDOW_HEIGHT - 650)/2 + 325 + 160, 90, 75  };
    
    SDL_Rect rect_achat = { (WINDOW_WIDTH - 865)/2 + 725, (WINDOW_HEIGHT - 650)/2 + 435, 110, 120  };

    int i_select = 0;
    int n_select = 1;

    SDL_Point mouse;
    SDL_Rect rect = { (WINDOW_WIDTH - 865)/2 + 30, (WINDOW_HEIGHT - 650)/2 + 35, 380, 110  };

    item_t item;

    SDL_bool launched_program = SDL_TRUE;
    while( launched_program ){

        SDL_Event event;

        while(SDL_PollEvent(&event)) {  

				switch(event.type) { 

					// Si croix en haut a droite selectionnée
					case SDL_QUIT:
						launched_program = SDL_FALSE;
                        SDL_FreeSurface(trade_box);
                        SDL_FreeSurface(trade_cell);
                        SDL_FreeSurface(trade_cell_select);
                        GameExit(EXIT_SUCCESS);
						break; 

                    case SDL_KEYDOWN:

                        switch(event.key.keysym.sym){

                            case SDLK_i:
                            case SDLK_ESCAPE:
                                launched_program = SDL_FALSE;
                                break;
                                
					        default:		
					            break;
                        }
                        break;
                    
                case SDL_MOUSEBUTTONUP:
                    SDL_SetCursor(cursor);
                    if( event.button.button == SDL_BUTTON_LEFT ){
                        if( SDL_PointInRect( &mouse, &rect_plus ) ){
                                n_select = (n_select + 1)%MAX_ITEM_STACK;
                                if(n_select<=0)
                                    n_select = 99;
                                
                        }
                        else if( SDL_PointInRect( &mouse, &rect_moins ) ){
                                n_select = n_select<=1?MAX_ITEM_STACK:n_select-1;

                                
                        }
                        else if( SDL_PointInRect( &mouse, &rect_achat ) ){
                                if( coins >= n_select * catalog->trade[i_select].prix ){

                                    item.nb = n_select;
                                    item.id = catalog->trade[i_select].item;

                                    if( inventory_canGive( item ) ){
                                        inventory_give(&item);
                                        coins -= n_select * catalog->trade[i_select].prix;
                                    }

                                }
                                n_select = 1;

                                
                        }
                    }
                    else if(event.button.button == SDL_BUTTON_RIGHT){
                        if( SDL_PointInRect( &mouse, &rect_plus ) ){
                                n_select = (n_select + 10)%MAX_ITEM_STACK;
                                
                        }
                        else if( SDL_PointInRect( &mouse, &rect_moins ) ){
                                n_select = n_select<=10?MAX_ITEM_STACK:n_select-10;

                                
                        }
                    }
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    SDL_SetCursor(cursor_click);
                    mouse.x = event.button.x;
                    mouse.y = event.button.y;
                    if( event.button.button == SDL_BUTTON_LEFT ){
                        rect.y = (WINDOW_HEIGHT - 650)/2 + 35;
                        for(int i=0; i<catalog->n_trade; i++){
                            if( SDL_PointInRect( &mouse, &rect ) ){
                                i_select = i;
                                n_select = 1;
                            }
                            rect.y += 115;
                        }
                        
                    }
                    break;
                    
                    default:
                        break;
                
                }
        }

        /* Affichage */
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);// Rectangle plein
        
        displayWater();
        displayBateau();
        diplayBackground();
        displayFarm( map.y*SIZE_MAP_X + map.x );
        displayPlayer( tile_action );
        displayPNJ();
        displayOverlay();

        // Filtre noire
        SDL_SetRenderDrawColor(renderer, 0x01, 0x01, 0x00, 0x60);
        SDL_RenderFillRect(renderer, NULL);

        displayGUI();
                
        displayTime();


        
        display_trade_vente(i_select, catalog);

        sprintf(str, "x%02d", n_select);
        surface = TTF_RenderText_Solid( hour_Font , str, color );
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        SDL_QueryTexture(texture, NULL, NULL, &rect_nb_select.w, &rect_nb_select.h);
        SDL_RenderCopy(renderer, texture, NULL, &rect_nb_select);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);

        sprintf(str, "%6dG.", -n_select * catalog->trade[i_select].prix);
        surface = TTF_RenderText_Solid( hour_Font , str, color );
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        SDL_QueryTexture(texture, NULL, NULL, &rect_prix.w, &rect_prix.h);
        SDL_RenderCopy(renderer, texture, NULL, &rect_prix);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);




        SDL_RenderPresent(renderer);





    }
    SDL_FreeSurface(trade_box);
    SDL_FreeSurface(trade_cell);
    SDL_FreeSurface(trade_cell_select);
}



void pnj_acheteur(catalog_t * catalog){

    trade_box = IMG_Load(GUI_TRADE_BOX);
    trade_cell = IMG_Load(GUI_TRADE_CELL_ACHAT);
    trade_cell_select = IMG_Load(GUI_TRADE_CELL_SELECT_ACHAT);

    SDL_Surface * surface;
    SDL_Texture * texture;
    SDL_Color color = WHITE_COLOR;
    char str[20];

    SDL_Rect rect_nb_select = { (WINDOW_WIDTH - 865)/2 + 530, (WINDOW_HEIGHT - 650)/2 + 410, 1, 1  };
    SDL_Rect rect_prix = { (WINDOW_WIDTH - 865)/2 + 540, (WINDOW_HEIGHT - 650)/2 + 230, 1, 1  };

    SDL_Rect rect_plus = { (WINDOW_WIDTH - 865)/2 + 510, (WINDOW_HEIGHT - 650)/2 + 325, 90, 75  };
    SDL_Rect rect_moins = { (WINDOW_WIDTH - 865)/2 + 510, (WINDOW_HEIGHT - 650)/2 + 325 + 160, 90, 75  };
    
    SDL_Rect rect_achat = { (WINDOW_WIDTH - 865)/2 + 725, (WINDOW_HEIGHT - 650)/2 + 435, 110, 120  };

    int i_select = 0;
    int n_select = 0;

    SDL_Point mouse;
    SDL_Rect rect = { (WINDOW_WIDTH - 865)/2 + 30, (WINDOW_HEIGHT - 650)/2 + 35, 380, 110  };

    item_t item;

    SDL_bool launched_program = SDL_TRUE;
    while( launched_program ){

        SDL_Event event;

        while(SDL_PollEvent(&event)) {  

				switch(event.type) { 

					// Si croix en haut a droite selectionnée
					case SDL_QUIT:
						launched_program = SDL_FALSE;
                        SDL_FreeSurface(trade_box);
                        SDL_FreeSurface(trade_cell);
                        SDL_FreeSurface(trade_cell_select);
                        GameExit(EXIT_SUCCESS);
						break; 

                    case SDL_KEYDOWN:

                        switch(event.key.keysym.sym){

                            case SDLK_i:
                            case SDLK_ESCAPE:
                                launched_program = SDL_FALSE;
                                break;
                                
					        default:		
					            break;
                        }
                        break;
                    
                case SDL_MOUSEBUTTONUP:
                    SDL_SetCursor(cursor);
                    if( event.button.button == SDL_BUTTON_LEFT ){
                        if( SDL_PointInRect( &mouse, &rect_plus ) ){
                                item.id = catalog->trade[i_select].item;
                                n_select = (n_select + 1)%MAX_ITEM_STACK;
                                item.nb = n_select;
                                if( inventory_canRemove(item) == 0 ){
                                    n_select = 0;
                                }
                                
                        }
                        else if( SDL_PointInRect( &mouse, &rect_moins ) ){
                                item.id = catalog->trade[i_select].item;
                                n_select = n_select<=1?MAX_ITEM_STACK:n_select-1;
                                item.nb = n_select;

                                if( inventory_canRemove(item) == 0 ){
                                        n_select = inventory_contains( item.id, 99 );
                                }

                                
                        }
                        else if( SDL_PointInRect( &mouse, &rect_achat ) ){
                                if( MAX_COINS >= n_select * catalog->trade[i_select].prix + coins ){

                                    item.nb = n_select;
                                    item.id = catalog->trade[i_select].item;

                                    if( inventory_canRemove( item ) ){
                                        inventory_remove(&item);
                                        coins += n_select * catalog->trade[i_select].prix;
                                    }

                                }
                                n_select = 0;

                                
                        }
                    }
                    else if(event.button.button == SDL_BUTTON_RIGHT){
                        if( SDL_PointInRect( &mouse, &rect_plus ) ){
                                item.id = catalog->trade[i_select].item;
                                n_select = (n_select + 10)%MAX_ITEM_STACK;
                                item.nb = n_select;
                                if( inventory_canRemove(item) == 0 ){
                                    n_select = 0;
                                }
                                
                        }
                        else if( SDL_PointInRect( &mouse, &rect_moins ) ){
                                n_select = n_select<=10?MAX_ITEM_STACK:n_select-10;

                                if( inventory_canRemove(item) == 0 ){
                                        n_select = inventory_contains( item.id, 99 );
                                }
                        }
                    }
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    SDL_SetCursor(cursor_click);
                    mouse.x = event.button.x;
                    mouse.y = event.button.y;
                    if( event.button.button == SDL_BUTTON_LEFT ){
                        rect.y = (WINDOW_HEIGHT - 650)/2 + 35;
                        for(int i=0; i<catalog->n_trade; i++){
                            if( SDL_PointInRect( &mouse, &rect ) ){
                                i_select = i;
                                n_select = 0;
                            }
                            rect.y += 115;
                        }
                        
                    }
                    break;
                    
                    default:
                        break;
                
                }
        }

        /* Affichage */
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);// Rectangle plein

        displayWater();
        displayBateau();  
        diplayBackground();
        displayFarm( map.y*SIZE_MAP_X + map.x );
        displayPlayer( tile_action );
        displayPNJ();
        displayOverlay();

        // Filtre noire
        SDL_SetRenderDrawColor(renderer, 0x01, 0x01, 0x00, 0x60);
        SDL_RenderFillRect(renderer, NULL);

        displayGUI();
                
        displayTime();


        
        display_trade_vente(i_select, catalog);

        sprintf(str, "x%02d", n_select);
        surface = TTF_RenderText_Solid( hour_Font , str, color );
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        SDL_QueryTexture(texture, NULL, NULL, &rect_nb_select.w, &rect_nb_select.h);
        SDL_RenderCopy(renderer, texture, NULL, &rect_nb_select);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);

        sprintf(str, "%6dG.", n_select * catalog->trade[i_select].prix);
        surface = TTF_RenderText_Solid( hour_Font , str, color );
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        SDL_QueryTexture(texture, NULL, NULL, &rect_prix.w, &rect_prix.h);
        SDL_RenderCopy(renderer, texture, NULL, &rect_prix);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);




        SDL_RenderPresent(renderer);





    }
    SDL_FreeSurface(trade_box);
    SDL_FreeSurface(trade_cell);
    SDL_FreeSurface(trade_cell_select);
}


void display_trade_vente( int i_select, catalog_t * catalog){

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, trade_box);
    if (texture == NULL) {
        return ;
    }
    SDL_Rect rect = { (WINDOW_WIDTH - 865)/2 , (WINDOW_HEIGHT - 650)/2, 865, 650  };
    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);


    texture = SDL_CreateTextureFromSurface(renderer, trade_cell);
    SDL_Rect rect_cell = { (WINDOW_WIDTH - 865)/2 + 30, (WINDOW_HEIGHT - 650)/2 + 35, 380, 110  };
    SDL_Rect rect_item = { (WINDOW_WIDTH - 865)/2 + 30 + 250, (WINDOW_HEIGHT - 650)/2 + 35 + 20, 60, 60  };
    SDL_Rect rect_prix = { (WINDOW_WIDTH - 865)/2 + 30 + 30, (WINDOW_HEIGHT - 650)/2 + 35 + 25, 100, 100  };
    SDL_Texture * select = SDL_CreateTextureFromSurface(renderer, trade_cell_select);
    SDL_Texture * item ;

    char prix[8] ;
    SDL_Color color = WHITE_COLOR;
    SDL_Surface * textSurface;
    SDL_Texture * text;

    for(int i=0; i<catalog->n_trade; i++ ){
        sprintf( prix,"%3dG.", catalog->trade[i].prix );
        // Copier la texture sur tout le rendu (pour remplir l'écran)
        item = SDL_CreateTextureFromSurface( renderer, items_surface[ catalog->trade[i].item ] );
        textSurface = TTF_RenderText_Solid( hour_Font , prix, color );
        text = SDL_CreateTextureFromSurface( renderer, textSurface );
        SDL_QueryTexture(text, NULL, NULL, &rect_prix.w, &rect_prix.h);
        if( i_select == i ){
            rect_item.y += 5;
            rect_prix.y += 5;
            SDL_RenderCopy(renderer, select, NULL, &rect_cell);
            SDL_RenderCopy(renderer, item, NULL, &rect_item);
            SDL_RenderCopy(renderer, text, NULL, &rect_prix);
            rect_item.y -= 5;
            rect_prix.y -= 5;
            

        }
        else{
            SDL_RenderCopy(renderer, texture, NULL, &rect_cell);
            SDL_RenderCopy(renderer, item, NULL, &rect_item);
            SDL_RenderCopy(renderer, text, NULL, &rect_prix);
        }
        rect_cell.y += 115;
        rect_item.y += 115;
        rect_prix.y += 115;
        SDL_DestroyTexture(item);
        SDL_DestroyTexture(text);
        SDL_FreeSurface(textSurface);
    }
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(select);





}


void display_trade_achat( int i_select, catalog_t * catalog){

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, trade_box);
    if (texture == NULL) {
        return ;
    }
    SDL_Rect rect = { (WINDOW_WIDTH - 865)/2 , (WINDOW_HEIGHT - 650)/2, 865, 650  };
    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);


    texture = SDL_CreateTextureFromSurface(renderer, trade_cell);
    SDL_Rect rect_cell = { (WINDOW_WIDTH - 865)/2 + 30, (WINDOW_HEIGHT - 650)/2 + 35, 380, 110  };
    SDL_Rect rect_item = { (WINDOW_WIDTH - 865)/2 + 30 + 250, (WINDOW_HEIGHT - 650)/2 + 35 + 20, 60, 60  };
    SDL_Rect rect_prix = { (WINDOW_WIDTH - 865)/2 + 30 + 30, (WINDOW_HEIGHT - 650)/2 + 35 + 25, 60, 60  };
    SDL_Texture * select = SDL_CreateTextureFromSurface(renderer, trade_cell_select);
    SDL_Texture * item ;

    char prix[8] ;
    SDL_Color color = WHITE_COLOR;
    SDL_Surface * textSurface;
    SDL_Texture * text;

    for(int i=0; i<catalog->n_trade; i++ ){
        sprintf( prix,"%3dG.", catalog->trade[i].prix );
        // Copier la texture sur tout le rendu (pour remplir l'écran)
        item = SDL_CreateTextureFromSurface( renderer, items_surface[ catalog->trade[i].item ] );
        textSurface = TTF_RenderText_Solid( hour_Font , prix, color );
        text = SDL_CreateTextureFromSurface( renderer, textSurface );
        SDL_QueryTexture(text, NULL, NULL, &rect_prix.w, &rect_prix.h);
        if( i_select == i ){
            rect_item.y += 5;
            rect_prix.y += 5;
            SDL_RenderCopy(renderer, select, NULL, &rect_cell);
            SDL_RenderCopy(renderer, item, NULL, &rect_item);
            SDL_RenderCopy(renderer, text, NULL, &rect_prix);
            rect_item.y -= 5;
            rect_prix.y -= 5;
            

        }
        else{
            SDL_RenderCopy(renderer, texture, NULL, &rect_cell);
            SDL_RenderCopy(renderer, item, NULL, &rect_item);
            SDL_RenderCopy(renderer, text, NULL, &rect_prix);
        }
        rect_cell.y += 115;
        rect_item.y += 115;
        rect_prix.y += 115;
        SDL_DestroyTexture(item);
        SDL_DestroyTexture(text);
        SDL_FreeSurface(textSurface);
    }
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(select);





}
