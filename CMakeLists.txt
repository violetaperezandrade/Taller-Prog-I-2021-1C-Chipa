cmake_minimum_required(VERSION 3.19)
project(DonkeyKong)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -pedantic-errors -pthread")

find_package(PkgConfig REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

add_executable(Client
        src/client/Client.cpp
        src/client/clientMain.cpp
        src/client/Input.cpp
        src/client/Login.cpp
        src/client/Monitor.cpp
        src/client/Processor.cpp
        src/client/View.cpp
        src/common/protocols/EntityInfo.cpp
        src/common/protocols/EntityProtocol.cpp
        src/common/protocols/InputProtocol.cpp
        src/common/Config.cpp
        src/common/Entity.cpp
        src/common/Logger.cpp
        src/common/Socket.cpp
        src/common/Thread.cpp
        src/client/SDLManager.cpp
        src/client/SoundManager.cpp)
target_link_libraries(Client jsoncpp SDL2 SDL2_image SDL2_ttf SDL2_mixer nlohmann_json::nlohmann_json)

add_executable(Server
        src/client/Monitor.cpp
        src/common/protocols/EntityInfo.cpp
        src/common/protocols/EntityProtocol.cpp
        src/common/protocols/InputProtocol.cpp
        src/common/Config.cpp
        src/server/entities/Hammer.cpp
        src/common/Entity.cpp
        src/common/Logger.cpp
        src/common/Socket.cpp
        src/common/Thread.cpp
        src/server/PeerManager.cpp
        src/server/Reconnector.cpp
        src/server/entities/Barrel.cpp
        src/server/entities/Character.cpp
        src/server/entities/Ember.cpp
        src/server/entities/Fire.cpp
        src/server/entities/Flame.cpp
        src/server/entities/Monkey.cpp
        src/server/entities/Movement.cpp
        src/server/entities/Platform.cpp
        src/server/entities/Princess.cpp
        src/server/entities/Stair.cpp
        src/server/entities/StateManager.cpp
        src/server/CollisionManager.cpp
        src/server/Game.cpp
        src/server/LoginManager.cpp
        src/server/Peer.cpp
        src/server/Receiver.cpp
        src/server/Sender.cpp
        src/server/Server.cpp
        src/server/serverMain.cpp)
target_link_libraries(Server jsoncpp nlohmann_json::nlohmann_json)