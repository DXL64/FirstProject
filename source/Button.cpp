#include "Button.h"

Button::Button(int x, int y)
{
    xPos = x ;
    yPos = y ;
    status = BUTTON_MOUSE_UP ;
}

bool Button::LoadButton(string file_path, SDL_Renderer* screen)
{
    bool success = BaseObject::LoadImg(file_path, screen) ;
    if(status == ONE_SPIRTES)
        buttonWidth = bRect.w ;
    else
        buttonWidth = bRect.w /2 ;
    buttonHeight = bRect.h ;
    return success ;
}

void Button::SetUpFrame()
{
    frameClip[0].w = buttonWidth ;
    frameClip[0].h = buttonHeight ;
    For(i, 1, BUTTON_SPRITES)
    {
        frameClip[i].x = frameClip[i-1].x + buttonWidth ;
        frameClip[i].y = 0 ;
        frameClip[i].w = buttonWidth ;
        frameClip[i].h = buttonHeight ;
    }
}

void Button::SetXY(int x,int y)
{
    xPos = x ;
    yPos = y ;
}

bool Button::isInside(SDL_Event* e)
{
    int currentX, currentY ;
    bool inside = true ;

    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        SDL_GetMouseState(&currentX, &currentY) ;

        if(currentX < xPos)
            inside = false ;
        else if(currentX > xPos + buttonWidth)
            inside = false ;
        else if(currentY < yPos)
            inside = false ;
        else if(currentY > yPos + buttonHeight)
            inside = false ;
        return inside ;
    }
    return inside ;
}

 void Button::RenderButton(SDL_Renderer* screen)
 {
     if(status == ONE_SPIRTES)
     {
         BaseObject::Render(xPos, yPos, screen) ;
         return ;
     }
     SDL_Rect* clip = &frameClip[status] ;
     BaseObject::Render(xPos, yPos, screen, clip) ;
 }

 void Button::Free()
 {
     BaseObject::Free() ;
 }
