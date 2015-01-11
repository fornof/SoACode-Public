#pragma once

#ifndef App_h_
#define App_h_

#include <Vorb/MainGame.h>

class DevScreen;
class InitScreen;
class LoadScreen;
class MainMenuScreen;
class GamePlayScreen;
class TexturePackLoader;

class App : public MainGame {
public:
    virtual ~App();

    virtual void addScreens();
    virtual void onInit();
    virtual void onExit();

    // Accessible Pointers To Screens
    InitScreen* scrInit = nullptr;
    LoadScreen* scrLoad = nullptr;
    MainMenuScreen* scrMainMenu = nullptr;
    GamePlayScreen* scrGamePlay = nullptr;

    DevScreen* scrDev = nullptr;
    std::vector<IGameScreen*> scrTests;
};

#endif // App_h_