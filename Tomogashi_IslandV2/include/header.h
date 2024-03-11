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
#include <SDL2/SDL_ttf.h>

#define NAME_PROG "Tomogashi Island"    /**< Nom du programme */
#define VERS_GAME "alpha 1.2.1"           /**< Version du jeu */

#define FPS 24
#define FPS_LIMIT 1000/FPS

#define WINDOW_NAME "Tomogashi Island"  /**< Nom de la fenêtre */
#define WINDOW_WIDTH   1560     //1920  /**< Taille de la fenmetre en X */ 
#define WINDOW_HEIGHT  960      //1080  /**< Taille de la fenmetre en Y */

#define SIZE_TILE 60                            /**< Taille en pixel d'un tuile */
#define NB_TILE_X WINDOW_WIDTH/SIZE_TILE        /**< Nombre de tuiles en X */           // <=> NB_TILE_X = 26
#define NB_TILE_Y WINDOW_HEIGHT/SIZE_TILE       /**< Nombre de tuiles en Y */           // <=> NB_TILE_Y = 16

#define FAILURE 0       /**< Valeur d'un test faux */
#define SUCCESS 1       /**< Valeur d'un test vrai */

#define SIZE_MAP_X 3       /**< Nombre de partie de la map en X */
#define SIZE_MAP_Y 4       /**< Nombre de partie de la map en Y */



#define NB_ANIMATION 4


/**
 * \enum dir_t
 * \brief enum des directions possibles
**/
typedef enum{
            nord,   /**< Direction nord */
            est,    /**< Direction est */
            sud,    /**< Direction sud */
            ouest   /**< Direction ouest */
}dir_t;


#define NB_ACTIONS 5

/**
 * \struct player_t
 * \brief structure représentant les informations du joueur
**/
typedef struct{

    int x;                  /**< Position sur l'axe X du joueur */
    int y;                  /**< Position sur l'axe Y du joueur */
    dir_t dir;              /**< Direction du joueur */
    int vit;                /**< Vitesse de deplacement du joueur */
    SDL_Surface * sprites[4][NB_ANIMATION];  /**< Ensembles des sprites du joueur */
    int frame;
    SDL_Surface * actions[NB_ACTIONS];

}player_t;

void afficher_cadre(SDL_Window * window, SDL_Renderer * renderer);



/**
 * \struct map_t
 * \brief structure représentant la map
**/
typedef struct{
    int map[SIZE_MAP_X * SIZE_MAP_Y][NB_TILE_X][NB_TILE_Y];          /**< Contenu de la map */
    SDL_Surface * background[SIZE_MAP_X * SIZE_MAP_Y];                 /**< Contenu de la map */
    SDL_Surface * overlay[SIZE_MAP_X * SIZE_MAP_Y];                 /**< Contenu de la map */
    unsigned int x;          /**< indice de la partie de map en X */
    unsigned int y;          /**< indice de la partie de map en Y */
}map_t;

void afficher_cadre();
void afficher_pose_map();



SDL_Window * window;            // Fenêtre du jeu
SDL_Surface * icon;             // Icon du jeu
SDL_Renderer * renderer;        // Rendu du jeu
SDL_Surface * icon;

map_t map;



int outWindow(int x, int y);
int outMap(map_t m);

int initMap(map_t * m);
void freeMap(map_t * m);
void diplayBackground();
int canToGo( dir_t dir);
int tileValue(int i_map, int x, int y);

void ErrorLog(char * message);
void WarningLog(char * message);


#define MAIN_MAP "data/map"



player_t player;
int InitPlayer();
int FreePlayer();
void displayPlayer();


TTF_Font * hour_Font;

time_t ts;
void displayTime();
void displayShadow();

int action( int );
int tileAction();
void displayAction( int );
int tile_action;


void limit_fps( unsigned int limit );

void displayOverlay();

typedef struct{

    SDL_Surface * hour;
    SDL_Surface * dialog;

}gui_t;

gui_t GUI;

void initGUI();
void freeGUI();

void GUI_print_hour();
void GUI_print_dialog();



void displayGUI();


int situation;

#define SITUATION_MAIN_MENU 0
#define SITUATION_MOVE 1
#define SITUATION_DIALOGUE 2


#define LIMIT_PER_LINE 75

#define DIALOG_TEST "data/dialog/dialogue_test.txt"
int dialog( char * file_name );

void GameExit( int exit_value );

int dialog( char * file_name );