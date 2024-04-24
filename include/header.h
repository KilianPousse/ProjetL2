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
#include <SDL2/SDL_mixer.h>

#define NAME_PROG "Tomogashi Island"    /**< Nom du programme */
#define VERS_GAME "vers. 1.0"           /**< Version du jeu */

#define FPS 24                  /**< Nombres de frame par seconde */
#define FPS_LIMIT 1000/FPS      /**< Temps d'attente entre deux frames */

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
    SDL_Texture * sprites[4][NB_ANIMATION];  /**< Ensembles des sprites du joueur */
    int frame;      /**< Frame d'animation du personnage */
    SDL_Texture * actions[NB_ACTIONS];  /**< Ensemble des surfaces d'icons d'actions */

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
    SDL_Texture * background[SIZE_MAP_X * SIZE_MAP_Y];                 /**< Contenu de la map */
    SDL_Texture * overlay[SIZE_MAP_X * SIZE_MAP_Y];                 /**< Contenu de la map */
    int x;          /**< indice de la partie de map en X */
    int y;          /**< indice de la partie de map en Y */
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

#define TIME_MAX_DAY 24 * 60 * FPS
/*     
 * \fn displayTime();
 * \brief Permet d'afficher le temps in game
*/
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

    SDL_Surface * hour;         /**< Boite de l'heure */
    SDL_Surface * dialog;       /**< Boite de dialogue */
    SDL_Surface * coins;        /**< Boite de l'argent */
    SDL_Surface * inventory;    /**< Boite de l'inventaire*/

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


/**
 * \fn int GUI_inventory();
 * \brief Affichage de l'inventaire
**/
int GUI_inventory();


/**
 * \fn int GUI_coins();
 * \brief Affichage de l'argent
**/
int GUI_coins();

#define LIMIT_PER_LINE 75   /**< Limite de caracteres par ligne */

#define DIALOG_TEST "data/dialog/dialogue_test.txt"


/**
 * \fn int GUI_coins();
 * \brief Affichage de l'argent
**/
int dialog( char * file_name );


/**
 * \fn void GameExit( int exit_value );
 * \brief Affichage de l'argent
 * \param exit_value valeur de sortie du jeu
**/
void GameExit( int exit_value );


/**
 * \fn int dialog( char * file_name );
 * \brief Affichage un dialogua a partir d'un fichier
 * \param file_name chemin du fichier de diagua a afficher
**/
int dialog( char * file_name );

#define FILE_SAVE "data/save/save"      /**< Chemin vers les sauvegardes */
#define FILE_DEFAULT_SAVE "data/save/default"      /**< Chemin vers la sauvegarde par défaut */

/**
 * \fn int LoadSave();
 * \brief Charge une sauvegarde
**/
int LoadSave();

/**
 * \fn int LoadSave();
 * \brief Charge une sauvegarde
**/
int SaveSave();

/**
 * \fn int newSave();
 * \brief créer une nouvelle sauvegarde
**/
int newSave();


/**
 * \fn void ErrorLog(char * message);
 * \brief Arret le programme avec un maessage d'erreur
 * \param message message a afficher
**/
void ErrorLog(char * message);

/**
 * \fn void WarningLog(char * message);
 * \brief Affiche un maessage (warning)
 * \param message message a afficher
**/
void WarningLog(char * message);


/* ------------- Gestion dde l'agriculture ------------- */

#define IMAP_FARM 5         /**< L'indice de la map d'agriculture */
#define NB_PLANTS_MAX NB_FARMLAND   /**< nombre de plantation maximale */
#define NB_FARMLAND 60              /**< nombre de plantation maximale */
#define NB_STEM_PLANT 4             /**< nombre d'étape de croissance max d'une plante  */


/**
 * \struct plante_t
 * \brief structure des plantes
**/
typedef struct{

    int id;     /**< identifiant de la plante*/
    int x, y;   /**< position de la plante*/
    int age;    /**< age de la plante*/
    int max_age;    /**< age a atteindre pour que la plante soit totalement poussée*/

}plant_t;


