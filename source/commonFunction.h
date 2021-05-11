
#ifndef CommonFunction_H_
#define CommonFunction_H_

#include <bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


using namespace std ;

#define ll long long
#define pb push_back
#define For(i,a,b) for(int i = a; i < b; i++)
#define Ford(i,a,b) for(int i = a; i > b; i--)

static SDL_Window* gWindow  ;
static SDL_Renderer* gScreen  ;
static SDL_Event gEvent ;

const int FRAME_PER_SECOND = 30 ;

const int SCREEN_WIDTH = 928;
const int SCREEN_HEIGHT = 522;
const int GROUND = 430 ;
const int SCREEN_BPP = 64 ;

const int COLOR_KEY_R = 167 ;
const int COLOR_KEY_G = 175 ;
const int COLOR_KEY_B = 180 ;
const int RENDER_DRAW_COLOR = 255 ;

const int BACKGROUND_LAYER = 9 ;
const int CHARACTER_SPRITES = 6 ;
const int ENEMY_SPRITES = 5 ;
const int JUMP = 64 ;
const int FALL = 204 ;
const int MAX_JUMP = 240 ;

const int BASE_OFFSET_SPEED = 0 ;
const int JUMP_POW = 18 ;
const int GRAVITY_FALL = 19.8 ;
const double GROUND_SPEED = 8.64 ;
const int MAX_ACCELERATION = 9 ;

const double LAYER_1_SPEED = 0   ;
const double LAYER_2_SPEED = 0.25;
const double LAYER_3_SPEED = 0.5 ;
const double LAYER_4_SPEED = 0.75;
const double LAYER_5_SPEED = 1.0 ;
const double LAYER_6_SPEED = 1.25;
const double LAYER_7_SPEED = 1.5 ;
const double LAYER_8_SPEED = 1.75 ;
const double LAYER_9_SPEED = 2.0 ;

const int ENEMY_SPEED = 8.64 ;
const int IN_AIR_ENEMY = 1 ;
const int ON_GROUND_ENEMY = 2 ;
const int ENEMY_RANGE = 240 ;
const int MIN_HEIGHT = 360 ;
const int MAX_HEIGHT = 330 ;
const int GRASS_HEIGHT = 8 ;

const int MIX_CHANNEL = -1 ;

const int BUTTON_SPRITES = 2 ;
const int BUTTON_MOUSE_DOWN = 0 ;
const int BUTTON_MOUSE_UP = 1 ;
const int ONE_SPIRTES = 3 ;
const int SMALL_BUTTON = 1 ;
const int COMMON_BUTTON = 2 ;

const int SIZE_OF_PIXEL_FONT = 28;
const int SIZE_OF_SEGOEUI_FONT = 55;
const int NUMBER_RANK = 7 ;

const int PLAY_BUTON_POSX = 390;
const int PLAY_BUTTON_POSY= 180;
const int HELP_BUTTON_POSX = 390;
const int HELP_BUTTON_POSY = 290;
const int EXIT_BUTTON_POSX = 390;
const int EXIT_BUTTON_POSY = 400;
const int BACK_BUTTON_POSX = 15;
const int BACK_BUTTON_POSY = 15;
const int PAUSE_BUTTON_POSX = 30;
const int PAUSE_BUTTON_POSY = 30;
const int CONTINUE_BUTTON_POSX = 30;
const int CONTINUE_BUTTON_POSY = 30;

const int EASY_BUTON_POSX = 389;
const int EASY_BUTTON_POSY= 180;
const int MEDIUM_BUTTON_POSX = 389;
const int MEDIUM_BUTTON_POSY = 290;
const int HARD_BUTTON_POSX = 389;
const int HARD_BUTTON_POSY = 400;

const int GREEN_DINO_POSX = 145 ;
const int GREEN_DINO_POSY = 312 ;
const int BLUE_DINO_POSX = 318 ;
const int BLUE_DINO_POSY = 312 ;
const int GOLD_DINO_POSX = 486 ;
const int GOLD_DINO_POSY = 312 ;
const int RED_DINO_POSX = 655 ;
const int RED_DINO_POSY = 312 ;

const int EASY_OPTION = 1 ;
const int MEDIUM_OPTION = 2 ;
const int HARD_OPTION = 3 ;

const int BLUE_OPTION = 1 ;
const int RED_OPTION = 2 ;
const int GOLD_OPTION = 3 ;
const int GREEN_OPTION = 4 ;

const int TEXT_SCORE_X = 670;
const int TEXT_SCORE_Y = 20;
const int TEXT_HIGH_SCORE_X = 670;
const int TEXT_HIGH_SCORE_Y = 80;
const int SCORE_X = 830;
const int SCORE_Y = 20;
const int HIGH_SCORE_X = 830;
const int HIGH_SCORE_Y = 80;

const string GAME_NAME = "Dino In Jungle" ;
const string Layer[BACKGROUND_LAYER] = {
	"imgs/background/layer01.png",
	"imgs/background/layer02.png",
	"imgs/background/layer03.png",
	"imgs/background/layer04.png",
	"imgs/background/layer05.png",
	"imgs/background/layer06.png",
	"imgs/background/layer07.png",
	"imgs/background/layer08.png",
	"imgs/background/layer09.png",
};

#endif // commonFunction_H_
