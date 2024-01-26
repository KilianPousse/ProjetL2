#define NAME_PROG "Tomogashi Island"
#define VERS_GAME "alpha 1.0"

#define WINDOW_NAME "Tomogashi Island"
#define WINDOW_WIDTH   1200//1920
#define WINDOW_HEIGHT  800//1080



#define FAILURE 0
#define SUCCESS 1


#define SIZE_MAP_X 8
#define SIZE_MAP_Y 9

#define MAIN_MAP "bin/data/map/main_map"

typedef struct{

    int size_x;
    int size_y;
    int map[SIZE_MAP_X][SIZE_MAP_Y];

}map_t;

map_t * map;



int initMap(char *);




#define DIR_NORD 0
#define DIR_EST 1
#define DIR_SUD 2       // "Visez vers le sud" - Libe
#define DIR_OUEST 3
