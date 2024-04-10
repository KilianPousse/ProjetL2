#define NB_ITEMS 10


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
