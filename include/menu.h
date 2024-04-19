
typedef struct bouton_s{
    char * texte; /**< Définiton des nom des boutons*/
    SDL_Rect rectangle;  /**< Définiton du rectangle pour savoir si le joueur clique dedans ou pas*/
    SDL_Texture * image; /**< Image du bouton si pas de clique*/
    SDL_Texture * clique; /**< Image du bouton si le joueur clique dessus*/
}bouton_t;

typedef struct nuages_s{
    SDL_Rect rectangle;
    SDL_Texture * image[2];
}nuages_t;

typedef struct logo_s{
    SDL_Rect rectangle;
    SDL_Texture * image[6];
}logo_t;

void menu_destruction(bouton_t * bouton, SDL_Texture * texture,nuages_t nuage, nuages_t nuagea,nuages_t nuageb,nuages_t nuagec,logo_t logo);
int menu_main();

int main_option();
void option_destruction(bouton_t * bouton, SDL_Texture * texture);
