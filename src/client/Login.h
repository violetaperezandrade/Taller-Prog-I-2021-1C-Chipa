#ifndef LOGIN_H
#define LOGIN_H
#define FONTSIZE 24
#include "SDLManager.h"
#include "../common/Logger.h"
#include "../common/Socket.h"
#include <iostream>
#include <map>
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
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TextRendered> textTextures;
    int& playerNumber;
public:
    Login(Logger& logger, SDLManager& mngr, Socket& skt, int& playerNumber);
    int runLoginWindow(char* ip, char* port);
    void loadTexturesVector(std::vector<SDL_Texture*>& v);
    int manageUnsuccessfulConnection();
    void renderer(TextRendered& loginError);
    void manageTextInput(SDL_Event e, bool& renderPass, std::string& inputTextPsw, bool& renderText,
                         std::string& inputTextUser);
    int manageCharReceived(char c, bool& quit, TextRendered& loginError, std::vector<SDL_Texture*>& v);
    void manageClickOnPrompt(bool& renderPass, bool& canWrite, bool user);
    void renderUsrAndPswText(bool& renderPass, std::string& inputTextPsw, std::string& inputTextUser);
    int manageMouseOnButton(SDL_Event& e, std::vector<SDL_Texture*>& v, std::string& inputTextUser,
                            std::string& inputTextPsw, bool& quit, TextRendered &loginError);
    void close(std::vector<SDL_Texture*>& v);
    ~Login();
};

#endif //LOGIN_H
