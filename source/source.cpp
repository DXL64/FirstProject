#include "CommonFunction.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Map.h"
#include "Timer.h"
#include "EnemyObject.h"
#include "Button.h"
#include "FunctionInMain.h"

Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX - 75, HELP_BUTTON_POSY);
Button HighscoreButton(HELP_BUTTON_POSX + 75, HELP_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button EasyButton(EASY_BUTON_POSX, EASY_BUTTON_POSY) ;
Button MediumButton(MEDIUM_BUTTON_POSX, MEDIUM_BUTTON_POSY) ;
Button HardButton(HARD_BUTTON_POSX, HARD_BUTTON_POSY) ;

TTF_Font* gFont = nullptr;
TTF_Font* gNameFont = nullptr ;

Mix_Music* gBackgroundMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClickMusic = nullptr;
Mix_Chunk* gJumpMusic = nullptr;
Mix_Chunk* gLoseMusic = nullptr;


BaseObject gInstruction ;
BaseObject gMenuChar ;
BaseObject gMenu ;
BaseObject gTextScore ;
BaseObject gScore ;
BaseObject gTextHighScore ;
BaseObject gHighScore ;
BaseObject gLose ;
BaseObject gMenuName ;
BaseObject gName ;
BaseObject gMenuHighScore ;

Button DinoBlue(BLUE_DINO_POSX, BLUE_DINO_POSY) ;
Button DinoGreen(GREEN_DINO_POSX, GREEN_DINO_POSY) ;
Button DinoRed(RED_DINO_POSX, RED_DINO_POSY) ;
Button DinoGold(GOLD_DINO_POSX, GOLD_DINO_POSY) ;

Enemy Ground1(ON_GROUND_ENEMY) ;
Enemy Ground2(ON_GROUND_ENEMY) ;
Enemy Air1(IN_AIR_ENEMY) ;
Enemy Air2(IN_AIR_ENEMY) ;

MainObject Dino ;

Map MapData ;

Timer Fps ;

SDL_Color textColor = { 0, 0, 0 } ;

int main(int argv, char** args)
{
    if(!Init())
        return 0 ;

    if(!LoadMedia())
        return 0 ;

    bool PlayAgain = false ;

    int GameOption = EASY_OPTION ;
    int CharOption = GREEN_OPTION ;

    Mix_PlayMusic(gMenuMusic, -1) ;

    HandleMenu(PlayAgain, GameOption) ;

    HandleChoosePlayer(CharOption) ;

    LoadCharacter(CharOption) ;

    string PlayerName = InputText(gEvent, gName, gMenuName, gNameFont, gScreen, gClickMusic) ;

    while(PlayAgain)
    {
        int OffsetSpeedGround = BASE_OFFSET_SPEED ;
        vector <double> offSetSpeedBackGround(BACKGROUND_LAYER, BASE_OFFSET_SPEED);

        bool QuitGame = false ;

        int acceleration = 0 ;
        int timePS = 0 ;
        int frame = 0 ;
        int speed = GROUND_SPEED ;

        int score = 0 ;
        int highScore = GetHighScore() ;

        Ground1.Rebuild(ON_GROUND_ENEMY) ;
        Ground2.Rebuild(ON_GROUND_ENEMY) ;
        Air1.Rebuild(IN_AIR_ENEMY) ;
        Air2.Rebuild(IN_AIR_ENEMY) ;

        srand((int)time(NULL)) ;

        Mix_PlayMusic(gBackgroundMusic, -1) ;
        while(!QuitGame)
        {
            Fps.start() ;

            UpdateScore(score, acceleration, timePS, GameOption) ;

            while(SDL_PollEvent(&gEvent) != 0)
            {
                if(gEvent.type == SDL_QUIT)
                {
                    QuitGame = 1 ;
                    PlayAgain = 0 ;
                }
                HandlePauseButton(&gEvent, PauseButton, ContinueButton, gScreen, gClickMusic) ;
                Dino.HandleButton(gEvent, gScreen, gJumpMusic) ;
            }
            SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR,
                                   RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR) ;
            SDL_RenderClear(gScreen) ;

            MapData.RenderScrollingBackground(offSetSpeedBackGround, gScreen) ;
            MapData.RenderScrollingGround(speed, acceleration, gScreen) ;

            Dino.Show(gScreen) ;

            Ground1.Move(acceleration, 0, 0) ;
            Ground1.RenderEnemy(gScreen) ;

            Air1.Move(acceleration, 0, 0) ;
            Air1.RenderEnemy(gScreen) ;

            if(GameOption == MEDIUM_OPTION || GameOption == HARD_OPTION)
            {
                int xBack = Ground1.GetXBack() ;
                if(Ground2.Move(acceleration, xBack, 1))
                    Ground2.RenderEnemy(gScreen) ;

                if(GameOption == HARD_OPTION)
                {
                    int xBack = Air1.GetXBack() ;
                    if(Air2.Move(acceleration, xBack, 1))
                        Air2.RenderEnemy(gScreen) ;
                }
            }

            DrawPlayScore(gTextScore, gScore, gFont, textColor, score, gScreen) ;
            DrawPlayerHighScore(gTextHighScore, gHighScore, gFont, textColor, highScore, gScreen) ;

            SDL_Rect* currenClip = &PauseButton.frameClip[PauseButton.status] ;
            PauseButton.RenderButton(gScreen) ;


            if(CheckCollision(Dino, Air1) || CheckCollision(Dino, Ground1))
            {
                Mix_PauseMusic();
                Mix_PlayChannel(MIX_CHANNEL, gLoseMusic, 0);
                UpdateHighScore(PlayerName, score, highScore, 1) ;
                QuitGame = 1 ;
            }
            if(GameOption == MEDIUM_OPTION || GameOption == HARD_OPTION)
            {
                if(CheckCollision(Dino, Ground2))
                {
                    Mix_PauseMusic();
                    Mix_PlayChannel(MIX_CHANNEL, gLoseMusic, 0);
                    UpdateHighScore(PlayerName, score, highScore, 1) ;
                    QuitGame = 1 ;
                }
                if(CheckCollision(Dino, Air2))
                {
                    Mix_PauseMusic();
                    Mix_PlayChannel(MIX_CHANNEL, gLoseMusic, 0);
                    UpdateHighScore(PlayerName, score, highScore, 1) ;
                    QuitGame = 1 ;
                }
            }

            SDL_RenderPresent(gScreen) ;

            double realTime = Fps.getTick() ;
            double ms = (double)1000 / FRAME_PER_SECOND ;
            if(realTime < ms)
            {
                double delayTime = ms - realTime ;
                SDL_Delay(delayTime) ;
            }
            UpdateHighScore(PlayerName, score, highScore, 0) ;
        }
        DrawLoseGame(gLose, &gEvent, PlayAgain, gScreen) ;
    }
    Close() ;
    return 0 ;
}

