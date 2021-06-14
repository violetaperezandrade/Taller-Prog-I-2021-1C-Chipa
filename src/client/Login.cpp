#include "Login.h"
#include <iostream>

Login::Login(Logger& logger,Socket& skt) : logger(logger),sktLogin(skt){
    if (initSDL() < 0){
        logger.errorMsg("Fallo initSDL", __FILE__, __LINE__);
    }
    windowLogin = createWindow("Login game",SCREEN_WIDTH_LOGIN,SCREEN_HEIGHT_LOGIN);
    windowRendererLogin = createRenderer(windowLogin);
    globalFont = createFont("../src/client/fonts/Kongtext Regular.ttf");
}

TTF_Font* Login::createFont(std::string path){

    TTF_Font* font = TTF_OpenFont(path.c_str(),FONTSIZE);
    if(font == NULL) logger.errorMsg("Error al cargar fuente",__FILE__,__LINE__);
    return font;
}

TextRendered Login::loadFromRenderedText(std::string textureText,
                                        SDL_Color textColor,
                                        SDL_Renderer* renderer, TTF_Font* font){

    TextRendered text;
    SDL_Texture* finalTexture = NULL;
    int w,h;
    SDL_Surface* textSurface = TTF_RenderText_Solid(font,textureText.c_str(),textColor);
    if(textSurface != NULL){

        //crear textura desde superficie
        finalTexture = SDL_CreateTextureFromSurface(renderer,textSurface);
        if(finalTexture == NULL) logger.errorMsg("Error al cargar textura desde texto",__FILE__,__LINE__);
        else{
            w = textSurface->w;
            h = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    text.texture = finalTexture;
    text.width = w;
    text.height = h;
    return text;
}

bool Login::initSDL() {

    bool error = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logger.errorMsg("Fallo inicializar video SDL", __FILE__, __LINE__);
        error = true;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        logger.errorMsg("Error al filtrar textura lineal", __FILE__, __LINE__);
    }
    if(TTF_Init() == -1){
        logger.errorMsg("Error al inicializar TTF",__FILE__,__LINE__);
        error = true;
    }
    return error;
}

void Login::closeSDL() {

    TTF_CloseFont(globalFont);
    globalFont = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    logger.infoMsg("Cerrar SDL", __FILE__, __LINE__);
}

void Login::renderLogin(int x, int y, int width, int height, SDL_Texture *texture, SDL_Renderer *windowRenderer) {

    SDL_Rect renderQuad = {x,y,width,height};
    SDL_Rect* clip = NULL;
    double angle = 0.0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(windowRendererLogin,texture,clip,&renderQuad,angle,center,flip);
}

bool View::mouseWasClickedInPosition(int x1, int x2, int y1, int y2, SDL_Event* e){

    bool ok = false;
    if(e->type == SDL_MOUSEBUTTONDOWN){
        int x,y;
        SDL_GetMouseState(&x,&y);
        if((x > x1 && x < x2) && (y > y1 && y < y2)) ok = true;
    }
    return ok;
}

int Login::runLoginWindow(char* ip, char* port) {

    int success = sktLogin.connect(ip,port);
    if(success < 0){
        TextRendered connError = loadFromRenderedText("Server unreachable or full, try again.",{255,0,0},windowRenderer,globalFont);
        SDL_Texture* warning = loadImageTexture("../src/client/img/warning.png",windowRenderer);
        SDL_SetRenderDrawColor(windowRenderer,0,0,0,0xFF);
        SDL_RenderClear(windowRenderer);
        render(5,210,connError.width-50,connError.height,connError.texture,windowRenderer);
        render(260,300,100,100,warning,windowRenderer);
        SDL_RenderPresent(windowRenderer);
        SDL_Delay(3000);
        return -1;
    }
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

    inputTextTextureUser = loadFromRenderedText(inputTextUser.c_str(),textColorInput,windowRendererLogin,globalFont);
    inputTextTexturePsw = loadFromRenderedText(inputTextPsw.c_str(),textColorInput,windowRendererLogin,globalFont);
    prompTextureUsr = loadFromRenderedText("Username: ",textColorPrompt,windowRendererLogin,globalFont);
    prompTexturePsw = loadFromRenderedText("Password: ",textColorPrompt,windowRendererLogin,globalFont);
    playButtonText = loadFromRenderedText(playText.c_str(),textColorPlay,windowRendererLogin,globalFont);

    SDL_Texture* textbox = loadImageTexture("../src/client/img/textbox-blue.png",windowRendererLogin);
    SDL_Texture* playButton = loadImageTexture("../src/client/img/play.png",windowRendererLogin);
    SDL_Texture* monkey = loadImageTexture("../src/client/img/dk2.png",windowRendererLogin);

    SDL_StartTextInput();

    bool renderPass = false;
    bool canWrite = false;
    bool quit = false;

    SDL_Event e;

    while(!quit){
        bool renderText = false;
        while(SDL_WaitEvent(&e) != 0){
            if(e.type == SDL_QUIT) quit = true;
            //if mouse was clicked username prompt
            if(mouseWasClickedOnPosition(300,600,80,130,&e) == true){
                renderPass = false;
                canWrite = true;
            }
            //if mouse was clicked password prompt
            else if(mouseWasClickedOnPosition(300,600,180,230,&e) == true){
                renderPass = true;
                canWrite = true;
            }

            if(canWrite){
                if(e.type == SDL_KEYDOWN){
                    if(e.key.keysym.sym == SDLK_BACKSPACE && (inputTextUser.length() > 0 || inputTextPsw.length() > 0)){
                        if(renderPass) inputTextPsw.pop_back();
                        else inputTextUser.pop_back();
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
            if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN ||){
                int x,y;
                SDL_GetMouseState(&x,&y);
                //Chequear si mouse esta dentro del boton
                bool onButton = false;
                //Posiciones del boton en la pantalla
                if((x > 220 && x < 420) && (y > 300 && y < 370)) onButton = true;

                if(onButton == true){
                    switch(e.type){
                        case SDL_MOUSEMOTION:
                            playButton = loadImageTexture("../src/client/img/playHover.png",windowRendererLogin);
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            playButton = loadImageTexture("../src/client/img/playClick.png",windowRendererLogin);
                            sktLogin.send(inputTextUser.c_str(), inputTextUser.length());
                            sktLogin.send(inputTextPsw.c_str(), inputTextPsw.length());
                            char succesLogin[1];
                            sktLogin.receive(succesLogin,1);
                            if(succesLogin[0] == 'F'){
                                loginError = loadFromRenderedText("User or pass invalid, try again.",{255,0,0},windowRendererLogin,globalFont);
                            }
                            else{
                                loginError = NULL;
                                quit = true;
                            }
                            break;
                    }
                }
                else{
                    playButton = loadImageTexture("play.png",windowRenderer);
                }
            }
        }
        std::string invisiblePsw (inputTextPsw.length(),'*');
        if(renderText){
            if(renderPass){
                if(inputTextPsw != "") inputTextTexturePsw = loadFromRenderedText(invisiblePsw.c_str(),textColorInput,windowRendererLogin,globalFont);
                else inputTextTexturePsw = loadFromRenderedText("|",textColorInput,windowRendererLogin,globalFont);
            }
            else{
                if(inputTextUser != "") inputTextTextureUser = loadFromRenderedText(inputTextUser.c_str(),textColorInput,windowRendererLogin,globalFont);
                else inputTextTextureUser = loadFromRenderedText("|",textColorInput,windowRendererLogin,globalFont);
            }
        }

        SDL_SetRenderDrawColor(windowRendererLogin,0,0,0,0xFF);
        SDL_RenderClear(windowRendererLogin);

        renderLogin(300,80,300,50,textbox,windowRendererLogin);
        renderLogin(300,180,300,50,textbox,windowRendererLogin);

        renderLogin(300,50, prompTextureUsr.width,prompTextureUsr.height,prompTextureUsr.texture,windowRendererLogin);
        renderLogin(310,95,inputTextTextureUser.width,inputTextTextureUser.height,inputTextTextureUser.texture,windowRendererLogin);
        renderLogin(300,150,prompTexturePsw.width,prompTexturePsw.height,prompTexturePsw.texture,windowRendererLogin);
        renderLogin(310,195,inputTextTexturePsw.width,inputTextTexturePsw.height,inputTextTexturePsw.texture,windowRendererLogin);

        renderLogin(220,300,200,70,playButton,windowRendererLogin);
        renderLogin(253,310,playButtonText.width+50,playButtonText.height+30,playButtonText.texture,windowRendererLogin);

        renderLogin(50,380,loginError.width-50,loginError.height,loginError.texture,windowRendererLogin);

        renderLogin(60,70,200,200,monkey,windowRendererLogin);
        SDL_RenderPresent(windowRendererLogin);
    }
    SDL_StopTextInput();
    return 0;
}

Login::~Login(){
    closeSDL();
}