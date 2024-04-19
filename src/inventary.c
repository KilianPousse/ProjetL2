#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "header.h"
#include "struct.h"
#include "style.h"
#include "hotbar.h"

#include "inventory.h"


item_t inventory_mainhand(  ){
    return inventory.hotbar[inventory.i_hotbar];
}

int inventory_use(  ){

    if( inventory.hotbar[inventory.i_hotbar].nb <= 0 )
        return 1;

    if( inventory.hotbar[inventory.i_hotbar].nb == 1 ){
        inventory.hotbar[inventory.i_hotbar].id = 0;
    }

    (inventory.hotbar[inventory.i_hotbar].nb)--;
    return 0;
}

int inventory_contains_hotbar( unsigned int id, int limit ){

    int j = 0;

    for(int i=0; i<NUM_ITEMS; i++){
        if( inventory.hotbar[ i ].id == id ){
            j+=inventory.hotbar[ i ].nb;
            if( j == limit )
                return i;
        }
    }

    return j;
}

int inventory_contains_pcpl( unsigned int id, int limit ){

    int j = 0;

    for(int i=0; i<NB_INVENTORY_ITEM; i++){
        if( inventory.pcpl[ i ].id == id ){
            j+=inventory.pcpl[ i ].nb;
            if( j == limit )
                return i;
        }
    }

    return j;
}

int inventory_contains( unsigned int id, int limit ){

    int x = inventory_contains_pcpl(id, limit);
    return x + inventory_contains_hotbar(id, limit-x);
}


void inventory_affiche(  ){


    for(int i=0; i<NB_INVENTORY_ITEM; i++){
        if(i%NUM_ITEMS == 0)
            printf("\n");
        printf(" [id:%02d|nb:%02d]", inventory.pcpl[i].id, inventory.pcpl[i].nb );
    }
    printf("\n");


    printf("-------------------------------------------------------------------------------------\n");

    for(int i=0; i<NB_HOTBAR_ITEM; i++){
        printf(" [id:%02d|nb:%02d]", inventory.hotbar[i].id, inventory.hotbar[i].nb );
    }
    printf("\n");


}


int inventory_clear(){

    for(int i=0; i<NB_HOTBAR_ITEM; i++){
        inventory.hotbar[i].nb = 0;
        inventory.hotbar[i].id = 0;
    }

    for(int i=0; i<NB_INVENTORY_ITEM; i++){
        inventory.pcpl[i].nb = 0;
        inventory.pcpl[i].id = 0;
    }

    return 0;
}

int inventory_canGive( item_t item ){

    int nb = item.nb;

    for( int i=0; i<NB_HOTBAR_ITEM; i++ ){
        //printf("/hotbar:[id:%d|nb:%d]  -- item[id:%d|nb:%d]/\n", inventory.hotbar[i].id, inventory.hotbar[i].nb, item.id, item.nb);
        if( inventory.hotbar[i].nb <= 0 && inventory.hotbar[i].id == 0)
            return 1;
        
        if( inventory.hotbar[i].id == item.id  ){
            nb = (inventory.hotbar[i].nb + nb) - MAX_ITEM_STACK;

            if( nb <= 0 )
                return 2;
        }


    }

    for( int i=0; i<NB_INVENTORY_ITEM; i++ ){
        //printf("/iventary:[id:%d|nb:%d]  -- item[id:%d|nb:%d]/\n", inventory.pcpl[i].id, inventory.pcpl[i].nb, item.id, item.nb);
        if( inventory.pcpl[i].nb <= 0 && inventory.pcpl[i].id == 0 )
            return 1;
        
        if( inventory.pcpl[i].id == item.id  ){
            nb = (inventory.pcpl[i].nb + nb) - MAX_ITEM_STACK;

            if( nb <= 0 )
                return 2;
        }


    }


    return 0;
}

