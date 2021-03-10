#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "commonFunction.h"

class BaseObject
{
    public:
        BaseObject() ;
        ~BaseObject() ;
        void SetRect(const int& x, const int& y) {bRect.x = x, bRect.y = y;} ;
        SDL_Rect GetRect() const {return bRect;} ;
        SDL_Texture* GetTexture() const {return bTexture;} ;
        bool LoadImg(string file_path, SDL_Renderer* screen) ;
        void Render(SDL_Renderer* des, const SDL_Rect* clip ) ;
        void  Free() ;
     protected:
        SDL_Texture* bTexture ;
        SDL_Rect bRect;

};

#endif // BASE_OBJECT_H
