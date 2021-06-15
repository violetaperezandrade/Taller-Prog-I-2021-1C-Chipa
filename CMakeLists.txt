cmake_minimum_required(VERSION 3.19)
project(DonkeyKong)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

#add_executable(Client src/client/View.cpp Y LO DEMAS)
#target_link_libraries(Client jsoncpp SDL2 SDL2_image nlohmann_json::nlohmann_json)

add_executable(Server
        src/common/protocols/EntityProtocol.cpp
        src/common/protocols/InputProtocol.cpp
        src/common/Logger.cpp
        src/common/Message.cpp
        src/common/Socket.cpp
        src/common/Thread.cpp
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
        src/server/CollisionManager.cpp
        src/server/Config.cpp
        src/server/Entity.cpp
        src/server/Game.cpp
        src/server/LoginManager.cpp
        src/server/Peer.cpp
        src/server/Receiver.cpp
        src/server/Sender.cpp
        src/server/Server.cpp
        src/server/serverMain.cpp)
target_link_libraries(Server pthread jsoncpp nlohmann_json::nlohmann_json)