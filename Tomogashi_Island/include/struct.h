typedef struct item_s{
    /*Image de l'item*/
    char * nom;
    char * type;    /*cosmétique/plantation/poisson/autre*/
    /*intéraction => porter/poser/manger */
}item_t;

typedef struct meuble_s{
    /*image du meuble*/
    char * nom;
    char * type;
    /*intéraction*/
}meuble_t;

typedef struct musique_s{
    /*à définir plus tard*/*
    /*change en fonction de la zone*/
}musique_t;

typedef struct argent_s{
    char * nom;
    /*image de l'image*/
    int val;
}argent_t;