int inventory_give( item_t * item ){

    if( item->nb > MAX_ITEM_STACK )
        item->nb = MAX_ITEM_STACK;

    int i_hotbar = -1;
    int i_pcpl = -1;

    for(int i=0; i<NB_HOTBAR_ITEM; i++){

        if( i_hotbar < 0 && inventory.hotbar[i].nb <= 0 && inventory.hotbar[i].id == 0 )
            i_hotbar = i;

        if( inventory.hotbar[i].id == item->id  ){
            inventory.hotbar[i].nb += item->nb;
            item->nb = inventory.hotbar[i].nb - MAX_ITEM_STACK;
            if( inventory.hotbar[i].nb > MAX_ITEM_STACK )
                inventory.hotbar[i].nb = MAX_ITEM_STACK;

            if( item->nb <= 0 )
                return 0;
        }

    }

    for(int i=0; i<NB_INVENTORY_ITEM; i++){

        if( i_hotbar < 0 && i_pcpl < 0 && inventory.pcpl[i].nb <= 0 && inventory.pcpl[i].id == 0 )
            i_pcpl = i;

        if( inventory.pcpl[i].id == item->id  ){
            inventory.pcpl[i].nb += item->nb;
            item->nb = inventory.pcpl[i].nb - MAX_ITEM_STACK;
            if( inventory.pcpl[i].nb > MAX_ITEM_STACK )
                inventory.pcpl[i].nb = MAX_ITEM_STACK;

            if( item->nb <= 0 )
                return 0;
        }

    }

    if( item->nb > 0 ){

        if( i_hotbar >= 0 ){
            inventory.hotbar[i_hotbar] = *item;
            return 0;
        }

        if( i_pcpl >= 0 ){
            inventory.pcpl[i_pcpl] = *item;
            return 0;
        }

    }

    return 1;
}

int inventory_give_hotbar( item_t * item ){

    if( item->nb > MAX_ITEM_STACK )
        item->nb = MAX_ITEM_STACK;

    int i_hotbar = -1;

    for(int i=0; i<NB_HOTBAR_ITEM; i++){

        if( i_hotbar < 0 && inventory.hotbar[i].nb <= 0 && inventory.hotbar[i].id == 0 )
            i_hotbar = i;

        if( inventory.hotbar[i].id == item->id  ){
            inventory.hotbar[i].nb += item->nb;
            item->nb = inventory.hotbar[i].nb - MAX_ITEM_STACK;
            if( inventory.hotbar[i].nb > MAX_ITEM_STACK )
                inventory.hotbar[i].nb = MAX_ITEM_STACK;

            if( item->nb <= 0 ){
                item->nb = 0;
                item->id = 0;
                return 0;
            }
        }



    }
    
    if( item->nb > 0 ){

        if( i_hotbar >= 0 ){
            inventory.hotbar[i_hotbar] = *item;
            item->nb = 0;
            item->id = 0;
            return 0;
        }
    }


}



int inventory_give_pcpl( item_t * item ){

    if( item->nb > MAX_ITEM_STACK )
        item->nb = MAX_ITEM_STACK;

    int i_pcpl = -1;

    for(int i=0; i<NB_INVENTORY_ITEM; i++){

        if( i_pcpl < 0 && inventory.pcpl[i].nb <= 0 && inventory.pcpl[i].id == 0 )
            i_pcpl = i;

        if( inventory.pcpl[i].id == item->id  ){
            inventory.pcpl[i].nb += item->nb;
            item->nb = inventory.pcpl[i].nb - MAX_ITEM_STACK;
            if( inventory.pcpl[i].nb > MAX_ITEM_STACK )
                inventory.pcpl[i].nb = MAX_ITEM_STACK;

            if( item->nb <= 0 ){
                item->nb = 0;
                item->id = 0;
                return 0;
            }
        }

    }
    
    if( item->nb > 0 ){

        if( i_pcpl >= 0 ){
            inventory.pcpl[i_pcpl] = *item;
            item->nb = 0;
            item->id = 0;
            return 0;
        }
    }


}

