#include "Login.h"
#include <iostream>

Login::Login(Logger& logger,Socket& skt,SDLManager& mngr) : logger(logger),sktLogin(skt),sdlMngr(mngr){

    windowLogin = sdlMngr.createWindow("Login game",SCREEN_WIDTH_LOGIN,SCREEN_HEIGHT_LOGIN);
    windowRendererLogin = sdlMngr.createRenderer(windowLogin);
    globalFont = sdlMngr.createFont("../src/client/fonts/Kongtext Regular.ttf",FONTSIZE);
}

int Login::runLoginWindow(char* ip, char* port) {

    std::vector<SDL_Texture*> v;
    int success = sktLogin.connect(ip, port, logger);
    if(success < 0){
        sdlMngr.renderWarnings("Server Unreachable",windowRendererLogin,windowLogin);
        logger.errorMsg("Error al conectar al servidor",__FILE__,__LINE__);
        return -1;
    }
    logger.debugMsg("Conexion al servidor satisfactoria",__FILE__,__LINE__);
    logger.infoMsg("Se inicia la ventana de login",__FILE__,__LINE__);
    std::string inputTextUser = "";
    std::string inputTextPsw = "";
    std::string playText = "PLAY!";

    SDL_Color textColorPrompt = {0xFF,0xFF,0xFF,0xFF};
    SDL_Color textColorInput = {0,0,0,0};
    SDL_Color textColorPlay = {204,255,0};

    TextRendered prompTextureUsr;
    TextRendered prompTexturePsw;
    TextRendered inputTextTextureUser;
    TextRendered inputTextTexturePsw;
    TextRendered playButtonText;
    TextRendered loginError;

    inputTextTextureUser = sdlMngr.loadFromRenderedText(inputTextUser.c_str(),textColorInput,windowRendererLogin,globalFont);
    inputTextTexturePsw = sdlMngr.loadFromRenderedText(inputTextPsw.c_str(),textColorInput,windowRendererLogin,globalFont);
    prompTextureUsr = sdlMngr.loadFromRenderedText("Username: ",textColorPrompt,windowRendererLogin,globalFont);
    prompTexturePsw = sdlMngr.loadFromRenderedText("Password: ",textColorPrompt,windowRendererLogin,globalFont);
    playButtonText = sdlMngr.loadFromRenderedText(playText.c_str(),textColorPlay,windowRendererLogin,globalFont);

    SDL_Texture* textboxIdle = sdlMngr.loadImageTexture("../src/client/img/Login/textbox-blue.png",windowRendererLogin);
    SDL_Texture* textboxClicked = sdlMngr.loadImageTexture("../src/client/img/Login/textbox-clicked.png",windowRendererLogin);
    SDL_Texture* textboxUser = textboxIdle;
    SDL_Texture* textboxPass = textboxIdle;
    SDL_Texture* playButton = sdlMngr.loadImageTexture("../src/client/img/Login/play.png",windowRendererLogin);
    SDL_Texture* monkey = sdlMngr.loadImageTexture("../src/client/img/Login/dk2.png",windowRendererLogin);

    v.push_back(inputTextTextureUser.texture);
    v.push_back(inputTextTexturePsw.texture);
    v.push_back(prompTexturePsw.texture);
    v.push_back(prompTextureUsr.texture);
    v.push_back(playButtonText.texture);
    v.push_back(textboxIdle);
    v.push_back(textboxClicked);
    v.push_back(textboxUser);
    v.push_back(textboxPass);
    v.push_back(playButton);
    v.push_back(monkey);

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
            if(sdlMngr.mouseWasClickedOnPosition(310,600,80,130,&e) == true){
                renderPass = false;
                canWrite = true;
                textboxUser = textboxClicked;
                textboxPass = textboxIdle;
            }
            //if mouse was clicked password prompt
            else if(sdlMngr.mouseWasClickedOnPosition(310,600,180,230,&e) == true){
                renderPass = true;
                canWrite = true;
                textboxPass = textboxClicked;
                textboxUser = textboxIdle;
            }

            if(canWrite){
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

            if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN){
                int x,y;
                SDL_GetMouseState(&x,&y);
                //Chequear si mouse esta dentro del boton
                bool onButton = false;
                //Posiciones del boton en la pantalla
                if((x > 220 && x < 420) && (y > 300 && y < 370)) onButton = true;

                if(onButton == true){
                    switch(e.type) {
                        case SDL_MOUSEMOTION:
                            playButton = sdlMngr.loadImageTexture("../src/client/img/Login/playHover.png", windowRendererLogin);
                            v.push_back(playButton);
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            playButton = sdlMngr.loadImageTexture("../src/client/img/Login/playClick.png", windowRendererLogin);
                            v.push_back(playButton);

                            sktLogin.send(inputTextUser.c_str(), 30, logger);
                            logger.infoMsg("Se envia usuario", __FILE__, __LINE__);

                            sktLogin.send(inputTextPsw.c_str(), 30, logger);
                            logger.infoMsg("Se envia contraseña", __FILE__, __LINE__);

                            char succesLogin[1];
                            logger.infoMsg("Se espera verificacion", __FILE__, __LINE__);
                            sktLogin.receive(succesLogin, 1, logger);

                            if(succesLogin[0] == 'F') {
                                sdlMngr.renderWarnings("Server full, wait",windowRendererLogin,windowLogin);
                                sdlMngr.freeAllTextures(v);
                                quit = true;
                                return -1;
                            }
                            if (succesLogin[0] == 'B') {
                                loginError = sdlMngr.loadFromRenderedText("User or pass invalid",{255,0,0},windowRendererLogin,globalFont);
                                v.push_back(loginError.texture);
                                logger.infoMsg("Se ingresaron mal las credenciales",__FILE__,__LINE__);
                            }
                            else{
                                loginError.texture = NULL;
                                quit = true;
                                logger.infoMsg("Se ingresaron correctamente las credenciales",__FILE__,__LINE__);
                            }
                            break;
                    }
                }
                else{
                    playButton = sdlMngr.loadImageTexture("../src/client/img/Login/play.png", windowRendererLogin);
                    v.push_back(playButton);
                }
            }
        }
        std::string invisiblePsw (inputTextPsw.length(),'*');
        if(renderText){
            if(renderPass){
                if(inputTextPsw != "") inputTextTexturePsw = sdlMngr.loadFromRenderedText(invisiblePsw.c_str(),textColorInput,windowRendererLogin,globalFont);
                else inputTextTexturePsw = sdlMngr.loadFromRenderedText("|",textColorInput,windowRendererLogin,globalFont);
            }
            else{
                if(inputTextUser != "") inputTextTextureUser = sdlMngr.loadFromRenderedText(inputTextUser.c_str(),textColorInput,windowRendererLogin,globalFont);
                else inputTextTextureUser = sdlMngr.loadFromRenderedText("|",textColorInput,windowRendererLogin,globalFont);
            }
        }

        SDL_SetRenderDrawColor(windowRendererLogin,0,0,0,0xFF);
        SDL_RenderClear(windowRendererLogin);

        sdlMngr.render(300,80,300,50,textboxUser,windowRendererLogin);
        sdlMngr.render(300,180,300,50,textboxPass,windowRendererLogin);

        sdlMngr.render(300,50, prompTextureUsr.width,prompTextureUsr.height,prompTextureUsr.texture,windowRendererLogin);
        sdlMngr.render(310,95,inputTextTextureUser.width,inputTextTextureUser.height,inputTextTextureUser.texture,windowRendererLogin);
        sdlMngr.render(300,150,prompTexturePsw.width,prompTexturePsw.height,prompTexturePsw.texture,windowRendererLogin);
        sdlMngr.render(310,195,inputTextTexturePsw.width,inputTextTexturePsw.height,inputTextTexturePsw.texture,windowRendererLogin);

        sdlMngr.render(220,300,200,70,playButton,windowRendererLogin);
        sdlMngr.render(250,308,playButtonText.width+30,playButtonText.height+30,playButtonText.texture,windowRendererLogin);

        sdlMngr.render(80,380,loginError.width,loginError.height,loginError.texture,windowRendererLogin);

        sdlMngr.render(60,70,200,200,monkey,windowRendererLogin);
        sdlMngr.presentRender(windowRendererLogin);
    }
    sdlMngr.finishInputText();
    sdlMngr.freeAllTextures(v);
    sdlMngr.destroyFont(globalFont);
    sdlMngr.destroyRenderer(windowRendererLogin);
    sdlMngr.destroyWindow(windowLogin);
    return 0;
}

Login::~Login(){}
