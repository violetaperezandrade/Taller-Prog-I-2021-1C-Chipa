#include "View.h"

View::View(){

    textures = {{"mario idle back", "../src/view/img/Sprites Mario/mario_idle_back.bmp"},
                {"mario climbing", "../src/view/img/Sprites Mario/mario_climbing.bmp"},
                {"mario idle right", "../src/view/img/Sprites Mario/mario_ide_right.bmp"},
                {"mario idle left","../src/view/img/Sprites Mario/mario_idle_left.bmp"},
                {"mario walking left","../src/view/img/Sprites Mario/mario_walk_left.bmp"},
                {"mario walking right","../src/view/img/Sprites Mario/mario_walk_right.bmp"},
                {"ladder with platform","../src/view/img/staticObjects.bmp"},
                {"platform", "../src/view/img/Platform.bmp"}
    };
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

void View::render(int x, int y, int width, int height, SDL_Texture* texture, SDL_Renderer* windowRenderer){
    SDL_Rect renderQuad = {x,y,width,height};
    SDL_Rect* clip = NULL;
    double angle = 0.0;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(windowRenderer,texture,clip,&renderQuad,angle,center,flip);
}

void View::free(SDL_Texture* texture){
    if(texture){
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

int View::run(){

    Controller cont;

    SDL_Window* window = createWindow("Donkey Kong II");
    SDL_Renderer* windowRenderer = createRenderer(window);
    SDL_Texture* textureMario = loadImageTexture(textures["mario idle back"],windowRenderer);
    SDL_Texture* textureLadder = loadImageTexture(textures["ladder with platform"],windowRenderer);
    SDL_Texture* texturePlatform = loadImageTexture(textures["platform"],windowRenderer);

    //Render filled quad
    SDL_Rect fillRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_SetRenderDrawColor( windowRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( windowRenderer, &fillRect );

    //Render initialmario texture
    render(0,0,50,50,textureMario,windowRenderer);

    //Esto iria en controlador pero hasta q no tengamos el Game lo dejo aca
    bool quit = false;
    SDL_Event e;
    Entity entity(0,0,20,20,0,0);
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT) quit = true;
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        textureMario = loadImageTexture(textures["mario climbing"],windowRenderer);
                        break;
                    case SDLK_DOWN:
                        textureMario = loadImageTexture(textures["mario idle back"],windowRenderer);
                        break;
                    case SDLK_LEFT:
                        textureMario = loadImageTexture(textures["mario walking left"],windowRenderer);
                        break;
                    case SDLK_RIGHT:
                        textureMario = loadImageTexture(textures["mario walking right"],windowRenderer);
                        break;
                    default:
                        textureMario = loadImageTexture(textures["mario idle back"],windowRenderer);
                        break;
                }
            }
            else if(e.type == SDL_KEYUP){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        textureMario = loadImageTexture(textures["mario idle back"],windowRenderer);
                        break;
                    case SDLK_DOWN:
                        textureMario = loadImageTexture(textures["mario idle back"],windowRenderer);
                        break;
                    case SDLK_LEFT:
                        textureMario = loadImageTexture(textures["mario idle left"],windowRenderer);
                        break;
                    case SDLK_RIGHT:
                        textureMario = loadImageTexture(textures["mario idle right"],windowRenderer);
                        break;
                    default:
                        textureMario = loadImageTexture(textures["mario idle back"],windowRenderer);
                        break;
                }
            }
            entity.handleEvent(e);
        }
        entity.move();
        SDL_SetRenderDrawColor(windowRenderer,0,0,0,0xFF);
        SDL_RenderClear(windowRenderer);
        render(0,50,400,100,textureLadder,windowRenderer);
        render(0,500,40,10,texturePlatform,windowRenderer);
        render(entity.getPosX(),entity.getPosY(),50,50,textureMario,windowRenderer);
        SDL_RenderPresent(windowRenderer);
    }
    SDL_RenderPresent(windowRenderer);
    return 0;

}
