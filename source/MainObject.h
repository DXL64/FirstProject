#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"

class MainObject : BaseObject
{
    public:
        MainObject()  ;

        ~MainObject() {;};

    bool LoadImg(string file_path, SDL_Renderer* screen) ;

    void SetUpFrame() ;

    void HandleButton(SDL_Event event, SDL_Renderer* screen, Mix_Chunk *gJumpMusic) ;

    void Show(SDL_Renderer* des) ;

    void Move() ;

    void ControlFrame() ;

    bool isOnGround(){return (yPos == GROUND);}

    int GetXPos() {return xPos;} ;

    int GetYPos(){return yPos;} ;

    int GetWidth_(){return widthFrame;} ;

    int GetHeight_(){return heightFrame;} ;

    int GetStatus(){return status;} ;

    void Free() ;

    private:
        double xPos, yPos ;

        int widthFrame, heightFrame ;

        SDL_Rect frameClip[BACKGROUND_LAYER] ;

        int frame, status ;
};

#endif // main_object_