/**
 * \struct farm_t
 * \brief structure des plantations
**/
typedef struct{

    plant_t plants[NB_FARMLAND];        /**< ensemble des plantations*/
    char n_plants;          /**< nombre de plantations utilisées*/
    SDL_Texture * texture[NB_PLANTS_MAX][NB_STEM_PLANT]; /**< textures des plantes*/
    
}farm_t;


/* ---- Identifiant des plantation ----- */
#define ID_PLANT_BLE 1
#define ID_PLANT_TOMATE 2
/* ------------------------------------- */


/**
 * \fn void displayFarm(int i_map)
 * \brief Affiche les plantations sur la carte
 * \param i_map Indice de la partie de la carte où afficher les plantations
 */
void displayFarm(int i_map);

/**
 * \fn int initFarmTexture()
 * \brief Initialise les textures des plantations
 * \return 1 en cas de succès, sinon 0
 */
int initFarmTexture();

/**
 * \fn int farmland_empty(int * x, int * y)
 * \brief Vérifie si une parcelle de plantation est vide
 * \param x Pointeur vers la position X de la parcelle vide (sortie)
 * \param y Pointeur vers la position Y de la parcelle vide (sortie)
 * \return 1 si une parcelle vide est trouvée, sinon 0
 */
int farmland_empty(int * x, int * y);

/**
 * \fn int farmland_finalstage(int x, int y)
 * \brief Vérifie si une parcelle de plantation est à son stade final
 * \param x Position X de la parcelle
 * \param y Position Y de la parcelle
 * \return 1 si la parcelle est à son stade final, sinon 0
 */
int farmland_finalstage(int x, int y);

/**
 * \fn int farmland_remove(int x, int y)
 * \brief Retire une parcelle de plantation
 * \param x Position X de la parcelle à retirer
 * \param y Position Y de la parcelle à retirer
 * \return 1 en cas de succès, sinon 0
 */
int farmland_remove(int x, int y);

/**
 * \fn void freeFarm()
 * \brief Libère les ressources allouées aux plantations
 */
void freeFarm();

// ... Suite du fichier header.h

/**
 * \def MAX_COINS
 * \brief Montant maximum d'argent que peut posséder le joueur
 */
#define MAX_COINS 999999

/**
 * \struct sprite_t
 * \brief Structure représentant les textures des sprites
 */
typedef struct {
    SDL_Texture * texture[NB_ANIMATION]; /**< Tableau des textures des sprites */
} sprite_t;

/**
 * \fn int initPNJ()
 * \brief Initialise les personnages non-joueurs (PNJ)
 * \return 1 en cas de succès, sinon 0
 */
int initPNJ();

/**
 * \fn int freePNJ()
 * \brief Libère les ressources allouées aux PNJ
 * \return 1 en cas de succès, sinon 0
 */
int freePNJ();

/**
 * \fn int displayPNJ()
 * \brief Affiche les PNJ sur la carte
 * \return 1 en cas de succès, sinon 0
 */
int displayPNJ();


/**
 * \fn SDL_Texture * chargerTexture(char * chemin, SDL_Renderer * renderer)
 * \brief Charge une texture à partir d'un chemin d'accès
 * \param chemin Chemin d'accès à l'image
 * \param renderer Renderer SDL pour la texture
 * \return Pointeur vers la texture chargée, NULL en cas d'erreur
 */
SDL_Texture * chargerTexture(char * chemin, SDL_Renderer * renderer);

/**
 * \def NB_PNJ
 * \brief Nombre de PNJ dans le jeu
 */
#define NB_PNJ 10

/**
 * \var sprite_t pnj_sprites[NB_PNJ]
 * \brief Tableau des textures des sprites des PNJ
 */
sprite_t pnj_sprites[NB_PNJ];

