#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "header.h"
#include "style.h"

int printLine( char * line, TTF_Font * font, SDL_Color color, unsigned int y ){

    // Crée une surface de texte
    SDL_Surface* textSurface = TTF_RenderText_Solid( font , line, color );
    if (textSurface == NULL) {
        return 1;
    }

    // Crée une texture à partir de la surface de texte
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        SDL_FreeSurface(textSurface); // Libère la surface maintenant que la texture est créée
        return 2;
    }
    
    SDL_Rect rect = { 440, y, 1, 1 };
    SDL_QueryTexture(textTexture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, textTexture, NULL, &rect);

    SDL_FreeSurface(textSurface); // Libère la surface maintenant que la texture est créée

    SDL_DestroyTexture(textTexture);

    return 0;

}

char printDialogue( const char * dialogue, TTF_Font * font, SDL_Color color ) {
    
    char word[32] = "\0"; // Tableau pour stocker le mot courrant de lecture
    unsigned int wordlen = 0; // Longueur actuelle du mot
    unsigned int linelen = 0; // Longueur actuelle de la ligne
    unsigned int i = 0; // Indice du caractère courrant 
    char line[ LIMIT_PER_LINE ] = "\0";

    int y = 720;
    
    for( i = 0; dialogue[i]; i++ ) {
        
        if( dialogue[i] != ' ' ) {
            word[ wordlen++ ] = dialogue[i]; // Ajoute le caractère au mot courrant
            word[ wordlen ] = '\0'; // Termine le mot avec un caractère nul pour former une chaîne de caractères valide
            linelen++; // Incrémente la longueur de la ligne
        } else{
            
            if( linelen > LIMIT_PER_LINE-1 ) { // Si la longueur de la ligne dépasse la limite
                linelen = wordlen+1; // Réinitialise la longueur de la ligne
                printLine( line, font, color, y ); 
                y += 40; // Passe à la ligne suivante
                line[ 0 ] = '\0';
            }
            
            word[ wordlen++ ] = ' '; // Ajoute un espace au mot courrant
            word[ wordlen ] = '\0'; // Termine le mot avec un caractère nul pour former une chaîne de caractères valide
            linelen++; // Incrémente la longueur de la ligne

            strcat( line, word );

            word[ wordlen = 0 ] = '\0'; // Réinitialise le mot pour le prochain
        }
    }
    printLine( line, font, color, y );

    return dialogue[i];
}

int recupDialogue( FILE * data, char * dialogue, char * interlocutor ){

    // Lecture du nom de l'interlocuteur suivi du dialogue
    if( fscanf( data, "%[^#]#%[^\n]\n", interlocutor, dialogue ) != 2 )
        return 3; // Retourne 1 en cas d'échec de la lecture

    // Calcul de la longueur du dialogue
    unsigned int dialoguelen = strlen( dialogue );

    // Ajout d'un espace à la fin du dialogue et mise à jour du caractère nul
    dialogue[ dialoguelen++ ] = ' '; 
    dialogue[ dialoguelen ] = '\0';

    return !strlen(interlocutor) + !strlen(dialogue); // Retourne 0 en cas de succès
}

int printfInterlocutor( char * inter, TTF_Font * font, SDL_Color color ){

    // Crée une surface de texte
    SDL_Surface* textSurface = TTF_RenderText_Solid( font , inter, color );
    if (textSurface == NULL) {
        WarningLog("Erreur lors de la création de la surface de texte de l'interlocuteur");
        return 1;
    }

    // Crée une texture à partir de la surface de texte
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        WarningLog("Erreur lors de la création de la texture de l'interlocuteur");
        SDL_FreeSurface(textSurface); // Libère la surface maintenant que la texture est créée
        return 2;
    }
    
    SDL_Rect rect = { 445, 656, 1, 1 };
    SDL_QueryTexture(textTexture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, textTexture, NULL, &rect);

    SDL_FreeSurface(textSurface); // Libère la surface maintenant que la texture est créée

    SDL_DestroyTexture(textTexture);

    return 0;

}


