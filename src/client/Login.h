#ifndef LOGIN_H
#define LOGIN_H
#define FONTSIZE 24
#include "SDLManager.h"
#include "../common/Logger.h"
#include "../common/Socket.h"
#include <vector>

#define SCREEN_WIDTH_LOGIN 640
#define SCREEN_HEIGHT_LOGIN 480

class Login {
private:
    SDL_Renderer* windowRendererLogin;
    SDL_Window* windowLogin;
    TTF_Font* globalFont;
    SDLManager& sdlMngr;
    Logger& logger;
    Socket& sktLogin;
public:
    int runLoginWindow(char* ip, char* port);
    Login(Logger& logger,Socket& skt,SDLManager& mngr);
    ~Login();
};

#endif //LOGIN_H