int inventory_canRemove( item_t item ){

    int inv;

    if( item.nb > MAX_ITEM_STACK )
        item.nb = MAX_ITEM_STACK;

   
    for(int i=0; i<NB_HOTBAR_ITEM; i++){

        if( inventory.hotbar[i].id == item.id  ){
            inv = inventory.hotbar[i].nb;
            inv -= item.nb;

            if( inv < 0 ){
                item.nb = -(inv);
            }
            else{
                return 1;
            }
        }

    }

    for(int i=0; i<NB_INVENTORY_ITEM; i++){

        if( inventory.pcpl[i].id == item.id  ){
            inv = inventory.pcpl[i].nb;
            inv -= item.nb;

            if( inv < 0 ){
                item.nb = -(inv);
            }
            else{
                return 1;
            }
        }

    }

    return 0;
}

int inventory_remove( item_t * item ){

    if( item->nb > MAX_ITEM_STACK )
        item->nb = MAX_ITEM_STACK;

    for(int i=0; i<NB_HOTBAR_ITEM; i++){

        if( inventory.hotbar[i].id == item->id  ){
            inventory.hotbar[i].nb -= item->nb;

            if( inventory.hotbar[i].nb < 0 ){
                item->nb = -(inventory.hotbar[i].nb);
                inventory.hotbar[i].nb = 0;
                inventory.hotbar[i].id = 0;
            }
            else{
                if( inventory.hotbar[i].nb == 0 )
                    inventory.hotbar[i].id = 0;
                item->nb = 0;
                return 0;
            }
        }

    }

    for(int i=0; i<NB_INVENTORY_ITEM; i++){

        if( inventory.pcpl[i].id == item->id  ){
            inventory.pcpl[i].nb -= item->nb;

            if( inventory.pcpl[i].nb < 0 ){
                item->nb = -(inventory.pcpl[i].nb);
                inventory.pcpl[i].nb = 0;
                inventory.pcpl[i].id = 0;
            }
            else{
                if( inventory.pcpl[i].nb == 0 )
                    inventory.pcpl[i].id = 0;
                item->nb = 0;
                return 0;
            }
        }

    }

    return 1;
}

int inventory_clic( int x, int y, int * i, int * j ){

    SDL_Point point = { x, y };
    SDL_Rect rect = { 382, 190, 130, 130 };

    for(*j=0; *j<NB_INVENTORY_ITEM/NB_HOTBAR_ITEM; (*j)++){

        rect.x = 382;
        for(*i=0; *i<NB_HOTBAR_ITEM; (*i)++){

            if( SDL_PointInRect( &point, &rect ) )
                return 1;

            rect.x += 140;
            

        }
        rect.y += 140;

    }
    
    *j = -1;
    rect.x = 382;
    rect.y = 680;

    for(*i=0; *i<NB_HOTBAR_ITEM; (*i)++){

        if( SDL_PointInRect( &point, &rect ) )
                return 2;
        
        rect.x += 140;
    }




    return 0;    
}



int inventory_display(){

    int xMouse, yMouse;
    int i, j;

    SDL_bool launched_program = SDL_TRUE;
    while( launched_program ){

        SDL_Event event;

        while(SDL_PollEvent(&event)) {  

				switch(event.type) { 

					// Si croix en haut a droite selectionnée
					case SDL_QUIT:
						launched_program = SDL_FALSE;
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
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    SDL_SetCursor(cursor_click);
                    if( event.button.button == SDL_BUTTON_RIGHT ){
                        printf("%d/%d\n", event.button.x, event.button.y);
                        switch(inventory_clic(event.button.x, event.button.y, &i, &j) ){

                            /* inventory */
                            case 1:
                                inventory_give_hotbar( &(inventory.pcpl[j*NB_HOTBAR_ITEM + i]) );
                                break;

                            /* Hotbar */
                            case 2:
                                inventory_give_pcpl( &(inventory.hotbar[ i]) );
                                break;

                            default:
                                break;

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


        
        GUI_inventory();



        SDL_RenderPresent(renderer);





    }




    return 0;
}