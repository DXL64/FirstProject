#include "Map.h"

bool Map::LoadImgBackGround(SDL_Renderer* screen)
{
    bool success = 1 ;
    For(i, 0, BACKGROUND_LAYER)
    {
        success = backGround[i].LoadImg(Layer[i].c_str(), screen) ;
        if(!success)
            return success ;
    }
    return success ;
}
bool Map::LoadImgGround(string file_path, SDL_Renderer* screen)
{
    bool success = 1 ;
    success = Ground.LoadImg(file_path, screen) ;
    return success ;
}
void Map::RenderScrollingBackground(vector <double> &offSetSpeed, SDL_Renderer* screen)
{
    vector<double> layerSpeed ;

    layerSpeed.pb(LAYER_1_SPEED) ;
    layerSpeed.pb(LAYER_2_SPEED) ;
    layerSpeed.pb(LAYER_3_SPEED) ;
    layerSpeed.pb(LAYER_4_SPEED) ;
    layerSpeed.pb(LAYER_5_SPEED) ;
    layerSpeed.pb(LAYER_6_SPEED) ;
    layerSpeed.pb(LAYER_7_SPEED) ;
    layerSpeed.pb(LAYER_8_SPEED) ;
    layerSpeed.pb(LAYER_9_SPEED) ;
    For(i, 0, BACKGROUND_LAYER)
    {
        offSetSpeed[i] = offSetSpeed[i] - layerSpeed[i] ;
        if(offSetSpeed[i] < -backGround[i].GetWidth())
            offSetSpeed[i] = 0 ;
        backGround[i].Render(offSetSpeed[i], 0, screen) ;
        backGround[i].Render(offSetSpeed[i] + backGround[i].GetWidth(), 0, screen) ;
    }
}
void Map::RenderScrollingGround(int &speed, int& acceleration, SDL_Renderer* screen)
{
    speed = speed - (GROUND_SPEED + acceleration) ;
    if(speed < - Ground.GetWidth())
        speed = 0 ;

    Ground.Render(speed, 0, screen) ;
    Ground.Render(speed + Ground.GetWidth(), 0, screen) ;
    return ;
}

void Map::Free()
{
    Ground.Free() ;
    For(i, 0, BACKGROUND_LAYER)
        backGround[i].Free() ;
}
