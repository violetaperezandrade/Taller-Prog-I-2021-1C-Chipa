#include "Login.h"
#include <iostream>

Login::Login(Logger& logger, SDLManager& mngr, Socket& skt, int& playerNumber) :
logger(logger),
sdlMngr(mngr),
sktLogin(skt),
playerNumber(playerNumber)
{

    windowLogin = sdlMngr.createWindow("Login game",SCREEN_WIDTH_LOGIN,SCREEN_HEIGHT_LOGIN);
    windowRendererLogin = sdlMngr.createRenderer(windowLogin);
    globalFont = sdlMngr.createFont("../src/client/fonts/Kongtext Regular.ttf",FONTSIZE);

    textures = {{"textboxIdle", sdlMngr.loadImageTexture("../src/client/img/Login/textbox-blue.png", windowRendererLogin)},
                {"textboxClicked", sdlMngr.loadImageTexture("../src/client/img/Login/textbox-clicked.png", windowRendererLogin)},
                {"playButton", sdlMngr.loadImageTexture("../src/client/img/Login/play.png", windowRendererLogin)},
                {"monkey", sdlMngr.loadImageTexture("../src/client/img/Login/dk2.png",windowRendererLogin)},
                {"textboxUser", sdlMngr.loadImageTexture("../src/client/img/Login/textbox-blue.png", windowRendererLogin)},
                {"textboxPass", sdlMngr.loadImageTexture("../src/client/img/Login/textbox-blue.png", windowRendererLogin)}

    };
    const char* playText = "PLAY!";
    std::string inputTextUser = "";
    std::string inputTextPsw = "";
    SDL_Color textColorPrompt = {0xFF, 0xFF, 0xFF, 0xFF};
    SDL_Color textColorInput = {0, 0, 0, 0};
    SDL_Color textColorPlay = {204, 255, 0};

    textTextures = {{"prompTextureUsr", sdlMngr.loadFromRenderedText("Username: ", textColorPrompt, windowRendererLogin, globalFont)},
                    {"prompTexturePsw", sdlMngr.loadFromRenderedText("Password: ", textColorPrompt, windowRendererLogin, globalFont)},
                    {"inputTextTextureUser", sdlMngr.loadFromRenderedText(inputTextUser.c_str(), textColorInput, windowRendererLogin, globalFont)},
                    {"inputTextTexturePsw", sdlMngr.loadFromRenderedText(inputTextPsw.c_str(), textColorInput, windowRendererLogin, globalFont)},
                    {"playButtonText", sdlMngr.loadFromRenderedText(playText, textColorPlay, windowRendererLogin, globalFont)},
    };

}

int Login::manageUnsuccessfulConnection(){
    sdlMngr.renderWarnings("Server Unreachable", windowRendererLogin, windowLogin);
    logger.errorMsg("Error al conectar al servidor", __FILE__, __LINE__);
    return -1;
}

void Login::loadTexturesVector(std::vector<SDL_Texture*>& v){
    v.push_back(textTextures["inputTextTextureUser"].texture);
    v.push_back(textTextures["inputTextTexturePsw"].texture);
    v.push_back(textTextures["prompTexturePsw"].texture);
    v.push_back(textTextures["prompTextureUsr"].texture);
    v.push_back(textTextures["playButtonText"].texture);
    v.push_back(textures["textboxIdle"]);
    v.push_back(textures["textboxClicked"]);
    v.push_back(textures["textboxUser"]);
    v.push_back(textures["textboxPass"]);
    v.push_back(textures["playButton"]);
    v.push_back(textures["monkey"]);
}