bool Init()
{
    int sdlInit = SDL_Init(SDL_INIT_EVERYTHING) ;

    if(sdlInit < 0)
        return 0 ;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") ;

    gWindow = SDL_CreateWindow(GAME_NAME.c_str(), SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) ;

    if(gWindow == NULL)
        return 0 ;

    gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED) ;

    if(gScreen == NULL)
        return 0 ;

    SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR,
                           RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR) ;

    int imgFlags = IMG_INIT_PNG;

    if(!(IMG_Init(imgFlags) && imgFlags))
        return 0 ;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        return 0 ;

    if (TTF_Init() == -1)
        return 0 ;

    return 1 ;
}

bool LoadMedia()
{
    if(!MapData.LoadImgGround("imgs/background/ground.png", gScreen))
        return 0 ;
    if(!MapData.LoadImgBackGround(gScreen))
        return 0 ;

    if(!Ground1.LoadImg(gScreen))
        return 0 ;
    if(!Ground2.LoadImg(gScreen))
        return 0 ;

    if(Air1.LoadImg(gScreen))
        Air1.SetUpFrame();

    if(Air2.LoadImg(gScreen))
        Air2.SetUpFrame();

    if(!gLose.LoadImg("imgs/background/lose.png", gScreen))
        return 0 ;

    gBackgroundMusic = Mix_LoadMUS("sound/bkgr_audio.wav");
    if(gBackgroundMusic == nullptr)
        return 0 ;

    gMenuMusic = Mix_LoadMUS("sound/menu_audio.wav");
    if (gMenuMusic == nullptr)
        return 0 ;

    gClickMusic = Mix_LoadWAV("sound/mouse_click.wav");
    if(gClickMusic == nullptr)
        return 0 ;

    gJumpMusic = Mix_LoadWAV("sound/jump_sound.wav");
    if(gJumpMusic == nullptr)
        return 0 ;

    gLoseMusic = Mix_LoadWAV("sound/lose_sound.wav");
    if(gLoseMusic == nullptr)
        return 0 ;

    gFont = TTF_OpenFont("font/pixel_font.ttf", SIZE_OF_PIXEL_FONT);
    if(gFont == nullptr)
        return 0 ;

    gNameFont = TTF_OpenFont("font/segoeui.ttf", SIZE_OF_SEGOEUI_FONT);
    if(gFont == nullptr)
        return 0 ;

    if(!EasyButton.LoadButton("imgs/button/easy.png", gScreen))
        return 0 ;
    EasyButton.SetUpFrame() ;

    if(!MediumButton.LoadButton("imgs/button/medium.png", gScreen))
        return 0 ;
    MediumButton.SetUpFrame() ;

    if(!HardButton.LoadButton("imgs/button/hard.png", gScreen))
        return 0 ;
    HardButton.SetUpFrame() ;

    if(!PlayButton.LoadButton("imgs/button/play_button.png", gScreen))
        return 0 ;
    PlayButton.SetUpFrame() ;

    if(!PauseButton.LoadButton("imgs/button/pause_button.png", gScreen))
        return 0 ;
    PauseButton.SetUpFrame() ;

    if(!ContinueButton.LoadButton("imgs/button/continue_button.png", gScreen))
        return 0 ;
    ContinueButton.SetUpFrame() ;

    if(!HelpButton.LoadButton("imgs/button/help_button.png", gScreen))
        return 0 ;
    HelpButton.SetUpFrame() ;

    if(!HighscoreButton.LoadButton("imgs/button/highscore_button.png", gScreen))
        return 0 ;
    HighscoreButton.SetUpFrame() ;

    if(!BackButton.LoadButton("imgs/button/back_button.png", gScreen))
        return 0 ;
    BackButton.SetUpFrame() ;

    if(!ExitButton.LoadButton("imgs/button/exit_button.png", gScreen))
        return 0 ;
    ExitButton.SetUpFrame() ;

    if(!gMenu.LoadImg("imgs/background/menuplus.png", gScreen))
        return 0 ;

    if(!gInstruction.LoadImg("imgs/background/instruction.png", gScreen))
        return 0 ;

    if(!gMenuChar.LoadImg("imgs/background/menuChar.png", gScreen))
        return 0 ;

    if(!gMenuName.LoadImg("imgs/background/menuName.png", gScreen))
        return 0 ;

    if(!gMenuHighScore.LoadImg("imgs/background/highscore.png", gScreen))
        return 0 ;

    if(!gTextScore.LoadText("Your Score: ", gFont, textColor, gScreen))
        return 0 ;

    if(!gTextHighScore.LoadText("High Score: ", gFont, textColor, gScreen))
        return 0 ;

    DinoBlue.status = ONE_SPIRTES ;
    if(!DinoBlue.LoadButton("imgs/character/Blue.png", gScreen))
        return 0 ;

    DinoRed.status = ONE_SPIRTES ;
    if(!DinoRed.LoadButton("imgs/character/Red.png", gScreen))
        return 0 ;

    DinoGreen.status = ONE_SPIRTES ;
    if(!DinoGreen.LoadButton("imgs/character/Green.png", gScreen))
        return 0 ;

    DinoGold.status = ONE_SPIRTES ;
    if(!DinoGold.LoadButton("imgs/character/Gold.png", gScreen))
        return 0 ;

    return 1 ;
}