/**
 * \def ID_PNJ_RISETTE
 * \brief Identifiant du PNJ "Risette"
 */
#define ID_PNJ_RISETTE 0

/**
 * \def ID_PNJ_PY
 * \brief Identifiant du PNJ "Py"
 */
#define ID_PNJ_PY 1
/**
 * \def ID_PNJ_CRABE
 * \brief Identifiant du PNJ "Crabe"
 */
#define ID_PNJ_CRABE 2
/**
 * \def ID_PNJ_ZEBI
 * \brief Identifiant du PNJ "Zebi"
 */
#define ID_PNJ_ZEBI 3
/**
 * \def ID_PNJ_KEN
 * \brief Identifiant du PNJ "Ken"
 */
#define ID_PNJ_KEN 4
/**
 * \def ID_PNJ_BROCOLI
 * \brief Identifiant du PNJ "Brocoli"
 */
#define ID_PNJ_BROCOLI 5
/**
 * \def ID_PNJ_SERGE
 * \brief Identifiant du PNJ "Serge"
 */
#define ID_PNJ_SERGE 6

/**
 * \var SDL_Window * window
 * \brief Fenêtre du jeu
 */
SDL_Window * window;

/**
 * \var SDL_Renderer * renderer
 * \brief Rendu du jeu
 */
SDL_Renderer * renderer;

/**
 * \var map_t map
 * \brief Carte du jeu
 */
map_t map;

/**
 * \var player_t player
 * \brief Joueur du jeu
 */
player_t player;

/**
 * \var gui_t GUI
 * \brief Ensemble des interfaces graphiques du jeu
 */
gui_t GUI;

/**
 * \var int tile_action
 * \brief Valeur de la tuile devant le joueur
 */
int tile_action;

/**
 * \var farm_t farm
 * \brief Ensemble des plantations
 */
farm_t farm;

/**
 * \var int coins
 * \brief Argent du joueur
 */
int coins;

/**
 * \var TTF_Font * hour_Font
 * \brief Police de l'heure
 */
TTF_Font * hour_Font;

/**
 * \var TTF_Font * text_Font
 * \brief Police de texte
 */
TTF_Font * text_Font;

/**
 * \var SDL_Window * window
 * \brief Fenêtre du jeu
 */
SDL_Window * window;

/**
 * \var SDL_Renderer * renderer
 * \brief Rendu du jeu
 */
SDL_Renderer * renderer;

/**
 * \var map_t map
 * \brief Carte du jeu
 */
map_t map;

/**
 * \var player_t player
 * \brief Joueur du jeu
 */
player_t player;

/**
 * \var gui_t GUI
 * \brief Ensemble des interfaces graphiques du jeu
 */
gui_t GUI;

/**
 * \var int tile_action
 * \brief Valeur de la tuile devant le joueur
 */
int tile_action;

/**
 * \var farm_t farm
 * \brief Ensemble des plantations
 */
farm_t farm;

/**
 * \var int coins
 * \brief Argent du joueur
 */
int coins;

/**
 * \var TTF_Font * hour_Font
 * \brief Police de l'heure
 */
TTF_Font * hour_Font;

/**
 * \var TTF_Font * text_Font
 * \brief Police de texte
 */
TTF_Font * text_Font;

time_t tps_game;

SDL_Surface * icon;
SDL_Cursor * cursor;
SDL_Cursor * cursor_select;
SDL_Cursor * cursor_click;

#define NB_SPRITES_WATER 14
SDL_Texture * water[NB_SPRITES_WATER];
int displayWater();
int initWater();
int freeWater();

SDL_Texture * bateau[NB_ACTIONS];
int initBateau();
int displayBateau();
int freeBateau();

int playMusic(char* path, Mix_Chunk** chunk, int* channel, int loop);
void music2fond();

Mix_Chunk* music;
char volume_music;
int channel_music;
Mix_Chunk* sfx;
int channel_sfx;
char volume_sfx;
