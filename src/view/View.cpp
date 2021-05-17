#include "View.h"
#include <iostream>

View::View(){

    texturesMario = {{'0', "../src/view/img/Sprites Mario/mario_idle_back.bmp"},
                {'4', "../src/view/img/Sprites Mario/mario_climbing.bmp"},
                {'r', "../src/view/img/Sprites Mario/mario_ide_right.bmp"},
                {'l',"../src/view/img/Sprites Mario/mario_idle_left.bmp"},
                {'7',"../src/view/img/Sprites Mario/mario_walk_left.bmp"},
                {'6',"../src/view/img/Sprites Mario/mario_walk_right.bmp"}

    };
    texturesEntities = {{'P', "../src/view/img/Platform.bmp"}};
    texturesMonkey = {{'0',"../src/view/img/Daco_187520.bmp"}};

    window = createWindow("Donkey Kong ii");
    windowRenderer = createRenderer(window);

}

SDL_Renderer* View::createRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(!renderer) std::cerr << "Error al crear renderer";
    else{
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    return renderer;
}

SDL_Window* View::createWindow(const char* title){
    SDL_Window* window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(!window) std::cerr << "Error al crear ventana";
    return window;
}

SDL_Texture* View::loadImageTexture(std::string path, SDL_Renderer* renderer){

    SDL_Texture* finalTexture = NULL;
    SDL_Surface* imageSurface = IMG_Load(path.c_str());
    if(!imageSurface) printf("Error al cargar imagen %s. SDL_image error: %s\n",
                             path.c_str(), IMG_GetError());
    else{
        SDL_SetColorKey(imageSurface,SDL_TRUE,SDL_MapRGB(imageSurface->format,0,0,0));
        finalTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        if(!finalTexture) printf("Error al cargar textura %s. SDL_Error: %s\n",
                                 path.c_str(),
                                 SDL_GetError());
        SDL_FreeSurface(imageSurface);
    }
    return finalTexture;
}

/*void View::render(int x, int y, int width, int height, SDL_Texture* texture, SDL_Renderer* windowRenderer){
    SDL_Rect renderQuad = {x,y,width,height};
    SDL_Rect* clip = NULL;
    double angle = 0.0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(windowRenderer,texture,clip,&renderQuad,angle,center,flip);
}*/
//Para usar en controller
void View::render(int x, int y, int width, int height, char stateEntity,char entityType) {
    SDL_Rect renderQuad = {x, y, width, height};
    SDL_Rect *clip = NULL;
    double angle = 0.0;
    SDL_Point *center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Texture *textureEntity;
    switch (entityType) {
        case 'C': //mario
            textureEntity = loadImageTexture(texturesMario[stateEntity], windowRenderer);
            break;
        case 'B': //barrel
            textureEntity = loadImageTexture(texturesEntities['B'], windowRenderer);
            break;
        case 'E': //embber
            textureEntity = loadImageTexture(texturesEntities['E'], windowRenderer);
            break;
        case 'F': //Fire
            textureEntity = loadImageTexture(texturesEntities['F'], windowRenderer);
            break;
        case 'f': //flame
            textureEntity = loadImageTexture(texturesEntities['f'], windowRenderer);
            break;
        case 'M': //monkey
            textureEntity = loadImageTexture(texturesMonkey['0'], windowRenderer);
            break;
        case 'P': //platform
            textureEntity = loadImageTexture(texturesEntities['P'], windowRenderer);
            break;
        case 'p': //princess
            textureEntity = loadImageTexture(texturesEntities['p'], windowRenderer);
            break;
        case 'S': //stair
            textureEntity = loadImageTexture(texturesEntities['S'], windowRenderer);
            break;
        default:
            break;
    }
    SDL_RenderCopyEx(windowRenderer, textureEntity, clip, &renderQuad, angle, center, flip);
}

void View::free(SDL_Texture* texture){
    if(texture){
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}
void View::refresh(){
    SDL_SetRenderDrawColor(windowRenderer,0,0,0,0xFF);
    SDL_RenderClear(windowRenderer);
    SDL_RenderPresent(windowRenderer);
}
/*int View::run(){

    SDL_Window* window = createWindow("Donkey Kong II");
    SDL_Renderer* windowRenderer = createRenderer(window);
    SDL_Texture* textureMario = loadImageTexture(texturesMario["mario idle back"],windowRenderer);
    SDL_Texture* textureLadder = loadImageTexture(texturesEntities["ladder with platform"],windowRenderer);
    SDL_Texture* texturePlatform = loadImageTexture(texturesEntities["P"],windowRenderer);

    //Render filled quad
    SDL_Rect fillRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_SetRenderDrawColor( windowRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( windowRenderer, &fillRect );

    //Render initialmario texture
    render(0,0,50,50,textureMario,windowRenderer);

    //Esto iria en controlador pero hasta q no tengamos el Game lo dejo aca
    bool quit = false;
    SDL_Event e;
    Entity mario('mario',0,0,20,20);
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT) quit = true;
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        textureMario = loadImageTexture(texturesMario["mario climbing"],windowRenderer);
                        break;
                    case SDLK_DOWN:
                        textureMario = loadImageTexture(texturesMario["mario idle back"],windowRenderer);
                        break;
                    case SDLK_LEFT:
                        textureMario = loadImageTexture(texturesMario["mario walking left"],windowRenderer);
                        break;
                    case SDLK_RIGHT:
                        textureMario = loadImageTexture(texturesMario["mario walking right"],windowRenderer);
                        break;
                    default:
                        textureMario = loadImageTexture(texturesMario["mario idle back"],windowRenderer);
                        break;
                }
            }
            else if(e.type == SDL_KEYUP){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        textureMario = loadImageTexture(texturesMario["mario idle back"],windowRenderer);
                        break;
                    case SDLK_DOWN:
                        textureMario = loadImageTexture(texturesMario["mario idle back"],windowRenderer);
                        break;
                    case SDLK_LEFT:
                        textureMario = loadImageTexture(texturesMario["mario idle left"],windowRenderer);
                        break;
                    case SDLK_RIGHT:
                        textureMario = loadImageTexture(texturesMario["mario idle right"],windowRenderer);
                        break;
                    default:
                        textureMario = loadImageTexture(texturesMario["mario idle back"],windowRenderer);
                        break;
                }
            }
            mario.handleEvent(e);
        }
        mario.move();
        //Esto seria el refresh que hay en controller
        SDL_SetRenderDrawColor(windowRenderer,0,0,0,0xFF);
        SDL_RenderClear(windowRenderer);
        render(0,50,400,100,textureLadder,windowRenderer);
        render(0,500,40,10,texturePlatform,windowRenderer);
        render(mario.getPosX(),mario.getPosY(),50,50,textureMario,windowRenderer);
        SDL_RenderPresent(windowRenderer);
    }
    SDL_RenderPresent(windowRenderer);
    return 0;

}*/
