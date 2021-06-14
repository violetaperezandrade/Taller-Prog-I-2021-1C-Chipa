#ifndef LOGIN_H
#define LOGIN_H
#define FONTSIZE 24
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../common/Logger.h"
#include "../common/Socket.h"

#define SCREEN_WIDTH_LOGIN 640
#define SCREEN_HEIGHT_LOGIN 480

struct TextRendered{
    SDL_Texture* texture;
    int width;
    int height;
};

class Login {
private:
    SDL_Renderer* windowRendererLogin;
    SDL_Window* windowLogin;
    TTF_Font* globalFont;
    bool initSDL();
    void closeSDL();
    Logger& logger;
    Socket& sktLogin;
public:
    void renderLogin(int x, int y, int width, int height, SDL_Texture* texture, SDL_Renderer* windowRenderer);
    TTF_Font* createFont(std::string path);
    TextRendered loadFromRenderedText(std::string textureText,
                                      SDL_Color textColor,
                                      SDL_Renderer* renderer, TTF_Font* font);
    bool mouseWasClickedOnPosition(int x1, int x2, int y1, int y2, SDL_Event* e);
    int runLoginWindow(char* ip, char* port);
    Login(Logger& logger,Socket& skt);
    ~Login();
};

#endif //LOGIN_H