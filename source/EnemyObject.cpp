#include "EnemyObject.h"

Enemy::Enemy(int type_)
{
    eWidth = eHeight = 0 ;

    type = type_ ;
    if(type == IN_AIR_ENEMY)
    {
        frame = 0 ;
        xPos = rand() % (SCREEN_WIDTH + ENEMY_RANGE) + SCREEN_WIDTH     ;
        yPos = rand() % (MAX_HEIGHT - MIN_HEIGHT + 1) + MIN_HEIGHT ;
    }
    else if(type == ON_GROUND_ENEMY)
    {
        xPos = rand() % (SCREEN_WIDTH + ENEMY_RANGE) + SCREEN_WIDTH  ;
        yPos = GROUND - GRASS_HEIGHT;
    }
}
void Enemy::Rebuild(int type_)
{

    type = type_ ;
    if(type == IN_AIR_ENEMY)
    {
        frame = 0 ;
        xPos = rand() % (SCREEN_WIDTH + ENEMY_RANGE) + SCREEN_WIDTH     ;
        yPos = rand() % (MAX_HEIGHT - MIN_HEIGHT + 1) + MIN_HEIGHT ;
    }
    else if(type == ON_GROUND_ENEMY)
    {
        xPos = rand() % (SCREEN_WIDTH + ENEMY_RANGE) + SCREEN_WIDTH  ;
        yPos = GROUND - GRASS_HEIGHT;
    }
}
bool Enemy::LoadImg(SDL_Renderer* screen)
{
    bool success = 0;
    if(type == IN_AIR_ENEMY)
    {
        success = BaseObject::LoadImg("imgs/enemy/bat.png", screen) ;
        success = inAirEnemy.LoadImg("imgs/enemy/bat.png", screen) ;
        eWidth = bRect.w / ENEMY_SPRITES;
        eHeight = bRect.h ;
    }
    else if(type == ON_GROUND_ENEMY)
    {
        success = BaseObject::LoadImg("imgs/enemy/cactus.png", screen) ;
        success = onGroundEnemy.LoadImg("imgs/enemy/cactus.png", screen) ;
        eWidth = bRect.w ;
        eHeight = bRect.h ;
    }
    return success ;
}
bool Enemy::Move(int &acceleration,int xBack,int gType)
{
    xPos = xPos - (ENEMY_SPEED + acceleration) ;
    if(xPos + eWidth <= 0)
    {
        xPos = rand() % (SCREEN_WIDTH + ENEMY_RANGE) + SCREEN_WIDTH;
        xBack_ = xPos ;
        if(type == IN_AIR_ENEMY)
            yPos = rand() % (MAX_HEIGHT - MIN_HEIGHT + 1) + MIN_HEIGHT ;
        if(gType == 1)
        {
            double dis = abs(xPos - xBack) ;
            if(dis < (double)SCREEN_WIDTH / 2 && dis > (double)SCREEN_WIDTH/8)
                return 0;
            return 1;
        }
    }
    return 1 ;
}
void Enemy::SetUpFrame()
{
    frameClip[0].w = eWidth ;
    frameClip[0].h = eHeight ;
    For(i, 1, ENEMY_SPRITES)
    {
        frameClip[i].x = frameClip[i-1].x + eWidth ;
        frameClip[i].y = 0 ;
        frameClip[i].w = eWidth ;
        frameClip[i].h = eHeight ;
    }
}

void Enemy::RenderEnemy(SDL_Renderer* screen)
{
    if(type == IN_AIR_ENEMY)
    {
        frame++ ;
        if(frame > ENEMY_SPRITES)
            frame = 0 ;

        SDL_Rect* currentClip = &frameClip[frame] ;
        SDL_Rect renderQuad = {xPos,yPos , eWidth, eHeight} ;
        SDL_RenderCopy(screen, bTexture, currentClip, &renderQuad) ;
    }
    else
    {
        onGroundEnemy.SetRect(xPos, yPos) ;
        onGroundEnemy.Render(screen);
    }
}
void Enemy::Free()
{
    BaseObject::Free() ;

    if(type == IN_AIR_ENEMY)
        inAirEnemy.Free() ;
    else
        onGroundEnemy.Free() ;
}
