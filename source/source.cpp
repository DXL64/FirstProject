#include "commonFunction.h"
#include "BaseObject.h"

BaseObject gBackground ;

bool init()
{
    int sdlInit = SDL_Init(SDL_INIT_EVERYTHING) ;
    if(sdlInit < 0) return 0 ;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") ;
    gWindow = SDL_CreateWindow("BraveSolider", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) ;
    if(gWindow == NULL) return 0 ;
    gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED) ;
    if(gScreen == NULL) return 0 ;
    SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR) ;
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) && imgFlags))
        return 0 ;
    return 1 ;
}
bool loadBackGround()
{
    bool ret = gBackground.LoadImg("image/background.png", gScreen) ;
    if(ret == 0) return 0;
    return 1 ;
}
void close()
{
    gBackground.Free() ;

    SDL_DestroyRenderer(gScreen) ;
    gScreen = NULL ;

    SDL_DestroyWindow(gWindow) ;
    gWindow = NULL ;

    IMG_Quit() ;
    SDL_Quit() ;

}
int main(int argv, char** args)
{
    if(init() == 0) return 0 ;
    if(loadBackGround() == 0) return 0 ;
    bool quit = 0 ;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = 1 ;
            }
        }
        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR) ;
        SDL_RenderClear(gScreen) ;
        gBackground.Render(gScreen, NULL) ;
        SDL_RenderPresent(gScreen) ;
    }
    close() ;
    return 0 ;
}


