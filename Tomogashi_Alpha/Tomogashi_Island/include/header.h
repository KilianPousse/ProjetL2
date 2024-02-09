/**
 * \file header.h
 * \brief Entete principale du projet
 * \details C'est ici qu'on retrouvera les initialisations des variables globals, struct, enum, fonctions, ...
 * \author Pousse Kilian - Pierre Elona - Vallee Alban 
 * \version alpha 1.2
 * \date 31/01/2024
**/
#define NAME_PROG "Tomogashi Island"    /**< Nom du programme */
#define VERS_GAME "alpha 1.2.1"           /**< Version du jeu */

#define WINDOW_NAME "Tomogashi Island"  /**< Nom de la fenêtre */
#define WINDOW_WIDTH   1088     //1920  /**< Taille de la fenmetre en X */
#define WINDOW_HEIGHT  768      //1080  /**< Taille de la fenmetre en Y */

#define SIZE_TILE 32                            /**< Taille en pixel d'un tuile */
#define NB_TILE_X WINDOW_WIDTH/SIZE_TILE        /**< Nombre de tuiles en X */
#define NB_TILE_Y WINDOW_HEIGHT/SIZE_TILE       /**< Nombre de tuiles en Y */

#define FAILURE 0       /**< Valeur d'un test faux */
#define SUCCESS 1       /**< Valeur d'un test vrai */

#define SIZE_MAP_X 3       /**< Nombre de partie de la map en X */
#define SIZE_MAP_Y 3       /**< Nombre de partie de la map en Y */



#define NB_ANIMATION 3


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

}player_t;




/**
 * \struct map_t
 * \brief structure représentant la map
**/
typedef struct{
    int map[SIZE_MAP_X * SIZE_MAP_Y][NB_TILE_X][NB_TILE_Y];          /**< Contenu de la map */
    SDL_Surface * background[SIZE_MAP_X * SIZE_MAP_Y];                 /**< Contenu de la map */
    int x;          /**< indice de la partie de map en X */
    int y;          /**< indice de la partie de map en Y */
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


#define MAIN_MAP "bin/data/map/main.txt"



player_t player;
int InitPlayer();
int FreePlayer();
void displayPlayer();