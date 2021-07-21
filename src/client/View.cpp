#include "View.h"

View::View(Monitor& monitor, Logger& logger, Config& config, SDLManager& mngr, bool& keepRunning, bool& serverActive,
           int& playerNumber, SoundManager& soundManager, int& playerAmount, int& endGame) :
    logger(logger),
    config(config),
    sdlMngr(mngr),
    monitor(monitor),
    playerID(0),
    keepRuning(keepRunning),
    serverActive(serverActive),
    playerNumber(playerNumber),
    soundManager(soundManager),
    playerAmount(playerAmount),
    endGame(endGame),
    hammerState()
{
    window = sdlMngr.createWindow("Donkey Kong ii", config.getResolutionWidth(), config.getResolutionHeight());
    windowRenderer = sdlMngr.createRenderer(window);

    //grey
    texturesMario[0]['d'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/mario_idle_back_off.png", windowRenderer);

    //red
    texturesMario[1]['1'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_jump_right.png", windowRenderer);
    texturesMario[1]['2'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_jump_left.png", windowRenderer);
    texturesMario[1]['6'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_walk_right.png", windowRenderer);
    texturesMario[1]['7'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_walk_left.png", windowRenderer);
    texturesMario[1]['8'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_climbing_right.png", windowRenderer);
    texturesMario[1]['9'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_climbing_right.png", windowRenderer);
    texturesMario[1]['r'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_idle_right.png", windowRenderer);
    texturesMario[1]['l'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_idle_left.png", windowRenderer);
    texturesMario[1]['x'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_dead.png", windowRenderer);
    texturesMario[1]['A'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_jump_right_hammer.png", windowRenderer);
    texturesMario[1]['B'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_jump_left_hammer.png", windowRenderer);
    texturesMario[1]['C'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_walk_right_hammer.png", windowRenderer);
    texturesMario[1]['D'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_walk_left_hammer.png", windowRenderer);
    texturesMario[1]['E'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_climbing_right.png", windowRenderer);
    texturesMario[1]['F'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_climbing_right.png", windowRenderer);
    texturesMario[1]['G'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_idle_right_hammer.png", windowRenderer);
    texturesMario[1]['H'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_idle_left_hammer.png", windowRenderer);
    texturesMario[1]['I'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/red/mario_dead.png", windowRenderer);

    //yellow
    texturesMario[2]['1'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_jump_right.png", windowRenderer);
    texturesMario[2]['2'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_jump_left.png", windowRenderer);
    texturesMario[2]['6'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_walk_right.png", windowRenderer);
    texturesMario[2]['7'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_walk_left.png", windowRenderer);
    texturesMario[2]['8'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_climbing_right.png", windowRenderer);
    texturesMario[2]['9'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_climbing_right.png", windowRenderer);
    texturesMario[2]['r'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_idle_right.png", windowRenderer);
    texturesMario[2]['l'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_idle_left.png", windowRenderer);
    texturesMario[2]['x'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_dead.png", windowRenderer);
    texturesMario[2]['A'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_jump_right_hammer.png", windowRenderer);
    texturesMario[2]['B'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_jump_left_hammer.png", windowRenderer);
    texturesMario[2]['C'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_walk_right_hammer.png", windowRenderer);
    texturesMario[2]['D'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_walk_left_hammer.png", windowRenderer);
    texturesMario[2]['E'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_climbing_right.png", windowRenderer);
    texturesMario[2]['F'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_climbing_right.png", windowRenderer);
    texturesMario[2]['G'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_idle_right_hammer.png", windowRenderer);
    texturesMario[2]['H'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_idle_left_hammer.png", windowRenderer);
    texturesMario[2]['I'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/yellow/mario_dead.png", windowRenderer);

    //lilac
    texturesMario[3]['1'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_jump_right.png", windowRenderer);
    texturesMario[3]['2'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_jump_left.png", windowRenderer);
    texturesMario[3]['6'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_walk_right.png", windowRenderer);
    texturesMario[3]['7'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_walk_left.png", windowRenderer);
    texturesMario[3]['8'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_climbing_right.png", windowRenderer);
    texturesMario[3]['9'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_climbing_right.png", windowRenderer);
    texturesMario[3]['r'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_idle_right.png", windowRenderer);
    texturesMario[3]['l'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_idle_left.png", windowRenderer);
    texturesMario[3]['x'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_dead.png", windowRenderer);
    texturesMario[3]['A'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_jump_right_hammer.png", windowRenderer);
    texturesMario[3]['B'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_jump_left_hammer.png", windowRenderer);
    texturesMario[3]['C'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_walk_right_hammer.png", windowRenderer);
    texturesMario[3]['D'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_walk_left_hammer.png", windowRenderer);
    texturesMario[3]['E'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_climbing_right.png", windowRenderer);
    texturesMario[3]['F'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_climbing_right.png", windowRenderer);
    texturesMario[3]['G'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_idle_right_hammer.png", windowRenderer);
    texturesMario[3]['H'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_idle_left_hammer.png", windowRenderer);
    texturesMario[3]['I'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/lilac/mario_dead.png", windowRenderer);

    //green
    texturesMario[4]['1'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_jump_right.png", windowRenderer);
    texturesMario[4]['2'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_jump_left.png", windowRenderer);
    texturesMario[4]['6'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_walk_right.png", windowRenderer);
    texturesMario[4]['7'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_walk_left.png", windowRenderer);
    texturesMario[4]['8'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_climbing_right.png", windowRenderer);
    texturesMario[4]['9'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_climbing_right.png", windowRenderer);
    texturesMario[4]['r'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_idle_right.png", windowRenderer);
    texturesMario[4]['l'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_idle_left.png", windowRenderer);
    texturesMario[4]['x'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_dead.png", windowRenderer);
    texturesMario[4]['A'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_jump_right_hammer.png", windowRenderer);
    texturesMario[4]['B'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_jump_left_hammer.png", windowRenderer);
    texturesMario[4]['C'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_walk_right_hammer.png", windowRenderer);
    texturesMario[4]['D'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_walk_left_hammer.png", windowRenderer);
    texturesMario[4]['E'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_climbing_right.png", windowRenderer);
    texturesMario[4]['F'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_climbing_right.png", windowRenderer);
    texturesMario[4]['G'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_idle_right_hammer.png", windowRenderer);
    texturesMario[4]['H'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_idle_left_hammer.png", windowRenderer);
    texturesMario[4]['I'] = sdlMngr.loadImageTexture("../src/client/img/Sprites-Mario/green/mario_dead.png", windowRenderer);

    std::string fontPath = "../src/client/fonts/Kongtext Regular.ttf";
    font = sdlMngr.createFont(fontPath.c_str(), FONTSIZE_IDENTIFIERS);

    playersColor[1] = {255,0,0};
    playersColor[2] = {255,233,0};
    playersColor[3] = {178,0,255};
    playersColor[4] = {0,255,0};
    playersColor[5] = {255,255,255}; //white

    usersNames[1] = sdlMngr.loadFromRenderedText("P1", playersColor[1], windowRenderer, font);
    usersNames[2] = sdlMngr.loadFromRenderedText("P2", playersColor[2], windowRenderer, font);
    usersNames[3] = sdlMngr.loadFromRenderedText("P3", playersColor[3], windowRenderer, font);
    usersNames[4] = sdlMngr.loadFromRenderedText("P4", playersColor[4], windowRenderer, font);
    usersNames[5] = sdlMngr.loadFromRenderedText("Lives",playersColor[5],windowRenderer,font);
    usersNames[6] = sdlMngr.loadFromRenderedText("Points",playersColor[5],windowRenderer,font);

    texturesEntities = {{'P', sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/blue_platform.png", windowRenderer)},
                        {'B',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/front_barrel.png", windowRenderer)},
                        {'b',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/oil_barrel.png", windowRenderer)},
                        {'f',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/flame.png", windowRenderer)},
                        {'F',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/fire.png", windowRenderer)},
                        {'p',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/princess.png", windowRenderer)},
                        {'S',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/yellow_stair.png", windowRenderer)},
                        {'E',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/flame.png", windowRenderer)},
                        {'H', sdlMngr.loadImageTexture("../src/client/img/hammer.png", windowRenderer)}
    };

    texturesMonkey = {{'0',sdlMngr.loadImageTexture("../src/client/img/Sprites-Monkey/monkey_left_hand_up.png", windowRenderer)}};

    defaultConfig = sdlMngr.loadImageTexture("../src/client/img/default.png", windowRenderer);

    divisorPoints = sdlMngr.loadImageTexture("../src/client/img/divisor.png",windowRenderer);

    spriteSheet = sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/4barrels.png", windowRenderer);
    spriteFrames[0].x = 0;
    spriteFrames[0].y = 0;
    spriteFrames[0].w = 24;
    spriteFrames[0].h = 24;

    spriteFrames[1].x =  24;
    spriteFrames[1].y =   0;
    spriteFrames[1].w =  24;
    spriteFrames[1].h = 24;

    spriteFrames[2].x = 0;
    spriteFrames[2].y =  24;
    spriteFrames[2].w =  24;
    spriteFrames[2].h = 24;

    spriteFrames[3].x = 24;
    spriteFrames[3].y =   24;
    spriteFrames[3].w =  24;
    spriteFrames[3].h = 24;
}

void View::changeLevel(){
    texturesEntities = {{'P', sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/pink_platform.png", windowRenderer)},
                        {'B',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/front_barrel.png", windowRenderer)},
                        {'b',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/oil_barrel.png", windowRenderer)},
                        {'f',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/flame.png", windowRenderer)},
                        {'F',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/fire.png", windowRenderer)},
                        {'p',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/princess.png", windowRenderer)},
                        {'S',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/long_cyan_stair.png", windowRenderer)},
                        {'E',sdlMngr.loadImageTexture("../src/client/img/Sprites-Entities/flame.png", windowRenderer)},
                        {'H', sdlMngr.loadImageTexture("../src/client/img/hammer.png", windowRenderer)}
    };

}

void View::renderBarrelAnimation(int x, int y, int width, int height) {
    SDL_Rect* currentFrame = &spriteFrames[frame/ROLLING_BARREL_FRAMES];
    sdlMngr.render(x,y,width,height,spriteSheet,windowRenderer,currentFrame);
    ++frame;
    if(frame/4 >= ROLLING_BARREL_FRAMES) frame = 0;
}


void View::getEntityInfoAndRender(int x, int y, int width, int height, char stateEntity, char entityType) {

    SDL_Texture *textureEntity;
    std::string c("Renderizar entidad de tipo: ");
    c.append(&entityType);
    logger.debugMsg(c, __FILE__, __LINE__);
    switch (entityType) {
        case 'C': //mario
            if(stateEntity == 'd'){
                textureEntity = texturesMario[0][stateEntity];
            }
            else {
                textureEntity = texturesMario[playerID][stateEntity];
            }
            break;
        case 'B': //barrel
            renderBarrelAnimation(x,y,width,height);
            return;
        case 'E': //ember
            textureEntity = texturesEntities['E'];
            break;
        case 'F': //Fire
            textureEntity = texturesEntities['F'];
            break;
        case 'f': //flame
            textureEntity = texturesEntities['f'];
            break;
        case 'M': //monkey
            textureEntity = texturesMonkey['0'];
            break;
        case 'P': //platform
            textureEntity = texturesEntities['P'];
            break;
        case 'p': //princess
            textureEntity = texturesEntities['p'];
            break;
        case 'S': //stair
            textureEntity = texturesEntities['S'];
            break;
        case 'd'://default water mark
            textureEntity = defaultConfig;
        case 'H':
            textureEntity = texturesEntities['H'];
        default:
            break;
    }
    sdlMngr.render(x, y, width, height, textureEntity, windowRenderer);
}

void View::renderPlayerID(int posX, int width, int posY){
    if (config.getPlayersAmount() > 1){
        sdlMngr.render(posX+(width/3),
                       posY-15,
                       usersNames[playerID].width,
                       usersNames[playerID].height,
                       usersNames[playerID].texture,
                       windowRenderer);
        logger.debugMsg("Renderizando player ID", __FILE__, __LINE__);
    }
}

void View::renderLivesAndPoints(){

    sdlMngr.render(0, 40, 800, 10, divisorPoints, windowRenderer);
    sdlMngr.render(1, 1,
                   usersNames[5].width,
                   usersNames[5].height,
                   usersNames[5].texture,
                   windowRenderer);
    sdlMngr.render(1,
                   40-usersNames[6].height,
                   usersNames[6].width,
                   usersNames[6].height,
                   usersNames[6].texture,
                   windowRenderer);

    TextRendered textLives;
    TextRendered textPoints;
    for (int i = 1; i <= playerID ; i++) {
        int posX = ((config.getResolutionWidth() / config.getPlayersAmount())/2) +
                (config.getResolutionWidth()*(i-1)/config.getPlayersAmount());
        int posY = 20-(usersNames[i].height/2);

        textLives = sdlMngr.loadFromRenderedText(std::to_string(lives[i-1]),
                                                 playersColor[5],
                                                 windowRenderer,
                                                 font);
        textPoints = sdlMngr.loadFromRenderedText(std::to_string(points[i-1]),
                                                  playersColor[5],
                                                  windowRenderer,
                                                  font);

        sdlMngr.render(posX, posY,
                       usersNames[i].width,
                       usersNames[i].height,
                       usersNames[i].texture,
                       windowRenderer);
        sdlMngr.render(posX + usersNames[i].width + 10,
                       1,
                       textLives.width,
                       textLives.height,
                       textLives.texture,
                       windowRenderer);
        sdlMngr.render(posX + usersNames[i].width + 10,
                       40-textPoints.height,
                       textPoints.width,
                       textPoints.height,
                       textPoints.texture,
                       windowRenderer);
        sdlMngr.destroyTexture(textLives.texture);
        sdlMngr.destroyTexture(textPoints.texture);
    }
}

void View::renderEntity(std::vector<Entity>::iterator it, std::vector<char>& states){
    int posX = it->getPosX();
    int posY = it->getPosY();
    int width = it->getWidth();
    int height = it->getHeight();
    char type = it->getType();
    char state = it->getState();

    if (type == 'C') {
        playerID++;
        std::string id(1, state);
        std::string hammerStr = "ABCDEFGHI";
        std::string resize = "ABCDGHI";
        if (hammerStr.find(id) != std::string::npos){
            if (hammerState[playerID] == 0){
                soundManager.playSoundFromState('h');
                hammerState[playerID]++;
            }
            if (resize.find(id) != std::string::npos){
                width = 94; //59
                height = 47; //36
                posY -= 5;
            }
            if (id == "H") posX -= 26;
            if (id == "D") posX -= 33;
        }
        else hammerState[playerID] = 0;
        renderPlayerID(posX, width, posY);
        states.push_back(state);

    }
    logger.debugMsg("Renderizo una entidad", __FILE__, __LINE__);
    getEntityInfoAndRender(posX, posY, width, height, state, type);
}

void View::renderPartialResults(){
    TTF_Font* fontResults = sdlMngr.createFont("../src/client/fonts/Kongtext Regular.ttf",FONTSIZE_RESULTS);
    TextRendered result = sdlMngr.loadFromRenderedText("Partial results",
                                                       playersColor[5],
                                                       windowRenderer,
                                                       fontResults);

    sdlMngr.clearRender(windowRenderer);
    sdlMngr.render((config.getResolutionWidth()/2)-result.width/2,
                   10,
                   result.width,
                   result.height,
                   result.texture,
                   windowRenderer);
    sdlMngr.render((config.getResolutionWidth()/2)-result.width/2,
                   result.height + 10,
                   result.width,
                   10,
                   divisorPoints,
                   windowRenderer);

    TextRendered player;
    for(int i = 1; i <= playerAmount; i++){
        int valuePoints = points[i-1];
        std::ostringstream filledPoints;
        filledPoints << std::setw(4) << std::setfill('0') << valuePoints;
        std::string pointsStr = filledPoints.str();

        std::string playerId = "Player " + std::to_string(i) + ":" + " " + pointsStr;
        player = sdlMngr.loadFromRenderedText(playerId,
                                              playersColor[i],
                                              windowRenderer,
                                              fontResults);

        sdlMngr.render((config.getResolutionWidth()/2)-(player.width/2),
                       (150 + (i-1)*(player.height+40)),
                       player.width,
                       player.height,
                       player.texture,
                       windowRenderer);
    }
    sdlMngr.presentRender(windowRenderer);
    SDL_Delay(6000);
    sdlMngr.clearRender(windowRenderer);
    sdlMngr.destroyFont(fontResults);
    sdlMngr.destroyTexture(result.texture);
    sdlMngr.destroyTexture(player.texture);

}

void View::renderFinalResults(int* pointsLvl1){
    TTF_Font* fontResultsTitle = sdlMngr.createFont("../src/client/fonts/Kongtext Regular.ttf",
                                                    FONTSIZE_RESULTS);
    TTF_Font* fontPoints = sdlMngr.createFont("../src/client/fonts/Kongtext Regular.ttf",
                                              FONTSIZE_POINTS_FINAL);
    TextRendered result = sdlMngr.loadFromRenderedText("Final results",
                                                       playersColor[5],
                                                       windowRenderer,
                                                       fontResultsTitle);
    TextRendered nameDescriptor = sdlMngr.loadFromRenderedText("Name",
                                                               playersColor[5],
                                                               windowRenderer,
                                                               fontPoints);
    TextRendered lvl1Descriptor = sdlMngr.loadFromRenderedText("L1",
                                                               playersColor[5],
                                                               windowRenderer,
                                                               fontPoints);
    TextRendered lvl2Descriptor = sdlMngr.loadFromRenderedText("L2",
                                                               playersColor[5],
                                                               windowRenderer,
                                                               fontPoints);
    TextRendered finalDescriptor = sdlMngr.loadFromRenderedText("Total",
                                                                playersColor[5],
                                                                windowRenderer,
                                                                fontPoints);

    sdlMngr.clearRender(windowRenderer);
    sdlMngr.render((config.getResolutionWidth()/2)-result.width/2,
                   10,
                   result.width,
                   result.height,
                   result.texture,
                   windowRenderer);
    sdlMngr.render((config.getResolutionWidth()/2)-result.width/2,
                   result.height + 10,
                   result.width,
                   10,
                   divisorPoints,
                   windowRenderer);

    TextRendered player;
    TextRendered status;

    SDL_Texture* itemTable = sdlMngr.loadImageTexture("../src/client/img/table.png",windowRenderer);
    SDL_Texture* divisorTable = sdlMngr.loadImageTexture("../src/client/img/divisorTable.png",windowRenderer);
    int max = 0;
    for(int i = 1; i <= playerAmount; i++){
        if(points[i] > points[max]) max = i;
        std::ostringstream filledPointsLvl1;
        std::ostringstream filledPointsLvl2;
        std::ostringstream filledPointsFinal;

        filledPointsLvl1 << std::setw(4) << std::setfill('0') << pointsLvl1[i-1];
        std::string pointsLvl1Str = filledPointsLvl1.str();

        filledPointsLvl2 << std::setw(4) << std::setfill('0') << points[i-1]-pointsLvl1[i-1];
        std::string pointsLvl2Str = filledPointsLvl2.str();

        filledPointsFinal << std::setw(4) << std::setfill('0') << points[i-1];
        std::string pointsFinalStr = filledPointsFinal.str();

        std::string playerId = "Player " + std::to_string(i) + " " + pointsLvl1Str + " " +
                pointsLvl2Str + " " + pointsFinalStr;
        player = sdlMngr.loadFromRenderedText(playerId,
                                              playersColor[i],
                                              windowRenderer,
                                              fontPoints);
        int posX = (config.getResolutionWidth()/2)-(player.width/2);
        int posY = 150 + (i-1)*(player.height+16);

        sdlMngr.render(posX,posY,player.width,player.height,player.texture,windowRenderer);
        sdlMngr.render(posX-20,
                       posY-10,
                       player.width + 40,
                       player.height+20,
                       itemTable,
                       windowRenderer);
        sdlMngr.render(posX + (player.width/2) - player.width/7,
                       posY-5,
                       10,
                       player.height+10,
                       divisorTable,
                       windowRenderer);
        sdlMngr.render(posX + (player.width/2) + player.width/13,
                       posY-5,
                       10,
                       player.height+10,
                       divisorTable,
                       windowRenderer);
        sdlMngr.render(posX + (player.width/2) + player.width*10/34,
                       posY-5,
                       10,
                       player.height+10,
                       divisorTable,
                       windowRenderer);
    }
    sdlMngr.render((config.getResolutionWidth()/2)-(player.width*10/23),
                   150-nameDescriptor.height -20,
                   nameDescriptor.width,
                   nameDescriptor.height,
                   nameDescriptor.texture,
                   windowRenderer);
    sdlMngr.render((config.getResolutionWidth()/2)-(player.width/14),
                   150-lvl1Descriptor.height -20,
                   lvl1Descriptor.width,
                   lvl1Descriptor.height,
                   lvl1Descriptor.texture,
                   windowRenderer);
    sdlMngr.render((config.getResolutionWidth()/2)-(player.width/14) + (player.width*10/46),
                   150-lvl2Descriptor.height -20,
                   lvl2Descriptor.width,
                   lvl2Descriptor.height,
                   lvl2Descriptor.texture,
                   windowRenderer);
    sdlMngr.render((config.getResolutionWidth()/2)-(player.width/14) + (player.width*20/53),
                   150-finalDescriptor.height -20,
                   finalDescriptor.width,
                   finalDescriptor.height,
                   finalDescriptor.texture,
                   windowRenderer);

    if(endGame == 1){
        soundManager.playSoundFromState('X');
        status = sdlMngr.loadFromRenderedText("Game Over",
                                              playersColor[1],
                                              windowRenderer,
                                              fontResultsTitle);
        sdlMngr.render((config.getResolutionWidth()/2)-(status.width/2),
                       400,status.width,
                       status.height,
                       status.texture,
                       windowRenderer);
    }
    else if(endGame == 2){
        soundManager.playFinishMusic();
        status = sdlMngr.loadFromRenderedText("Congrats!",
                                              playersColor[5],
                                              windowRenderer,
                                              fontResultsTitle);
        TextRendered winMsg = sdlMngr.loadFromRenderedText("The winner is: ",
                                                           playersColor[5],
                                                           windowRenderer,
                                                           fontResultsTitle);
        TextRendered winner = sdlMngr.loadFromRenderedText("Player "+std::to_string(max+1),
                                                           playersColor[max+1],
                                                           windowRenderer,
                                                           fontResultsTitle);
        sdlMngr.render((config.getResolutionWidth()/2)-(status.width)/2,
                       400,
                       status.width,
                       status.height,
                       status.texture,
                       windowRenderer);
        sdlMngr.render((config.getResolutionWidth()/2)-(winMsg.width)/2,
                       400+status.height+10,
                       winMsg.width,
                       winMsg.height,
                       winMsg.texture,
                       windowRenderer);
        sdlMngr.render((config.getResolutionWidth()/2)-(winner.width)/2,
                       400+status.height+winMsg.height+20,
                       winner.width,
                       winner.height,
                       winner.texture,
                       windowRenderer);

    }
    sdlMngr.presentRender(windowRenderer);

}

int View::run() {
    sdlMngr.renderFilledQuad(windowRenderer, config.getResolutionWidth(), config.getResolutionHeight());
    int previousLevel = 1;
    std::vector<char> states;
    TextRendered waitMessage = sdlMngr.loadFromRenderedText("Waiting for the other players...",
                                                            playersColor[1],
                                                            windowRenderer,
                                                            font);
    sdlMngr.render((config.getResolutionWidth()-waitMessage.width)/2,
                   (config.getResolutionHeight()-waitMessage.height)/4,
                   waitMessage.width+20,
                   waitMessage.height+20,
                   waitMessage.texture,
                   windowRenderer);
    sdlMngr.presentRender(windowRenderer);
    soundManager.playMusic("level 1", -1);
    int pointsLvl1[4];
    while(keepRuning && serverActive) {
        if (monitor.getLevel() == 1) soundManager.runLevel1();
        else if (monitor.getLevel() == 2){
            soundManager.playMusic("level 2", -1);
            soundManager.runLevel2();
        }
        sdlMngr.clearRender(windowRenderer);
        std::vector<Entity> entityVector;
        monitor.getInfo(entityVector, points, lives);
        std::string len = std::to_string(entityVector.size());
        logger.debugMsg("Obtengo el vector de entities con longitud: " + len, __FILE__, __LINE__);
        if(endGame == 1 || endGame == 2){
            renderFinalResults(pointsLvl1);
            break;
        }

        int currLvl = monitor.getLevel();
        if(currLvl != previousLevel && currLvl != 0){
            renderPartialResults();
            for(int i=0; i < 4; i++) {
                pointsLvl1[i] = points[i];
            }
            changeLevel();
            logger.debugMsg("Se cambia de nivel desde la vista: ", __FILE__, __LINE__);
            previousLevel++;
            soundManager.playMusic("level 2", -1);
        }

        int pos = 0;
        int size = entityVector.size();
        int myCharacterPos = size - config.getPlayersAmount() + playerNumber -1;
        auto it = entityVector.begin();
        while (it != entityVector.end()) {
            if (pos != myCharacterPos){
                renderEntity(it, states);
            } else {
                playerID++;
            }
            renderLivesAndPoints();
            ++it;
            pos++;
        }
        playerID = playerNumber-1;
        renderEntity(entityVector.begin()+myCharacterPos, states);
        playerID = 0;
        logger.debugMsg("Fin de iteracion sobre vector de entidades", __FILE__, __LINE__);
        soundManager.iterateStates(states);
        sdlMngr.presentRender(windowRenderer);
        sdlMngr.clearRender(windowRenderer);
    }
    if (!serverActive){
        logger.debugMsg("Inactive server", __FILE__, __LINE__);
        sdlMngr.renderWarnings("Server crashed unexpectedly", windowRenderer, window);
    }
    return 0;
}

View::~View(){
    sdlMngr.destroyFont(font);
    sdlMngr.destroyRenderer(windowRenderer);
    sdlMngr.destroyWindow(window);
}