void HandleMenu(bool& PlayAgain, int& GameOption)
{
    bool QuitMenu = false ;
    bool QuitGame = false ;
    while(!QuitMenu)
    {
        while(SDL_PollEvent(&gEvent) != 0)
        {
            if(gEvent.type == SDL_QUIT)
            {
                QuitGame = true ;
            }

            HandlePlayButton(&gEvent, gMenu, PlayButton, EasyButton, MediumButton, HardButton, GameOption, QuitMenu, PlayAgain, gScreen, gClickMusic) ;
            if(QuitMenu)
                break ;

            HandleHelpButton(&gEvent, HelpButton, BackButton, QuitGame, gInstruction, gScreen, gClickMusic) ;

            HandleHighScoreButton(&gEvent, HighscoreButton, BackButton, QuitGame, gMenuHighScore, gScreen, gClickMusic, gFont) ;

            HandleExitButton(&gEvent, ExitButton, QuitGame, gClickMusic) ;

        }
        if(QuitGame)
            exit(0) ;
        if(QuitMenu)
            break ;
        gMenu.Render(gScreen) ;

        PlayButton.RenderButton(gScreen) ;

        HelpButton.RenderButton(gScreen) ;

        HighscoreButton.RenderButton(gScreen) ;

        ExitButton.RenderButton(gScreen) ;

        SDL_RenderPresent(gScreen) ;
    }
}

