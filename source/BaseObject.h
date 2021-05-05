#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunction.h"

class BaseObject
{
    public:
        BaseObject() ;

        ~BaseObject() ;

        void SetRect(int x, int y) {bRect.x = x, bRect.y = y;} ;

        SDL_Rect GetRect() const {return bRect;} ;

        SDL_Texture* GetTexture() const {return bTexture;} ;

        bool LoadImg(string file_path, SDL_Renderer* screen) ;

        bool LoadText(string Text,TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *screen) ;

        void Render(SDL_Renderer* des, SDL_Rect* clip = nullptr) ;

        void Render(int x, int y, SDL_Renderer* des, SDL_Rect* clip = nullptr) ;

        void  Free() ;

        int GetWidth(){return bRect.w ;} ;

        int GetHeight(){return bRect.h ;} ;
     protected:

        SDL_Texture* bTexture ;

        SDL_Rect bRect, tRect;

};

#endif // BASE_OBJECT_H
