#define NB_ITEMS 25


typedef struct {

    unsigned char id;
    int nb;

}item_t;

int initItem();
int freeItem();


item_t farmland_planttype(int x, int y);

SDL_Surface * items_surface[NB_ITEMS];

#define ID_ITEM_GRAINE_BLE 1
#define PATH_ITEM_GRAINE_BLE "assets/textures/item/graine_ble.png"

#define ID_ITEM_BLE 2
#define PATH_ITEM_BLE "assets/textures/item/ble.png"

#define ID_ITEM_GRAINE_TOMATE 3
#define PATH_ITEM_GRAINE_TOMATE "assets/textures/item/graine_tomate.png"

#define ID_ITEM_TOMATE 4
#define PATH_ITEM_TOMATE "assets/textures/item/tomate.png"

#define ID_ITEM_POISSON 5
#define PATH_ITEM_POISSON "assets/textures/item/poisson.png"

#define ID_ITEM_THON 6
#define PATH_ITEM_THON "assets/textures/item/thon.png"

#define ID_ITEM_POISSON_LANTERNE 7
#define PATH_ITEM_POISSON_LANTERNE "assets/textures/item/poisson_lanterne.png"

#define ID_ITEM_KOI 8
#define PATH_ITEM_KOI "assets/textures/item/koi.png"

#define ID_ITEM_REQUIN 9
#define PATH_ITEM_REQUIN "assets/textures/item/requin.png"

#define ID_ITEM_POISSON_DORE 10
#define PATH_ITEM_POISSON_DORE "assets/textures/item/poisson_dore.png"

