#include <SDL2/SDL.h>

#ifdef _WIN32
#pragma comment (lib,"sdl.lib") 
#pragma comment (lib,"sdlmain.lib")
#endif

typedef struct TileMap
{
    int** data;
    int ldata,hdata; // largeur et hauteur de la map. Width/Heigth of the map
    SDL_Surface* tileset;
    int ltile,htile; // largeur et hauteur d'un tile. Width/Heigth of a tile
    int xtile,ytile; // nombre de tiles sur le tileset en x et y
} TileMap;

int Load(const char* fictileset,TileMap* m)
{
    char ficbmp[50];
    int i,j;
    FILE* F = fopen(fictileset,"r");
    if (!F)
        return -1;
    fscanf(F,"%s %d %d",ficbmp,&m->xtile,&m->ytile);
    fscanf(F,"%d %d",&m->ldata,&m->hdata);
    m->data = (int**)malloc(m->ldata*sizeof(int*));
    for(i=0;i<m->ldata;i++)
        m->data[i] = (int*)malloc(m->hdata*sizeof(int));
    for(j=0;j<m->hdata;j++)
        for(i=0;i<m->ldata;i++)
            fscanf(F,"%d",&m->data[i][j]);
    fclose(F);
    m->tileset = SDL_LoadBMP(ficbmp);
    if (m->tileset==NULL)
        return -1;
    m->ltile = m->tileset->w / m->xtile;
    m->htile = m->tileset->h / m->ytile;
    return 0;
}

void FreeTileMap(TileMap* m)
{
    int i;
    SDL_FreeSurface(m->tileset);
    for(i=0;i<m->ldata;i++)
        free(m->data[i]);
    free(m->data);
}

void Afficher(SDL_Surface* screen,TileMap* m)
{
    int i,j;
    SDL_Rect Rect_dest;
    SDL_Rect Rect_source;
    Rect_source.w = (Uint16)m->ltile;
    Rect_source.h = (Uint16)m->htile;
    for(i=0;i<m->ldata;i++)
    {
        for(j=0;j<m->hdata;j++)
        {
            Rect_dest.x = (Uint16)(i*m->ltile);
            Rect_dest.y = (Uint16)(j*m->htile);
            Rect_source.x = (Uint16)((m->data[i][j]%m->xtile) * m->ltile);
            Rect_source.y =  (Uint16)((m->data[i][j]/m->xtile) * m->htile);
            SDL_BlitSurface(m->tileset,&Rect_source,screen,&Rect_dest);
        }
    }
    
}

int mai(int argc,char** argv)
{
    SDL_Surface* screen;
    TileMap m;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    if (Load("tileset1.txt",&m)==-1)
    {        
        printf("Echec de chargement tileset1.bmp ; tileset1.txt\n");
        SDL_Quit();
        return -1;
    }
    screen = SDL_GetVideoDriver(32);        //m.ltile*m.ldata,m.htile*m.hdata, 32,SDL_SWSURFACE);
    Afficher(screen,&m);
    do  // attend qu'on appuie sur une touche.
    {
        SDL_WaitEvent(&event);
    } while (event.type!=SDL_KEYDOWN);
    FreeTileMap(&m);
    SDL_Quit();
    return 0;
}