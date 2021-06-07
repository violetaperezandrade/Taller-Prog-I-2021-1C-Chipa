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

int Login::runLoginWindow() {

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

    bool quit = false;
    SDL_Event e;

    while(!quit){
        bool renderText = false;

        //while(SDL_PollEvent(&e) != 0){
        while(SDL_WaitEvent(&e) != 0){
            if(e.type == SDL_QUIT) quit = true;
            if(e.type == SDL_KEYDOWN){

                if(e.key.keysym.sym == SDLK_TAB || e.key.keysym.sym == SDLK_RETURN){
                    renderPass = true;
                    continue;
                }
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
            else if(e.type == SDL_TEXTINPUT){
                if(!(SDL_GetModState() & KMOD_CTRL && (tolower(e.text.text[0]) == 'c' || tolower(e.text.text[0]) == 'v'))){
                    if(renderPass) inputTextPsw += e.text.text;
                    else inputTextUser += e.text.text;
                    renderText = true;
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

        renderLogin(300,150,300,50,textbox,windowRendererLogin);
        renderLogin(300,250,300,50,textbox,windowRendererLogin);

        renderLogin(300,120, prompTextureUsr.width,prompTextureUsr.height,prompTextureUsr.texture,windowRendererLogin);
        renderLogin(310,165,inputTextTextureUser.width,inputTextTextureUser.height,inputTextTextureUser.texture,windowRendererLogin);
        renderLogin(300,220,prompTexturePsw.width,prompTexturePsw.height,prompTexturePsw.texture,windowRendererLogin);
        renderLogin(310,265,inputTextTexturePsw.width,inputTextTexturePsw.height,inputTextTexturePsw.texture,windowRendererLogin);

        renderLogin(220,350,200,70,playButton,windowRendererLogin);
        renderLogin(253,359,playButtonText.width+50,playButtonText.height+30,playButtonText.texture,windowRendererLogin);

        renderLogin(50,140,200,200,monkey,windowRendererLogin);
        SDL_RenderPresent(windowRendererLogin);
    }
    sktLogin.send(inputTextUser.c_str(), inputTextUser.length());
    sktLogin.send(inputTextPsw.c_str(), inputTextPsw.length());
    char succesLogin[1];
    sktLogin.receive(succesLogin,1);
    if(succesLogin[0] == 'F'){
        //Renderizar ventana de error
    }
    SDL_StopTextInput();
    return 0;
}

Login::~Login(){
    closeSDL();
}