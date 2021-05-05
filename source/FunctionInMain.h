#ifndef FUNCTION_IN_MAIN_H_
#define FUNCTION_IN_MAIN_H_

#include "CommonFunction.h"
#include "MainObject.h"
#include "EnemyObject.h"
#include "Button.h"


bool Init() ;

bool LoadBackGround() ;

bool LoadMedia() ;

void Close() ;

bool CheckCollision(MainObject& Dino, Enemy& Enem) ;

void HandlePlayButton(SDL_Event* e, BaseObject& gMenu,
            Button& PlayButton, Button& EasyButton,
            Button& MediumButton, Button& HardButton,
            int& GameOption, bool& QuitMenu,
            bool& PlayGame, SDL_Renderer* screen,
            Mix_Chunk *gClickMusic) ;

void HandleHelpButton(SDL_Event* e,
            Button& HelpButton, Button& BackButton,
            bool& QuitGame, BaseObject& gInstruction,
            SDL_Renderer* screen, Mix_Chunk *gClick) ;

void HandleExitButton(SDL_Event* e, Button& ExitButton,
            bool& QuitGame, Mix_Chunk* gClickMusic);

void HandlePauseButton(SDL_Event* e,
            Button& PauseButton, Button& ContinueButton,
            bool& GameState,
            SDL_Renderer* screen, Mix_Chunk *gClickMusic) ;

void DrawPlayScore(BaseObject& gTextScore, BaseObject& gScore,
                         TTF_Font* gFont, SDL_Color textColor,
                         int &score, SDL_Renderer* screen) ;

void DrawPlayerHighScore(BaseObject& gTextHighScore, BaseObject& gHighScore,
                         TTF_Font* gFont, SDL_Color textColor,
                         int &highscore, SDL_Renderer* screen) ;

int GetHighScore() ;

void UpdateHighScore(int& score, int &oldHighScore) ;

void UpdateScore(int &score, int &acceleration, int &time, int GameOption) ;

void DrawLoseGame(BaseObject &gLose, SDL_Event* e, bool &PlayAgain, SDL_Renderer* screen) ;

#endif // FUNCTION_IN_MAIN_H_
