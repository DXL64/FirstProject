#ifndef MAP_H_
#define MAP_H_

#include "CommonFunction.h"
#include "BaseObject.h"

class Map
{
    public:
        Map() {;} ;

        ~Map(){;} ;

    bool LoadImgBackGround(SDL_Renderer* screen) ;

    bool LoadImgGround(string file_path, SDL_Renderer* screen) ;

    void RenderScrollingBackground(vector <double> &offSetSpeed, SDL_Renderer* screen) ;

    void RenderScrollingGround(int &speed, int& acceleration, SDL_Renderer* screen) ;

    void Free() ;

    private:
        BaseObject backGround[BACKGROUND_LAYER] ;

        BaseObject Ground ;

};
#endif // map_h_
