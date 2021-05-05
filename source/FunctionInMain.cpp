#include "FunctionInMain.h"

bool CheckCollision(MainObject& Dino, Enemy& Enem)
{
    bool check = false ;
    SDL_Rect DinoChar = {Dino.GetXPos() + 15, Dino.GetYPos() + 15, Dino.GetWidth_() - 25, Dino.GetHeight_() - 35} ;
    SDL_Rect Enemy = {Enem.GetXPos() + 10, Enem.GetYPos() + 10 , Enem.GetWidth_() - 15 , Enem.GetHeight_() - 15} ;
    check = SDL_HasIntersection(&DinoChar, &Enemy) ;
    return check ;
}

void HandlePlayButton(SDL_Event* e, BaseObject& gMenu,
            Button& PlayButton, Button& EasyButton,
            Button& MediumButton, Button& HardButton,
            int& GameOption, bool& QuitMenu,
            bool& PlayGame, SDL_Renderer* screen,
            Mix_Chunk *gClickMusic)
{

    if(PlayButton.isInside(e))
    {
        if(e->type == SDL_MOUSEMOTION)
        {
            PlayButton.status = BUTTON_MOUSE_DOWN ;
        }
        else if(e->type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0) ;
            PlayButton.status = BUTTON_MOUSE_DOWN ;

            bool QuitOption = false ;
            while(!QuitOption)
            {
                while(SDL_PollEvent(e) != 0)
                {
                    if(e->type == SDL_QUIT)
                    {
                        exit(0) ;
                    }
                    if(EasyButton.isInside(e))
                    {
                        if(e->type == SDL_MOUSEMOTION)
                        {
                            EasyButton.status = BUTTON_MOUSE_DOWN ;
                        }
                        else if(e->type == SDL_MOUSEBUTTONDOWN)
                        {
                            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0) ;
                            EasyButton.status = BUTTON_MOUSE_DOWN ;
                            QuitOption  = true ;
                            QuitMenu = true ;
                            GameOption = EASY_OPTION ;
                        }
                    }
                    else
                        EasyButton.status = BUTTON_MOUSE_UP ;

                    if(MediumButton.isInside(e))
                    {
                        if(e->type == SDL_MOUSEMOTION)
                        {
                            MediumButton.status = BUTTON_MOUSE_DOWN ;
                        }
                        else if(e->type == SDL_MOUSEBUTTONDOWN)
                        {
                            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0) ;
                            MediumButton.status = BUTTON_MOUSE_DOWN ;
                            QuitOption  = true ;
                            QuitMenu = true ;
                            GameOption = MEDIUM_OPTION ;
                        }
                    }
                    else
                        MediumButton.status = BUTTON_MOUSE_UP ;

                    if(HardButton.isInside(e))
                    {
                        if(e->type == SDL_MOUSEMOTION)
                        {
                            HardButton.status = BUTTON_MOUSE_DOWN ;
                        }
                        else if(e->type == SDL_MOUSEBUTTONDOWN)
                        {
                            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0) ;
                            HardButton.status = BUTTON_MOUSE_DOWN ;
                            QuitOption  = true ;
                            QuitMenu = true ;
                            GameOption = HARD_OPTION ;
                        }
                    }
                    else
                        HardButton.status = BUTTON_MOUSE_UP ;

                    gMenu.Render(0, 0, screen) ;

                    EasyButton.RenderButton(screen) ;

                    MediumButton.RenderButton(screen) ;

                    HardButton.RenderButton(screen) ;

                    SDL_RenderPresent(screen) ;
                }
            }
            PlayGame = true ;
        }
    }
    else
        PlayButton.status = BUTTON_MOUSE_UP ;
}

void HandleHelpButton(SDL_Event* e,
            Button& HelpButton, Button& BackButton,
            bool& QuitGame, BaseObject& gInstruction,
            SDL_Renderer* screen, Mix_Chunk *gClickMusic)
{

    if(HelpButton.isInside(e))
    {
        if(e->type == SDL_MOUSEMOTION)
        {
            HelpButton.status = BUTTON_MOUSE_DOWN ;
        }
        else if(e->type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0) ;
            HelpButton.status = BUTTON_MOUSE_DOWN ;

            bool backMenu = false ;
            while(!backMenu)
            {
                while(SDL_PollEvent(e) != 0)
                {
                    if(e->type == SDL_QUIT)
                    {
                        backMenu = true ;
                        QuitGame = true ;
                    }
                    else if(BackButton.isInside(e))
                    {
                        if(e->type == SDL_MOUSEMOTION)
                        {
                            BackButton.status = BUTTON_MOUSE_DOWN ;
                        }
                        else if(e->type == SDL_MOUSEBUTTONDOWN)
                        {
                            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0) ;
                            BackButton.status = BUTTON_MOUSE_DOWN ;
                            backMenu  = true ;
                        }
                    }
                    else
                    {
                        BackButton.status = BUTTON_MOUSE_UP ;
                    }
                    gInstruction.Render(0, 0, screen) ;

                    BackButton.RenderButton(screen) ;

                    SDL_RenderPresent(screen) ;

                }
            }
        }
    }
    else
    {
        HelpButton.status = BUTTON_MOUSE_UP ;
    }
}

