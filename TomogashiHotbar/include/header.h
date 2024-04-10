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



#define NB_ANIMATION 4       /**< Nombre de frame dans une animation */

/* ------------------ Player ------------------ */

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


#define NB_ACTIONS 5  /**< Nombre d'icons d'actions */

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
    int frame;      /**< Frame d'animation du personnage */
    SDL_Surface * actions[NB_ACTIONS];  /**< Ensemble des surfaces d'icons d'actions */

}player_t;

#define PLAYER_SIZE 50

/**
 * \fn int InitPlayer();
 * \brief Permet d'initialiser le joueur
 * \return 0 si echec et 1 si succes
**/
int InitPlayer();

/**
 * \fn int FreePlayer();
 * \brief Permet de liberer le joueur
 * \return 0 si echec et 1 si succes
**/
int FreePlayer();

/**
 * \fn dvoid displayPlayer();
 * \brief Permet d'afficher le joueur
**/
void displayPlayer();

/* ------------------ ----- ------------------ */


/**
 * \fn void afficher_cadre(SDL_Window * window, SDL_Renderer * renderer);
 * \brief Fonction optinelle qui affiche un cadrillage pour délimiter les tuiles de la map
 * \param window Fentre d'affiche
 * \param renderer Rendu de la fenêtre
**/
void afficher_cadre(SDL_Window * window, SDL_Renderer * renderer);




/* ------------------ Map ------------------ */

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

/**
 * \fn int outWindow(int x, int y);
 * \brief Permet de savoir si le joueur se trouve hors de la fênetre
 * \param x position X du joueur
 * \param y position Y du joueur
 * \return 0 --> Si joueur dans la fenêtre
 * \return 1 --> Si joueur dans la fenêtre
 * \return 2 --> Si joueur dans la fenêtre
 * \return 3 --> Si joueur dans la fenêtre
 * \return 4 --> Si joueur dans la fenêtre
**/
int outWindow(int x, int y);

/**
 * \fn int outMap(map_t m);
 * \brief Permet de savoir si le joueur est hors de la map
 * \param m est la map du jeu
 * \return 0 --> est toujours dans la map
 * \return 1 --> sortie par la gauche
 * \return 2 --> sortie par en haut
 * \return 3 --> sortie par la droite
 * \return 4 --> sortie par en bas
**/
int outMap(map_t m);

/**
 * \fn int initMap(map_t * m);
 * \brief Permet d'initialiser la map
 * \param m est la map du jeu à initialiser
**/
int initMap(map_t * m);

/**
 * \fn freeMap(map_t * m);
 * \brief Permet de liberer la map
 * \param m est la map du jeu à libérer
**/
void freeMap(map_t * m);

/**
 * \fn diplayBackground();
 * \brief Permet d'afficher l'arrière plan du jeu
**/
void diplayBackground();

/**
 * \fn displayOverlay();
 * \brief Permet d'afficher le calque au dessus de l'arrière plan du jeu
**/
void displayOverlay();

/**
 * \fn int canToGo( dir_t dir);
 * \brief Permet de savoir si le joueur peut aller en avancant dans un direction
 * \param dir est la direction du mouvement du joueur
 * \return 0 --> Le joueur ne peut pas y aller
 * \return 1 --> Le joueur peut y aller
**/
int canToGo( dir_t dir);

/**
 * \fn int tileValue(int i_map, int x, int y);
 * \brief Permet de recuperer la valeur d'une tuile selon une position
 * \param i_map indice de la parcel de map
 * \param x position X du joueur
 * \param y position Y du joueur
 * \return la valeur d'une tuile de la map à la position donnée
**/
int tileValue(int i_map, int x, int y);

#define MAIN_MAP "data/map"     /**< chemin vers les données de la map */

/**
 * \fn void afficher_pose_map();
 * \brief Fonction optinelle qui affiche dans le terminal la position du joueur dans les maps
**/
void afficher_pose_map();

/* ------------------ --- ------------------ */



/**
 * \fn displayTime();
 * \brief Permet d'afficher le temps in game
**/
void displayTime();

/**
 * \fn displayShadow(();
 * \brief Permet d'afficher l'effet de la nuit
**/
void displayShadow();

/**
 * \fn int action( int tile );
 * \brief Permet de realiser l'action de la valeur de la tuile
 * \param tile valeur de la tuile du joueur
 * \return la valeur de la tuile du joueur
**/
int action( int tile );

/**
 * \fn int tileAction();
 * \brief Permet de recuperer l'action dans une tuile
 * \return -1 --> si l'action est hors de la fenêtre de jeu
 * \return la valeur de l'action tuile du joueur
**/
int tileAction();

/**
 * \fn void displayAction( int action );
 * \brief Permet d'afficher l'icon de l'action
 * \param action valeur de l'action du joueur
**/
void displayAction( int action );


/**
 * \fn void limit_fps( unsigned int limit );
 * \brief Permet de limiter les fps a la limite (24 fps)
 * \param limite limite des fps
**/
void limit_fps( unsigned int limit );

/**
 * \struct gui_t
 * \brief structure comportants les interfaces
**/
typedef struct{

    SDL_Surface * hour;
    SDL_Surface * dialog;

}gui_t;


/**
 * \fn void initGUI();
 * \brief Permet d'inoitialiser les interfaces
**/
void initGUI();

/**
 * \fn void freeGUI();
 * \brief Permet d'e libérer les surafaces
**/
void freeGUI();

/**
 * \fn void GUI_print_hour();
 * \brief Permet d'afficher l'interface de l'hour
**/
void GUI_print_hour();

/**
 * \fn void GUI_print_hour();
 * \brief Permet d'afficher l'interface des dialogues
**/
void GUI_print_dialog();

/**
 * \fn void displayGUI();
 * \brief Permet d'afficher l'interface
**/
void displayGUI();  

#define LIMIT_PER_LINE 75   /**< Limite de caracteres par ligne */

#define DIALOG_TEST "data/dialog/dialogue_test.txt"

int dialog( char * file_name );

void GameExit( int exit_value );

int dialog( char * file_name );


#define FILE_SAVE "data/save/save"
int LoadSave();
int SaveSave();


void ErrorLog(char * message);
void WarningLog(char * message);

SDL_Surface * zoomSurface(SDL_Surface* originalSurface, double zoomFactor);

/* ------------- Gestion dde l'agriculture ------------- */

#define IMAP_FARM 5
#define NB_PLANTS_MAX 3
#define NB_FARMLAND 10
#define NB_STEM_PLANT 2

typedef struct{

    int x, y;
    int id;
    long age;

}plant_t;

typedef struct{

    plant_t plants[NB_FARMLAND];
    int n_plants;
    SDL_Surface * texture[NB_PLANTS_MAX][NB_STEM_PLANT];
    
}farm_t;

#define ID_PLANT_CARROT 1

void displayFarm( int i_map );
int initFarmTexture(  );


SDL_Window * window;            /**< Fenêtre du jeu */
SDL_Surface * icon;             /**< Icon du jeu */
SDL_Renderer * renderer;        /**< Rendu du jeu */
SDL_Surface * icon;             /**< Icon du jeu */
map_t map;                      /**< Map du jeu */
player_t player;                /**< Joueur du jeu */
time_t tps_game;                /**< Temps dans le jeu */
gui_t GUI;                      /**< Ensemble des Game User Interfaces*/
int tile_action;                /**< Valeur de la tuile devant le joueur */
SDL_Cursor * cursor;
farm_t farm;


TTF_Font * hour_Font;       /**< Police de l'heure */

