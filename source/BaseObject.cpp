 #include "BaseObject.h"

BaseObject::BaseObject()
{
    bTexture = NULL ;
    bTexture = NULL ;
    bRect.x = 0 ;
    bRect.y = 0 ;
    bRect.w = 0 ;
    bRect.h = 0 ;
}

BaseObject::~BaseObject()
{
    Free() ;
}

bool BaseObject::LoadImg(string file_path, SDL_Renderer* screen)
{
    SDL_Texture* newTexture = NULL ;
    SDL_Surface* loadSurface = IMG_Load(file_path.c_str()) ;
    if(loadSurface == NULL) return 0 ;

    SDL_SetColorKey(loadSurface,SDL_TRUE, SDL_MapRGB(loadSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B)) ;

    newTexture = SDL_CreateTextureFromSurface(screen, loadSurface) ;

    if(newTexture != NULL)
    {
        bRect.w = loadSurface->w ;
        bRect.h = loadSurface->h ;
    }

    SDL_FreeSurface(loadSurface) ;
    bTexture = newTexture ;

    return (bTexture != NULL) ;
}
void BaseObject::Render(SDL_Renderer* des, SDL_Rect* clip )
{
    SDL_Rect renderQuad = {bRect.x, bRect.y, bRect.w, bRect.h} ;
    SDL_RenderCopy(des, bTexture, clip, &renderQuad) ;
}
void BaseObject::Render(int x, int y, SDL_Renderer* des, SDL_Rect* clip)
{
    SDL_Rect renderQuad = {x, y, bRect.w, bRect.h} ;
    if(clip != nullptr)
    {
        renderQuad.w = clip->w ;
        renderQuad.h = clip->h ;
    }
    SDL_RenderCopy(des, bTexture, clip, &renderQuad) ;
    return ;
}
bool BaseObject::LoadText(string Text,TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *screen)
{
    SDL_Texture* newTexture = NULL ;
	SDL_Surface* loadSurface = TTF_RenderText_Solid(gFont, Text.c_str(), textColor);
	if (loadSurface == NULL) return 0 ;

    newTexture = SDL_CreateTextureFromSurface(screen, loadSurface);

    if (newTexture != NULL)
    {
        bRect.w = loadSurface->w;
        bRect.h = loadSurface->h;
    }

    SDL_FreeSurface(loadSurface);
    bTexture = newTexture ;

	return (bTexture != NULL) ;
}

void BaseObject::Free()
{
    if(bTexture != NULL)
    {
        SDL_DestroyTexture(bTexture) ;
        bTexture = NULL ;
        bRect = {0,0,0,0} ;
    }
}