void Login::renderer(TextRendered& loginError){
    SDL_SetRenderDrawColor(windowRendererLogin,0,0,0,0xFF);
    SDL_RenderClear(windowRendererLogin);

    sdlMngr.render(300, 80, 300, 50, textures["textboxUser"], windowRendererLogin);
    sdlMngr.render(300, 180, 300, 50, textures["textboxPass"], windowRendererLogin);

    sdlMngr.render(300, 50, textTextures["prompTextureUsr"].width, textTextures["prompTextureUsr"].height, textTextures["prompTextureUsr"].texture, windowRendererLogin);
    sdlMngr.render(310, 95, textTextures["inputTextTextureUser"].width, textTextures["inputTextTextureUser"].height, textTextures["inputTextTextureUser"].texture, windowRendererLogin);
    sdlMngr.render(300, 150, textTextures["prompTexturePsw"].width, textTextures["prompTexturePsw"].height, textTextures["prompTexturePsw"].texture, windowRendererLogin);
    sdlMngr.render(310, 195, textTextures["inputTextTexturePsw"].width, textTextures["inputTextTexturePsw"].height, textTextures["inputTextTexturePsw"].texture, windowRendererLogin);

    sdlMngr.render(220, 300, 200, 70, textures["playButton"], windowRendererLogin);
    sdlMngr.render(250,308,textTextures["playButtonText"].width+30,textTextures["playButtonText"].height+30, textTextures["playButtonText"].texture, windowRendererLogin);

    sdlMngr.render(80, 380, loginError.width, loginError.height, loginError.texture, windowRendererLogin);

    sdlMngr.render(60, 70, 200, 200, textures["monkey"], windowRendererLogin);
    sdlMngr.presentRender(windowRendererLogin);

}

void Login::manageTextInput(SDL_Event e, bool& renderPass, std::string& inputTextPsw, bool& renderText,
                            std::string& inputTextUser){
    if(e.type == SDL_KEYDOWN){
        if(e.key.keysym.sym == SDLK_BACKSPACE){
            if(renderPass){
                if(!inputTextPsw.empty()){
                    inputTextPsw.pop_back();
                }
            }
            else{
                if(!inputTextUser.empty()){
                    inputTextUser.pop_back();
                }
            }
            renderText = true;
        }
            //copy paste
        else if(e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL){
            if(renderPass) SDL_SetClipboardText(inputTextPsw.c_str());
            else SDL_SetClipboardText(inputTextUser.c_str());
        }
        else if(e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL){
            if(renderPass) inputTextPsw = SDL_GetClipboardText();
            else inputTextUser = SDL_GetClipboardText();
            renderText = true;
        }
    }
    if(e.type == SDL_TEXTINPUT){
        if(!(SDL_GetModState() & KMOD_CTRL && (tolower(e.text.text[0]) == 'c' || tolower(e.text.text[0]) == 'v'))){
            if(renderPass) inputTextPsw += e.text.text;
            else inputTextUser += e.text.text;
            renderText = true;
        }
    }
}

int Login::manageCharReceived(char c, bool& quit, TextRendered& loginError, std::vector<SDL_Texture *>& v) {

    if(c == 'F') {
        sdlMngr.renderWarnings("Server full, wait", windowRendererLogin, windowLogin);
        sdlMngr.freeAllTextures(v);
        quit = true;
        return -1;
    }
    if (c == 'B') {
        loginError = sdlMngr.loadFromRenderedText("User or pass invalid", {255, 0, 0},
                                                  windowRendererLogin, globalFont);
        v.push_back(loginError.texture);
        logger.infoMsg("Se ingresaron mal las credenciales", __FILE__, __LINE__);
    }
    else{
        loginError.texture = NULL;
        quit = true;
        logger.infoMsg("Se ingresaron correctamente las credenciales",__FILE__,__LINE__);
    }
    return 0;
}

int Login::manageMouseOnButton(SDL_Event& e, std::vector<SDL_Texture*>& v, std::string& inputTextUser,
                        std::string& inputTextPsw, bool& quit, TextRendered& loginError) {
    switch (e.type) {
        case SDL_MOUSEMOTION:
            textures["playButton"] = sdlMngr.loadImageTexture("../src/client/img/Login/playHover.png",
                                                              windowRendererLogin);
            v.push_back(textures["playButton"]);
            break;
        case SDL_MOUSEBUTTONDOWN:
            textures["playButton"] = sdlMngr.loadImageTexture("../src/client/img/Login/playClick.png",
                                                              windowRendererLogin);
            v.push_back(textures["playButton"]);

            sktLogin.send(inputTextUser.c_str(), 30, logger);
            logger.infoMsg("Se envia usuario", __FILE__, __LINE__);

            sktLogin.send(inputTextPsw.c_str(), 30, logger);
            logger.infoMsg("Se envia contraseña", __FILE__, __LINE__);

            char successLogin[1];
            logger.infoMsg("Se espera verificacion", __FILE__, __LINE__);
            sktLogin.receive(successLogin, 1, logger);
            if (manageCharReceived(successLogin[0], quit, loginError, v) < 0) return -1;
            playerNumber = successLogin[0];
            break;
    }
    return 0;
}

