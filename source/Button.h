#ifndef BUTTON_H_
#define BUTTON_H_

#include "CommonFunction.h"
#include "BaseObject.h"

class Button:BaseObject
{
    public:
        Button(int x, int y) ;

        ~Button(){;} ;

        void SetXY(int x, int y) ;

        void SetUpFrame() ;

        bool LoadButton(string file_path, SDL_Renderer* screen) ;

        void RenderButton(SDL_Renderer* screen) ;

        void Free() ;

        bool isInside(SDL_Event* e) ;

        int status ;
        SDL_Rect frameClip[BUTTON_SPRITES] ;

    private:

        int xPos, yPos ;

        int buttonWidth, buttonHeight ;


};
#endif // BUTTON_H_