void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& QuitGame, Mix_Chunk* gClickMusic)
{
    if(ExitButton.isInside(e))
    {
        if(e->type == SDL_MOUSEMOTION)
        {
            ExitButton.status = BUTTON_MOUSE_DOWN ;
        }
        else if(e->type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0) ;
            ExitButton.status = BUTTON_MOUSE_DOWN ;
            QuitGame  = true ;
        }
    }
    else
        ExitButton.status = BUTTON_MOUSE_UP ;
}

void HandlePauseButton(SDL_Event* e,
            Button& PauseButton, Button& ContinueButton,
            bool& GameState,
            SDL_Renderer* screen, Mix_Chunk *gClickMusic)
{
    if(PauseButton.isInside(e))
    {
        if(e->type == SDL_MOUSEMOTION)
            PauseButton.status = BUTTON_MOUSE_DOWN ;
        else if(e->type == SDL_MOUSEBUTTONDOWN)
        {
            PauseButton.status = BUTTON_MOUSE_DOWN ;
            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0) ;
            Mix_PauseMusic() ;
            GameState = false ;
            bool continueGame = false ;
            while(!continueGame)
            {
                while(SDL_PollEvent(e) != 0)
                {
                    if(e->type == SDL_QUIT)
                        exit(0) ;
                    if(ContinueButton.isInside(e))
                    {
                        if(e->type == SDL_MOUSEMOTION)
                            ContinueButton.status = BUTTON_MOUSE_DOWN ;
                        if(e->type == SDL_MOUSEBUTTONDOWN)
                        {
                            Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0) ;
                            Mix_ResumeMusic() ;
                            ContinueButton.status = BUTTON_MOUSE_DOWN ;
                            GameState = true ;
                            continueGame  = true ;
                        }
                    }
                    else
                        ContinueButton.status = BUTTON_MOUSE_UP ;

                    ContinueButton.RenderButton(screen) ;
                    SDL_RenderPresent(screen) ;
                }
            }
        }
    }
    else
        PauseButton.status = BUTTON_MOUSE_UP ;
}

void DrawPlayScore(BaseObject& gTextScore, BaseObject& gScore,
                         TTF_Font* gFont, SDL_Color textColor,
                         int &score, SDL_Renderer* screen)
{
    gTextScore.Render(TEXT_SCORE_X, TEXT_SCORE_Y, screen) ;
    if(gScore.LoadText(to_string(score), gFont, textColor, screen))
        gScore.Render(SCORE_X, SCORE_Y, screen) ;
}

void DrawPlayerHighScore(BaseObject& gTextHighScore, BaseObject& gHighScore,
                         TTF_Font* gFont, SDL_Color textColor,
                         int &highScore, SDL_Renderer* screen)
{
    gTextHighScore.Render(TEXT_HIGH_SCORE_X, TEXT_HIGH_SCORE_Y, screen) ;
    if(gHighScore.LoadText(to_string(highScore), gFont, textColor, screen))
        gHighScore.Render(HIGH_SCORE_X, HIGH_SCORE_Y, screen) ;
}

int GetHighScore()
{
    ifstream ip("highscore.txt", ifstream::in) ;

    int HighScore ;
    ip >> HighScore ;

    ip.close() ;

    return HighScore ;
}

void UpdateHighScore(int &score, int& oldHighScore)
{
    ofstream op ("highscore.txt", ofstream::out);

    if(score >= oldHighScore)
    {
        oldHighScore = score ;
        op << score ;
    }
    else op << oldHighScore ;

    op.close();
}

void UpdateScore(int &score, int &acceleration, int &time, int GameOption)
{
    if(time == 8 * FRAME_PER_SECOND)
        acceleration += GameOption ;
    else if(time > 8 * FRAME_PER_SECOND) time = 0 ;
    if(time % 4 == 0)
        score += GameOption ;
    time++ ;
    if(acceleration >= MAX_ACCELERATION)
        acceleration = 0 ;
}

void DrawLoseGame(BaseObject &gLose, SDL_Event* e, bool &PlayAgain, SDL_Renderer* screen)
{
        bool EndGame = false ;

        if(!PlayAgain) return ;
        while(!EndGame)
        {
            while(SDL_PollEvent(e) != 0)
            {
                if (e->type == SDL_QUIT)
					exit(0) ;
				if (e->type == SDL_KEYDOWN)
				{
					switch (e->key.keysym.sym)
					{
                        case SDLK_SPACE:
                            EndGame = true;
                            break;
                        case SDLK_ESCAPE:
                            EndGame = true;
                            PlayAgain = false;
                            break;
					}
				}
            }
            gLose.Render(screen) ;

            SDL_RenderPresent(screen) ;
        }
}