void Login::manageClickOnPrompt(bool& renderPass, bool& canWrite, bool user){
    if (user){
        renderPass = false;
        canWrite = true;
        textures["textboxUser"] = textures["textboxClicked"];
        textures["textboxPass"] = textures["textboxIdle"];
    }
    else{
        renderPass = true;
        canWrite = true;
        textures["textboxPass"] = textures["textboxClicked"];
        textures["textboxUser"] = textures["textboxIdle"];
    }
}

void Login::renderUsrAndPswText(bool& renderPass, std::string& inputTextPsw, std::string& inputTextUser){
    SDL_Color textColorInput = {0, 0, 0, 0};
    std::string invisiblePsw (inputTextPsw.length(),'*');
        if(renderPass){
            if(inputTextPsw != "") textTextures["inputTextTexturePsw"] = sdlMngr.loadFromRenderedText(
                    invisiblePsw.c_str(),
                    textColorInput,
                    windowRendererLogin,
                    globalFont);
            else textTextures["inputTextTexturePsw"] = sdlMngr.loadFromRenderedText("|",
                                                                                    textColorInput,
                                                                                    windowRendererLogin,
                                                                                    globalFont);
        }
        else{
            if(inputTextUser != "") textTextures["inputTextTextureUser"] = sdlMngr.loadFromRenderedText(
                    inputTextUser.c_str(),
                    textColorInput,
                    windowRendererLogin,
                    globalFont);
            else textTextures["inputTextTextureUser"] = sdlMngr.loadFromRenderedText("|",
                                                                                     textColorInput,
                                                                                     windowRendererLogin,
                                                                                     globalFont);
        }
}

int Login::runLoginWindow(char* ip, char* port) {
    TextRendered loginError;
    std::vector<SDL_Texture*> v;
    int success = sktLogin.connect(ip, port, logger);
    if(success < 0) return manageUnsuccessfulConnection();
    logger.debugMsg("Conexion al servidor satisfactoria",__FILE__,__LINE__);
    logger.infoMsg("Se inicia la ventana de login",__FILE__,__LINE__);
    std::string inputTextUser = "";
    std::string inputTextPsw = "";
    std::string playText = "PLAY!";
    loadTexturesVector(v);
    sdlMngr.startInputText();
    bool renderPass = false;
    bool canWrite = false;
    bool quit = false;
    SDL_Event e;
    while(!quit){
        bool renderText = false;
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
                return -1;
            }
            //if mouse was clicked username prompt
            if(sdlMngr.mouseWasClickedOnPosition(310, 600, 80 , 130, &e)){
                manageClickOnPrompt(renderPass, canWrite, true);
            }
            //if mouse was clicked password prompt
            else if(sdlMngr.mouseWasClickedOnPosition(310, 600, 180, 230, &e)){
                manageClickOnPrompt(renderPass, canWrite, false);
            }

            if(canWrite) manageTextInput(e, renderPass, inputTextPsw, renderText, inputTextUser);

            if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN){
                int x, y;
                SDL_GetMouseState(&x, &y);
                //Posiciones del boton en la pantalla
                if((x > 220 && x < 420) && (y > 300 && y < 370)){ //el mouse esta adentro del boton
                    if (manageMouseOnButton(e,
                                            v,
                                            inputTextUser,
                                            inputTextPsw,
                                            quit,
                                            loginError) < 0) return -1;
                }
                else{
                    textures["playButton"] = sdlMngr.loadImageTexture("../src/client/img/Login/play.png",
                                                                      windowRendererLogin);
                    v.push_back(textures["playButton"]);
                }
            }
        }
        if (renderText) renderUsrAndPswText(renderPass, inputTextPsw, inputTextUser);
        renderer(loginError);
    }
    close(v);
    return 0;
}
void Login::close(std::vector<SDL_Texture*>& v){
    sdlMngr.finishInputText();
    sdlMngr.freeAllTextures(v);
    sdlMngr.destroyFont(globalFont);
    globalFont = NULL;
    sdlMngr.destroyRenderer(windowRendererLogin);
    windowRendererLogin = NULL;
    sdlMngr.destroyWindow(windowLogin);
    windowLogin = NULL;
}

Login::~Login(){}