void HandleChoosePlayer(int& CharOption)
{
    bool choosePlayer = true ;

    while(choosePlayer)
    {
        while(SDL_PollEvent(&gEvent) != 0)
        {
            gMenuChar.Render(gScreen) ;
            if(gEvent.type == SDL_QUIT)
                exit(0) ;

            if(DinoBlue.isInside(&gEvent))
            {
                if(gEvent.type == SDL_MOUSEMOTION)
                    DinoBlue.RenderButton(gScreen) ;
                if(gEvent.type == SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0) ;
                    DinoBlue.RenderButton(gScreen)  ;
                    CharOption = BLUE_OPTION ;
                    choosePlayer = false ;
                }
            }

            if(DinoRed.isInside(&gEvent))
            {
                if(gEvent.type == SDL_MOUSEMOTION)
                    DinoRed.RenderButton(gScreen) ;
                if(gEvent.type == SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0) ;
                    DinoRed.RenderButton(gScreen)  ;
                    CharOption = RED_OPTION ;
                    choosePlayer = false ;
                }
            }

            if(DinoGreen.isInside(&gEvent))
            {
                if(gEvent.type == SDL_MOUSEMOTION)
                    DinoGreen.RenderButton(gScreen) ;
                if(gEvent.type == SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0) ;
                    DinoGreen.RenderButton(gScreen)  ;
                    CharOption = GREEN_OPTION ;
                    choosePlayer = false ;
                }
            }

            if(DinoGold.isInside(&gEvent))
            {
                if(gEvent.type == SDL_MOUSEMOTION)
                    DinoGold.RenderButton(gScreen) ;
                if(gEvent.type == SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel(MIX_CHANNEL, gClickMusic, 0) ;
                    DinoGold.RenderButton(gScreen)  ;
                    CharOption = GOLD_OPTION ;
                    choosePlayer = false ;
                }
            }

            SDL_RenderPresent(gScreen) ;
        }
    }
}

void LoadCharacter(int CharOption)
{
    if(CharOption == BLUE_OPTION)
    {
        if(Dino.LoadImg("imgs/character/DinoBlue.png", gScreen))
            Dino.SetUpFrame() ;
    }
    if(CharOption == GREEN_OPTION)
    {
        if(Dino.LoadImg("imgs/character/DinoGreen.png", gScreen))
            Dino.SetUpFrame() ;
    }
    if(CharOption == RED_OPTION)
    {
        if(Dino.LoadImg("imgs/character/DinoRed.png", gScreen))
            Dino.SetUpFrame() ;
    }
    if(CharOption == GOLD_OPTION)
    {
        if(Dino.LoadImg("imgs/character/DinoGold.png", gScreen))
            Dino.SetUpFrame() ;
    }
}

void Close()
{
    TTF_CloseFont(gFont) ;
    TTF_CloseFont(gNameFont) ;

    PlayButton.Free() ;
    PauseButton.Free() ;
    ContinueButton.Free() ;
    HelpButton.Free() ;
    HighscoreButton.Free() ;
    BackButton.Free() ;
    ExitButton.Free() ;
    EasyButton.Free() ;
    MediumButton.Free() ;
    HardButton.Free() ;

    DinoBlue.Free() ;
    DinoGreen.Free() ;
    DinoRed.Free() ;
    DinoGold.Free() ;

    gInstruction.Free() ;
    gMenuChar.Free() ;
    gMenu.Free() ;
    gTextScore.Free() ;
    gScore.Free() ;
    gTextHighScore.Free() ;
    gHighScore.Free() ;
    gLose.Free() ;
    gMenuName.Free() ;
    gName.Free() ;
    gMenuHighScore.Free() ;

    Ground1.Free() ;
    Ground2.Free() ;
    Air1.Free() ;
    Air2.Free() ;

    Dino.Free() ;

    MapData.Free() ;

    Mix_FreeMusic(gBackgroundMusic) ;
    gBackgroundMusic = NULL ;

    Mix_FreeMusic(gMenuMusic) ;
    gMenuMusic = NULL ;

    Mix_FreeChunk(gClickMusic) ;
    gClickMusic = NULL ;

    Mix_FreeChunk(gJumpMusic) ;
    gJumpMusic = NULL ;

    Mix_FreeChunk(gLoseMusic) ;
    gLoseMusic = NULL ;

    SDL_DestroyRenderer(gScreen) ;
    gScreen = NULL ;

    SDL_DestroyWindow(gWindow) ;
    gWindow = NULL ;

    TTF_Quit() ;
    IMG_Quit() ;
    SDL_Quit() ;
}
