
/**
 * \file menu.h
 * \brief Création des structures utilisées dans menu.c
 * \details Permet de stocker les diffèrentes structures et fonctions 
 * \author Pousse Kilian - Pierre Elona - Vallee Alban 
 * \version alpha 2.2
 * \date 15/04/2024
**/




/**
 * \enum bouton_t
 * \brief Structure representant tout les informations nécessaire aux boutons et à leurs interactions
**/
typedef struct bouton_s{
    char * texte; /**< Définiton des nom des boutons*/
    SDL_Rect rectangle;  /**< Définiton du rectangle pour savoir si le joueur clique dedans ou pas*/
    SDL_Texture * image; /**< Image du bouton si pas de clique*/
    SDL_Texture * clique; /**< Image du bouton si le joueur clique dessus*/
}bouton_t;


/**
 * \enum nuages_t
 * \brief Structure representant tout les informations nécessaire aux nuages et à leurs interactions
**/
typedef struct nuages_s{
    SDL_Rect rectangle; /**< Définitons de la taille du nuage dans un rectange de taille choisi lors de la création du nuage*/
    SDL_Texture * image[2];/**< Tableau d'image pour animer le nuages*/
}nuages_t;

/**
 * \enum logo_t
 * \brief Structure representant le logo du jeu et ses animations
**/
typedef struct logo_s{
    SDL_Rect rectangle;
    SDL_Texture * image[6];
}logo_t;

void menu_destruction(bouton_t * bouton, SDL_Texture * texture,nuages_t nuage, nuages_t nuagea,nuages_t nuageb,nuages_t nuagec,logo_t logo);
int menu_main();

int main_option();
void option_destruction(bouton_t * bouton, SDL_Texture * texture);