int recupDialogueSprites( char * inter, SDL_Surface * sprites[] ){

    char path[256];
    char name[ strlen(inter) ];
    
    for(int i=0; inter[i]; i++){
        name[i] = tolower( inter[i] );
    }
    name[strlen(inter)] = '\0';
    //printf("*'%s'(%d) == '%s'(%d)*\n", name, strlen(name), inter, strlen(inter));

    for(int i=0; i<4; i++){
        sprintf( path, "%s/%s/idle_%d.png", IMG_SPRITES, name, i );
        //printf("//%s//\n", path);
        sprites[i] = IMG_Load(path);
    }

    return 0;
}

int printfDialogueSprites( SDL_Surface * sprites[] , unsigned int frame){

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, sprites[frame%4]);
    if (texture == NULL) {
        return 1;
    }

    SDL_Rect rect = { 30 , 660, SIZE_TILE * 5, SIZE_TILE * 5 };

    // Copier la texture sur tout le rendu (pour remplir l'écran)
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);
    
    return 0;
}


int dialog( char * file_name ){

    FILE * file = fopen( file_name, "r" );
    if( file == NULL ){
        WarningLog("Impossible de charger le texte du dialogue");
        return 1;
    }

    unsigned int frame = 0;

    char inter[24] = "???";
    char dial[1024] = "...";
    
    
    if( recupDialogue( file, dial, inter ) != 0 ){
        fclose( file );
        return 3;
    }
    //printf("'%s': '%s'\n", inter, dial);

    SDL_bool launched_program = SDL_TRUE;
    SDL_Rect rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    SDL_Color color = WHITE_COLOR;
    TTF_Font * font = TTF_OpenFont(FONT_DIALOG, 35);
    if( font == NULL ){
        WarningLog("Impossible de charger la police d'écriture du dialogue");
        fclose( file );
        return 2;
    }

    unsigned int frame_limit = 0;

    SDL_Surface * sprites[4];
    recupDialogueSprites( inter, sprites );


    while( launched_program ){

        frame_limit = SDL_GetTicks() + FPS_LIMIT;
        SDL_Event event;

        while(SDL_PollEvent(&event)) {  

				switch(event.type) { 

					// Si croix en haut a droite selectionnée
					case SDL_QUIT:
						launched_program = SDL_FALSE;
                        fclose( file );
                        TTF_CloseFont( font );
                        for(int i=0; i<4; i++){
                            SDL_FreeSurface( sprites[i] );
                        }
                        GameExit(EXIT_SUCCESS);
						break; 

                    case SDL_KEYDOWN:

                        switch(event.key.keysym.sym){

                            case SDLK_e:
                            case SDLK_SPACE:
                                // Une touche a été relâchée
                                if( recupDialogue( file, dial, inter ) != 0 )
                                    launched_program = SDL_FALSE;
                                printf("'%s': '%s'\n", inter, dial);
                                recupDialogueSprites( inter, sprites );
                                break;
								
								
                                
					        default:		
					            break;
                        }
                        break;

                         case SDL_MOUSEBUTTONDOWN:
                        SDL_SetCursor( cursor_click );
                        break;
                    
                    case SDL_MOUSEBUTTONUP:
                        SDL_SetCursor( cursor );
                        break;
                    
                    default:
                        break;
                
				}
                
        }

                /* On fait le rendu ! */
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderClear(renderer);// Rectangle plein
                
                displayWater();
                displayBateau();
                diplayBackground();
                displayFarm( map.y*SIZE_MAP_X + map.x );
                displayPlayer( tile_action );
                displayPNJ();
                displayOverlay();

                displayGUI();
                displayTime();

                // Filtre noire
                SDL_SetRenderDrawColor(renderer, 0x01, 0x01, 0x00, 0x60);
                SDL_RenderFillRect(renderer, &rect);

                printfDialogueSprites( sprites, (frame/12)%NB_ANIMATION );

                GUI_print_dialog();

                printfInterlocutor( inter, font, color );
                printDialogue( dial, font, color );

                SDL_RenderPresent(renderer);
                limit_fps( frame_limit );

                
			 frame++;
    }


    
    for(int i=0; i<4; i++){
        SDL_FreeSurface( sprites[i] );
    }
    fclose( file );
    TTF_CloseFont( font );



    return 0;
}