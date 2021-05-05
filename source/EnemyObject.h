#ifndef ENEMY_OBJECT_H_
#define ENEMY_OBJECT_H_

#include "CommonFunction.h" ;
#include "BaseObject.h"

class Enemy:BaseObject
{
    public:
        Enemy(int type = 0) ;

        ~Enemy(){;} ;

        void Rebuild(int type_) ;

        bool LoadImg(SDL_Renderer* screen) ;

        bool Move(int& acceleration,int xBack, int gType) ;

        void RenderEnemy(SDL_Renderer* screen) ;

        void SetUpFrame() ;

        int GetXPos(){return xPos;} ;

        int GetYPos(){return yPos;} ;

        int GetWidth_(){return eWidth;} ;

        int GetHeight_(){return eHeight;} ;

        int GetXBack(){return xBack_;} ;

        int GetType(){return type ;} ;

        void Free() ;

    private:
        int xPos, yPos, xBack_ ;

        int eWidth, eHeight ;

        int type, frame ;

        SDL_Rect frameClip[ENEMY_SPRITES] ;

        BaseObject inAirEnemy, onGroundEnemy ;

};

#endif // ENEMY_OBJECT_H_
