
#ifndef commonFunction_H_
#define commonFunction_H_

#include <bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>

using namespace std ;

static SDL_Window* gWindow  ;
static SDL_Renderer* gScreen  ;
static SDL_Event e ;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32 ;

const int COLOR_KEY_R = 167 ;
const int COLOR_KEY_G = 175 ;
const int COLOR_KEY_B = 180 ;

const int RENDER_DRAW_COLOR = 255 ;
#endif // commonFunction_H_
